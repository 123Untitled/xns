#!/usr/bin/env -S zsh --no-rcs --errexit --pipefail

# This script is used to generate a single header file for xns library.



# -- C O L O S  ---------------------------------------------------------------

SUCCESS='\x1b[32m'
ERROR='\x1b[31m'
RESET='\x1b[0m'
ERASE='\x1b[1F\x1b[0J'


CXX='clang++'

# -- C H E C K  R E Q U I R E D  P R O G R A M S ------------------------------

# required programs
PROGRAMS=('mkdir' 'tsort' $CXX 'tsort' 'openssl')

# loop through all required commands
for CMD in $PROGRAMS; do
	# check if command is installed
	if [[ -z "$(command -v $CMD)" ]]; then
		# print error message
		echo 'error:' $ERROR$CMD$RESET 'is not installed.'
		# exit script
		exit 1
	fi
done




# -- H E A D E R  F I L E S ----------------------------------------------------

# output directory
OUTDIR='xns'

# temporary directory
TMPDIR=$OUTDIR'/'$(openssl rand -hex 8)

# output file
OUTFILE=$OUTDIR'/xns.hpp'

# get all subdirectories in inc
INCDIRS=('includes/'**'/'*(/N) 'includes')

# get all header files in inc
HEADERS=('includes/'**'/'*'.hpp'(.N))

# add -I flag for each header file
INCLUDES=()
for SUB in $INCDIRS; do
	INCLUDES+=('-I'$SUB)
done

JOBS=8
SORTED=()

mkdir -p $TMPDIR



function get_dependencies {

	#local FILE=$(openssl md5 <<< $1)'.shd'
	# get basename
	local FILE=${1##*/}'.shd'
	# set IFS to newline, tab and space + backslash
	IFS=$'\n\t \\'
	# split content into array
	local WORDS=($($CXX $INCLUDES $1 -MT $1 -MM))
	# reset default IFS
	IFS=$' \t\n'

	# get first word and remove last character ':'
	local TARGET=${WORDS[1]:0:-1}

	# loop over array
	for ((I=2; I <= $#WORDS; ++I)); do
		echo $TARGET $WORDS[$I] >> $TMPDIR'/'$FILE
	done
}


function launch_dependencies {

	local -i RUNNING=0
	local -i TOTAL=$#HEADERS
	local -i COMPLETED=0

	for HEADER in $HEADERS; do
		get_dependencies $HEADER &

		((++RUNNING))
		((++COMPLETED))

		if [[ $RUNNING -eq $JOBS ]]; then
			wait
			RUNNING=0
			PERCENT=$((COMPLETED*100/TOTAL))
			echo -n '\rdependencies resolved:' $PERCENT'%'
		fi
	done
	wait
	echo '\rdependencies resolved: \x1b[32m100%\x1b[0m'
}



# use tsort to topologically sort header files
function topological_sort {

	local DEPS=($TMPDIR'/'*'.shd')
	local FORMATED=()

	IFS=$'\n'
	# concatenate all dependencies
	for DEP in $DEPS; do
		FORMATED+=($(<$DEP))
	done

	local OUTPUT=($(tsort -q <<< $FORMATED))

	IFS=$' \t\n'

	[[ $? -ne 0 ]] && echo 'error: tsort failed.' && exit 1

	# reverse order of lines
	for ((I = $#OUTPUT; I > 0; --I)); do
		# add line to variable
		SORTED+=($OUTPUT[$I])
	done

}


# -- G E N E R A T E  S I N G L E  H E A D E R --------------------------------

function generate_single_header {

	local OUTPUT=''
 	# regex to match local header
	local REGEX='^[[:space:]]*#[[:space:]]*include[[:space:]]*".*"'
	IFS=$'\n'
	# loop over all header files
	for HEADER in $SORTED; do

		# remove comments
		#CLEANED=$($CXX -fpch-preprocess $INCLUDES $HEADER)

		# skip only local includes (e.g. #include "...")
		for L in $(<$HEADER); do
			if [[ $L =~ '^[[:space:]]*//.*' ]]; then
				continue
			fi
			if [[ $L =~ '^[[:space:]]*/\*.*\*/[[:space:]]*$' ]]; then
				continue
			fi
			if [[ ! $L =~ $REGEX ]]; then
				OUTPUT+=$L$'\n'
			fi
		done
	done
	# add include guard
	echo -E '#ifndef XNS_SINGLE_HEADER' > $OUTFILE
	echo -E '#define XNS_SINGLE_HEADER' >> $OUTFILE
	echo -E $OUTPUT >> $OUTFILE
	echo -E '#endif' >> $OUTFILE

	rm -rf $TMPDIR

}

launch_dependencies
topological_sort
generate_single_header


exit 0





# -- G E N E R A T E  S I N G L E  H E A D E R --------------------------------


function system_headers {
	# system header associative array
	typeset -A INC_SYSTEM
	# regex to match system header
	local REGEX='^[[:space:]]*#[[:space:]]*include[[:space:]]*<([^>]*)>'
	# loop over all header files
	for HEADER in $SORTED; do

		IFS=$'\n'
		local CONTENT=$(<$HEADER)

		for FLINE in $CONTENT; do
			if [[ $FLINE =~ $REGEX ]]; then
				INC_SYSTEM[${match[1]}]=1
			fi
		done
	done
}


