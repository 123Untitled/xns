#!/usr/bin/env zsh --no-rcs

# This script is used to generate a single header file for xns library.


# main color
color='\x1b[32m'
error='\x1b[31m'
reset='\x1b[0m'
erase='\x1b[1F\x1b[0J'



# -- C H E C K  R E Q U I R E D  P R O G R A M S ------------------------------

# required programs
programs=('clang++' 'tsort')
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

# get all subdirectories in inc
INC_DIRS=($(find 'inc' -type d))

# get all header files in inc
HEADERS=($(find 'inc' -type f -name '*.hpp'))

INCLUDES=()
# add -I flag for each header file
for header in ${INC_DIRS[@]}; do
	INCLUDES+=("-I$header")
done


FORMATED=

function parse {

	local content

	content=$(clang++ ${INCLUDES[@]} $1 -MT $1 -MM)
	#content=$(clang++ ${INCLUDES[@]} $1 -MT $1 -MM 2> /dev/null)

	if [[ $? -ne 0 ]]; then
		# print error message
		echo $error'Error:'$reset 'failed to parse' $error''$header''$reset
		# exit script
		exit 1
	fi

	#echo -n $color'.'$reset

	# split content into array
	words=(${=content})

	hpp=
	# loop over array
	for x in $words; do
		# get header file name
		if [[ $x == *":" ]]; then
			hpp=${x:0:-1}
		elif ! [[ $x == *"\\" ]]; then
			FORMATED+=$hpp' '$x'\n'
			#echo $hpp' '$x >> parsed.d
		fi
	done
}



ANIM=('-' '\' '|' '/')
I=1
# disable cursor
echo -n '\x1b[?25l'
echo -n 'Generating single header '
for header in ${HEADERS[@]}; do
	# print animation
	echo -n '['${ANIM[$I]}']'
	# move cursor right 3 characters
	echo -n '\x1b[3D'
	# increment animation index
	((++I))
	[[ $I -eq 5 ]] && I=1
	parse $header
done
# enable cursor
echo -n '\x1b[?25h'

echo '['$color'ok'$reset']'

# get tsort stdout and stderr in one variable without printing



TSORTED=$(echo $FORMATED | tsort 2>&1)

# check if tsort failed
if [[ $? -ne 0 ]]; then
	# print error message
	echo $error'Error:'$reset 'failed to sort header files.'
	# exit script
	#exit 1
fi

# check regex patter 'tsort: cycle in data'
if [[ $TSORTED =~ 'tsort: cycle in data' ]]; then
	# print error message
	echo $error'Error:'$reset 'failed to sort header files.'
	# exit script
	#exit 1
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
typeset -A system

# loop over all header files
for header in $FINAL; do
	# check if file exists
	if ! [[ -f $header ]]; then
		continue
	fi

	local content=$(<$header)

	# check if header file includes system header
	while [[ $content =~ '(#[[:space:]]*include[[:space:]]*<([^>]*)>)' ]]; do
		system[${match[2]}]=1
		# add header to system array
		content=${content/$match[1]/}
	done

done



# -- G E N E R A T E  S I N G L E  H E A D E R --------------------------------

# output file
output='xns.hpp'


file='namespace xns {'

# loop over all header files
for header in $FINAL; do
	# check if file exists
	if ! [[ -f $header ]]; then
		continue
	fi

	local content=$(<$header)
	# split by line
	local lines=( ${(@f)content} )

F=0
	# loop over all lines
	for line in $lines; do

		if [[ $F -eq 0 ]]; then
			if [[ $line =~ '^[[:space:]]*namespace[[:space:]]*xns[[:space:]]*{' ]]; then
				F=1
			fi
		else
			if [[ $line =~ "^}" ]]; then
				break
			else
				file+=$line$'\n'
				#echo -E $line >> $output_tmp
			fi
		fi

	done


done

file+='}'


# remove all comments
preprocessed=$(clang++ -std=c++2a -E -P -x c++ - <<< "$file")

# add include guard
echo -E '#ifndef XNS_SINGLE_HEADER' > $output
echo -E '#define XNS_SINGLE_HEADER' >> $output

# loop over all system headers
for header in ${(k)system}; do
	# add system header to output file
	echo '#include <'$header'>' >> $output
done

# append preprocessed variable to output file
echo -E $preprocessed >> $output

# end include guard
echo -E '#endif' >> $output





exit 0

