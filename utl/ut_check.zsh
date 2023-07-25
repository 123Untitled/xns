#!/bin/zsh

# this script is used to generate missing unit test files

CO='\x1b[31m'
CE='\x1b[32m'
NC='\x1b[0m'

GIT_DIR='xns'
INC_DIR='inc'
SRC_DIR='src'
UT_DIR='unit_tests'
REPO='git@github.com:123Untitled/xns.git'


# -- C H E C K  W O R K I N G  D I R E C T O R Y ------------------------------

# check if the script is run in a git repository
if [ ! -d .git ]; then
	echo 'Please run this script in the' $CO$GIT_DIR$NC 'repository.'
	exit 1
fi

# get the git repository name
GIT_REPO=$(git config --get remote.origin.url)

# check if the script is run in the right repository
if [ $GIT_REPO != $REPO ]; then
	echo 'Please run this script in the' $CO$GIT_DIR$NC 'repository.'
	exit 1
fi


# -- C H E C K  D I R E C T O R I E S -----------------------------------------

# check if the include directory exists
if [ ! -d $INC_DIR ]; then
	echo 'The' $CO$INC_DIR$NC 'directory does not exist.'
	exit 1
fi

# check if the source directory exists
if [ ! -d $SRC_DIR ]; then
	echo 'The' $CO$SRC_DIR$NC 'directory does not exist.'
	exit 1
fi

# check if the unit test directory exists
if [ ! -d $SRC_DIR'/'$UT_DIR ]; then
	echo 'The' $CO$SRC_DIR'/'$UT_DIR$NC 'directory does not exist.'
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
HEADERS=($INC_DIR'/'**'/'*'.hpp'(.N))
# get basenames and remove extension
HEADERS=(${${HEADERS[@]##*/}[@]%'.hpp'})

# get all unit test files
UNIT_TESTS=($SRC_DIR'/'$UT_DIR'/'**'/'*'.cpp'(.N))
# get basenames and remove '_tests' suffix and extension
UNIT_TESTS=(${${UNIT_TESTS[@]##*/}[@]%'_tests.cpp'})

# remove 'xns' 'testclass' 'type_trait' and 'unit_tests' from the header files
HEADERS=(${(@)HEADERS:#xns})
HEADERS=(${(@)HEADERS:#testclass})
HEADERS=(${(@)HEADERS:#type_traits})
HEADERS=(${(@)HEADERS:#unit_tests})



function model {

	# check if there is one argument
	if [ $# -ne 1 ]; then
		exit 1
	fi

	local FILE_NAME=$1

	# unit test file model
	UNIT_TEST_MODEL="#include \"unit_tests.hpp\"

/* unit test */
template <>
bool UT::unit_tests<\"$FILE_NAME\">(void) {
\t// start unit test
\tSTART_UT(\"$FILE_NAME\");
\t// code here...
\treturn false;
}
"

	echo $UNIT_TEST_MODEL
}


# loop over all header files
for HEADER in $HEADERS; do
	# check if the unit test file exists
	if [[ ! $UNIT_TESTS =~ $HEADER ]]; then
		# print message
		echo 'Generating' $CE$HEADER'_tests.cpp'$NC'.'

		continue
		# get the unit test file path
		local FILE_PATH=$SRC_DIR'/'$UT_DIR'/'$HEADER'_tests.cpp'
		# generate unit test file
		model $HEADER > $FILE_PATH
		# check if the unit test file was generated
		if [ $? -ne 0 ]; then
			echo 'Failed to generate' $CE$HEADER'_tests.cpp'$NC'.'
			exit 1
		fi
		# add unit test file to git
		git add $FILE_PATH
		# commit unit test file
		git commit -m "add unit test for $HEADER"

	else
		echo $CO$HEADER'_tests.cpp'$NC 'already exists.'
		continue
	fi
done










