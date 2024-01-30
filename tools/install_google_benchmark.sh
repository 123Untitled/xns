#!/usr/bin/env -S zsh --no-rcs --no-globalrcs

# This script is used to install google benchmark

# -- V A R I A B L E S --------------------------------------------------------

# get pwd without external command
ROOT=${0:a:h:h}

# required packages
REQUIRED_PKG=('git' 'openssl' 'cmake')

# url of repository
REPO_URL='https://github.com/google/benchmark.git'

# path of repository
REPO_PATH=$ROOT'/'$(openssl sm3 <<< $REPO_URL)

# install path
INSTALL_PATH=$ROOT'/external/google_benchmark'


# -- C H E C K  P A C K A G E S -----------------------------------------------

# check required packages
for PKG in $REQUIRED_PKG; do
	if ! command -v $PKG &> /dev/null; then
		echo 'error:' $PKG 'could not be found :('
		exit 1
	fi
done


# -- C L O N E  R E P O -------------------------------------------------------

# remove old repo
if [ -d $REPO_PATH ]; then
	rm -rf $REPO_PATH
fi

# clone repo
if ! git clone -v $REPO_URL $REPO_PATH; then
	echo 'error: failed to clone google benchmark repository :('
	exit 1
fi


# -- I N S T A L L ------------------------------------------------------------

# create install path
mkdir -p $INSTALL_PATH

# move into repository
cd $REPO_PATH

# make build directory
if ! cmake -E make_directory 'build'; then
	echo 'error: failed to create build directory :('
	rm -rf $REPO_PATH
	exit 1
fi

# configure flags
local FLAGS=('-DBENCHMARK_DOWNLOAD_DEPENDENCIES=on'
			 '-DCMAKE_BUILD_TYPE=Release')

# configure
if ! cmake -E chdir 'build' cmake  $FLAGS -DCMAKE_INSTALL_PREFIX=$INSTALL_PATH '..'; then
	echo 'error: failed to configure google benchmark :('
	rm -rf $REPO_PATH
	exit 1
fi

# build library
if ! cmake --build 'build' --config Release; then
	echo 'error: failed to build google benchmark :('
	rm -rf $REPO_PATH
	exit 1
fi

# test library
if ! cmake -E chdir 'build' ctest --build-config Release; then
	echo 'error: failed to test google benchmark :('
	rm -rf $REPO_PATH
	exit 1
fi

# install library
if ! cmake --build 'build' --config Release --target install; then
	echo 'error: failed to install google benchmark :('
	rm -rf $REPO_PATH
	exit 1
fi


cd '..'

# remove repository
rm -rf $REPO_PATH



# copy library
#cp 'build/src/libbenchmark.a' 'build/src/libbenchmark_main.a' $INSTALL_PATH'/lib'



# Debug vs Release
# By default, benchmark builds as a debug library.
# You will see a warning in the output when this is the case.
# To build it as a release library instead, add -DCMAKE_BUILD_TYPE=Release when generating the build system files, as shown above.
# The use of --config Release in build commands is needed to properly support multi-configuration tools (like Visual Studio for example)
# and can be skipped for other build systems (like Makefile).
# To enable link-time optimisation, also add -DBENCHMARK_ENABLE_LTO=true when generating the build system files.
# If you are using gcc, you might need to set GCC_AR and GCC_RANLIB cmake cache variables, if autodetection fails.
# If you are using clang, you may need to set LLVMAR_EXECUTABLE, LLVMNM_EXECUTABLE and LLVMRANLIB_EXECUTABLE cmake cache variables.
# To enable sanitizer checks (eg., asan and tsan), add:

# -DCMAKE_C_FLAGS="-g -O2 -fno-omit-frame-pointer -fsanitize=address -fsanitize=thread -fno-sanitize-recover=all"
# -DCMAKE_CXX_FLAGS="-g -O2 -fno-omit-frame-pointer -fsanitize=address -fsanitize=thread -fno-sanitize-recover=all "

