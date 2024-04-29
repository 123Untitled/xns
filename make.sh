#!/usr/bin/env -S zsh --no-rcs --no-globalrcs
###############################################################################
#                                                                             #
#                        :::    ::: ::::    :::  ::::::::                     #
#                       :+:    :+: :+:+:   :+: :+:    :+:                     #
#                       +:+  +:+  :+:+:+  +:+ +:+                             #
#                       +#++:+   +#+ +:+ +#+ +#++:++#++                       #
#                     +#+  +#+  +#+  +#+#+#        +#+                        #
#                   #+#    #+# #+#   #+#+# #+#    #+#                         #
#                  ###    ### ###    ####  ########                           #
#                                                                             #
###############################################################################

# This script is used to compile the project.
# Makefile forever, but not really lol.


# -- O P E R A T I N G  S Y S T E M -------------------------------------------

# check if operating system is supported
function check_os {

	if [[ -z $OSTYPE ]]; then
		if ! OSTYPE=$(uname -s); then
			echo 'could not detect operating system.'
			exit 1
		fi
	fi

	# check for macosx
	if   [[ $OSTYPE =~ 'darwin' ]]; then
		OS='macos'
	# check for linux
	elif [[ $OSTYPE =~ 'linux' ]]; then
		OS='linux'
	# check for other
	else
		echo 'unsupported operating system:' $OSTYPE
		exit 1
	fi
}


# operating system
OS=''

# call check_os function
check_os



# -- P W D  &  S C R I P T  D I R E C T O R Y ---------------------------------

# get current absolute directory path
ABSDIR=$(pwd -P)

# get script absolute directory path
SCRIPTDIR=${${0%/*}:a}

# get script absolute path
MAKE=${0:a}

# script name
SCRIPTNAME=${0##*/}


# -- D I R E C T O R I E S ----------------------------------------------------

# sources directory
SRCDIR=$ABSDIR'/sources'

# includes directory
INCDIR=$ABSDIR'/includes'

# tests directory
TSTDIR=$ABSDIR'/tests'

# tests includes directory
TSTINC=$TSTDIR'/includes'

# tests sources directory
TSTSRC=$TSTDIR'/sources'

# build directory
BLDDIR=$ABSDIR'/.build'

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

# external directory
EXTDIR=$ABSDIR'/external'

# tool directory
TOOLDIR=$ABSDIR'/tools'


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

# repository visibility
CLONE=''


# -- C O M P I L E R  S E T T I N G S -----------------------------------------

# compiler
#CXX=('/opt/homebrew/Cellar/llvm/'*'/bin/clang++'(N))
#CXX='/opt/homebrew/Cellar/gcc/13.2.0/bin/g++-13'
CXX='clang++'
#CXX='g++'

# archiver
ARCHIVER='ar'

# archiver flags
ARFLAGS='-rcs'

# linker
LINKER=$CXX

# standard
STD='-std=c++2a'

# debug
DEBUG='-g'

# debug level
DLEVEL=('0' '1' '2' '3'
		'dwarf' 'dwarf+' 'dwarf-2' 'dwarf-3' 'dwarf-4' 'dwarf-5' 'dwarf32' 'dwarf64'
		'gdb' 'gdb0' 'gdb1' 'gdb2' 'gdb3'
		'stabs' 'stabs+'
		'coff' 'xcoff' 'xcoff+'
)

# optimization
OPT='-O'

# opt level
OLEVEL=('fast' 'g' 's' '0' '1' '2' '3')

# compiler flags
CXXFLAGS=()

# warning scope
CXXFLAGS+=('-Wall' '-Wextra')

# warning impact
CXXFLAGS+=('-Werror')

# standard respect
CXXFLAGS+=('-Wpedantic' '-Weffc++')

# unused suppression
CXXFLAGS+=('-Wno-unused' '-Wno-unused-variable' '-Wno-unused-parameter' '-Wno-unused-result')

# optimization
#CXXFLAGS+=('-Winline')

# type conversion
CXXFLAGS+=('-Wconversion' '-Wsign-conversion' '-Wfloat-conversion' '-Wnarrowing')

# shadowing
CXXFLAGS+=('-Wshadow')

# exception
CXXFLAGS+=('-fexceptions' '-Wexceptions')

# runtime type information
CXXFLAGS+=('-fno-rtti')

# thread static
#CXXFLAGS+=('-fno-threadsafe-statics')


# diagnostics
#CXXFLAGS+=('fdiagnostics-absolute-paths')

#-fdiagnostics-absolute-paths                                                   -- print absolute paths in diagnostics
#-fdiagnostics-color                                                            -- colorize diagnostics
#-fdiagnostics-fixit-info                                                       -- supply fixit into with diagnostic messages
#-fdiagnostics-format                                                           -- diagnostics format
#-fdiagnostics-generate-patch                                                   -- print fix-it hints to stderr in unified diff format
#-fdiagnostics-hotness-threshold                                                -- prevent optimization remarks from being output if they do not meet threshold
#-fdiagnostics-parseable-fixits                                                 -- print fixit hints in machine-readable form
#-fdiagnostics-parseable-fixits                                                 -- print fixits in a machine parseable form
#-fdiagnostics-print-source-range-info                                          -- print source range spans in numeric form
#-fdiagnostics-show-caret                                                       -- show the source line with a caret indicating the column
#-fdiagnostics-show-category                                                    -- diagnostics show category
#-fdiagnostics-show-hotness                                                     -- enable profile hotness information in diagnostic line
#-fdiagnostics-show-location                                                    -- how often to emit source location at the beginning of line-wrapped diagnostics
#-fdiagnostics-show-note-include-stack                                          -- display include stacks for diagnostic notes
#-fdiagnostics-show-option                                                      -- amend appropriate diagnostic messages with the command line option that controls them
#-fdiagnostics-show-option                                                      -- enable -Woption information in diagnostic line
#-fdiagnostics-show-template-tree


# defines
DEFINES=()

# linker flags
LDFLAGS=()


# memory checker
LEAKER='valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes'


MAX_JOBS=''

if [[ $OS =~ 'macos' ]]; then
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
local BANNER=\
'\n'\
'      :::    ::: ::::    :::  ::::::::\n'\
'     :+:    :+: :+:+:   :+: :+:    :+:\n'\
'     +:+  +:+  :+:+:+  +:+ +:+        \n'\
'     +#++:+   +#+ +:+ +#+ +#++:++#++  \n'\
'   +#+  +#+  +#+  +#+#+#        +#+   \n'\
' #+#    #+# #+#   #+#+# #+#    #+#    \n'\
'###    ### ###    ####  ########      \n'
	echo $COLOR$BANNER$RESET
}

function target_info() {
	echo $COLOR$SCRIPTNAME$RESET \
		'launching' '['$COLOR${1##*/}$RESET']' 'build'
}



# -- R E Q U I R E D  P R O G R A M S -----------------------------------------

function required {
	# default required programs
	local COMMANDS=(
		'mkdir'
		'wait' # zsh built-in
		'pwd' # zsh built-in
		'rm'
		'cd' # zsh built-in
		'wc'
		'git'
		'cat'
		'file'
		'uname'
		'openssl'
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

	# local variables
	local -r SSH_REPO='git@github.com:123Untitled/xns.git'
	local -r PUB_REPO='https://github.com/123Untitled/xns.git'

	# check current directory is same as script directory
	# and have .git directory
	if [[ $ABSDIR != $SCRIPTDIR || ! -d '.git' ]]; then
		echo 'please run this script in the' $COLOR$PROJECT$RESET 'repository.\n'
		exit 1
	fi

	# get the git remote url
	local REMOTE=$(git config --get 'remote.origin.url')

	# check if the script is run in the ssh repository
	if [[ $REMOTE == $SSH_REPO ]]; then
		CLONE='private'
		return
	fi

	# check if the script is run in the public repository
	if [[ $REMOTE == $PUB_REPO ]]; then
		CLONE='public'
		return
	fi

	echo 'please run this script in the' $COLOR$PROJECT$RESET 'repository.\n'
	exit 1
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

	# check if local install directory exists
	if [[ -d $PROJECT ]]; then
		# remove local install directory
		rm -rf $PROJECT
	fi
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


function message {
	echo $1':' $COLOR$SCRIPTNAME$RESET $2'.\n'
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


function generate_compile_command {
	# $1: file
	# $2: object
	# $3: json
	CMPCMD=('\t{\n'
			'\t\t"directory": "'$ABSDIR'",\n'
			'\t\t"file": "'$1'",\n'
			'\t\t"output": "'$2'"\n'
			'\t\t"arguments": [\n'
			'\t\t\t"'$CXX'",\n'
			'\t\t\t"-c",\n'
			'\t\t\t"'$1'",\n'
			'\t\t\t"-o",\n'
			'\t\t\t"'$2'",\n'
			'\t\t\t"'$STD'",\n'
			'\t\t\t"'$OPT'",\n'
			'\t\t\t"'$DEBUG'",\n'
		)

		for FLAG in $CXXFLAGS; do
			CMPCMD+=('\t\t\t"'$FLAG'",\n')
		done

		for DEFINE in $DEFINES; do
			CMPCMD+=('\t\t\t"'$DEFINE'",\n')
		done

		for INCLUDE in $INCLUDES; do
			CMPCMD+=('\t\t\t"'$INCLUDE'",\n')
		done

		CMPCMD+=('\t\t]\n\t}')

		echo $CMPCMD > $3

}

function handle_compilation {
	# openssl hash
	local HASH=$(openssl md5 <<< $FILE)
	HASH=${HASH#* }
	# get basename of file (without extension)
	local BASE=${${FILE##*/}%%.*}'_'

	local I=''
	for ((I = 1; I <= ${#BASE}; ++I)); do
		# assign char at hash position
		HASH[$I]=${BASE[$I]}
	done

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

		generate_compile_command $FILE $OBJ $JSN

		# compile source file
		$CXX $STD $OPT $DEBUG $CXXFLAGS $DEFINES $INCLUDES \
					-MT $OBJ -MMD -MF $DEP -c $FILE -o $OBJ 2> $LOG

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
					cat $LOGDIR/*.log
					#handle_errors
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
			cat $LOGDIR/*.log
			#handle_errors
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
	local -r TARGET=$1
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

	local -r TARGET=$1
	local -r FUNCTOR=$2

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

	# check if JSNS is empty
	if [[ ${#JSNS[@]} -eq 0 ]]; then
		return
	fi

	# check if need to (re)generate database
	if [[ ! -e $DATABASE ]] || is_link_required $DATABASE $JSNS; then
		# start json string
		local CONTENT='[\n'
		# get all json files content
		for JSN in $JSNS; do
			CONTENT+=$(<$JSN)',\n'
		done
		# erase last comma with bracket
		CONTENT+=']\n'
		# write content to database
		echo $CONTENT > $DATABASE
		# check if compilation database succeeded
		description $DATABASE
	fi
}



# -- B U I L D  M O D E -------------------------------------------------------

function require_build_mode {

	if command -v 'fzy' &> /dev/null; then

		IFS=$'\n'
		local MODES=('release' 'install' 'test')
		MODE=$('fzy' '--prompt=> ' <<< ${MODES[@]})
		IFS=$' \t\n'

		if [[ -z $MODE ]]; then
			exit 1
		fi

		echo 'MODE='$MODE > $SETUP

	else

		echo 'usage:' $COLOR$SCRIPTNAME$RESET 'release | install <prefix> | test <name>\n'
		echo 'hint:' 'install' $COLOR'fzy'$RESET 'to use interactive mode.\n'

		exit 1
	fi
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

function require_prefix {
	echo 'usage:' $COLOR$SCRIPTNAME$RESET 'install <prefix>\n'
	exit 1
}


function setup_install {

	# check for prefix exists
	if [[ ! -d $PREFIX ]]; then
		echo 'error:' $COLOR$SCRIPTNAME$RESET 'invalid prefix directory.\n'
		exit 1
	fi

	# get parent directory
	local ABSPARENT=${ABSDIR%/*}
	# get absolute path of prefix
	local ABSPREFIX=${PREFIX:a}

	# check if prefix is parent directory (because current directory may be project name)
	if [[ $ABSPARENT == $ABSPREFIX && ${ABSDIR##*/} == $PROJECT ]]; then
		echo 'error:' $COLOR$SCRIPTNAME$RESET 'install directory conflict with' $PROJECT 'repository.\n'
		exit 1
	fi

	# check if prefix requires sudo
	if [[ ! -w $PREFIX ]]; then
		echo 'error:' $COLOR$SCRIPTNAME$RESET 'requires permission to install in' $PREFIX '\n'
		exit 1
	fi

	# append project name to prefix
	PREFIX=$ABSPREFIX'/'$PROJECT
}



# -- S O U R C E  F I L E S ---------------------------------------------------

function setup_files {

	# add main include directory
	INCLUDES=($INCDIR)


	# test mode
	if [[ $MODE == 'test' ]]; then

		# append all test include directories
		INCLUDES+=($TSTINC/**/*(/N) $TSTINC)

		if [[ $TEST == 'all' ]]; then
			# append all test files (pattern matching _*.cpp)
			SRCS+=($TSTSRC'/'**'/_'*'.cpp'(.N))
		else
			# append test file
			SRCS=($TSTSRC'/'**'/_'$TEST'.cpp'(.N))

			# check if test file exists
			if [[ ${#SRCS[@]} -eq 0 ]]; then
				message 'error' 'test file not found'
				exit 1
			fi

			# search in source directory if there is a source file with the same name
			# not work because some test files need another source files
			# goal is to compile only the necessary source files
			# will be implemented later...
			#SRCS+=($SRCDIR'/'**'/'$TEST'.cpp'(.N))
		fi

		# get all source files
		SRCS+=($SRCDIR/**/*.'cpp'(.N))

		# append defines
		DEFINES+=('-DXNS_TEST_'${TEST:u})

		# set optimization level
		OPT+='0'
		DEBUG+='0'
		  #OPT+=$OLEVEL[2] # -Og
		  #OPT+=$OLEVEL[7] # -O3
		#DEBUG+=$DLEVEL[4] # -g3


	# release or install
	else
		# get all source files
		SRCS=($SRCDIR/**/*.'cpp'(.N))

		# set optimization level
		  OPT+=$OLEVEL[7] # -O3
		DEBUG+=$DLEVEL[1] # -g0
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
			if [[ $ARG_COUNT -ne 1 ]]; then
				message 'usage' 'release'
				exit 1
			fi
			;;

		'install')
			echo 'MODE=install' > $SETUP

			if [[ $ARG_COUNT -eq 1 ]]; then
				return
			fi

			# check number of arguments
			if [[ $ARG_COUNT -eq 2 ]]; then
				# append prefix to setup file
				echo 'PREFIX='${ARGUMENTS[2]} >> $SETUP
				return
			fi

			# print usage message
			message 'usage' 'install <prefix>'
			exit 1
			;;

		'test')

			# check clone type
			if [[ $CLONE == 'public' ]]; then
				message 'error' \
					'tests are not available in public repository'
				exit 1
			fi

			# submodule : tests
			# initialize submodules
			if ! git submodule update --init --quiet; then
				message 'error' 'failed to initialize submodules'
				exit 1
			fi

			message '\ninfo' 'submodule tests initialized'

			make_silent_clean
			echo 'MODE=test'    > $SETUP

			# check number of arguments
			if [[ $ARG_COUNT -eq 2 ]]; then
				# append test to setup file
				echo 'TEST='${ARGUMENTS[2]} >> $SETUP
				return
			fi


			;;

		'rm')
			target_info 'rm'
			make_clean
			exit 0
			;;

		*)
			message 'error' 'unknown argument'
			exit 1
			;;
	esac


}


function setup_mode {

	# create default .setup file if not exists
	if [[ ! -f $SETUP ]]; then
		make_silent_clean
		echo 'MODE=' > $SETUP
	fi

	# load .setup file
	source $SETUP

	if [[ -z $MODE ]]; then
		require_build_mode
	fi

	# switch build mode
	case $MODE in

		'release')
			;;

		'install')
			if [[ -z $PREFIX ]]; then
				require_prefix
			fi
			setup_install
			;;

		'test')
			if [[ -z $TEST ]]; then
				require_test_file
			fi
			;;

		*)
			message 'error' 'invalid mode'
			make_silent_clean
			exit 1
			;;
	esac
}


# -- M A K E  I N S T A L L -- ################################################

function make_install {

	# remove cursor
	echo -n '\x1b[?25l'

	function __exit {
		# show cursor
		echo '\x1b[?25h'
		exit 1
	}

	echo $SEPARATOR

	local COUNT='0'
	local FIRST='0'

	[[ ! -d $PREFIX ]] && ((++FIRST))

	local -r PFX_INCLUDE=$PREFIX'/include/'$PROJECT
	local -r PFX_LIBRARY=$PREFIX'/lib'
	local -r PFX_STATIC=$PFX_LIBRARY'/'${STATIC##*/}


	# -- main directories -----------------------------------------------------

	# loop over directories
	for DIR in $PFX_INCLUDE $PFX_LIBRARY; do
		# check if directory exists
		if [[ ! -d $DIR ]]; then
			# create directory and check if succeeded
			mkdir -p $DIR || __exit
			echo -n $SUCCESS'.'$RESET
			((++COUNT))
		fi
	done


	# -- library --------------------------------------------------------------

	# check if static library is more recent than prefix
	if [[ ! -f $PFX_STATIC || $STATIC -nt $PFX_STATIC ]]; then
		# cp and check if succeeded
		cp $STATIC $PFX_LIBRARY || __exit
		echo -n $SUCCESS'.'$RESET
		((++COUNT))
	fi


	# -- includes -------------------------------------------------------------

	# construct xns include directory
	local -r XNSINC=$INCDIR'/'$PROJECT
	# get all sub include directories
	local -r SUBDIRS=($XNSINC'/'**'/'*(/N))

	# loop over directories
	for DIR in $SUBDIRS; do

		# construct target directory
		local PFX_SUBDIR=$PFX_INCLUDE'/'${DIR#$XNSINC'/'}

		# check if directory exists
		if [[ ! -d $PFX_SUBDIR ]]; then
			# create directory and check if succeeded
			mkdir -p $PFX_SUBDIR || __exit
			echo -n $SUCCESS'.'$RESET
			((++COUNT))
		fi

		# get all headers
		local HEADERS=($DIR'/'*'.hpp'(.N))

		# loop over headers
		for HEADER in $HEADERS; do

			# construct target header
			local PFX_HEADER=$PFX_SUBDIR'/'${HEADER##*'/'}

			# check if header is more recent than target
			if [[ ! -f $PFX_HEADER || $HEADER -nt $PFX_HEADER ]]; then
				# cp and check if succeeded
				cp $HEADER $PFX_SUBDIR || __exit
				echo -n $SUCCESS'.'$RESET
				((++COUNT))
			fi

			# get base name of header
			local BASE=${HEADER##*'/'}
			# get relative path of prefix header
			local REL=${HEADER##*'/xns/'}
			# construct proxy header path
			local PROXY=$PFX_INCLUDE'/'$BASE

			# check if proxy header is present
			if [[ ! -f $PROXY ]]; then
				# create proxy header and check if succeeded
				echo '#include "'$REL'"' > $PROXY || __exit
				echo -n $SUCCESS'.'$RESET
				((++COUNT))
			fi

		done

	done


	# -- resuming -------------------------------------------------------------

	# check number of installed files
	if [[ $COUNT -eq 0 ]]; then
		echo $COLOR'[✓]'$RESET 'nothing to install.'
	else
		echo '\n\n' 🫠 $COUNT 'files installed.'
	fi

	# print description for first installation
	[[ $FIRST -eq 1 ]] && description $PREFIX

	# show cursor
	echo -n '\x1b[?25h'
}



# -- M A I N ------------------------------------------------------------------

function main {

	banner
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

		'install')
			target_info 'install'
			compile
			linkage $STATIC make_static
			make_install
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
	echo $COLOR'[Ξ]'$RESET 'targets up to date.\n';
}

# '[⚙]'

# call main function
main; exit 0
