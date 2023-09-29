
# -- M A K E F I L E ----------------------------------------------------------

###############################################################################
#        ▁▁▁▁▁▁▁▁  ▁▁▁▁▁▁▁▁  ▁▁▁▁ ▁▁▁  ▁▁▁▁▁▁▁▁                               #
#       ╱        ╲╱        ╲╱    ╱   ╲╱        ╲    language: makefile        #
#      ╱         ╱         ╱         ╱         ╱    author:   @tutur          #
#     ╱         ╱         ╱        ▁╱       ▁▁╱     created:  2020-05-01      #
#     ╲▁▁╱▁▁╱▁▁╱╲▁▁▁╱▁▁▁▁╱╲▁▁▁▁╱▁▁▁╱╲▁▁▁▁▁▁▁▁╱      updated:  2020-05-01      #
#                                                                             #
###############################################################################



# -- F O R M A T T I N G ------------------------------------------------------

# formatting (erase line, move cursor up, set color)
override COLOR := "\x1b[1;32m"
override ERASE := "\x1b[1F\x1b[0J"

# reset formatting
override RESET := "\x1b[0m"
override GREP  := grep --color=auto '^\w\+'



# -- V E R S I O N  C H E C K -------------------------------------------------

# minimal version required
PREREQ := 4.2
VMIN   := $(firstword $(sort $(MAKE_VERSION) $(PREREQ)))

# compare version
ifneq ($(PREREQ), $(VMIN))
    $(error $(shell echo "Please use $(C_)GNU Make $(PREREQ)$(R_) or later"))
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



# -- T A R G E T S ------------------------------------------------------------

# project name
override PROJECT = xns

# main executable
override EXEC = exec_$(PROJECT)

# static library
override STATIC_LIB = lib$(PROJECT).a

# single header
override SINGLE_HEADER = $(PROJECT).hpp

# compile commands for clangd
override COMPILE_COMMANDS = compile_commands.json



# -- D I R E C T O R I E S ----------------------------------------------------

# source directory
override SRCDIR := sources

# include directory
override INCDIR := includes

# release directory
override RLSDIR := $(PROJECT)

# build directory
override BLDDIR := build

# scripts directory
override SCRDIR := scripts

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










# -- C O M P I L E R  S E T T I N G S -----------------------------------------

# single header script
override SHS := $(SCRDIR)/single_header.sh

# make directory if not exists
override MKDIR := mkdir -p

# remove recursively force
override RM := rm -rf

# compiler
override CCX := $(shell which clang++)

# archiver
override AR := $(shell which ar)

# archiver flags
override ARFLAGS := -rcs

# compiler standard
override STD := -std=c++2a

# compiler optimization
override OPT := -O0 -g3

# warning scope
override CXXFLAGS :=	-Wall -Wextra

# warning impact
override CXXFLAGS += -Werror

# standard respect
override CXXFLAGS += -Wpedantic -Weffc++

# unused suppression
override CXXFLAGS += -Wno-unused -Wno-unused-variable -Wno-unused-parameter

# optimization
override CXXFLAGS += -Winline

# type conversion
override CXXFLAGS += -Wconversion -Wsign-conversion -Wfloat-conversion -Wnarrowing

# shadowing
override CXXFLAGS += -Wshadow

# linker flags
override LDFLAGS ?=

# dependency flags
override DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

# compile commands flags
override CMPFLAGS = -MJ $(JSNDIR)/$*.json

# include flags
override INCLUDES := $(addprefix -I,$(HDRDIR))

# command line defines
DEF ?=

# defines flags
override DEFINES := $(addprefix -D,$(DEF))




# -- P H O N Y  T A R G E T S -------------------------------------------------

# phony targets
.PHONY: all clean fclean re ascii obj exec lib static


# snow emoji
EMOJI = 🚀
BUILD_MODE := release


# -- M A I N  T A R G E T S ---------------------------------------------------

all: ascii static
	echo "$(EMOJI) [$(BUILD_MODE)] All targets are up to date !\n";

# static library target
static: obj $(RLSDIR)/$(STATIC_LIB) $(RLSDIR)/$(SINGLE_HEADER)


# -- L I B R A R Y  T A R G E T S ---------------------------------------------

$(RLSDIR)/$(SINGLE_HEADER): $(HDR) Makefile | $(RLSDIR)
	echo '#ifndef XNS_HEADER\n#define XNS_HEADER\n' > $@
	for file in $(HDR); do
		BASE=$${file:t};
		echo '#include "inc/'$$BASE'"' >> $@;
	done
	echo '\n#endif' >> $@
	mkdir -p $(RLSDIR)/inc
	cp $(HDR) $(RLSDIR)/inc
	echo $(COLOR)single header$(RESET) $@;


$(RLSDIR)/$(STATIC_LIB): $(OBJ) $(COMPILE_COMMANDS) | $(RLSDIR)
	echo $(COLOR)static library link$(RESET) $@;
	$(AR) $(ARFLAGS) $@ $(OBJ);
	file $(RLSDIR)/$(STATIC_LIB) | $(GREP); echo;


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

$(OBJHIR) $(DEPHIR) $(JSNHIR) $(RLSDIR):
	$(MKDIR) $@

# -- C L E A N I N G ----------------------------------------------------------

clean:
	echo $(COLOR)'[x]'$(RESET) 'cleaned';
	$(RM) $(BLDDIR) $(PROJECT).dSYM

fclean: clean
	echo $(COLOR)'[x]'$(RESET) 'full cleaned';
	$(RM) $(EXEC) $(STATIC_LIB) $(RLSDIR) $(COMPILE_COMMANDS) .cache .env


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



