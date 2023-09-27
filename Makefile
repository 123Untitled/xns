
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

# set default target
.DEFAULT_GOAL := all


# -- C O L O R  S E T T I N G S -----------------------------------------------

# set color variables
override C_ := \x1b[32m
override R_ := \x1b[0m


# -- F E A T U R E  C H E C K -------------------------------------------------

# check recipe prefix feature
ifeq ($(origin .RECIPEPREFIX), undefined)
    $(error $(shell echo "$(C_)Recipe prefix$(R_) feature is not supported"))
endif



# -- V E R S I O N  C H E C K -------------------------------------------------

# minimal version required
PREREQ := 4.2
VMIN   := $(firstword $(sort $(MAKE_VERSION) $(PREREQ)))

# compare version
ifneq ($(PREREQ), $(VMIN))
    $(error $(shell echo "Please use $(C_)GNU Make $(PREREQ)$(R_) or later"))
endif


# -- S E T T I N G S ----------------------------------------------------------


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

# check for macOSX
ifeq ($(OS), Darwin)
    override PLATFORM   := macosx
    override THREAD     := $(shell sysctl -n hw.ncpu)
# check for Linux
else ifeq ($(OS), Linux)
    override PLATFORM   := linux
    override THREAD     := $(shell nproc)
# unsupported OS
else
   $(error $(shell echo "Unsupported OS: \033[1;32m$(OS)\033[0m"))
endif


# -- D I R E C T O R I E S ----------------------------------------------------

# source directory
override SRCDIR := sources

# include directory
override INCDIR := includes

# library directory
override LIBDIR := lib

# build directory
override BLDDIR := build

# object directory
override OBJDIR := $(BLDDIR)/object

# dependency directory
override DEPDIR := $(BLDDIR)/dependency

# json directory
override JSNDIR := $(BLDDIR)/json


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
EXEC = exec_$(PROJECT)

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
			-Winline -Weffc++

# linker flags
LDFLAGS ?=

# dependency flags
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

# compile commands flags
CMPFLAGS = -MJ $(JSNDIR)/$*.json

# include flags
INCLUDES := $(addprefix -I,$(HDRDIR))

DEF ?=

# variable must be expanded at runtime
DEFINES = $(addprefix -D,$(DEF))





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
override COLOR := "\x1b[1;32m"
override ERASE := "\x1b[1F\x1b[0J"

# reset formatting
override RESET := "\x1b[0m"
override GREP  := grep --color=auto '^\w\+'


# -- P H O N Y  T A R G E T S -------------------------------------------------

# phony targets
.PHONY: all clean fclean re ascii obj exec lib static


EMOJI = 🚀
BUILD_MODE := release


# -- M A I N  T A R G E T S ---------------------------------------------------

all: ascii lib
	echo "$(EMOJI) [$(BUILD_MODE)] All targets are up to date !\n";


# executable target
exec: obj $(EXEC)

# library target
lib: static

# static library target
static: obj $(STATIC_LIB)


# -- L I B R A R Y  T A R G E T S ---------------------------------------------

$(EXEC): $(OBJ) $(COMPILE_COMMANDS)
	echo $(COLOR)executable link$(RESET) $@;
	$(CCX) $(LDFLAGS) $(OBJ) -o $@;
	file $(EXEC) | $(GREP); echo;

$(STATIC_LIB): $(OBJ) $(COMPILE_COMMANDS)
	echo $(COLOR)static library link$(RESET) $@;
	$(AR) $(ARFLAGS) $@ $(OBJ);
	file $(STATIC_LIB) | $(GREP); echo;


# -- C O M P I L A T I O N ----------------------------------------------------

# self call with threads
obj:
	$(MAKE) --silent -j$(THREAD) $(OBJ)
	echo $(ERASE)'🫠 All files compiled.\n';

-include $(DEP)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp Makefile | $(OBJHIR) $(DEPHIR) $(JSNHIR)
	echo $(ERASE)$(COLOR)compilation$(RESET) $<;
	$(CCX) $(STD) $(OPT) $(CXXFLAGS) $(DEFINES) $(CMPFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@


# -- C O M P I L E  C O M M A N D S -------------------------------------------

$(COMPILE_COMMANDS): $(JSN)
	echo $(COLOR)'database >'$(RESET) $@;
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
	$(RM) $(EXEC) $(STATIC_LIB) $(COMPILE_COMMANDS) .cache .env


# -- R E C O M P I L E --------------------------------------------------------

re: fclean all


# -- A S C I I  A R T ---------------------------------------------------------

ascii:
	echo \
		$(COLOR) \
		"   ▁▁▁▁▁▁▁▁  ▁▁▁▁▁▁▁▁  ▁▁▁▁ ▁▁▁  ▁▁▁▁▁▁▁▁	\n" \
		"  ╱        ╲╱        ╲╱    ╱   ╲╱        ╲	\n" \
		" ╱         ╱         ╱         ╱         ╱	\n" \
		"╱         ╱         ╱        ▁╱       ▁▁╱	\n" \
		"╲▁▁╱▁▁╱▁▁╱╲▁▁▁╱▁▁▁▁╱╲▁▁▁▁╱▁▁▁╱╲▁▁▁▁▁▁▁▁╱	\n" \
		'\t\t\tGNU Make'$(RESET)': '$(MAKE_VERSION)"\n\n";



