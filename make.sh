#!/bin/zsh

# This script is used to compile the project.
# Makefile forever, but $not really lol.



# -- C O L O R  S E T T I N G S -----------------------------------------------

# escape
esc='\x1b'

# main color
color=$esc'[32m'
C1=$esc'[32m'
color2=$esc'[33m'
error=$esc'[31m'
reset=$esc'[0m'
R=$esc'[0m'
erase=$esc'[1F'$esc'[0J'


yes=0
no=1


# -- S C R I P T  P A T H  S E T T I N G S ------------------------------------

# get absolute directory of script
abspath=$(cd ${0%/*}; pwd)

# get dirname of script
rootname=${abspath##*/}

# get absolute path of script
script=$abspath/${0##*/}

# basename of the script without using basename command
scriptname=${0##*/}







# -- O P E R A T I N G  S Y S T E M -------------------------------------------

# check if operating system is supported
function check_os {

	# check for macosx
	if   [[ $OSTYPE == 'darwin'* ]]; then
		dlib='-dynamiclib'
		dext='dylib'

	# check for linux
	elif [[ $OSTYPE == 'linux-gnu'* ]]; then
		dlib='-shared'
		dext='so'

	# check for other
	else
		echo 'Unsupported OS:' $color$OSTYPE$reset
		exit 1
	fi
}

check_os

function goodby {
	echo $error'Aborded.'$reset
	exit 1
}


# check if all required commands are installed
function cmd_exists {
	[[ -n $(command -v $1) ]] && return $yes || return $no
}


function required {
	# required programs
	local commands=('clang++'
					'ar'
					'mkdir'
					'rm'
					'cd'
					'pwd'
					'sed'
					'cat'
					'bat'
					'vared')
	# loop through all required commands
	for cmd in $commands; do
		if ! cmd_exists $cmd; then
			echo $error'Error:'$reset 'required program' \
					$color$cmd$reset 'is not installed.'
			exit 1
		fi
	done
	return $yes
}






# check if all required commands are installed
#for cmd in $required_commands; do
#	check_command $cmd
#done

# .env file
env=$abspath/'.env'

# check for .env file
if [[ ! -f $env ]]; then
	# create .env file
	echo 'Create a' $color'.env'$reset 'file'
	echo 'BUILD_MODE=' > $env
fi

# load .env file
source $env

if [[ -z $BUILD_MODE ]]; then
	echo '\n🥕 Set a build mode in' $color'.env'$reset 'file [active, debug, release]'

	while (true); do
		vared -c  -p '   change it now: ' -c build_mode;
		if [[ $build_mode == 'active' || $build_mode == 'debug' || $build_mode == 'release' ]]; then
			break;
		else
			echo 'invalid build mode'
		fi
	done

	sed -i '' 's/BUILD_MODE=.*/BUILD_MODE='$build_mode'/g' $env
	echo "🍌 Build mode changed to '$build_mode'."
	exit 0
fi



# -- D I R E C T O R I E S ----------------------------------------------------

# source directory
srcdir=$abspath/'src'

# include directory
incdir=$abspath/'inc'

# build directory
blddir=$abspath/'_bld'

# object directory
objdir=$blddir/'_obj'

# dependency directory
depdir=$blddir/'_dep'

# json directory
jsndir=$blddir/'_jsn'

# cache directory
cachedir=$abspath/'.cache'


# check if srcdir exists
if [[ ! -d $srcdir ]]; then
	echo 'No' $C1$rootname'/'${srcdir##*/}$R 'directory found.';
	exit 1
fi

# check if incdir exists
if [[ ! -d $incdir ]]; then
	echo 'No' $C1$rootname'/'${incdir##*/}$R 'directory found.';
	exit 1
fi



# -- S O U R C E  F I L E S ---------------------------------------------------


# get source files
src=($srcdir/**/*.'cpp'(.N))

# check for any source file ?
if [[ ${#src[@]} -eq 0 ]]; then
	# get base name of srcdir + parent directory
	local folder=$rootname/${srcdir##*/}
	echo 'No source files found in' $color$folder$reset 'directory.'
	exit 1
fi


# get all directories hierarchy in incdir
inc=($incdir/**/*(/N) $incdir)

# insert -I prefix to each directory
inc=("${inc[@]/#/-I}")



# get arguments from command line
args=(${@:2})

# target
target=$1

# object array
obj=()

# json array
jsn=()


# -- T A R G E T S ------------------------------------------------------------

# project name
project='xns'

# target executable
executable=$abspath/$project'exec'

# target dynamic library
dynamic=$abspath/'lib'$project.$dext

# target static library
static=$abspath/'lib'$project.'a'

# compilation database
compdb=$abspath/'compile_commands.json'

# log file
logfile=$abspath/'compile.log'


# -- C O M P I L E R  S E T T I N G S -----------------------------------------

# compiler
#cxx='clang++'
cxx='/opt/homebrew/Cellar/llvm/16.0.4/bin/clang++'

# archiver
archiver='ar'

# archiver flags
arflags='-rcs'

# linker
linker=$cxx

# standard
std='-std=gnu++2b'

# optimization
opt='-O0'

# debug
debug='-g3'

# cxx flags
cxxflags=('-Wall' '-Wextra' '-Werror' '-Wpedantic'\
		'-Wno-unused' '-Wno-unused-variable' '-Wno-unused-parameter'\
		'-Winline' '-fno-exceptions' '-Weffc++'\
		'-Wno-gnu-string-literal-operator-template')

# defines
defines=()


[[ $BUILD_MODE == "debug" ]] && defines+=('-DXNS_UT' '-DMETA_UT')
[[ $BUILD_MODE == 'development' ]] && defines+=('-DDEVELOPMENT')
[[ $BUILD_MODE == 'release' ]] && defines+=('-DRELEASE')


# linker flags
ldflags=''


# memory checker
memcheck='valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes'

# memory checker flags
memflags=''




# -- I M P L E M E N T A T I O N ----------------------------------------------

function descript {
	local cible=$1
	local resume=$(file $cible)

	local regex='.*: (.*)'
	[[ $resume =~ $regex ]] && echo $color'[+]'$reset ${cible##*/} '|' ${match[1]}
}


function make_clean {
	# remove build directory
	rm -rf $blddir
	# print cleaned message
	echo $color'[x]'$reset "Cleaned\n";
}

function make_fclean {
	# remove build and cache directory
	rm -rf $blddir $cachedir
	# remove all targets
	rm -f $executable $dynamic $static $compdb $env $logfile
	# print full cleaned message
	echo $color'[x]'$reset "Full cleaned\n";
}

function make_executable {
	# link executable
	$linker $obj -o $executable $ldflags || exit 1
	# check if linking succeeded
	descript $executable
	echo;
}

function make_dynamic {
	# link dynamic library
	$linker $obj $dlib -o $dynamic $ldflags || exit 1
	# check if linking succeeded
	descript $dynamic
	echo;
}

function make_static {
	# link static library
	$archiver $arflags $static $obj || exit 1
	# check if linking succeeded
	descript $static
	echo;
}

function make_compdb {
	# generate compilation database
	echo "[\n"$(cat $jsn | sed '$s/,\s*$//')"\n]" | jq > $compdb
	# check if compilation database succeeded
	descript $compdb
	echo;
}

function get_objects {
	# get all object files
	obj=($objdir/**/*.'o'(.N))
}

function get_jsons {
	# get all json files
	jsn=($jsndir/**/*.'json'(.N))
}


# -- U T I L I T I E S  F U N C T I O N S -------------------------------------

function is_missing {
	# get target file
	local file=$1
	# file exists ?
	[[ ! -e $file ]] && return $yes || return $no
}

function dir_exists {
	# get target directory
	local dir=$1
	# directory exists ?
	[[ -d $dir ]] && return $yes || return $no
}

function is_there_any_files {
	# get all arguments
	local files=($@)
	# is there any files ?
	[[ ${#files[@]} -gt 0 ]] && return $yes || return $no
}


function is_link_required {
	# get first argument
	local target=$1
	# get all other arguments
	local required=(${@:2})
	# loop over object files
	for file in $required; do
		# check if this script is modified
		[[ $file -nt $target ]] && return $yes
	done
	return $no

}




function check_dependency {
	# get arguments
	local obj=$1
	local dep=$2
	# check if object or dependency file is missing
	if is_missing $dep && return $yes
	if is_missing $obj && return $yes
	# get file content
	local content=$(<$dep)
	# split content into array
	local array=( ${=content} )
	# loop over array
	for x in "${array[@]}"; do
		# ignore '\' and file name ending with ':'
		if ! [[ $x == "\\" ]] && ! [[ $x == *":" ]]; then
			# check if dependency is modified
			[[ $x -nt $obj ]] && return $yes
		fi
	done
	return $no
}


function make_compile {

	local file=$1
	local  obj=$2
	local  dep=$3
	local  jsn=$4

	local smpl=${file##*/}

	# big compilation line !!!
	$cxx $std $opt $debug $cxxflags $defines -MJ $jsn -MT $obj -MMD -MF $dep $inc -c $file -o $obj 2>> $logfile

	# check if compilation failed
	if [[ $? -ne 0 ]]; then
		# print error message
		#echo $error'[x]'$reset "Compilation failed for $smpl"
		echo -n $error'[x]'$reset
		exit 1
	fi
	# print success message and remove file extension
	#echo $color'[✓]'$reset "Compiled" $smpl
	echo -n $color'[✓]'$reset


	exit 0


}
# generate separator
separator='\x1b[90m'


# loop over columns
for x in $(seq $COLUMNS); do
	# add separator
	separator+='─'
done

separator+=$reset


function error_colorizer {

	# check log file
	if [[ ! -e $logfile ]]; then
		# print error message
		echo $error':('$reset 'log file is gone somewhere...'
		exit 1
	fi

	# fill an array of lines
	local lines=(${(f)"$(<$logfile)"})

	#for l in $lines; do
	#	echo 'line:' $l'\n'
	#done
	#exit 1


	# loop over lines
	for line in $lines; do


		# regex pattern to match: "In file included from ..."
		if [[ $line =~ "^In file included from" ]]; then
			continue
		fi

		# regex pattern to match: "x errors generated."
		if [[ $line =~ "^[0-9]+ errors? generated.$" ]]; then
			continue
		fi

		# match symbol '^~~~~~'
		if [[ $line =~ "^ *~*\^~* *$" ]]; then
			continue
		fi




		# white space split
		local words=(${=line})

		# loop over words
		for word in "${words[@]}"; do

			# regex pattern
			local location="^(.*):([0-9]+):([0-9]+):"

			# check if word match pattern
			if [[ $word =~ $location ]]; then

				echo $separator
				# get file name
				local file=${match[1]##*/}
				# get line number
				local y=${match[2]}
				# get column number
				local x=${match[3]}

				# print file name
				echo -n '['$color$file$reset']' '['$color$y$reset'] ['$color$x$reset'] '


			# match for "note:" or "warning:" or "error:"
			local hint="^(note:|warning:|error:)$"
			#elif [[ $word =~ $pattern ]]; then
			elif [[ $word =~ $hint ]]; then
				# print error
				echo -n $error$word$reset' '


			else
				# print word
				echo -n $word' '
			fi


		done
		echo '\n'

	done

	# patter to match:
	# /Users/untitled/Desktop/code/main_projects/SEQterm/lib/xns/src/main.cpp:43:1:


}


function memory {




}



function compile {
	# create build directories
	mkdir -p $blddir $objdir $depdir $jsndir
	# declare compiled files counter
	local -i compiled=0
	# array of pids
	pids=()
	# loop over source files
	for file in $src; do
		# get file name without path and extension
		local base=${${file##*/}%.*}
		# add object file extension
		local obj=$objdir/$base'.o'
		# add dependency file extension
		local dep=$depdir/$base'.d'
		# add json file extension
		local jsn=$jsndir/$base'.json'
		# check if source file is modified
		if check_dependency $obj $dep || [[ $script -nt $obj ]]; then

			# check for first iteration
			if [[ $compiled -eq 0 ]]; then
				# print version
				$cxx --version; echo;
				# print separator
				echo $separator
			fi
			# compile source file
			(make_compile $file $obj $dep $jsn $compiled) &
			# add pid to array
			pids+=($!)
			# increment compiled files counter
			((++compiled))

		fi
	done
	#wait

	# wait for all compilation to finish
	for pid in "${pids[@]}"; do
		wait $pid
		# Vérifier le code de retour du processus
		if [[ $? -ne 0 ]]; then
			# wait for all compilation to finish
			wait
			echo "\n\n$color$scriptname$reset: error, compilation failed.\n"
			error_colorizer
			exit 1
		fi
	done


	#echo "\x1b[1F\x1b[0J"
	echo '\n\n'🫠 $compiled "files compiled."

				# print separator
				echo $separator

}








function database {

	get_jsons

	is_there_any_files $jsn || return 1

	# handle compilation database
	if is_missing $compdb || is_link_required $compdb $jsn; then
		make_compdb
	fi

}


function linkage {

	local final=$1
	local magic=$2

	get_objects

	is_there_any_files $obj || return 1

	# handle target
	if is_missing $final || is_link_required $final $obj; then
		$magic # !!!
	fi

}



function main {

	# -- B A N N E R --------------------------------------------------------------

	echo $color;
	echo		"   ▁▁▁▁▁▁▁▁  ▁▁▁▁▁▁▁▁  ▁▁▁▁ ▁▁▁  ▁▁▁▁▁▁▁▁ ";
	echo		"  ╱        ╲╱        ╲╱    ╱   ╲╱        ╲";
	echo		" ╱         ╱         ╱         ╱         ╱";
	echo		"╱         ╱         ╱        ▁╱       ▁▁╱ ";
	echo		"╲▁▁╱▁▁╱▁▁╱╲▁▁▁╱▁▁▁▁╱╲▁▁▁▁╱▁▁▁╱╲▁▁▁▁▁▁▁▁╱\n";
	echo $color"$scriptname"$reset 'launching' '['$color$project$reset']' 'build\n'


	check_os
	required
	#init variable
	#required

	if [[ $target == 'run' ]]; then
		compile
		database
		linkage $executable make_executable
		$executable
		exit 0

	elif [[ $target == 'clean' ]]; then
		make_clean

	elif [[ $target == 'fclean' ]]; then
		make_fclean

	elif [[ $target == 're' ]]; then
		make_clean
		compile
		database
		linkage $executable make_executable

	elif [[ $target == 'exec' ]] || [[ -z $target ]]; then
		compile
		database
		linkage $executable make_executable

	elif [[ $target == 'dynamic' ]]; then
		compile
		database
		linkage $dynamic make_dynamic

	elif [[ $target == 'static' ]]; then
		compile
		database
		linkage $static make_static

	else
		echo 'Unknown target:' $color$target$reset
		exit 1
	fi



	echo "💫 [$BUILD_MODE] All targets are up to date !";

}


main






exit 0

