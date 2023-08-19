#!/usr/bin/env zsh --no-rcs --errexit

# this script is used to generate ninja files for building




# -- C O L O R S --------------------------------------------------------------

# colors for terminal output
SUCCESS='\x1b[32m'
WARNING='\x1b[33m'
ERROR='\x1b[31m'
RESET='\x1b[0m'


# -- R E Q U I R E M E N T S --------------------------------------------------

# list all required programs
REQUIRED=('clang++'
		  'command'
		  'which'
		  'echo'
		  'git'
		  'ar'
		  'ninja'
		  'date'
		  'shasum'
		  'mkdir'
		  'rm'
		  'pwd'
		  'uname'
		  'vared'
		  'bindkey'
);

# check if all required programs are installed
for REQ in $REQUIRED; do
	if ! command -v $REQ &> /dev/null; then
		echo "error: $ERROR$REQ$RESET is not installed"
		exit 1
	fi
done



# -- C H E C K  W O R K I N G  D I R E C T O R Y ------------------------------

XNS_PUBLIC_URL='https://github.com/123Untitled/xns.git'
XNS_SSH_URL='git@github.com:123Untitled/xns.git'


function invalid_repository {
	echo 'Please run this script in the' $ERROR'xns'$RESET 'repository.'
	exit 1
}

# check if the script is run in the right repository
if [[ ! -d .git ]]; then
	invalid_repository
	exit 1
fi

# get remote origin url
REMOTE_ORIGIN_URL=$(git config --get remote.origin.url)

# check if remote origin url corresponds to the public url or the ssh url
if [[ $REMOTE_ORIGIN_URL != $XNS_PUBLIC_URL ]] && [[ $REMOTE_ORIGIN_URL != $XNS_SSH_URL ]]; then
	invalid_repository
	exit 1
fi



# -- O P E R A T I N G  S Y S T E M -------------------------------------------

# check if 'OS' is not set
if [[ -z $OS ]]; then
	OS=$($(which uname) -s)
fi

# detect operating system
if   [[ $OS =~ 'Darwin' ]]; then
	DEXT='dylib'
elif [[ $OS =~ 'Linux'  ]]; then
	DEXT='so'
else
	echo "error: $ERROR$OS$RESET is not supported"
	exit 1
fi


# -- P R O J E C T ------------------------------------------------------------

# project name
PROJECT='xns'

# executable name
EXECUTABLE='exec'

# static library name
STATIC='lib'$PROJECT'.a'

# dynamic library name
DYNAMIC='lib'$PROJECT'.'$DEXT

# ninja file name
NINJAFILE='build.ninja'

# compile database name
COMPILEDB='compile_commands.json'

# mode file name
MODEFILE='.mode'

# single header
SINGLE_HEADER=$PROJECT'.hpp'



# -- D I R E C T O R I E S ----------------------------------------------------

# current working directory
ROOT='.' #$(pwd)

# build directory
BLDDIR=$ROOT/'build'

# source directory
SRCDIR=$ROOT/'src'

# include directory
INCDIR=$ROOT/'inc'

# object directory
OBJDIR=$BLDDIR/'obj'

# dependency directory
DEPDIR=$BLDDIR/'dep'

# log directory
LOGDIR=$BLDDIR/'log'

# script directory
SCRIPTDIR=$ROOT/'script'

# clangd cache directory
CDCACHE=$ROOT/'.cache'


# -- F I L E S ----------------------------------------------------------------

# get recursively all source files in srcdir
SRCS=($SRCDIR/**/*.'cpp'(.N))

# get recursively all subdirectories in incdir
INCS=($INCDIR/**/*(/N) $INCDIR)

# insert -I prefix to each directory
INCS=("${INCS[@]/#/-I}")

# init object files
OBJS=()



# -- T E S T S ----------------------------------------------------------------

# test directory
TESTDIR=$ROOT/'test'

# test source directory
TEST_SRCDIR=$TESTDIR/'src'

# test include directory
TEST_INCDIR=$TESTDIR/'inc'

# get recursively all source files in testdir
TEST_SRCS=($TEST_SRCDIR/**/*.'cpp'(.N))

# get recursively all subdirectories in testinc
TEST_INCS=($TEST_INCDIR/**/*(/N) $TEST_INCDIR)

# insert -I prefix to each directory
TEST_INCS=("${TEST_INCS[@]/#/-I}")




# -- T O O L C H A I N --------------------------------------------------------
BREW_CXX='/opt/homebrew/opt/llvm/bin/clang++'

# compiler
#COMPILER=$BREW_CXX
COMPILER=$(which clang++)

# linker
LINKER=$COMPILER

# archiver
ARCHIVER=$(which ar)

# archiver flags
ARFLAGS='-rcs'

# c++ standard
STANDARD='-std=c++2a'

# debug mode
DEBUG='-g3'

# optimization level
OPTIMIZATION='-O0'

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

# linker flags
LDFLAGS=''

# make directories
MK=($(which mkdir) '-pv')

# remove files
RM=($(which rm) '-rfv')


# -- H I E R A R C H Y --------------------------------------------------------

# create directories
$MK $BLDDIR $OBJDIR $DEPDIR $LOGDIR





# -- A R G U M E N T S --------------------------------------------------------

# check command line arguments
if [[ $# -eq 1 && $1 == 'help' ]]; then
	echo "usage: ./make.sh [release|debug|test|install|rm]"
	exit 0
fi



if [[ $# -gt 0 ]]; then
	# check for 'rm' argument
	if [[ $1 == 'rm' ]]; then
		# check if ninja file exists
		if [[ -f $NINJAFILE ]]; then
			# call ninja clean
			ninja -t clean
		fi
		# remove build directory and clangd cache
		$RM $BLDDIR $CDCACHE $NINJAFILE $SINGLE_HEADER
		exit 0

	# check for 'release' argument
	elif [[ $1 == 'release' ]]; then
		echo 'MODE=release' > $BLDDIR/$MODEFILE

	# check for 'debug' argument
	elif [[ $1 == 'debug' ]]; then
		echo 'MODE=debug' > $BLDDIR/$MODEFILE

	# check for 'test' argument
	elif [[ $1 == 'test' ]]; then
		echo 'MODE=test' > $BLDDIR/$MODEFILE
		if [[ $# -eq 2 ]]; then
			if [[ $2 == 'main' ]]; then
				TEST_SRCS=($TEST_SRCDIR/'main.cpp')
			else
				# search for test file
				for TEST in $TEST_SRCS; do
					# extract basename
					local BASENAME=${TEST##*/}
					# remove _tests.cpp suffix
					BASENAME=${BASENAME%_tests.cpp}
					# check if test name matches
					if [[ $BASENAME == $2 ]]; then
						TEST_SRCS=($TEST)
						break
					fi
				done
			fi
		fi

	# check for 'install' argument
	elif [[ $1 == 'install' ]]; then
		echo 'not implemented yet...'
		exit 1

	# invalid argument
	else
		echo "error: invalid argument '$1'"
		exit 1
	fi
fi



# -- M O D E ------------------------------------------------------------------

# check if mode file exists
if [[ -f $BLDDIR/$MODEFILE ]]; then
	# source mode file
	source $BLDDIR/$MODEFILE
else
	# ask for mode
	bindkey -e
	vared -p 'Select mode [release, debug, test]: ' -c MODE
	# write mode to file
	echo "MODE='$MODE'" > $BLDDIR/$MODEFILE
fi

# check if mode is valid
if [[ $MODE != 'release' && $MODE != 'test' ]]; then
	echo 'error: invalid' $ERROR'mode'$RESET
	$RM $BLDDIR/$MODEFILE
	exit 1
fi


echo $SUCCESS'xns'$RESET 'build started.'

function make_ninja {

	# run ninja and check for errors
	if ninja -f $NINJAFILE; then

		if [[ $MODE == 'release' ]]; then
			# check if xns.hpp is outdated
			if [[ ! -f $SINGLE_HEADER || $SINGLE_HEADER -ot $STATIC || $SINGLE_HEADER -ot $SCRIPTDIR/'single_header.sh' ]]; then
				$SCRIPTDIR/'single_header.sh'
			fi
		fi

		#echo 'success' $SUCCESS'ninja'$RESET 'build'
		exit 0
	fi

	return 1
	# check clang-filter executable exists
	if [[ ! -x "clang-filter" ]]; then
		git clone 'git@github.com:123Untitled/build_system.git' 'build_system'
		if [[ $? -ne 0 ]]; then
			echo $error':('$reset 'failed to clone build_system repository.'
			exit 1
		fi
		(cd 'build_system'/'clang-filter' && make && cp 'clang-filter' '../../')
		if [[ $? -ne 0 ]]; then
			echo $error':('$reset 'failed to compile clang-filter.'
			exit 1
		fi
		rm -rf 'build_system'
	fi

	./clang-filter < $LOGDIR/*.log
	rm -f $LOGDIR/*.log
}


# -- G E N E R A T O R --------------------------------------------------------

# check if ninja file exists
if [[ -f $NINJAFILE ]]; then
	# check ninja mode
	local NCONTENT=$(<$NINJAFILE)
	# split by newline
	local NLINES=(${(@f)NCONTENT})
	# loop over lines
	for LINE in $NLINES; do

		# search for mode pattern
		if ! [[ $LINE =~ "^ *mode *= *([a-zA-Z]+)$" ]]; then continue; fi

		# get mode
		local NMODE=${match[1]}

		# check if mode has changed
		if [[ $NMODE != $MODE ]]; then
			# call ninja clean
			ninja -t clean
			break
		fi

		# check if this script is newer than ninja file
		if [[ $0 -nt $NINJAFILE ]]; then break; fi

		# else call ninja
		make_ninja
		exit 0

	done

fi



# -- U P D A T E  D A T A  F O R  S E L E C T E D  M O D E --------------------

# check for release mode
if [[ $MODE == 'release' ]]; then
	# set maximum optimization level
	OPTIMIZATION='-O3'
	# disable debug symbols
	DEBUG='-g0'
# check for test mode
elif [[ $MODE == 'test' ]]; then
	# add test source files
	SRCS+=($TEST_SRCS)
	# add test include directories
	INCS+=($TEST_INCS)
fi



# title generator
function title {
	# get argument
	local NAME=$1
	# to uppercase
	NAME=${NAME:u}
	# start composing title
	TITLE='# -- '
	# add spaces after each character, except spaces
	for (( i=0; i<${#NAME}; ++i )); do
		if [[ ${NAME:$i:1} =~ ' ' ]]; then
			TITLE+=' '
		else
			TITLE+=${NAME:$i:1}' '
		fi
	done
	# get length of title
	local LENGTH=${#TITLE}
	# add dashes
	for (( i=${#TITLE}; i < 79; ++i )); do
		TITLE+='-'
	done
	# print title on stdout
	echo $TITLE
}


# ninja generator function
function generate_ninja {


	# get timestamp
	TIMESTAMP=$(date "+%Y-%m-%d %H:%M:%S")

	# variables
	echo "\n$(title 'ninjafile')\n"                             > $NINJAFILE
	echo "# generated by make.sh on $TIMESTAMP\n"              >> $NINJAFILE
	echo "ninja_required_version = 1.11.1\n"                 >> $NINJAFILE
	echo "\n$(title 'variables')\n"                              >> $NINJAFILE
	echo "mode = $MODE"                                        >> $NINJAFILE
	echo "cxx = $COMPILER"                                     >> $NINJAFILE
	echo "cxxflags = $STANDARD $OPTIMIZATION $DEBUG $CXXFLAGS" >> $NINJAFILE
	echo "ldflags = $LDFLAGS"                                  >> $NINJAFILE

	# add static library flags in release mode
	if [[ $MODE == 'release' ]]; then
		echo "archiver = $ARCHIVER"                            >> $NINJAFILE
		echo "arflags = $ARFLAGS"                              >> $NINJAFILE
	fi

	echo "incs = $INCS"                                        >> $NINJAFILE
	echo "builddir = $BLDDIR\n"                              >> $NINJAFILE

	# rules
	echo "\n$(title 'rules')\n" >> $NINJAFILE

	# database
	echo "rule database" >> $NINJAFILE
	echo "  command = ninja -t compdb > \$out" >> $NINJAFILE
	echo "  description = generating compilation database\n" >> $NINJAFILE

	# compile
	echo "rule compile" >> $NINJAFILE
	echo "  command = \$cxx \$cxxflags \$incs -MMD -MF \$dep -c \$in -o \$out" >> $NINJAFILE
	#echo "  command = \$cxx \$cxxflags \$incs -MMD -MF \$dep -c \$in -o \$out 2> \$log" >> $NINJAFILE
	echo "  depfile = \$dep" >> $NINJAFILE
	echo "  description = compiling \$in\n" >> $NINJAFILE

	if [[ $MODE == 'test' ]]; then
		# link
		echo "rule link" >> $NINJAFILE
		echo "  command = \$cxx \$in -o \$out" >> $NINJAFILE
		echo "  description = linking \$out\n" >> $NINJAFILE
	fi

	if [[ $MODE == 'release' ]]; then
		# archive
		echo "rule archive" >> $NINJAFILE
		echo "  command = \$archiver -rcs \$out \$in" >> $NINJAFILE
		echo "  description = archiving \$out\n" >> $NINJAFILE

		# single header generation
		echo "rule single_header" >> $NINJAFILE
		echo "  command = ./single_header.sh" >> $NINJAFILE
		echo "  description = generating \$out\n" >> $NINJAFILE

	fi


	# builds
	echo "\n$(title 'sources build')\n" >> $NINJAFILE

	# xns sources build
	for SRC in $SRCS; do
		local HASH=$(shasum -a 1 <<< $SRC)
		HASH=${HASH%% *}
		local OBJ=$OBJDIR'/'$HASH'.o'
		local DEP=$DEPDIR'/'$HASH'.d'
		local LOG=$LOGDIR'/'$HASH'.log'
		# base name of source file
		local BASE=${SRC##*/}
		OBJS+=($OBJ)

		echo "# $BASE" >> $NINJAFILE
		echo "build $OBJ: \$" >> $NINJAFILE
		echo "compile $SRC | $NINJAFILE" >> $NINJAFILE
		echo "  dep = $DEP" >> $NINJAFILE
		echo "  log = $LOG\n" >> $NINJAFILE

	done


	if [[ $MODE == 'release' ]]; then

		# static library
		echo "\n$(title 'static library')\n" >> $NINJAFILE
		echo "build $STATIC: archive \$" >> $NINJAFILE
		for OBJ in $OBJS; do
			echo "$OBJ \$" >> $NINJAFILE
		done

		# single header
		#echo "\n$(title 'single header')\n" >> $NINJAFILE
		#echo "build $SINGLE_HEADER: single_header | $STATIC\n" >> $NINJAFILE


	# executable build
	elif [[ $MODE == 'test' ]]; then
		# tests executable
		echo "\n$(title 'tests')\n" >> $NINJAFILE
		echo "build $EXECUTABLE: link $OBJS\n" >> $NINJAFILE
	fi

	# database build
	echo "\n$(title 'database')\n" >> $NINJAFILE
	echo "build $COMPILEDB: database | $NINJAFILE\n\n\n" >> $NINJAFILE

}


# wait generation function
function wait_generation {
	# get pid
	local PID=$1
	local ANIM=('-' '\' '|' '/')
	local I=1
	# generate ninja file
	echo -n 'Generating' $SUCCESS'ninja'$RESET 'file '
	# disable cursor
	echo -n '\x1b[?25l'
	# wait for ninja file to be generated
	while kill -0 $PID 2> /dev/null; do

		# print animation
		echo -n '['${ANIM[$I]}']'
		# move cursor right 3 characters
		echo -n '\x1b[3D'
		# increment animation index
		((++I))
		[[ $I -eq 5 ]] && I=1
		sleep 0.05
	done

	echo '['$SUCCESS'ok'$RESET']'
	# enable cursor
	echo -n '\x1b[?25h'
}

# generate ninja file
generate_ninja & wait_generation $!
wait $!


function filter {
	local line
	while read -r line; do

		if [[ $line =~ "^\[[0-9]+/[0-9]+\]" ]]; then
			# erase line
			echo -n '\x1b[2K'
			echo -n '\x1b[0G'
			echo -n "$line"
			# move cursor to beginning of line
			continue
		fi

		#n=${l#\[ninja\]}
		#[ "x$l" != "x$n" ] && printf "%s\n" "$n" || printf "%s\n" "$l" >&2
	done
}

#NINJA_STATUS="[%f/%t] "
#set -o pipefail
#ninja | filter
#echo $?

#exit 0

# print success
#echo "$(title 'done')"
#echo 'run' $SUCCESS'ninja'$RESET 'to build'


make_ninja











