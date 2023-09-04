#!/usr/bin/env zsh --no-rcs

# this script is used to generate missing unit test files

CO='\x1b[31m'
CE='\x1b[32m'
NC='\x1b[0m'

GIT_DIR='xns'

XNS_INC_DIR='inc'
XNS_SRC_DIR='src'
TEST_DIR='test'
TEST_SRC_DIR=$TEST_DIR/'src'


SSH_REPO='git@github.com:123Untitled/xns.git'
PUB_REPO='https://github.com/123Untitled/xns.git'



# -- C H E C K  W O R K I N G  D I R E C T O R Y ------------------------------

# check if the script is run in a git repository
if [ ! -d .git ]; then
	echo 'Please run this script in the' $CO$GIT_DIR$NC 'repository.'
	exit 1
fi

# get the git repository name
GIT_REPO=$(git config --get remote.origin.url)

# check if the script is run in the right repository
if [[ $GIT_REPO != $SSH_REPO && $GIT_REPO != $PUB_REPO ]]; then
	echo 'Please run this script in the' $CO$GIT_DIR$NC 'repository.'
	exit 1
fi


# -- C H E C K  D I R E C T O R I E S -----------------------------------------

# check if the include directory exists
if [ ! -d $XNS_INC_DIR ]; then
	echo 'The' $CO$XNS_INC_DIR$NC 'directory does not exist.'
	exit 1
fi


# check if the unit test directory exists
if [ ! -d $TEST_SRC_DIR ]; then
	echo 'The' $CO$TEST_SRC_DIR$NC 'directory does not exist.'
	exit 1
fi


# -- C H E C K  G I T  S T A T U S --------------------------------------------

# check if there is staged files
git diff --cached --exit-code --quiet

# check status
if [ $? -ne 0 ]; then
	echo 'Please' $CE'commit'$NC 'or' $CE'stash'$NC 'your changes first.'
	exit 1
fi


# -- C H E C K  M I S S I N G  U N I T  T E S T  F I L E S --------------------

# get all header files
HEADERS=($XNS_INC_DIR/**/*.hpp(.N))
# get all unit test files
UNIT_TESTS=($TEST_SRC_DIR/**/*.cpp(.N))


# get basenames and remove extension
HEADERS=(${${HEADERS[@]##*/}[@]%'.hpp'})

# remove extensions
UNIT_TESTS=(${${UNIT_TESTS[@]##*/}[@]%'.cpp'})
# remove '_tests' suffix
UNIT_TESTS=(${(@)UNIT_TESTS%'_tests'})


# remove main
UNIT_TESTS=(${(@)UNIT_TESTS:#main})
# remove testclass
HEADERS=(${(@)HEADERS:#testclass})




function model {

	# check if there is one argument
	if [ $# -ne 1 ]; then
		echo 'Internal error: function' $CO'model'$NC 'expects one argument.'
		exit 1
	fi

	local FILE_NAME=$1

	# unit test file model
	UNIT_TEST_MODEL=\
"#include \"unit_tests.hpp\"
#include \"$FILE_NAME.hpp\"

/* unit test */
template <>
bool UT::unit_tests<\"$FILE_NAME\">(void) {
\t// code here...
\treturn false;
}

int main(void) {
\treturn UT::unit_tests<\"$FILE_NAME\">()
\t\t? EXIT_SUCCESS : EXIT_FAILURE;
}
"
	echo $UNIT_TEST_MODEL
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
		if [[ ! $UNIT_TESTS =~ $HEADER ]]; then
			# print message
			echo $CE$HEADER'_tests.cpp'$NC 'does not exist.'"\r"

			echo -n 'Generate file ? '
			if ! prompt; then
				continue
			fi

			# get the unit test file path
			local FILE_PATH=$TEST_SRC_DIR'/'$HEADER'_tests.cpp'

			# check if the unit test file already exists
			if [ -f $FILE_PATH ]; then
				echo 'Internal error: file' $CO$FILE_PATH$NC 'already exists.'
				exit 1
			fi

			# generate unit test file
			model $HEADER > $FILE_PATH

			# check if the unit test file was generated
			if [ $? -ne 0 ]; then
				echo 'Failed to generate' $CE$HEADER'_tests.cpp'$NC'.'
				exit 1
			fi

			# add unit test file to git
			git add -v $FILE_PATH
			# commit unit test file
			git commit -v -m "add unit test for $HEADER"
			# push changes
			git push -v

		fi
	done
}


function missing_header {

	# loop over all unit test files
	for UNIT in $UNIT_TESTS; do
		# check if the associated header file exist
		if [[ ! $HEADERS =~ $UNIT ]]; then
			# print message
			echo $CO$UNIT'_tests.cpp'$NC 'does not have an associated header file.'"\r"
			# find file path
			local FILE_PATH=$UT_DIR'/src/'$UNIT'_tests.cpp'
			# check if file exists
			if [ ! -f $FILE_PATH ]; then
				echo 'Internal error: file' $CO$FILE_PATH$NC 'does not exist.'
				exit 1
			fi
			# purpose to delete the unit test file
			echo -n 'Delete file ? '
			if prompt; then
				echo 'deleting file...'
			else
				echo 'keeping file...'
			fi
		fi

	done

}

missing_test
missing_header









