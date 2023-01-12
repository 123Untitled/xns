
# -- M A K E F I L E -----------------------------------------------------------

################################################################################
#        ▁▁▁▁▁▁▁▁  ▁▁▁▁▁▁▁▁  ▁▁▁▁ ▁▁▁  ▁▁▁▁▁▁▁▁                                #
#       ╱        ╲╱        ╲╱    ╱   ╲╱        ╲    language: makefile         #
#      ╱         ╱         ╱         ╱         ╱    author:   @tutur           #
#     ╱         ╱         ╱        ▁╱       ▁▁╱     created: 2020-05-01        #
#     ╲▁▁╱▁▁╱▁▁╱╲▁▁▁╱▁▁▁▁╱╲▁▁▁▁╱▁▁▁╱╲▁▁▁▁▁▁▁▁╱      updated: 2020-05-01        #
#                                                                              #
################################################################################


# -- V E R S I O N  C H E C K --------------------------------------------------

MINIMAL_VERSION := 4.2
ifneq ($(MINIMAL_VERSION), $(firstword $(sort $(MAKE_VERSION) $(MINIMAL_VERSION))))
	$(error $(shell echo "Please use \033[1;32mGNU Make 4.2\033[0m or later"))
endif


# -- S E T T I N G S -----------------------------------------------------------

.DEFAULT_GOAL := all
.ONESHELL:
.DELETE_ON_ERROR:

override SHELL := $(shell which zsh)

override MAKEFLAGS += --warn-undefined-variables --no-builtin-rules

# use thread to speed up the build process
#override MAKEFLAGS += -j$(shell sysctl -n hw.ncpu)


# -- O S   D E T E C T I O N ---------------------------------------------------

# Detect OPERATING SYSTEM
override OS := $(shell uname -s)

ifeq ($(OS), Darwin)
	override PLATFORM := macosx
else ifeq ($(OS), Linux)
	override PLATFORM := linux
else
	$(error $(shell echo "Unsupported OS: \033[1;32m$(OS)\033[0m"))
endif


# -- D I R E C T O R I E S ------------------------------------------------------

override SRCDIR := src
override INCDIR := inc
override OBJDIR := _obj
override DEPDIR := _dep
override JSNDIR := _jsn
override LIBDIR := _lib


# -- P R O G R A M  U T I L I T I E S -------------------------------------------

# check if 'fd' is installed
ifeq ($(shell which fd),)
	override FINDDIR := $(shell which find $(SRCDIR) -type d)
	override FINDSRC := $(shell which find $(SRCDIR) -type f -name '*.cpp')
else
	override FINDDIR := $(shell fd --full-path $(SRCDIR) --type directory --absolute-path)
	override FINDSRC := $(shell fd --full-path $(SRCDIR) --extension cpp --type file --absolute-path)
endif

MKDIR := mkdir -p

RM := rm -rvf



# -- C O M P I L E R  S E T T I N G S -------------------------------------------

CCX := $(shell which clang++)

AR := $(shell which ar)

ARFLAGS := -rcs

STD := -std=c++20

OPT := -O0

CXXFLAGS :=	-Wall -Wextra -Werror -Wpedantic \
			-Wno-unused -Wno-unused-variable -Wno-unused-parameter \
			-Winline

LDFLAGS ?=

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

CMPFLAGS = -MJ $(JSNDIR)/$*.json

INCLUDES := -I$(INCDIR)


# -- T A R G E T S --------------------------------------------------------------

DYNAMIC_LIB			= libxfunc.dylib
STATIC_LIB			= $(LIBDIR)/libxfunc.a
COMPILE_COMMANDS	= compile_commands.json


# -- S O U R C E S --------------------------------------------------------------

override SRC := $(FINDSRC)

override FILES := $(notdir $(SRC))

override SUB := $(dir $(SRC))

override OBJ := $(addprefix $(OBJDIR)/, $(FILES:%.cpp=%.o))

override DEP := $(addprefix $(DEPDIR)/, $(FILES:%.cpp=%.d))

override JSN := $(addprefix $(JSNDIR)/, $(FILES:%.cpp=%.json))


# -- F O R M A T T I N G --------------------------------------------------------

override RESET := "\x1b[0m"
override COLOR := "\x1b[1F\x1b[0J\x1b[3;31m"

EXA := exa -alB --bytes --icons --no-permissions --no-time --no-user --group-directories-first
FILE := file

define resume
	@echo "";
	@file $(1) | sed -e 's/^[^:]*://g' -e 's/^[ \t]*//g';
	@$(EXA) $(1);
endef



# -- M A I N  T A R G E T S -----------------------------------------------------

all: ascii $(DYNAMIC_LIB) $(COMPILE_COMMANDS)
	@echo $(COLOR)'[v]'$(RESET) "All targets are up to date !";
	$(call resume, $(DYNAMIC_LIB))


# -- L I B R A R Y  T A R G E T S -----------------------------------------------

$(DYNAMIC_LIB): obj | $(LIBDIR)
	@echo $(COLOR)Dynamic-Link$(RESET) $@;
	@$(CCX) $(OBJ) $(LDFLAGS) -dynamiclib -o $@;

$(STATIC_LIB): obj | $(LIBDIR)
	@echo $(COLOR)Static-Link$(RESET) $@;
	@$(AR) $(ARFLAGS) $@ $(OBJ);


# -- C O M P I L A T I O N ------------------------------------------------------

# call self with threads
obj:
	@$(MAKE) -s -j$(shell sysctl -n hw.ncpu) $(OBJ)

-include $(DEP)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp Makefile | $(OBJDIR) $(DEPDIR) $(JSNDIR)
	@echo $(COLOR)Compilation$(RESET) $<;
	@$(CCX) $(STD) $(OPT) $(CXXFLAGS) $(CMPFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@


# -- C O M P I L E  C O M M A N D S ---------------------------------------------

$(COMPILE_COMMANDS): obj
	@echo $(COLOR)Compile-Commands$(RESET) $@;
	@echo "[\n"$$(cat $(JSN) | sed '$$s/,\s*$$//')"\n]" | jq > $@


# -- D I R E C T O R I E S  C R E A T I O N -------------------------------------

$(OBJDIR) $(DEPDIR) $(JSNDIR) $(LIBDIR):
	@$(MKDIR) $@


# -- C L E A N I N G ------------------------------------------------------------

clean:
	@$(RM) $(OBJ) $(OBJDIR) $(DEP) $(DEPDIR) $(JSNDIR)

fclean: clean
	@$(RM) $(DYNAMIC_LIB) $(STATIC_LIB) $(LIBDIR) $(COMPILE_COMMANDS) .cache


# -- R E C O M P I L E ----------------------------------------------------------

re: fclean all


# -- A S C I I  A R T -----------------------------------------------------------

ascii:
	@echo \
		$(COLOR) \
		"   ▁▁▁▁▁▁▁▁  ▁▁▁▁▁▁▁▁  ▁▁▁▁ ▁▁▁  ▁▁▁▁▁▁▁▁	\n" \
		"  ╱        ╲╱        ╲╱    ╱   ╲╱        ╲	\n" \
		" ╱         ╱         ╱         ╱         ╱	\n" \
		"╱         ╱         ╱        ▁╱       ▁▁╱	\n" \
		"╲▁▁╱▁▁╱▁▁╱╲▁▁▁╱▁▁▁▁╱╲▁▁▁▁╱▁▁▁╱╲▁▁▁▁▁▁▁▁╱	\n\n" \
		$(RESET);


# -- P H O N Y  T A R G E T S ---------------------------------------------------

.PHONY: all clean fclean re ascii obj



