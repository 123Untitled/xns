#!/bin/zsh

# This script is used to compile the project.
# Makefile forever, but not really lol.


# -- C O L O R  S E T T I N G S -----------------------------------------------

# main color
color='\x1b[32m'
reset='\x1b[0m'
erase='\x1b[1F\x1b[0J'


# -- S C R I P T  S E T T I N G S ---------------------------------------------

# get make.sh absolute path
abspath=$(cd $(dirname $0); pwd -P) # maybe -P is not wanted !!!

# script name
this=$(basename $0)

# .env file
env=$abspath/'.env'


# -- B A N N E R --------------------------------------------------------------

echo $color;
echo		"   ▁▁▁▁▁▁▁▁  ▁▁▁▁▁▁▁▁  ▁▁▁▁ ▁▁▁  ▁▁▁▁▁▁▁▁ ";
echo		"  ╱        ╲╱        ╲╱    ╱   ╲╱        ╲";
echo		" ╱         ╱         ╱         ╱         ╱";
echo		"╱         ╱         ╱        ▁╱       ▁▁╱ ";
echo		"╲▁▁╱▁▁╱▁▁╱╲▁▁▁╱▁▁▁▁╱╲▁▁▁▁╱▁▁▁╱╲▁▁▁▁▁▁▁▁╱\n";
echo $color"$this"$reset 'launching\n';


#exit 0

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



# required programs
required_commands=(clang++ mkdir rm find basename jq sed)

# check if all required commands are installed
function check_command {
	if ! [ -x "$(command -v $1)" ]; then
		echo $color$1$reset "is not installed."
		exit 1;
	else
		echo $color$1$reset "is installed."
	fi
}





# check if all required commands are installed
#for cmd in $required_commands; do
#	check_command $cmd
#done

# check for .env file
if [ -f $end ]; then # !!!!!!!!!!!!1
	# load .env file
	source $env
else
	# create .env file
	echo 'Create a' $color'.env'$reset 'file'
	echo 'BUILD_MODE=' > .env
	source .env
fi

if [[ -z $BUILD_MODE ]]; then
	echo '\n🥕 Set a build mode in' $color'.env'$reset 'file [debug, development or release]';
	#vared -p '   change it now: ' -c build_mode;
	while (true); do
		vared -p '   change it now: ' -c build_mode;
		if [[ $build_mode == 'debug' || $build_mode == 'development' || $build_mode == 'release' ]]; then
			break;
		else
			echo 'invalid build mode'
		fi
	done
	sed -i '' 's/BUILD_MODE=.*/BUILD_MODE='$build_mode'/g' .env;
	echo "🍌 Build mode changed to '$build_mode'."
	exit 0
fi



# -- D I R E C T O R I E S ----------------------------------------------------

# source directory
srcdir=$abspath/'src'

# check if srcdir exists
[[ -d $srcdir ]] || echo No $color'src'$reset directory found. || exit 1

# include directory
incdir=$abspath/'inc'

# check if incdir exists
[[ -d $incdir ]] || echo No $color'inc'$reset directory found. || exit 1

# build directory
blddir=$abspath/'build'

# object directory
objdir=$abspath/$blddir/'_obj'

# dependency directory
depdir=$abspath/$blddir/'_dep'

# json directory
jsndir=$abspath/$blddir/'_jsn'

# cache directory
cachedir=$abspath/'.cache'




# -- S O U R C E  F I L E S ---------------------------------------------------


# get source files
src=($(find $srcdir -type f -name '*.cpp'))

# check for any source file ?
if [[ ${#src[@]} -eq 0 ]]; then
	echo 'No source files found in'\
		$color$(basename $srcdir)$reset 'directory.'
	exit 1
fi

# get all directories hierarchy in incdir
inc=($(find $incdir -type d))

# insert -I prefix to each directory
inc=("${inc[@]/#/-I}")



# arguments
args=$@

# target
target=$1

# object array
obj=()

# json array
jsn=()

yes=0
no=1


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



# -- C O M P I L E R  S E T T I N G S -----------------------------------------

# compiler
cxx='clang++'

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




# -- I M P L E M E N T A T I O N ----------------------------------------------


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
	rm -f $executable $dynamic $static $compdb '.env'
	# print full cleaned message
	echo $color'[x]'$reset "Full cleaned\n";
}

function make_executable {
	# link executable
	$linker $obj -o $executable $ldflags
	# check if linking succeeded
	file $executable | grep --color=always $executable
	echo;
}

function make_dynamic {
	# link dynamic library
	$linker $obj $dlib -o $dynamic $ldflags
	# check if linking succeeded
	file $dynamic | grep --color=always $dynamic
	echo;
}

function make_static {
	# link static library
	$archiver $arflags $static $obj
	# check if linking succeeded
	file $static | grep --color=always $static
	echo;
}

function make_compdb {
	# generate compilation database
	echo "[\n"$(cat $jsn | sed '$s/,\s*$//')"\n]" | jq > $compdb
	# check if compilation database succeeded
	file $compdb | grep --color=always $compdb
	echo;
}

function get_objects {
	# get all object files
	obj=($(find $objdir -type f -name '*.o'))
}

function get_jsons {
	# get all json files
	jsn=($(find $jsndir -type f -name '*.json'))
}


# -- U T I L I T I E S  F U N C T I O N S -------------------------------------

function is_missing {
	# get target file
	local file=$1
	# file exists ?
	[[ ! -e $file ]] && return yes || return no
}

function dir_exists {
	# get target directory
	local dir=$1
	# directory exists ?
	[[ -d $dir ]] && return yes || return no
}

function is_there_any_files {
	# get all arguments
	local files=($@)
	# is there any files ?
	[[ ${#files[@]} -gt 0 ]] && return yes || return no
}


function is_link_required {
	# get first argument
	local target=$1
	# get all other arguments
	local required=(${@:2})
	# loop over object files
	for file in $required; do
		# check if this script is modified
		[[ $file -nt $target ]] && return yes
	done
	return no

}




function check_dependency {
	# get arguments
	local obj=$1
	local dep=$2
	# check if object or dependency file is missing
	if is_missing $dep && return yes
	if is_missing $obj && return yes
	# get file content
	local content=$(<$dep)
	# split content into array
	local array=( ${=content} )
	# loop over array
	for x in "${array[@]}"; do
		# ignore '\' and file name ending with ':'
		if ! [[ $x == "\\" ]] && ! [[ $x == *":" ]]; then
			# check if dependency is modified
			[[ $x -nt $obj ]] && return yes
		fi
	done
	return no
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
		local base=${$(basename $file)%.*}
		# add object file extension
		local obj=$objdir/$base'.o'
		# add dependency file extension
		local dep=$depdir/$base'.d'
		# add json file extension
		local jsn=$jsndir/$base'.json'
		# check if source file is modified
		if check_dependency $obj $dep || [[ $this -nt $obj ]]; then
			# erase line except first iteration
			[[ $compiled -gt 0 ]] && echo $erase
			# print message
			echo -n $file $color'compiling...'$reset
			# compile source file
			clang++ $std $cxxflags $defines -MJ $jsn -MT $obj -MMD -MF $dep $inc -c $file -o $obj &
			# increment compiled files counter
			((++compiled))
			# add pid to array
			pids+=($!)

		fi
	done

	# wait for all compilation to finish
	for pid in "${pids[@]}"; do
		wait $pid
		# Vérifier le code de retour du processus
		if [[ $? -ne 0 ]]; then
			wait
			echo "$color$this$reset: error, compilation failed."
			exit 1
		fi
	done

	echo "\x1b[1F\x1b[0J"
	echo 🫠 $compiled "files compiled.\n"
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

	get_objects

	is_there_any_files $obj || return 1

	# handle executable target
	if [[ $target == 'exec' ]] || [[ -z $target ]] || [[ $target == 're' ]]; then
		# is there an executable ?
		if is_missing $executable || is_link_required $executable $obj; then
			make_executable
		fi

	# handle dynamic library target
	elif [[ $target == 'dynamic' ]]; then
		# is there a dynamic library ?
		if is_missing $dynamic || is_link_required $dynamic $obj; then
			make_dynamic
		fi

	# handle static library target
	elif [[ $target == 'static' ]]; then
		# is there a static library ?
		if is_missing $static || is_link_required $static $obj; then
			make_static
		fi
	fi

	#echo "$(EMOJI) [$(BUILD_MODE)] All targets are up to date !";
	echo "All targets are up to date !";

}


function main {



	if [[ $target == 'clean' ]]; then
		make_clean

	elif [[ $target == 'fclean' ]]; then
		make_fclean

	elif [[ $target == 're' ]]; then
		make_clean
		compile
		database
		linkage

	elif [[ $target == 'exec' ]] || [[ -z $target ]]; then
		compile
		database
		linkage

	elif [[ $target == 'dynamic' ]]; then
		compile
		database
		linkage

	elif [[ $target == 'static' ]]; then
		compile
		database
		linkage

	else
		echo 'Unknown target:' $color$target$reset
		exit 1
	fi

}


main





exit 0

