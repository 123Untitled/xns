#!/usr/bin/env -S zsh --no-rcs --errexit --pipefail

# This script is used to generate a single header file for xns library.


# main color
SUCCESS='\x1b[32m'
ERROR='\x1b[31m'
RESET='\x1b[0m'
ERASE='\x1b[1F\x1b[0J'



# -- C H E C K  R E Q U I R E D  P R O G R A M S ------------------------------

# required programs
programs=('shasum' 'mkdir')
#'clang++' 'tsort')
# loop through all required commands
for cmd in $programs; do
	# check if command is installed
	if [[ -z "$(command -v $cmd)" ]]; then
		# print error message
		echo $color'Error:'$reset 'required program' \
			$color''$cmd''$reset 'is not installed.'
		# exit script
		exit 1
	fi
done



# -- G E T  A L L  H E A D E R  F I L E S -------------------------------------


# output directory
OUT_DIR='xns'

# output file
OUT_FILE=$OUT_DIR'/xns.hpp'

# get all subdirectories in inc
INC_DIRS=('includes'/**/*(/N) 'includes')

# get all header files in inc
HEADERS=('includes'/**/*.'hpp'(.N))

INCLUDES=()
# add -I flag for each header file
for HEADER in $INC_DIRS; do
	INCLUDES+=("-I$HEADER")
done



mkdir -p $OUT_DIR

# -- P R E P R O C E S S  H E A D E R  F I L E S ------------------------------


FORMATED=




function parse {

	local FILE=$1
	local CONTENT=$(clang++ $INCLUDES $FILE -MT $FILE -MM)

	# split content into array
	local WORDS=(${=CONTENT})

	local HEADER=
	# loop over array
	for W in $WORDS; do
		# get header file name
		if [[ $W == *":" ]]; then
			HEADER=${W:0:-1}
		elif ! [[ $W == *"\\" ]]; then
			FORMATED+=$HEADER' '$W'\n'
		fi
	done
}



ANIM=('-' '\' '|' '/')
I=1
# disable cursor
echo -n '\x1b[?25l'
echo -n 'Generating single header '

for HEADER in $HEADERS; do
	# print animation
	echo -n '['${ANIM[$I]}']'
	# move cursor right 3 characters
	echo -n '\x1b[3D'
	# increment animation index
	((++I))
	[[ $I -eq 5 ]] && I=1
	parse $HEADER
done
# enable cursor
echo -n '\x1b[?25h'

echo '['$SUCCESS'ok'$RESET']'


# get tsort stdout and stderr in one variable without printing
TSORTED=$(echo $FORMATED | tsort 2>&1)


# check if tsort failed
if [[ $? -ne 0 ]]; then
	# print error message
	echo $error'Error:'$reset 'failed to sort header files.'
	exit 1
fi

# check regex patter 'tsort: cycle in data'
if [[ $TSORTED =~ 'tsort: cycle in data' ]]; then
	# print error message
	echo $error'Error:'$reset 'cyclic dependency in header files.'
	exit 1
fi


# zsh split string into lines
lines=(${(@f)TSORTED})

FINAL=()
# reverse order of lines
for ((i = $#lines; i > 0; --i)); do
	# add line to variable
	FINAL+=($lines[$i])
done


# -- G E N E R A T E  S I N G L E  H E A D E R --------------------------------


# system header associative array
typeset -A INC_SYSTEM

# loop over all header files
for HEADER in $FINAL; do

	local CONTENT=$(<$HEADER)

	# check if header file includes system header
	while [[ $CONTENT =~ '(#[[:space:]]*include[[:space:]]*<([^>]*)>)' ]]; do
		INC_SYSTEM[${match[2]}]=1
		# add header to system array
		CONTENT=${CONTENT/$match[1]/}
	done

done



# -- G E N E R A T E  S I N G L E  H E A D E R --------------------------------



OUT=''




function generate_file2 {

	# loop over all header files
	for HEADER in $FINAL; do

		# check if file exists
		if ! [[ -f $HEADER ]]; then
			continue
		fi

		# get file content
		local CONTENT=$(<$HEADER)
		# split by line
		local STRIPE=(${(@f)CONTENT})

		local REGEX='^[[:space:]]*#[[:space:]]*include[[:space:]]*".*"'

		# skip only local includes (e.g. #include "...")
		for L in $STRIPE; do
			if [[ $L =~ $REGEX ]]; then
				continue;
			else
				OUT+=$L$'\n'
			fi
		done

	done


}

generate_file2

# add include guard
echo -E '#ifndef XNS_SINGLE_HEADER' > $OUT_FILE
echo -E '#define XNS_SINGLE_HEADER' >> $OUT_FILE

echo -E $OUT >> $OUT_FILE

echo -E '#endif' >> $OUT_FILE

exit 0





# remove all comments
#preprocessed=$(clang++ -std=c++2a -E -P -dD -x c++ - <<< "$file")



# # loop over all system headers
# for HEADER in ${(k)INC_SYSTEM}; do
# 	# add system header to output file
# 	echo '#include <'$HEADER'>' >> $OUT_FILE
# done

# echo -E $file >> $OUT_FILE

# end include guard






# function generate_file {
#
# 	file='namespace xns {'
#
# 	# loop over all header files
# 	for header in $FINAL; do
# 		# check if file exists
# 		if ! [[ -f $header ]]; then
# 			continue
# 		fi
#
# 		local content=$(<$header)
# 		# split by line
# 		local lines=( ${(@f)content} )
#
# 	F=0
# 		# loop over all lines
# 		for line in $lines; do
#
# 			if [[ $F -eq 0 ]]; then
# 				if [[ $line =~ '^[[:space:]]*namespace[[:space:]]*xns[[:space:]]*{' ]]; then
# 					F=1
# 				fi
# 			else
# 				if [[ $line =~ "^}" ]]; then
# 					break
# 				else
# 					file+=$line$'\n'
# 					#echo -E $line >> $output_tmp
# 				fi
# 			fi
#
# 		done
#
#
# 	done
#
# 	file+='}'
# }
