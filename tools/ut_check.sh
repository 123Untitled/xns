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


# -- C H E C K  W O R K I N G  D I R E C T O R Y ------------------------------

# check if the script is run in a git repository
if [ ! -d .git ]; then
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
if [ ! -d $INCDIR ]; then
	echo 'the' $CO$INCDIR$NC 'directory does not exist.'
	exit 1
fi


# check if the unit test directory exists
if [ ! -d $TSTDIR ]; then
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






function model {

	# check if there is one argument
	if [ $# -ne 1 ]; then
		exit 1
	fi

	# unit test file model
	local MODEL=\
'#include "unit_tests.hpp"\n'\
'#include "'$1'.hpp"\n\n'\
'/* unit test */\n'\
'int unit_tests_'$1'(void) {\n'\
'\treturn 0;\n'\
'}\n\n'\
'#if defined(XNS_TEST_'${1:u}')\n'\
'int main(void) {\n'\
'\treturn unit_tests_'$1'();\n'\
'}\n'\
'#endif\n'

	echo $MODEL
}


function prompt {
	echo -n '[y/n] ? '

	while true; do
		# read one character
		read -k 1 -s INPUT
		# echo
		if   [[ $INPUT =~ '[yY]' ]]; then
			echo 'yes.'
			return 0
		elif [[ $INPUT =~ '[nN]' ]]; then
			echo 'no.'
			return 1
		elif [[ $INPUT =~ '[qQ]' ]]; then
			echo 'abort.'
			exit 0
		fi
	done
	# never reach this point
}




function missing_test {

	# loop over all header files
	for HEADER in $HEADERS; do

		# check if the associated unit file exist
		if [[ ! -v UTABLE[$HEADER] ]]; then

			# print message
			echo -n $CE'_'$HEADER'.cpp'$NC 'does not exist, generating it ? '

			if prompt; then

				# get the unit test file path
				local FILE_PATH=$TSTDIR'/_'$HEADER'.cpp'

				# check if the unit test file already exists
				if [ -f $FILE_PATH ]; then
					exit 1
				fi

				# generate unit test file
				model $HEADER > $FILE_PATH

				# add unit test file to git
				git add -v $FILE_PATH
				# commit unit test file
				git commit -v -m "add unit test for $HEADER"
				# push changes
				git push -v
			fi

		fi
	done
}


function missing_header {

	# loop over all unit test files
	for TEST in $TESTS; do
		# check if the associated header file exist
		if [[ ! -v HTABLE[$TEST] ]]; then

			# print message
			echo -n $CO'_'$TEST'.cpp'$NC 'is not associated to a header file, delete it ? '

			if prompt; then

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

missing_header
missing_test
