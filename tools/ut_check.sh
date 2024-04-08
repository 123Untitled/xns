#!/usr/bin/env -S zsh --no-rcs --err-exit

# this script is used to generate missing unit test files

CO='\x1b[31m'
CE='\x1b[32m'
NC='\x1b[0m'

PROJECT='xns'

INCDIR='includes'
TSTDIR='tests/sources'


SSH_REPO='git@github.com:123Untitled/xns.git'
PUB_REPO='https://github.com/123Untitled/xns.git'


# -- C H E C K  R E Q U I R E M E N T S ---------------------------------------

local -r -a REQUIRED=(
	'git'
	'fzy'
)

# loop over all required commands
for COMMAND in $REQUIRED; do
	# check if the command is installed
	if ! command -v $COMMAND &> /dev/null; then
		echo $COMMAND 'is required to run this script.'
		exit 1
	fi
done


# -- C H E C K  W O R K I N G  D I R E C T O R Y ------------------------------

# check if the script is run in a git repository
if [[ ! -d .git ]]; then
	echo 'please run this script in the' $CO$PROJECT$NC 'repository.'
	exit 1
fi

# get the git repository name
GIT_REPO=$(git config --get remote.origin.url)

# check if the script is run in the right repository
if [[ $GIT_REPO != $SSH_REPO && $GIT_REPO != $PUB_REPO ]]; then
	echo 'please run this script in the' $CO$PROJECT$NC 'repository.'
	exit 1
fi


# -- C H E C K  G I T  S T A T U S --------------------------------------------

# check if there is staged files
if ! git diff --cached --exit-code --quiet; then
	echo 'please' $CE'commit'$NC 'or' $CE'stash'$NC 'your changes first.'
	exit 1
fi



# -- C H E C K  D I R E C T O R I E S -----------------------------------------

# check if the include directory exists
if [[ ! -d $INCDIR ]]; then
	echo 'the' $CO$INCDIR$NC 'directory does not exist.'
	exit 1
fi


# check if the unit test directory exists
if [[ ! -d $TSTDIR ]]; then
	echo 'the' $CO$TSTDIR$NC 'directory does not exist.'
	exit 1
fi




# -- I N I T I A L I Z A T I O N ----------------------------------------------

# get all header files
HEADERS=($INCDIR'/'**'/'*'.hpp'(.N))

# get basenames and remove extension
HEADERS=(${${HEADERS[@]##*/}[@]%'.hpp'})

# get all unit test files
TESTS=($TSTDIR'/'**'/'*'.cpp'(.N))

# remove extensions and '_' prefix
TESTS=(${${TESTS[@]##*/_}[@]%'.cpp'})

# remove 'all' file
TESTS=(${(@)TESTS:#all})


# create an header table
typeset -A HTABLE
# create an unit test table
typeset -A UTABLE

# loop over all header files
for HEADER in $HEADERS; do
	# add header to table
	HTABLE[$HEADER]=1
done

# loop over all unit test files
for TEST in $TESTS; do
	# add unit test to table
	UTABLE[$TEST]=1
done






function ___model {

	# check if there is two arguments
	if [[ $# -ne 2 ]]; then
		echo 'usage: ___model <path> <basename>'
		exit 1
	fi

	# unit test file model
	local -r -a MODEL=(
			'#include "'$1'"\n\n'
			'/* unit test */\n'
			'static int ___'$2'(void) {\n'
			'\treturn 0;\n'
			'}\n\n'
			'static int ___'$2'(int ac, char** av) {\n'
			'\treturn 0;\n'
			'}\n\n'
			'#if defined(XNS_TEST_'${2:u}')\n'
			'int main(int ac, char** av) {\n'
			'\treturn (ac > 1)\n'
			'\t\t? ___'$2'(ac - 1, av + 1)\n'
			'\t\t: ___'$2'();\n'
			'}\n'
			'#endif'
	)

	echo $MODEL
}



function ___prompt {
	echo -n '[y/n] ? '

	while true; do
		# read one character
		read -k 1 -s INPUT
		# echo
		if   [[ $INPUT =~ '[yY]' || $INPUT == $'\n' ]]; then
			echo 'yes.'
			return 0
		elif [[ $INPUT =~ '[nN]' || $INPUT == $'\e' ]]; then
			echo 'no.'
			return 1
		elif [[ $INPUT =~ '[qQaA]' ]]; then
			echo 'abort.'
			exit 0
		fi
	done
	# never reach this point
}


function missing_test {

	local CHOICES=()

	# loop over all header files
	for HEADER in $HEADERS; do
		# check if the associated unit file exist
		if [[ ! -v UTABLE[$HEADER] ]]; then
			CHOICES+=($HEADER)
		fi
	done

	# send choices to fzy
	IFS=$'\n'
	local -r SELECT=$(fzy <<< $CHOICES)
	IFS=$' \t\n'

	if [[ -z $SELECT ]]; then
		exit 0
	fi

	echo -n $CE$SELECT$NC 'does not have a unit test file, generating it ? '

	___prompt || exit 0

	# get the unit test file path
	local TEST_PATH=$TSTDIR'/_'$SELECT'.cpp'

	# check if the unit test file already exists
	if [[ -f $TEST_PATH ]]; then
		echo $CO'error'$NC 'unit test file already exists.'
		exit 1
	fi

	# search full path of the header file
	local INCLUDE_PATH=($INCDIR'/'**'/'$SELECT'.hpp'(.N))


	# remove 'includes/' prefix
	INCLUDE_PATH=${INCLUDE_PATH#includes/}

	# generate unit test file
	___model $INCLUDE_PATH $SELECT > $TEST_PATH

	# check if the unit test file was generated
	if [ ! -f $TEST_PATH ]; then
		echo $CO'error'$NC 'generating unit test file.'
		exit 1
	fi

	echo $CE'_'$SELECT'.hpp'$NC 'unit test file generated.'

	exit 0
}


function missing_header {

	# loop over all unit test files
	for TEST in $TESTS; do
		# check if the associated header file exist
		if [[ ! -v HTABLE[$TEST] ]]; then

			# print message
			echo -n $CO'_'$TEST'.cpp'$NC 'is not associated to a header file, delete it ? '

			if ___prompt; then

				# get the unit test file path
				local FILE_PATH=$TSTDIR'/_'$TEST'.cpp'

				# check if the unit test file already exists
				if [ ! -f $FILE_PATH ]; then
					exit 1
				fi

				# remove unit test file
				git rm $FILE_PATH
				# commit unit test file
				git commit -v -m 'remove unit test for '$TEST
				# push changes
				git push -v

			fi
		fi

	done
}

local -r SELECT=$(echo 'generate test\ndelete test' | fzy)

if   [[ $SELECT == 'generate test' ]]; then
	missing_test
elif [[ $SELECT == 'delete test' ]]; then
	missing_header
fi

exit 0
