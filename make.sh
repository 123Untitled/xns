#!/usr/bin/env -S zsh --no-rcs

# This script is used to compile the project.
# Makefile forever, but not really lol.

local BANNER=\
'   ▁▁▁▁▁▁▁▁  ▁▁▁▁▁▁▁▁  ▁▁▁▁ ▁▁▁  ▁▁▁▁▁▁▁▁ \n'\
'  ╱        ╲╱        ╲╱    ╱   ╲╱        ╲\n'\
' ╱         ╱         ╱         ╱         ╱\n'\
'╱         ╱         ╱        ▁╱       ▁▁╱ \n'\
'╲▁▁╱▁▁╱▁▁╱╲▁▁▁╱▁▁▁▁╱╲▁▁▁▁╱▁▁▁╱╲▁▁▁▁▁▁▁▁╱  \n'



# -- S C R I P T  P A T H  S E T T I N G S ------------------------------------

# get absolute directory of script
abspath=$(cd ${0%/*}; pwd)

# get dirname of script
rootname=${abspath##*/}

# get absolute path of script
MAKE=$abspath/${0##*/}

# basename of the script without using basename command
scriptname=${0##*/}


# -- D I R E C T O R I E S ----------------------------------------------------

# sources directory
SRCDIR=$abspath'/sources/core'

# includes directory
INCDIR=$abspath'/includes'

# tests directory
TSTDIR=$abspath'/sources/tests'

# tests includes directory
TSTINC=$TSTDIR'/inc'

# tests sources directory
TSTSRC=$TSTDIR'/src'

# build directory
BLDDIR=$abspath'/build'

# object directory
OBJDIR=$BLDDIR'/object'

# dependency directory
DEPDIR=$BLDDIR'/dependency'

# json directory
JSNDIR=$BLDDIR/'json'

# compile log directory
LOGDIR=$BLDDIR/'log'

# cache directory
CACHEDIR=$abspath/'.cache'



# -- T A R G E T S ------------------------------------------------------------

# project name
PROJECT='xns'

# target executable
EXECUTABLE=$abspath'/exec_'$PROJECT

# target static library
STATIC=$abspath'/lib'$PROJECT'.a'

# compilation database
DATABASE=$abspath/'compile_commands.json'

# .setup file
SETUP=$abspath'/.setup'

# command line arguments
ARGUMENT=$1

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
CXX='/opt/homebrew/Cellar/llvm/17.0.2/bin/clang++'

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
#CXXFLAGS+=('-Wconversion' '-Wsign-conversion' '-Wfloat-conversion' '-Wnarrowing')

# shadowing
#CXXFLAGS+=('-Wshadow')

# defines
DEFINES=()


# linker flags
LDFLAGS=''

# memory checker
LEAKER='valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes'


FZF_OPTS=('--algo=v2' '--height=50%' '--no-multi' '--layout=reverse' '--border=rounded' '--scroll-off=50'  '--bind' 'tab:down' \
		  '--color=border:8,fg:7,bg:0,hl:2,fg+:3,bg+:8,hl+:4,info:5,prompt:6,pointer:6,marker:3,spinner:5,header:1')



# -- C O L O R  S E T T I N G S -----------------------------------------------

# main color
	COLOR='\x1b[32m'
  SUCCESS='\x1b[33m'
	ERROR='\x1b[31m'
	RESET='\x1b[0m'
	ERASE='\x1b[1F\x1b[0J'
SEPARATOR=''








# -- O P E R A T I N G  S Y S T E M -------------------------------------------

# check if operating system is supported
function check_os {
	# check for macosx
	if   [[ $OSTYPE == 'darwin'* ]]; then
		#echo 'Detected OS:' $color'macosx'$reset
	# check for linux
	elif [[ $OSTYPE == 'linux-gnu'* ]]; then
		#echo 'Detected OS:' $color'linux'$reset
	# check for other
	else
		echo 'Unsupported OS:' $COLOR$OSTYPE$RESET
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
		'vared'
		'openssl'
		'flock'
		'fzf'
		'jq'
	)
	# append arguments
	COMMANDS+=( "$@" )
	# loop through all required commands
	for CMD in $COMMANDS; do
		# check if command is installed
		if [[ -z "$(command -v $CMD)" ]]; then
			# print error message
			echo '\nerror:' $ERROR$CMD$RESET 'is not installed.'
			exit 1
		fi
	done
}





# -- C H E C K  W O R K I N G  D I R E C T O R Y ------------------------------


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
	# regex to match description
	if [[ $(file $1) =~ '.*: (.*)' ]]; then
		# print separator
		echo $SEPARATOR$SUCCESS'[+]'$RESET ${1##*/} '|' ${match[1]}
	fi
}

function make_clean {
	# remove all targets
	DELETED=$(rm -rfv $EXECUTABLE $STATIC $BLDDIR $CACHEDIR $DATABASE $SETUP | wc -l)
	# print full cleaned message
	echo $SEPARATOR$COLOR'[⏺]'$RESET 'full cleaned ('${DELETED##* } 'files)\n';
}

function make_executable {
	# link executable
	$LINKER $LDFLAGS $OBJS -o $EXECUTABLE || exit 1
	# check if linking succeeded
	description $EXECUTABLE
}

function make_static {
	# link static library
	$ARCHIVER $ARFLAGS $STATIC $OBJS || exit 1
	# check if linking succeeded
	description $STATIC
}

function make_database {
	echo "[\n"$(cat $JSNS | sed '$s/,\s*$//')"\n]" | jq > $DATABASE
	# check if compilation database succeeded
	description $DATABASE
}



# -- U T I L I T I E S  F U N C T I O N S -------------------------------------




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



function check_dependency {
	# check if object or dependency file is missing
	if [[ ! -f $1 ]] || [[ ! -f $2 ]] || [[ $MAKE -nt $1 ]]; then
		return 0
	fi
	# split content into words
	local WORDS=(${=$(<$2)})
	# loop over array
	for WORD in $WORDS; do
		# check if word is not target or escape
		if [[ $WORD != "\\" ]] && [[ $WORD != *":" ]]; then
			# check if dependency is missing
			[[ $WORD -nt $1 ]] && return 0
		fi
	done
	return 1
}




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

		# increment compiled files counter
		flock -x $LOCK
		local COUNT=$(<$COMPILED)
		((++COUNT))
		echo $COUNT > $COMPILED
		flock -u $LOCK

		# compile source file
		$CXX $STD $OPT $DEBUG $CXXFLAGS $DEFINES $INCLUDES \
			-MJ $JSN -MT $OBJ -MMD -MF $DEP -c $FILE -o $OBJ 2> $LOG

		# check if compilation failed
		if [[ $? -ne 0 ]]; then
			echo -n   $ERROR'[x]'$RESET; exit 1
		else
			echo -n $SUCCESS'[✓]'$RESET; exit 0
		fi


	fi

	exit 0

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
			fi


			if [[ $LOGLINE =~ $REGEX ]]; then
				BASE=${match[1]}
				NUMBER=$(printf "%10d" ${match[2]})
				MSG=$(printf "%10s" ${match[4]})

				echo $NUMBER $COLOR'|'$RESET $BASE
				echo $MSG

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


	echo 0 > $COMPILED
	touch $LOCK
	# array of pids
	PIDS=()

	# loop over source files
	for FILE in $SRCS; do
		handle_compilation $FILE &
		PIDS+=($!)
	done


	# loop over pids
	for PID in $PIDS; do
		# wait for pid
		wait $PID
		# check if compilation failed
		if [[ $? -ne 0 ]]; then
			wait
			echo '\n'$SEPARATOR
			handle_errors
			exit 1
		fi
	done

	# get number of compiled files
	local COUNT=$(<$COMPILED)

	if [[ $COUNT -eq 0 ]]; then
		echo $COLOR'[✓]'$RESET 'nothing to compile.'
	else
		echo '\n\n' 🫠 $COUNT 'files compiled.'
	fi

}


function database {

	# get all json files
	JSNS=($JSNDIR'/'**'/'*'.json'(.N))
	# check if there is any json files
	if [[ ${#JSNS[@]} -eq 0 ]]; then
		exit 1
	fi

	# handle compilation database
	if [[ ! -e $DATABASE ]] || is_link_required $DATABASE $JSNS; then
		make_database
	fi
}

function linkage {

	local TARGET=$1
	local FUNCTOR=$2

	# get all object files
	OBJS=($OBJDIR'/'**'/'*'.o'(.N))
	# check if there is any object files
	if [[ ${#OBJS[@]} -eq 0 ]]; then
		exit 1
	fi
	# handle target
	if [[ ! -e $TARGET ]] || is_link_required $TARGET $OBJS; then
		$FUNCTOR
	fi
}



function require_build_mode {

	BUILD_MODE=$(echo -e 'release\ntest\ninstall' | fzf $FZF_OPTS)

	if [[ -z $BUILD_MODE ]]; then
		exit 1
	fi

	echo 'BUILD_MODE='$BUILD_MODE > $SETUP
}


function require_test_file {

	# get all tests files
	local FILES=($TSTSRC'/'**'/_'*'.cpp'(.N))

	# keep only basename without extension
	FILES=("${FILES[@]##*/}")
	# remove extension
	FILES=("${FILES[@]%%.*}")
	# remove _ prefix
	FILES=("${FILES[@]#_}")

	TEST=$(echo -e ${(j:\n:)FILES} | fzf $FZF_OPTS)

	# check if test is selected
	if [[ -z $TEST ]]; then
		exit 1
	fi
	echo 'TEST='$TEST >> $SETUP
}

function require_config {
	# not implemented yet...
}



function setup_build_mode() {

	# check for .setup file
	if [[ ! -f $SETUP ]]; then
		make_clean
		echo 'BUILD_MODE=' > $SETUP
	fi

	# load .setup file
	source $SETUP

	if [[ -z $BUILD_MODE ]]; then
		require_build_mode
	fi

	if   [[ $BUILD_MODE == 'test' ]] && [[ -z $TEST ]]; then
		require_test_file
	#elif [[ $BUILD_MODE == 'configure' ]]; then
		#require_config
	fi
}


# -- S O U R C E  F I L E S ---------------------------------------------------

function setup_files() {
	# get source files
	SRCS=($SRCDIR/**/*.'cpp'(.N))
	# get all directories hierarchy in incdir
	INCLUDES=($INCDIR/**/*(/N) $INCDIR)

	if [[ $BUILD_MODE == 'test' ]]; then
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
	fi
	# insert -I prefix to each directory
	INCLUDES=("${INCLUDES[@]/#/-I}")
}








# -- B A N N E R --------------------------------------------------------------

function banner() {
	echo $COLOR$BANNER$RESET
}

function target_info() {
	echo $COLOR$scriptname$RESET \
		'launching' '['$COLOR${1##*/}$RESET']' 'build'
}


function handle_argument {

	if [[ $ARG_COUNT -eq 0 ]]; then
		return
	fi

	# switch argument
	case $ARGUMENT in

		'rm')
			target_info 'rm'
			make_clean
			exit 0
			;;
		'release')
			make_clean
			echo 'BUILD_MODE=release' > $SETUP
			;;
		'test')
			make_clean
			echo 'BUILD_MODE=test'    > $SETUP
			;;
		'install')
			make_clean
			echo 'BUILD_MODE=install' > $SETUP
			;;
		*)
			echo 'unknown argument:' $COLOR$ARGUMENT$RESET'\n'
			exit 1
			;;
	esac

}


# main function
function main() {

	banner
	check_os
	required $CXX $ARCHIVER #$LEAKER
	repository
	initialize_separator

	handle_argument

	setup_build_mode
	setup_files

	# switch build mode
	case $BUILD_MODE in

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
		'install')
			target_info 'install'
			compile
			linkage $STATIC make_static
			;;
		*)
			exit 1
			;;
	esac

	echo $SEPARATOR
	echo '💫' "[$BUILD_MODE]" 'All targets are up to date !\n';
}



# call main function
main; exit 0


