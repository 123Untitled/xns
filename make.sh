#!/usr/bin/env -S zsh --no-rcs --no-globalrcs

ARRRAY=(1 2 3 4 5 6 7 8 9 10)

#
echo $ARRRAY
#
REMOVE=3
ARRRAY=("${ARRRAY[@]/$REMOVE}")
#
#ARRRAY=(${ARRRAY:|REMOVE})
#
echo $ARRRAY
#
#exit


# This script is used to compile the project.
# Makefile forever, but not really lol.

OPS=$(uname -s)

BANNER2=\
'   ▁▁▁▁▁▁▁▁  ▁▁▁▁▁▁▁▁  ▁▁▁▁ ▁▁▁  ▁▁▁▁▁▁▁▁ \n'\
'  ╱        ╲╱        ╲╱    ╱   ╲╱        ╲\n'\
' ╱         ╱         ╱         ╱         ╱\n'\
'╱         ╱         ╱        ▁╱       ▁▁╱ \n'\
'╲▁▁╱▁▁╱▁▁╱╲▁▁▁╱▁▁▁▁╱╲▁▁▁▁╱▁▁▁╱╲▁▁▁▁▁▁▁▁╱  \n'

BANNER1=\
'\n'\
':::    ::: ::::    :::  ::::::::  \n'\
':+:    :+: :+:+:   :+: :+:    :+: \n'\
' +:+  +:+  :+:+:+  +:+ +:+        \n'\
'  +#++:+   +#+ +:+ +#+ +#++:++#++ \n'\
' +#+  +#+  +#+  +#+#+#        +#+ \n'\
'#+#    #+# #+#   #+#+# #+#    #+# \n'\
'###    ### ###    ####  ########  \n'

BANNER=\
'\n'\
'      :::    ::: ::::    :::  ::::::::\n'\
'     :+:    :+: :+:+:   :+: :+:    :+:\n'\
'     +:+  +:+  :+:+:+  +:+ +:+        \n'\
'     +#++:+   +#+ +:+ +#+ +#++:++#++  \n'\
'   +#+  +#+  +#+  +#+#+#        +#+   \n'\
' #+#    #+# #+#   #+#+# #+#    #+#    \n'\
'###    ### ###    ####  ########      \n'





# -- S C R I P T  P A T H  S E T T I N G S ------------------------------------

# get absolute directory of script
ABSDIR=$(cd ${0%/*}; pwd)

# get dirname of script
rootname=${ABSDIR##*/}

# get absolute path of script
MAKE=$ABSDIR/${0##*/}

# basename of the script without using basename command
scriptname=${0##*/}



# -- D I R E C T O R I E S ----------------------------------------------------

# sources directory
SRCDIR=$ABSDIR'/sources/core'

# includes directory
INCDIR=$ABSDIR'/includes'

# tests directory
TSTDIR=$ABSDIR'/sources/tests'

# tests includes directory
TSTINC=$TSTDIR'/inc'

# tests sources directory
TSTSRC=$TSTDIR'/src'

# build directory
BLDDIR=$ABSDIR'/build'

# object directory
OBJDIR=$BLDDIR'/object'

# dependency directory
DEPDIR=$BLDDIR'/dependency'

# json directory
JSNDIR=$BLDDIR'/json'

# compile log directory
LOGDIR=$BLDDIR'/log'

# cache directory
CACHEDIR=$ABSDIR'/.cache'

# install directory
INSTALLDIR=''


# -- T A R G E T S ------------------------------------------------------------

# project name
PROJECT='xns'

# target executable
EXECUTABLE=$ABSDIR'/exec_'$PROJECT

# target static library
STATIC=$ABSDIR'/lib'$PROJECT'.a'

# compilation database
DATABASE=$ABSDIR'/compile_commands.json'

# .setup file
SETUP=$ABSDIR'/.setup'

# command line arguments
ARGUMENTS=($@)

# number of arguments
ARG_COUNT=$#

# source files
SRCS=()

# include files
INCLUDES=()

# object array
OBJS=()

# json array
JSNS=()

# test name
TEST=''

# number of compiled files
COMPILED=$BLDDIR'/.compiled'

# lock file (mutex)
LOCK=$BLDDIR'/.lock'


# -- C O M P I L E R  S E T T I N G S -----------------------------------------

# compiler
#CXX='/opt/homebrew/Cellar/llvm/17.0.6_1/bin/clang++'
CXX='clang++'

# archiver
ARCHIVER='ar'

# archiver flags
ARFLAGS='-rcs'

# linker
LINKER=$CXX

# standard
STD='-std=c++2a'

# debug
DEBUG='-g3'

# optimization
OPT=''

# release level
FAST='-O3'

# debug level
SLOW='-O0'

# compiler flags
CXXFLAGS=()

# warning scope
CXXFLAGS+=('-Wall' '-Wextra')

# warning impact
CXXFLAGS+=('-Werror')

# standard respect
CXXFLAGS+=('-Wpedantic' '-Weffc++')

# unused suppression
CXXFLAGS+=('-Wno-unused' '-Wno-unused-variable' '-Wno-unused-parameter')

# optimization
CXXFLAGS+=('-Winline')

# type conversion
CXXFLAGS+=('-Wconversion' '-Wsign-conversion' '-Wfloat-conversion' '-Wnarrowing')

# shadowing
CXXFLAGS+=('-Wshadow')

# defines
DEFINES=()

# linker flags
LDFLAGS=()


if [[ $OPS =~ 'Darwin' ]]; then
	LDFLAGS+=('-framework' 'CoreMIDI' '-framework' 'CoreAudio' '-framework' 'CoreFoundation')
fi

# memory checker
LEAKER='valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes'


FZF_OPTS=('--algo=v2' '--height=50%' '--no-multi' '--layout=reverse' '--border=rounded' '--scroll-off=50'  '--bind' 'tab:down' \
		  '--color=border:8,fg:7,bg:0,hl:2,fg+:3,bg+:8,hl+:4,info:5,prompt:6,pointer:6,marker:3,spinner:5,header:1')


MAX_JOBS=''
if [[ $OPS =~ 'Darwin' ]]; then
	MAX_JOBS=$(sysctl -n hw.ncpu)
else
	MAX_JOBS=$(nproc)
fi


# -- C O L O R  S E T T I N G S -----------------------------------------------

# main color
	COLOR='\x1b[32m'
  SUCCESS='\x1b[33m'
	ERROR='\x1b[31m'
	RESET='\x1b[0m'
	ERASE='\x1b[1F\x1b[0J'
SEPARATOR=''


function initialize_separator {
	# generate separator
	SEPARATOR='\x1b[90m'
	# loop over columns
	for _ in $(seq $COLUMNS); do
		# add separator
		SEPARATOR+='─'
	done # reset color
	SEPARATOR+=$RESET
}


# -- B A N N E R --------------------------------------------------------------

function banner() {
	echo $COLOR$BANNER$RESET
}

function target_info() {
	echo $COLOR$scriptname$RESET \
		'launching' '['$COLOR${1##*/}$RESET']' 'build'
}



# -- O P E R A T I N G  S Y S T E M -------------------------------------------

# check if operating system is supported
function check_os {

	if [[ -z $OSTYPE ]]; then
		OSTYPE=$(uname -s)
	fi

	# check for macosx
	if   [[ $OSTYPE =~ 'darwin' ]]; then
		#echo 'detected OS:' $color'macosx'$reset
	# check for linux
	elif [[ $OSTYPE =~ 'linux' ]]; then
		#echo 'detected OS:' $color'linux'$reset
	# check for other
	else
		echo 'unsupported OS:' $COLOR$OSTYPE$RESET
		exit 1
	fi
}



# -- R E Q U I R E D  P R O G R A M S -----------------------------------------

function required {
	# default required programs
	local COMMANDS=(
		'mkdir'
		'wait'
		'pwd'
		'rm'
		'cd'
		'wc'
		'git'
		'cat'
		'sed'
		'file'
		'uname'
		'vared'
		'openssl'
		'fzf'
		'fzy'
		'jq'
	)
	# append arguments
	COMMANDS+=($@)
	# loop through all required commands
	for CMD in $COMMANDS; do
		# check if command is installed
		if ! command -v $CMD &> /dev/null; then
			# print error message
			echo '\nerror:' $ERROR$CMD$RESET 'is not installed.'
			exit 1
		fi
	done
}



# -- R E P O S I T O R Y  C H E C K -------------------------------------------

function repository {

	local SSH_REPO='git@github.com:123Untitled/xns.git'
	local PUB_REPO='https://github.com/123Untitled/xns.git'

	# check if the script is run in a git repository
	if [ ! -d .git ]; then
		echo 'please run this script in the' $CO$PROJECT$NC 'repository.\n'
		exit 1
	fi

	# get the git repository name
	GIT_REPO=$(git config --get remote.origin.url)

	# check if the script is run in the right repository
	if [[ $GIT_REPO != $SSH_REPO && $GIT_REPO != $PUB_REPO ]]; then
		echo 'please run this script in the' $COLOR$PROJECT$RESET 'repository.\n'
		exit 1
	fi

}



# -- I M P L E M E N T A T I O N ----------------------------------------------

function description {
	# regex to match description keep all before first comma
	if [[ $(file $1) =~ '.*: ([^,]+).*' ]]; then
		# print separator
		echo $SEPARATOR$SUCCESS'[+]'$RESET ${1##*/} '|' ${match[1]}
	fi
}

function make_clean {
	# remove all targets
	DELETED=$(rm -rfv $EXECUTABLE $STATIC $BLDDIR $CACHEDIR $DATABASE $SETUP | wc -l)
	# print full cleaned message
	echo $SEPARATOR$COLOR'[x]'$RESET 'full cleaned ('${DELETED##* } 'files)\n';
}

function make_silent_clean {
	# remove all targets
	rm -rf $EXECUTABLE $STATIC $BLDDIR $CACHEDIR $DATABASE $SETUP
}

function make_executable {
	# link executable
	$LINKER $OBJS -o $EXECUTABLE $LDFLAGS || exit 1
	# check if linking succeeded
	description $EXECUTABLE
}

function make_static {
	# link static library
	$ARCHIVER $ARFLAGS $STATIC $OBJS || exit 1
	# check if linking succeeded
	description $STATIC
}




# -- C O M P I L A T I O N  F U N C T I O N S ---------------------------------

function check_dependency {
	# check if object or dependency file is missing
	if [[ ! -f $1 ]] || [[ ! -f $2 ]] || [[ $MAKE -nt $1 ]]; then
		return 0
	fi
	# loop over words in dependency file
	for WORD in ${=$(<$2)}; do
	#for WORD in $WORDS; do
		# check if word is not target or escape
		if [[ $WORD != '\' ]] && [[ $WORD != *':' ]]; then
			# check if dependency is missing
			[[ $WORD -nt $1 ]] && return 0
		fi
	done
	return 1
}

function handle_compilation {
	# openssl hash
	local HASH=$(openssl md5 <<< $FILE)
	# add object file extension
	local OBJ=$OBJDIR'/'$HASH'.o'
	# add dependency file extension
	local DEP=$DEPDIR'/'$HASH'.d'
	# add json file extension
	local JSN=$JSNDIR'/'$HASH'.json'
	# add compiler log file extension
	local LOG=$LOGDIR'/'$HASH'.log'


	# check if source file is modified
	if check_dependency $OBJ $DEP; then

		echo >> $COMPILED

		# compile source file
		$CXX $STD $OPT $DEBUG $CXXFLAGS $DEFINES $INCLUDES \
			-MJ $JSN -MT $OBJ -MMD -MF $DEP -c $FILE -o $OBJ 2> $LOG

		# check if compilation failed
		if [[ $? -ne 0 ]]; then
			echo -n   $ERROR'[x]'$RESET
			exit 1
		else
			echo -n $SUCCESS'[✓]'$RESET
			exit 0
		fi

	fi

	exit 0
}


function compile_release {
	$CXX $STD $FAST $CXXFLAGS $DEFINES $INCLUDES $FILE -o $OBJ
}

function handle_errors {
	# get all log files
	local LOGS=($LOGDIR'/'*'.log'(.N))
	# declare associative array
	declare -A ERRORS
	# regex to match error
	local REGEX='^.*/([^/]+):([0-9]+):([0-9]+): *(.+)$'

	for LOG in $LOGS; do
		# split log file into lines
		local LOGLINES=(${(f)"$(<$LOG)"})

		for LOGLINE in $LOGLINES; do
			# ignore pattern 'In file included from'
			if [[ $LOGLINE =~ 'In file included from' ]]; then
				continue
			# ignore pattern '[0-9]+ warnings and [0-9]+ errors generated.'
			elif [[ $LOGLINE =~ '[0-9]+ errors? generated.' ]]; then
				continue
			fi
			#echo $LOGLINE
			#continue


			if [[ $LOGLINE =~ $REGEX ]]; then
				#BASE=${match[1]}
				#NUMBER=$(printf "%10d" ${match[2]})
				#MSG=$(printf "%10s" ${match[4]})
				#echo $NUMBER $COLOR'|'$RESET $BASE
				#echo $MSG
				echo $COLOR${match[1]} ${match[2]}$RESET ${match[4]}

			elif [[ $LOGLINE =~ '^ *~* *\^ *~* *$' ]]; then
				echo $LOGLINE'\n'
			else
				echo $LOGLINE
			fi


		done

	done
}



function compile {


	echo $SEPARATOR

	rm -rf $LOGDIR
	# create build directories
	mkdir -p $OBJDIR $DEPDIR $JSNDIR $LOGDIR

	echo -n > $COMPILED

	# array of pids
	PIDS=()

	# loop over source files
	for FILE in $SRCS; do
		handle_compilation $FILE &
		PIDS+=($!)

		# check equal or more than max jobs
		if [[ ${#PIDS[@]} -eq $MAX_JOBS ]]; then

			for PID in $PIDS; do
				# wait for pid
				wait $PID
				# check if compilation failed
				if [[ $? -ne 0 ]]; then
					# wait all pids
					wait
					echo '\n'$SEPARATOR
					#cat $LOGDIR/*.log
					handle_errors
					exit 1
				fi
			done

			PIDS=()
		fi
	done

	# loop over pids
	for PID in $PIDS; do
		# wait for pid
		wait $PID
		# check if compilation failed
		if [[ $? -ne 0 ]]; then
			wait
			echo '\n'$SEPARATOR
			#cat $LOGDIR/*.log
			handle_errors
			exit 1
		fi
	done

	# get number of compiled files
	local COUNT=$(cat $COMPILED | wc -l)
	# strip leading spaces
	COUNT=${COUNT##* }
	#
	if [[ $COUNT -eq 0 ]]; then
		echo $COLOR'[✓]'$RESET 'nothing to compile.'
	else
		echo '\n\n' 🫠 $COUNT 'files compiled.'
	fi

}


# -- L I N K  F U N C T I O N S -----------------------------------------------

function is_link_required {
	# get first argument
	local TARGET=$1
	shift
	# loop over object files
	for DEPENDENCY in $@; do
		# check if this script is modified
		if [[ $DEPENDENCY -nt $TARGET ]]; then
			return 0
		fi
	done
	return 1
}

function linkage {

	local TARGET=$1
	local FUNCTOR=$2
	# get all object files
	OBJS=($OBJDIR'/'*'.o'(.N))
	# handle target
	if [[ ! -e $TARGET ]] || is_link_required $TARGET $OBJS; then
		$FUNCTOR
	fi
}

function database {
	# get all json files
	JSNS=($JSNDIR'/'*'.json'(.N))
	# check if need to (re)generate database
	if [[ ! -e $DATABASE ]] || is_link_required $DATABASE $JSNS; then
		# start json string
		local CONTENT='['
		# get all json files content
		for JSN in $JSNS; do
			CONTENT+=$(<$JSN)
		done
		# erase last comma with bracket
		CONTENT[-1]=']'
		# format json content with jq
		jq <<< $CONTENT > $DATABASE
		# check if compilation database succeeded
		description $DATABASE
	fi
}



# -- B U I L D  M O D E -------------------------------------------------------

function require_build_mode {

	IFS=$'\n'
	local MODES=('release' 'install' 'test' 'debug' 'config' 'help' 'rm' )
	MODE=$(fzy <<< ${MODES[@]})
	IFS=$' \t\n'

	#MODE=$(echo -e 'release\ntest\ninstall' | fzf $FZF_OPTS)

	if [[ -z $MODE ]]; then
		exit 1
	fi

	echo 'MODE='$MODE > $SETUP
}


function require_test_file {

	# get all tests files
	local FILES=($TSTSRC'/'**'/_'*'.cpp'(.N))

	# loop over test files
	for I in {1..${#FILES[@]}}; do

		if [[ $FILES[$I] =~ '^.*/_(.*)\.cpp$' ]]; then
			FILES[$I]=${match[1]}
		fi

	done

	IFS=$'\n'
	TEST=$(fzy <<< ${FILES[@]})
	IFS=$' \t\n'

	# check if test is selected
	if [[ -z $TEST ]]; then
		exit 1
	fi
	echo 'TEST='$TEST >> $SETUP
}





function setup_release {
	# check arguments
	case $ARG_COUNT; in

		0)
			INSTALLDIR=$ABSDIR
			;;
		1)
			INSTALLDIR=$ABSDIR
			;;
		2)
			INSTALLDIR=$ARGUMENTS[2]
			;;
		*)
			echo 'usage:' $COLOR$scriptname$RESET 'release [directory]\n'
			exit 1
			;;
	esac

	[[ ! -d $INSTALLDIR ]] && \
		(echo 'install directory' $COLOR$INSTALLDIR$RESET 'does not exist.\n'; exit 1)

	INSTALLDIR+='/'$PROJECT
}





# -- S O U R C E  F I L E S ---------------------------------------------------

function setup_files {
	# get source files
	SRCS=($SRCDIR/**/*.'cpp'(.N))
	# get all directories hierarchy in incdir
	INCLUDES=($INCDIR/**/*(/N) $INCDIR)

	if [[ $MODE == 'test' ]]; then
		# get all directories hierarchy in incdir
		INCLUDES+=($TSTINC/**/*(/N) $TSTINC)
		if [[ $TEST == 'all' ]]; then
			# get all tests files (pattern matching _*.cpp)
			SRCS+=($TSTSRC'/'**'/_'*'.cpp'(.N))
		else
			# get all tests files (pattern matching _*.cpp)
			SRCS+=($TSTSRC'/'**'/_'$TEST'.cpp'(.N))
		fi
		# append defines
		DEFINES+=('-DXNS_TEST_'${TEST:u})
		#echo $DEFINES
		# set optimization level
		OPT=$FAST
	fi
	# insert -I prefix to each directory
	INCLUDES=("${INCLUDES[@]/#/-I}")
}










function handle_argument {

	if [[ $ARG_COUNT -eq 0 ]]; then
		return
	fi

	# switch argument
	case $ARGUMENTS[1]; in

		'release')
			echo 'MODE=release' > $SETUP
			;;

		'test')
			make_silent_clean
			echo 'MODE=test'    > $SETUP
			(($ARG_COUNT == 2)) && echo 'TEST='$ARGUMENTS[2] >> $SETUP
			;;

		'rm')
			target_info 'rm'
			make_clean
			exit 0
			;;

		*)
			echo 'unknown argument:' \
				$COLOR$ARGUMENTS[1]$RESET'\n'
			exit 1
			;;
	esac


}

function setup_mode {

	# check for .setup file
	if [[ ! -f $SETUP ]]; then
		make_silent_clean
		echo 'MODE=' > $SETUP
	fi


	# load .setup file
	source $SETUP

	if [[ -z $MODE ]]; then
		require_build_mode
	fi

	if   [[ $MODE == 'test' ]] && [[ -z $TEST ]]; then
		require_test_file

	elif [[ $MODE == 'release' ]]; then
		setup_release
	fi
}



# -- M A I N ------------------------------------------------------------------

function main {

	banner
	check_os
	required $CXX $ARCHIVER
	repository
	initialize_separator

	handle_argument

	setup_mode
	setup_files

	# switch build mode
	case $MODE in

		'release')
			target_info $STATIC
			compile
			linkage $STATIC make_static
			;;
		'test')
			target_info $TEST
			compile
			database
			linkage $EXECUTABLE make_executable
			;;
		*)
			exit 1
			;;
	esac

	echo $SEPARATOR
	echo '💫' "[$MODE]" 'All targets are up to date !\n';
}



# call main function
main; exit 0


