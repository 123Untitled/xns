#!/bin/zsh

# this script is used to generate new c++ class

# options: -h: generate header file    [.hpp]
#          -t: generate template file  [.hpp]
#          -s: generate source file    [.cpp]
#          -u: generate unit test file [.cpp]

# usage: ./new_class.sh -[ahstu] <class_name>

CO='\x1b[31m'
CE='\x1b[32m'
NC='\x1b[0m'

GIT_DIR='xns'
INCDIR='includes'
SRCDIR='sources/core'
TSTDIR='sources/tests/src'
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


# -- C H E C K  A R G U M E N T S ---------------------------------------------

# check for empty argument
if [ $# -ne 2 ]; then
	echo 'Usage: ./new_class.zsh [-'$CO'htsu'$NC'] <'$CO'class_name'$NC'>.'
	exit 1
fi

# check for valid option
if [[ ! $1 =~ ^-[htsu]*$ ]]; then
	echo 'Invalid' $CO'option'$NC'.'
	exit 1
fi


# remove duplicate options
OPTIONS=(${(u)${(s::)1}})

# rules for options:
# if -h is present, cannot have -t
# if -s is present, cannot have -t
# if -t is present, cannot have -h or -s

# check for -t, -h, and -s
if [[ $OPTIONS =~ 't' && $OPTIONS =~ 'h' && $OPTIONS =~ 's' ]]; then
	echo 'you need to choose between' $CO'template'$NC 'and' $CO'header'$NC'/'$CO'source'$NC'.'
	exit 1
fi

# check for -t and -s
if [[ $OPTIONS =~ 't' && $OPTIONS =~ 's' ]]; then
	echo 'you need to choose between' $CO'template'$NC 'and' $CO'source'$NC'.'
	exit 1
fi

# check for -t and -h
if [[ $OPTIONS =~ 't' && $OPTIONS =~ 'h' ]]; then
	echo 'you need to choose between' $CO'template'$NC 'and' $CO'header'$NC'.'
	exit 1
fi

# check for valid class name
if [[ ! $2 =~ ^[a-zA-Z_][a-zA-Z0-9_]*$ ]]; then
	echo 'Invalid '$CO'class'$NC 'name.'
	exit 1
fi

# class name
CLASS_NAME=$2







# namespace name
NAMESPACE='xns'

# to upper case
UPPER_CLASS_NAME=${(U)CLASS_NAME}

# add space between each character
SPACED_CLASS_NAME=${(j: :)${(s::)UPPER_CLASS_NAME}}

# replace all underscores with spaces
CLEANED_CLASS_NAME=${SPACED_CLASS_NAME// _ /'  '}

# generate fill line after class name for header file
FILL_LINE_HEADER=''
for i in {1..$((68 - ${#CLEANED_CLASS_NAME}))}; do
	FILL_LINE_HEADER+='-'
done

# generate fill line after class name for source file
FILL_LINE_SOURCE=''
for i in {1..$((72 - ${#CLEANED_CLASS_NAME}))}; do
	FILL_LINE_SOURCE+='-'
done





# -- H E A D E R  F I L E  M O D E L ------------------------------------------

# header file model
HEADER_MODEL="#ifndef "$UPPER_CLASS_NAME"_HPP
#define "$UPPER_CLASS_NAME"_HPP


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace "$NAMESPACE" {


\t// -- "$CLEANED_CLASS_NAME" "$FILL_LINE_HEADER"

\tclass "$CLASS_NAME" final {


\t\tpublic:

\t\t\t// -- public constructors -----------------------------------------

\t\t\t/* default constructor */
\t\t\t"$CLASS_NAME"(void) noexcept;

\t\t\t/* copy constructor */
\t\t\t"$CLASS_NAME"(const ""$CLASS_NAME""&) noexcept;

\t\t\t/* move constructor */
\t\t\t"$CLASS_NAME"(""$CLASS_NAME""&&) noexcept;

\t\t\t/* destructor */
\t\t\t~"$CLASS_NAME"(void) noexcept;


\t\t\t// -- public assignment operators ---------------------------------

\t\t\t/* copy assignment operator */
\t\t\t"$CLASS_NAME"& operator=(const "$CLASS_NAME"&) noexcept;

\t\t\t/* move assignment operator */
\t\t\t"$CLASS_NAME"& operator=("$CLASS_NAME"&&) noexcept;


\t\tprivate:

\t\t\t// -- private members ---------------------------------------------

\t};

}

#endif
"



# -- S O U R C E  F I L E  M O D E L ------------------------------------------

# source file model
SOURCE_MODEL="#include \""$CLASS_NAME".hpp\"


// -- "$CLEANED_CLASS_NAME" "$FILL_LINE_SOURCE"


// -- public constructors -----------------------------------------------------

/* default constructor */
"$NAMESPACE"::"$CLASS_NAME"::"$CLASS_NAME"(void) noexcept
//:
{
\t// code here...
}

/* copy constructor */
"$NAMESPACE"::"$CLASS_NAME"::"$CLASS_NAME"(const "$CLASS_NAME"& other) noexcept
//:
{
\t// code here...
}

/* move constructor */
"$NAMESPACE"::"$CLASS_NAME"::"$CLASS_NAME"("$CLASS_NAME"&& other) noexcept
//:
{
\t// code here...
}

/* destructor */
"$NAMESPACE"::"$CLASS_NAME"::~"$CLASS_NAME"(void) noexcept {
\t// code here...
}


// -- public assignment operators ---------------------------------------------

/* copy assignment operator */
"$NAMESPACE"::"$CLASS_NAME"& "$NAMESPACE"::"$CLASS_NAME"::operator=(const "$CLASS_NAME"& other) noexcept {
\t// check for self assignment
\tif (this != &other) {
\t} // return self reference
\treturn *this;
}

/* move assignment operator */
"$NAMESPACE"::"$CLASS_NAME"& "$NAMESPACE"::"$CLASS_NAME"::operator=("$CLASS_NAME"&& other) noexcept {
\t// check for self assignment
\tif (this != &other) {
\t} // return self reference
\treturn *this;
}
"


# -- T E M P L A T E  F I L E  M O D E L --------------------------------------

# template file model
TEMPLATE_MODEL="#ifndef "$UPPER_CLASS_NAME"_HPP
#define "$UPPER_CLASS_NAME"_HPP


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace "$NAMESPACE" {


	// -- "$CLEANED_CLASS_NAME" "$FILL_LINE_HEADER"

	template <class T>
	class "$CLASS_NAME" final {


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = "$CLASS_NAME"<T>;

			/* value type */
			using value_type = T;


			// -- public constructors -----------------------------------------

			/* default constructor */
			"$CLASS_NAME"(void) noexcept
			//:
			{
				// code here...
			}

			/* copy constructor */
			"$CLASS_NAME"(const self& other) noexcept
			//:
			{
				// code here...
			}

			/* move constructor */
			"$CLASS_NAME"(self&& other) noexcept
			//:
			{
				// code here...
			}

			/* destructor */
			~"$CLASS_NAME"(void) noexcept {
				// code here...
			}


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			self& operator=(const self& other) noexcept {
				// check for self assignment
				if (this != &other) {
				} // return self reference
				return *this;
			}

			/* move assignment operator */
			self& operator=(self&& other) noexcept {
				// check for self assignment
				if (this != &other) {
				} // return self reference
				return *this;
			}


		private:

			// -- private members ---------------------------------------------

	};

}

#endif
"

# unit test file model
UNIT_TEST_MODEL="#include \"unit_tests.hpp\"


// -- "$CLEANED_CLASS_NAME" "$FILL_LINE_SOURCE"

/* unit test */
template <>
bool unit_test<\"$CLASS_NAME\">(void) {
\t// start unit test
\tSTART_UT(\"$CLASS_NAME\");
	// code here...
	return false;
}
"

# get all source files
SRC_FILES=($SRCDIR/**/*.cpp(.N))
# get all source files basename
SRC_FILES=(${SRC_FILES[@]##*/})
# get all header files
HEADER_FILES=($INCDIR/**/*.hpp(.N))
# get all header files basename
HEADER_FILES=(${HEADER_FILES[@]##*/})


# source generator
function gen_source {
	# file to generate
	local FILE=$CLASS_NAME'.cpp'
	# check file already exists
	if [[ $SRC_FILES =~ $FILE ]]; then
		echo $CE$FILE$NC' already exists'
		exit 1
	fi
	# generate file
	echo -n "$SOURCE_MODEL" >> $SRCDIR'/'$FILE && echo $CO$FILE$NC 'source file generated.'
	#echo $CO$FILE$NC 'source file generated.'
}

# header generator
function gen_header {
	# file to generate
	local FILE="$CLASS_NAME".hpp
	# check if file exists
	if [[ $HEADER_FILES =~ $FILE ]]; then
		echo $CE$FILE$NC' already exists'
		exit 1
	fi
	# generate file
	echo -n "$HEADER_MODEL" >> $INCDIR'/'$FILE && echo $CO$FILE$NC 'header file generated.'
	#echo $CO$FILE$NC 'header file generated.'

}

# template generator
function gen_template {
	# file to generate
	local FILE="$CLASS_NAME".hpp
	# check if file exists
	if [[ $HEADER_FILES =~ $FILE ]]; then
		echo $CE$FILE$NC' already exists'
		exit 1
	fi
	# generate file
	echo -n "$TEMPLATE_MODEL" >> $INCDIR'/'$FILE && echo $CO$FILE$NC 'template file generated.'
	#echo $CO$FILE$NC 'template file generated.'
}

# unit test generator
function gen_unit_test {
	# file to generate
	local FILE=$TSTDIR'/_'$CLASS_NAME'.cpp'
	# check if file exists
	if (-f $file) {
		echo $CE$FILE$NC 'already exists'
		exit 1
	}
	# generate file
	echo -n "$UNIT_TEST_MODEL" >> $DIR'/'$FILE && echo $CO$FILE$NC 'unit test file generated.'
	#echo $CO$FILE$NC 'unit test file generated.'
}


# -- C H E C K  F I L E  E X I S T E N C E ------------------------------------

FUNCTIONS=()

# check for header file
[[ $OPTIONS =~ 'h' ]] && FUNCTIONS+=('gen_header')

# check for template file
[[ $OPTIONS =~ 't' ]] && FUNCTIONS+=('gen_template')

# check for source file
[[ $OPTIONS =~ 's' ]] && FUNCTIONS+=('gen_source')

# check for unit test file
[[ $OPTIONS =~ 'u' ]] && FUNCTIONS+=('gen_unit_test')



# -- G E N E R A T E  F I L E S -----------------------------------------------

for FUNCTION in $FUNCTIONS; do
	$FUNCTION
done
