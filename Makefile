
# -- M A K E F I L E ----------------------------------------------------------

###############################################################################
#        ▁▁▁▁▁▁▁▁  ▁▁▁▁▁▁▁▁  ▁▁▁▁ ▁▁▁  ▁▁▁▁▁▁▁▁                               #
#       ╱        ╲╱        ╲╱    ╱   ╲╱        ╲    language: makefile        #
#      ╱         ╱         ╱         ╱         ╱    author:   @tutur          #
#     ╱         ╱         ╱        ▁╱       ▁▁╱     created:  2020-05-01      #
#     ╲▁▁╱▁▁╱▁▁╱╲▁▁▁╱▁▁▁▁╱╲▁▁▁▁╱▁▁▁╱╲▁▁▁▁▁▁▁▁╱      updated:  2020-05-01      #
#                                                                             #
###############################################################################

# dependencies:
# GNU Make 4.2 or later
# clang++ 10.0.0 or later
# zsh 5.7.1 or later
# GNU ar 2.34 or later
# GNU find 4.7.0 or later


# -- V E R S I O N  C H E C K -------------------------------------------------

# minimal version required
MINIMAL_VERSION := 4.2

# compare version
ifneq ($(MINIMAL_VERSION), $(firstword $(sort $(MAKE_VERSION) $(MINIMAL_VERSION))))
 $(error $(shell echo "Please use \033[1;32mGNU Make $(MINIMAL_VERSION)\033[0m or later"))
endif


# -- S E T T I N G S ----------------------------------------------------------

# set default target
.DEFAULT_GOAL := all

# use one shell for all commands
.ONESHELL:

# delete intermediate files on error
.DELETE_ON_ERROR:

# silent mode
.SILENT:

# set shell program
override SHELL := $(shell which zsh)

# set shell flags
.SHELLFLAGS := -d -f -c -e -o pipefail -u

# set make flags
override MAKEFLAGS += --warn-undefined-variables --no-builtin-rules


# -- O P E R A T I N G  S Y S T E M -------------------------------------------



# Detect operating system
override OS := $(shell uname -s)

# exit if OS is not supported
ifeq ($(OS), Darwin)
 override PLATFORM := macosx
 override DLIB := -dynamiclib
 override THREAD := $(shell sysctl -n hw.ncpu)
 override DLIB_EXT := dylib
else ifeq ($(OS), Linux)
 override PLATFORM := linux
 override DLIB := -shared
 override THREAD := $(shell nproc)
 override DLIB_EXT := so
else
 $(error $(shell echo "Unsupported OS: \033[1;32m$(OS)\033[0m"))
endif


# -- D I R E C T O R I E S ----------------------------------------------------

# source directory
override SRCDIR := src

# include directory
override INCDIR := inc

# library directory
override LIBDIR := lib

# build directory
override BLDDIR := _bld

# object directory
override OBJDIR := $(BLDDIR)/_obj

# dependency directory
override DEPDIR := $(BLDDIR)/_dep

# json directory
override JSNDIR := $(BLDDIR)/_json


# -- S O U R C E S ------------------------------------------------------------

# get all source files
override SRC := $(shell find $(SRCDIR) -type f -name '*.cpp')

# get all header files
override HDR := $(shell find $(INCDIR) -type f -name '*.hpp')

# get all header directories
override HDRDIR := $(sort $(dir $(HDR)))


# -- P R O G R A M  U T I L I T I E S -----------------------------------------

# make directory if not exists
MKDIR := mkdir -p

# remove recursively force
RM := rm -rf


# -- T A R G E T S ------------------------------------------------------------

# project name
PROJECT = xns

# main executable
EXEC = $(PROJECT)exec

# dynamic library
DYNAMIC_LIB = lib$(PROJECT).$(DLIB_EXT)

# static library
STATIC_LIB = lib$(PROJECT).a

# compile commands for clangd
COMPILE_COMMANDS = compile_commands.json


# -- C O M P I L E R  S E T T I N G S -----------------------------------------

# compiler
CCX := $(shell which clang++)

#CCX := /opt/homebrew/Cellar/gcc/12.2.0/bin/g++-12

# archiver
AR := $(shell which ar)

# archiver flags
ARFLAGS := -rcs

# compiler standard
STD := -std=gnu++2b

# compiler optimization
OPT := -O0 -g3

# compiler flags
CXXFLAGS :=	-Wall -Wextra -Werror -Wpedantic \
			-Wno-unused -Wno-unused-variable -Wno-unused-parameter \
			-Winline -fno-exceptions -Weffc++ -Wno-gnu-string-literal-operator-template

# linker flags
LDFLAGS ?=

# dependency flags
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

# compile commands flags
CMPFLAGS = -MJ $(JSNDIR)/$*.json

# include flags
INCLUDES := $(addprefix -I,$(HDRDIR))

DEF ?=

DEFINES := $(addprefix -D,$(DEF))





# pattern substitution for object files
override OBJ := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o,    $(SRC))

# pattern substitution for dependency files
override DEP := $(patsubst $(OBJDIR)/%.o,   $(DEPDIR)/%.d,    $(OBJ))

# pattern substitution for compile commands
override JSN := $(patsubst $(SRCDIR)/%.cpp, $(JSNDIR)/%.json, $(SRC))

#
override HIR := $(sort $(dir $(SRC)))
override OBJHIR := $(HIR:$(SRCDIR)/%=$(OBJDIR)/%)
override DEPHIR := $(HIR:$(SRCDIR)/%=$(DEPDIR)/%)
override JSNHIR := $(HIR:$(SRCDIR)/%=$(JSNDIR)/%)


# -- F O R M A T T I N G ------------------------------------------------------

# formatting (erase line, move cursor up, set color)
override COLOR := "\x1b[3;31m"
override ERASE := "\x1b[1F\x1b[0J\x1b[3;31m"

# reset formatting
override RESET := "\x1b[0m"
override GREP := grep --color=auto '^\w\+'


# -- B U I L D  M O D E -------------------------------------------------------

# build mode
override MODE ?= debug


# -- P H O N Y  T A R G E T S -------------------------------------------------

# phony targets
.PHONY: all clean fclean re ascii obj exec lib dynamic static debug development change


# -- M A I N  T A R G E T S ---------------------------------------------------

all: development
	echo $(COLOR)'🚀'$(RESET) "All targets are up to date !";

development:
	$(MAKE) --silent ascii exec

debug:
	$(MAKE) --silent ascii exec DEF='XNS_UT META_UT'


# executable target
exec:		obj $(EXEC) $(COMPILE_COMMANDS)

# library target
lib:		dynamic static

# dynamic library target
dynamic:	obj $(DYNAMIC_LIB) $(COMPILE_COMMANDS)

# static library target
static:		obj $(STATIC_LIB) $(COMPILE_COMMANDS)


# -- L I B R A R Y  T A R G E T S ---------------------------------------------

$(EXEC): $(OBJ)
	echo $(COLOR)Exec-Link$(RESET) $@;
	$(CCX) $(LDFLAGS) $(OBJ) -o $@;
	file $(EXEC) | $(GREP); echo;

$(DYNAMIC_LIB): $(OBJ)
	echo $(COLOR)Dynamic-Link$(RESET) $@;
	$(CCX) $(OBJ) $(LDFLAGS) $(DLIB) -o $@;
	file $(DYNAMIC_LIB) | $(GREP); echo;

$(STATIC_LIB): $(OBJ)
	echo $(COLOR)Static-Link$(RESET) $@;
	$(AR) $(ARFLAGS) $@ $(OBJ);
	file $(STATIC_LIB) | $(GREP); echo;


# -- C O M P I L A T I O N ----------------------------------------------------

# self call with threads
obj:
	$(MAKE) --silent -j$(THREAD) $(OBJ)
	echo $(ERASE)'🫠'$(RESET) "All files compiled.\n";

-include $(DEP)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp Makefile | $(OBJHIR) $(DEPHIR) $(JSNHIR)
	echo $(ERASE)Compilation$(RESET) $<;
	$(CCX) $(STD) $(OPT) $(CXXFLAGS) $(DEFINES) $(CMPFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@


# -- C O M P I L E  C O M M A N D S -------------------------------------------

$(COMPILE_COMMANDS): $(JSN)
	echo $(COLOR)'jq >'$(RESET) $@;
	echo "[\n"$$(cat $(JSN) | sed '$$s/,\s*$$//')"\n]" | jq > $@
	file $(COMPILE_COMMANDS) | $(GREP); echo;


# -- D I R E C T O R I E S  C R E A T I O N -----------------------------------

$(OBJHIR) $(DEPHIR) $(JSNHIR):
	$(MKDIR) $@

# -- C L E A N I N G ----------------------------------------------------------

clean:
	echo $(COLOR)'[x]'$(RESET) "Cleaned";
	$(RM) $(BLDDIR) $(PROJECT).dSYM

fclean: clean
	echo $(COLOR)'[x]'$(RESET) "Full cleaned";
	$(RM) $(EXEC) $(DYNAMIC_LIB) $(STATIC_LIB) $(COMPILE_COMMANDS) .cache


# -- R E C O M P I L E --------------------------------------------------------

re: fclean all


# -- C H A N G E  T A R G E T -------------------------------------------------

# rule to change the build mode (debug, development, release)
# usage: make change MODE=release
# use sed to change the line in the Makefile (all: debug, development, release)

change:
	sed -i 's/all:.*$$/all: $(MODE)/' Makefile


# -- A S C I I  A R T ---------------------------------------------------------

ascii:
	echo \
		$(COLOR) \
		"   ▁▁▁▁▁▁▁▁  ▁▁▁▁▁▁▁▁  ▁▁▁▁ ▁▁▁  ▁▁▁▁▁▁▁▁	\n" \
		"  ╱        ╲╱        ╲╱    ╱   ╲╱        ╲	\n" \
		" ╱         ╱         ╱         ╱         ╱	\n" \
		"╱         ╱         ╱        ▁╱       ▁▁╱	\n" \
		"╲▁▁╱▁▁╱▁▁╱╲▁▁▁╱▁▁▁▁╱╲▁▁▁▁╱▁▁▁╱╲▁▁▁▁▁▁▁▁╱	\n\n" \
		$(RESET);

