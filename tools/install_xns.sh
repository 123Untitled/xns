#!/usr/bin/env -S zsh --no-rcs --no-globalrcs



# get current directory name
local DIR_NAME=${$(pwd):t}

# check current directory is 'xns'
if [[ $DIR_NAME != 'xns' ]]; then
	echo 'please run this script in 'xns' directory.'
	exit 1
fi

# check libxns.a exists
if [[ ! -f 'libxns.a' ]]; then
	echo 'libxns.a not found.'
	exit 1
fi

# check includes directory exists
if [[ ! -d 'includes' ]]; then
	echo "includes directory not found."
	exit 1
fi

# remove previous 'install' directory
if [[ -d 'install' ]]; then
	rm -rf 'install'
	echo 'removed previous install directory.'
fi

# create 'install' directories
if ! mkdir -p 'install/lib' 'install/include/'; then
	echo 'failed to create 'install' directories.'
	exit 1
fi

echo 'created install directories.'


# copy 'libxns.a' to 'install/lib' directory
if ! cp 'libxns.a' 'install/lib'; then
	echo 'failed to copy libxns.a.'
	exit 1
fi

echo 'copied libxns.a to install/lib directory.'

# copy includes to 'install/include' directory, but rename directory to 'xns'
if ! cp -r 'includes' 'install/include/'; then
	echo 'failed to copy includes directory.'
	exit 1
fi

if ! mv 'install/include/includes' 'install/include/xns'; then
	echo 'failed to rename includes directory.'
	exit 1
fi

echo 'copied includes to install/include/xns directory.'

# move into 'xns' directory
if ! cd 'install/include/xns'; then
	echo 'failed to move into install/include/xns directory.'
	exit 1
fi

# generate proxy header for each header file
local HEADERS=(**'/'*'.hpp'(.N))


local ASCII=\
'/*****************************************************************************/\n'\
'/*                                                                           */\n'\
'/*                       :::    ::: ::::    :::  ::::::::                    */\n'\
'/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */\n'\
'/*                      +:+  +:+  :+:+:+  +:+ +:+                            */\n'\
'/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */\n'\
'/*                    +#+  +#+  +#+  +#+#+#        +#+                       */\n'\
'/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */\n'\
'/*                 ###    ### ###    ####  ########                          */\n'\
'/*                                                                           */\n'\
'/*****************************************************************************/\n'

echo -e $ASCII > 'xns.hpp'
echo '#pragma once\n' >> 'xns.hpp'
echo '#ifndef XNS_HEADER' >> 'xns.hpp'
echo '#define XNS_HEADER\n' >> 'xns.hpp'


for HEADER in $HEADERS; do
	echo '#include "'$HEADER'"' >> 'xns.hpp'
done

echo '\n#endif // XNS_HEADER' >> 'xns.hpp'


for HEADER in $HEADERS; do
	# get basename of header file
	local BASENAME=${HEADER:t}
	echo -e $ASCII > $BASENAME
	echo '#include "'$HEADER'"' >> $BASENAME
done


