################################################################################
# Name            : Makefile
# Project         : FlashPhoto
# Description     : Main Makefile
# Creation Date   : Fri May 16 14:59:49 2014
# Original Author : jharwell
#
# Note: This file is -j (parallel build) safe, provided you don't mess with it
# too much.
#
#  Products:
#  Make Target     Product                  Description
#  ===========     =======                  ===================
#  all             bin/FlashPhoto           The main executable
#  clean           N/A                      Removes excutable, all .o
#  veryclean       N/A                      Everything clean removes, +
#                                           the external libraries
#  bin/FlashPhoto  bin/FlashPhoto           The main executable
#  documentation   Various                  Generates documentation for
#                                           project from the doxygen
#                                           comments/markup in the code
################################################################################

###############################################################################
# Directory Definitions
###############################################################################
# src/      - Root of the source tree for the project
# build/    - Root directory for project build process
# ext/      - Direcotry for all external libraries
# ext/lib/  - Directory for installation of all external libraries
# doc/      - Directory where all documentation lives
# config/   - Directory for all autoconf/configure/automake inputs/output
BUILDDIR        = ./build
SRCDIR          = ./src
BINDIR          = bin
OBJDIR          = $(BUILDDIR)/obj
EXTDIR          = ./ext
GLUIDIR         = $(EXTDIR)/glui
JPEGDIR         = $(EXTDIR)/jpeg-9a
PNGDIR          = $(EXTDIR)/libpng-1.6.16
DOCDIR          = ./doc
EXTLIBDIR       = $(EXTDIR)/lib
CONFIGDIR       = ./config

###############################################################################
# Definitions
###############################################################################

# Tell make we want to execute all commands using bash (otherwise it uses
# sh). make generally works best with bash, and as SHELL is inherited from the
# invoking shell when make is run, it may have a value like sh, tcsh, etc. If
# you don't do this, then some shell commands will not behave as you
# expect. This is in keeping with the principle of least surprise.
SHELL           = bash

###############################################################################
# C++ Compilation Options
###############################################################################

# This is the list of directories to search during the linking step for
# external libraries (such as GLUI) that are NOT in one of the pre-defined
# locations on linux, such as /usr/lib, /lib, etc.
CXXLIBDIRS ?= -L$(EXTDIR)/lib

# Define the list of include directories during compilation. Lines MUST end
# with a backslash (\). This syntax is the way to define multi-line variables
# in make.
#
# Using -isystem instead of -I tells the compiler to treat all includes in
# that directory as system includes, and suppress all resulting warnings from
# them. This is EXTREMELY useful when compiling external libraries (such as
# GLUI) that we do not have control over.
define CXXINCDIRS
-I. \
-I$(SRCDIR) \
-isystem$(GLUIDIR)/include \
-isystem$(JPEGDIR) \
-isystem$(PNGDIR)
endef

# Specify the compiler flags to use when compiling. Note the use of fopenmp in
# order to enable OpenMP pragmas in the code.
define CXXFLAGS
$(OPT) -g -W -Wall -Wextra -Weffc++ -Wshadow \
-Wold-style-cast -Wswitch-default -std=gnu++11 -Wno-unused-parameter $(CXXINCDIRS)
endef

# In general, note that the order libraries are specified to the linker
# MATTERS. If a library is specified too early on the command line, which can
# happen when:
# 1. It is specified on the command line before the linker processes any
#    source files that contain references to it
# 2. It is specified on the command line with the libraries to link against
#    before another library that contains references to it.
#
# In both these cases the linker will "drop" the library and you will see
# unresolved reference errors.
#
# In general, you should put MORE general/base libraries at the end, and the
# libraries that depend on them BEFORE the base library. (i.e. link libglui
# before libmath via -lglui -lm).
#
# For graphics support, we also need to link with the Glut and OpenGL libraries.
# This is specified differently depending on whether we are on linux or OSX.
UNAME = $(shell uname)
ifeq ($(UNAME), Darwin) # Mac OSX
CXXLIBS = -framework glut -framework opengl -lglui
else # LINUX
CXXLIBS = -lglut -lGL -lGLU -lglui
CXXFLAGS += -fopenmp
endif

# On some lab machines the glut and opengl libraries are located in the directory
# where the nvidia graphics driver was installed rather than the default /usr/lib
# directory.  In this case, we need to tell the linker to search this nvidia directory
# for libraries as well.  Uncomment the line below.
#NVIDIA_LIB =  /usr/lib/nvidia-304  #or whichever nvidia driver number shows up in that dir
ifneq ($(NVIDIA_LIB), )
CXXLIBS += -L$(NVIDIA_LIB)
endif
CXXLIBS += -ljpeg -lpng -lm -lpthread -lz

# Define the compiler to use
CXX         = g++

# Define the optimization level to use when compiling. Only change this if you
# know what you are doing, as sometimes turning on the compiler optimizer,
# while it may speed certain parts of your code up, it also can make code that
# worked at -O0 no longer work. If you are curious as to why this might be,
# John has the details.
OPT         = -O0

###############################################################################
# Functions
###############################################################################
# Recursive wildcard: search a list of directories for all files that match a pattern
# usage: $(call rwildcard, $(DIRS1) $(DIRS2) ..., pattern)
#
# All directory lists passed as first arg must be separated by spaces, and they
# themselves must be space separated as well. There must NOT be a space between
# the last dir list the , and the start of the pattern.
#
# You should never need to modify this.
# usage: $(call rwildcard, $(DIRS1) $(DIRS2) ..., pattern)
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2)  $(filter $(subst *,%,$2),$d))

# make-depend: generate dependencies for C++ source files dynamically. Very useful
# for including .h files as target dependencies.
# usage: $(call make-depend,source-file,object-file,depend-file)
#
# You should never need to modify this.
# usage: $(call make-depend,source-file,object-file,depend-file)
make-depend-cxx=$(CXX) -MM -MF $3 -MP -MT $2 $(CXXFLAGS) $1

###############################################################################
# Target Definitions
###############################################################################
# Define what directories to search for source code. For us, this will just
# be a single source directory, src/.
SOURCES = $(SRCDIR)

# Define the list of files to compile for this project, which is built by
# recursively finding all .cc files in src/.
SRC_CXX = $(call rwildcard,$(SOURCES),*.cc)

# For each of the .cc files found under src/, determine the name of the
# corresponding .o file to create in obj/ via pattern substitution (patsust).
OBJECTS_CXX = $(notdir $(patsubst %.cc,%.o,$(SRC_CXX)))

# The target executable (what you are building)
TARGET = $(BINDIR)/FlashPhoto

###############################################################################
# All targets
###############################################################################

# Phony targets: targets of this type will be run everytime by make (i.e. make
# does not assume that the target recipe will build the target name)
.PHONY: clean veryclean all documentation

# The default target which will be run if the user just types "make" with a
# target name
all: $(TARGET)

# Unless invoked with make clean, include generated dependencies. This makes
# it so that anytime you make an edit in a .h file, make will know that all
# .cc files that include are out of date and will need to be recompiled.
#
# $(MAKECMDGOALS) is a special make variable that contains a space separated
# list of variables that make was told to build.
ifneq "$MAKECMDGOALS" "clean"
-include $(addprefix $(OBJDIR)/,$(OBJECTS_CXX:.o=.d))
endif

# The Objectifier. This rule says that each .o file in obj/, depends on the
# presence of the obj/ directory. This is necessary so that parallel make
# (make -j) works. Also, some .o files depend on .cc files that in turn depend
# on header files generated by building external libraries, so add them as
# dependencies as well.
$(addprefix $(OBJDIR)/, $(OBJECTS_CXX)): | $(OBJDIR) $(EXTDIR)/lib/libpng.a $(EXTDIR)/lib/libjpeg.a

# The Target Executable. Note that libglui is an order-only prerequisite, in
# that as long as it exists, make will not attempt to recompile it. This makes
# sense; once you build GLUI, you should never have to rebuild it.
$(TARGET): $(addprefix $(OBJDIR)/, $(OBJECTS_CXX)) | $(BINDIR) $(EXTDIR)/lib/libglui.a
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) $(addprefix $(OBJDIR)/, $(OBJECTS_CXX)) -o $@ $(CXXLIBS)

# GLUI
# Making this target causes make to be invoking a second time. This is called
# a sub-make or recursive make call. The $(MAKE) variable is special in make,
# and using it instead of just "make" will call make again with the exact same
# arguments used to call THIS make process. This is very useful to easily pass
# command line arguments to sub-makes.
$(EXTDIR)/lib/libglui.a:
	@$(MAKE) -C$(GLUIDIR) install
$(EXTDIR)/lib/libjpeg.a:
	@$(MAKE) -C$(JPEGDIR) install
$(EXTDIR)/lib/libpng.a:
	@$(MAKE) -C$(PNGDIR) install

# Bootstrap Bill. This creates all of the order-only prerequisites; that is,
# files/directories that have to be present in order for a given target build
# to succeed, but that make knows do not need to be remade each time their
# modification time is updated and they are newer than the target being built.
$(BINDIR) $(OBJDIR) $(BUILDDIR):
	@mkdir -p $@

# The Cleaner. Clean up the project, by removing ALL files generated during
# the build process to build the main target.
clean:
	@rm -rf $(BUILDDIR) $(CONFIGDIR)/autom4te.cache $(CONFIGDIR)/config.log $(CONFIGDIR)/config.guess $(CONFIGDIR)/config.status

# The Super Cleaner. Clean the project, but also clean all external libraries.
veryclean: clean
	-@$(MAKE) -C$(GLUIDIR) clean uninstall
	-@$(MAKE) -C$(JPEGDIR) clean uninstall
	-@$(MAKE) -C$(PNGDIR) clean uninstall
	@rm -rf $(BUILDDIR) $(CONFIGDIR)/autom4te.cache $(CONFIGDIR)/config.log $(CONFIGDIR)/config.guess $(CONFIGDIR)/config.status share

# The Documenter. Generate documentation for the project.
documentation:
	cd $(DOCDIR) && doxygen Doxyfile
	cd ..

###############################################################################
# Pattern Rules
###############################################################################
# For compiling the C++ source. Specify that any .o file in obj/ can be built
# from any .cc file in src/. Before doing compilation, emit (possibly) make
# rules for the includes for the .cc file, as they may have changed since the
# last invocation of make.
$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	@$(call make-depend-cxx,$<,$@,$(subst .o,.d,$@))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c -o  $@ $<
