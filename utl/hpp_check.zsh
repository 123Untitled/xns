#!/bin/zsh

CO='\x1b[33m'
NC='\x1b[0m'

# This script is used to check if all .hpp files in inc directory are included in inc/xns.hpp

INC_DIR='inc'
XNS_FILE='xns.hpp'
XNS_HEADER=$INC_DIR'/'$XNS_FILE


# -- C H E C K  I F  I N C / X N S . H P P  E X I S T S -----------------------

# check if inc directory exists
if [ ! -d $INC_DIR ]; then
	echo $CO$INC_DIR$NC' directory does not exist'
	exit 1
# check if inc/xns.hpp exists
elif [ ! -f $XNS_HEADER ]; then
	echo $CO$XNS_FILE$NC' does not exist'
	exit 1
# check if inc/xns.hpp is readable
elif [ ! -r $XNS_HEADER ]; then
	echo $CO$XNS_FILE$NC' is not readable'
	exit 1
# check if inc/xns.hpp is empty
elif [ ! -s $XNS_HEADER ]; then
	echo $CO$XNS_FILE$NC' is empty'
	exit 1
fi

echo $INC_DIR'/'$CO$XNS_FILE$NC' exists and is readable.'

# get inc/xns.hpp content splitted by lines
XNS_CONTENT=("${(@f)$(<inc/xns.hpp)}")

# extract all included files
INCLUDED_FILES=()

# loop through all lines to find regex matches
for LINE in $XNS_CONTENT; do
	if [[ $LINE =~ ^#include\ \"(.*)\"$ ]]; then
		INCLUDED_FILES+=($match[1])
	fi
done

# sort the array
INCLUDED_FILES=("${(@o)INCLUDED_FILES}")


# -- G E T  H E A D E R S  F I L E S ------------------------------------------

# get all .hpp files recursively in inc directory
PROJECT_HEADERS=($INC_DIR/**/*.hpp(.N))

# check if there is any file
if [ -z "$PROJECT_HEADERS" ]; then
	echo 'No '$CO'.hpp'$NC' files in '$CO$INC_DIR$NC' directory'
	exit 1
fi

# keep only the basename of the files
PROJECT_HEADERS=("${PROJECT_HEADERS[@]##*/}")

# sort the array
PROJECT_HEADERS=("${(@o)PROJECT_HEADERS}")



# -- C O M P A R E  A R R A Y S -----------------------------------------------

# get longest string length
MAX_LENGTH=0
for FILE in $PROJECT_HEADERS; do
	if [ ${#FILE} -gt $MAX_LENGTH ]; then
		MAX_LENGTH=${#FILE}
	fi
done

# missing files
MISSING_FILES=()

# check if all files in inc/xns.hpp are in inc directory
for FILE in $PROJECT_HEADERS; do
	if [[ ! " ${INCLUDED_FILES[@]} " =~ " ${FILE} " ]]; then
		MISSING_FILES+=($FILE)
		printf "%-${MAX_LENGTH}s%s\n" $FILE ' is not included in '$XNS_FILE
	fi
done

# check if there is any missing file
if [ -z "$MISSING_FILES" ]; then
	echo 'All '$CO'.hpp'$NC' files in '$CO$INC_DIR$NC' directory are included in '$CO$XNS_FILE$NC
	exit 0
else
	exit 1
fi



# to be implemented...


exit 0






