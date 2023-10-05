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
  SUCCESS='\x1b[32m'
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

function required() {
	# default required programs
	local COMMANDS=('mkdir' 'rm' 'cd' 'pwd' 'sed' 'cat' 'file' 'vared' 'jq' 'openssl' 'wait' 'fzf' 'flock' 'wc')
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










# -- I M P L E M E N T A T I O N ----------------------------------------------

function description {
	# $1: target file
	local RESUME=$(file $1)
	# regex to match description
	local REGEX='.*: (.*)'
	if [[ $RESUME =~ $REGEX ]]; then
		# print separator
		echo $SEPARATOR
		echo $COLOR'[+]'$RESET ${1##*/} '|' ${match[1]}
	fi
}

function make_clean {
	echo $SEPARATOR
	# remove all targets
	DELETED=$(rm -rfv $EXECUTABLE $STATIC $BLDDIR $CACHEDIR $DATABASE $SETUP | wc -l)
	# print full cleaned message
	echo $COLOR'[x]'$RESET 'full cleaned ('${DELETED##* } 'files)\n';
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
	if [[ ! -f $1 ]] || [[ ! -f $2 ]];
	then return 0; fi
	# get file content
	local CONTENT=$(<$2)
	# split content into words
	local WORDS=(${=CONTENT})
	# loop over array
	for WORD in $WORDS; do

		if [[ $WORD != "\\" ]] && [[ $WORD != *":" ]]; then
			# check if dependency is missing
			[[ $WORD -nt $1 ]] && return 0
		fi
	done
	if [[ $MAKE -nt $1 ]]; then
		return 0
	fi
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


function compile {

	echo $SEPARATOR

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
			cat $LOGDIR'/'*'.log'
			exit 1
		fi
	done

	# get number of compiled files
	local COUNT=$(<$COMPILED)

	if [[ $COUNT -eq 0 ]]; then
		echo $COLOR'[✓]'$RESET 'nothing to compile.'
	else
		echo '\n\n'🫠 $COUNT 'files compiled.'
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

	BUILD_MODE=$(echo -e 'release\ntest' | fzf $FZF_OPTS)

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



function setup_build_mode() {

	# check for .setup file
	if [[ ! -f $SETUP ]]; then
		echo 'BUILD_MODE=' > $SETUP
	fi

	# load .setup file
	source $SETUP

	if [[ -z $BUILD_MODE ]]; then
		require_build_mode
	fi

	if [[ $BUILD_MODE == 'test' ]] && [[ -z $TEST ]]; then
		require_test_file
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
		# get all tests files (pattern matching _*.cpp)
		SRCS+=($TSTSRC'/'**'/_'$TEST'.cpp'(.N))
	fi
	# insert -I prefix to each directory
	INCLUDES=("${INCLUDES[@]/#/-I}")
}








# -- B A N N E R --------------------------------------------------------------

function banner() {
	echo $SUCCESS$BANNER$RESET
}

function target_info() {
	echo $SUCCESS$scriptname$RESET \
		'launching' '['$SUCCESS${1##*/}$RESET']' 'build'
}


function handle_argument {

	if [[ $ARG_COUNT -eq 0 ]]; then
		return
	fi

	# clean
	if [[ $ARGUMENT == 'rm' ]]; then
		target_info 'rm'
		make_clean
		exit 0

	elif [[ $ARGUMENT == 'release' ]]; then
		make_clean
		echo 'BUILD_MODE=release' > $SETUP

	# test
	elif [[ $ARGUMENT == 'test' ]]; then
		make_clean
		echo 'BUILD_MODE=test'    > $SETUP

	else
		echo 'unknown argument:' $COLOR$ARGUMENT$RESET
		exit 1
	fi


}


# main function
function main() {

	banner
	check_os
	required $CXX $ARCHIVER #$LEAKER
	initialize_separator

	handle_argument

	setup_build_mode
	setup_files

	# release mode
	if [[ $BUILD_MODE == 'release' ]]; then
		target_info $STATIC
		compile
		linkage $STATIC make_static

	# test mode
	elif [[ $BUILD_MODE == 'test' ]]; then
		target_info $TEST
		compile
		database
		linkage $EXECUTABLE make_executable
	fi


	echo $SEPARATOR
	echo '💫' "[$BUILD_MODE]" 'All targets are up to date !\n';

}



# call main function
main; exit 0


