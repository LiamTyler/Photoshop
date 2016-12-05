################################################################################
# Name            : Makefile
# Project         : Image Processing Suite
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
#  all             various                The main executables
#
#  clean           N/A                      Removes excutables, all .o
#  veryclean       N/A                      Everything clean removes, +
#                                           the external libraries
#  documentation   Various                  Generates documentation for
#                                           project from the doxygen
#                                           comments/markup in the code
################################################################################

###############################################################################
# Directory Definitions
###############################################################################
# src/      - Root of the source tree for the project
# build/    - Root directory for project build process
# doc/      - Directory where all documentation lives
# config/   - Directory for all autoconf/configure/automake inputs/output
# tests/    - Root of test code directory
export BUILDROOT = $(realpath ./build)
export SRCROOT   = $(realpath ./src)
export SRCDIR   = ./src
export EXTDIR   = $(realpath ./ext)
export GLUIDIR  = $(EXTDIR)/glui
export JPEGDIR  = $(EXTDIR)/jpeg-9a
export PNGDIR   = $(EXTDIR)/libpng-1.6.16
export LIBIMGTOOLS_DIR = $(realpath $(SRCROOT)/lib/libimgtools)
export BINDIR   = $(BUILDROOT)/bin
export LIBDIR   = $(BUILDROOT)/lib
CONFIGDIR       = ./config
DOCDIR          = ./doc
CXXTESTDIR      = $(EXTDIR)/cxxtest-4.4
TESTDIR         = ./tests

###############################################################################
# Definitions
###############################################################################

# Tell make we want to execute all commands using bash (otherwise it uses
# sh). make generally works best with bash, and as SHELL is inherited from the
# invoking shell when make is run, it may have a value like sh, tcsh, etc. If
# you don't do this, then some shell commands will not behave as you
# expect. This is in keeping with the principle of least surprise.
export SHELL           = bash

###############################################################################
# C++ Compilation Options
###############################################################################

# Define the compiler to use
export CXX         = g++

# Define the optimization level to use when compiling. Only change this if you
# know what you are doing, as sometimes turning on the compiler optimizer,
# while it may speed certain parts of your code up, it also can make code that
# worked at -O0 no longer work. If you are curious as to why this might be,
# John has the details.
export OPT         = -O0

# Specify the compiler flags to use when compiling. Note the use of fopenmp in
# order to enable OpenMP pragmas in the code.
define CXXFLAGS
$(OPT) -g -W -Wall -Wextra -Weffc++ -Wshadow -Wfloat-equal \
-Wold-style-cast -Wswitch-default -std=gnu++11 -Wno-unused-parameter $(CXXINCDIRS)
endef
export CXXFLAGS


# This is the list of directories to search during the linking step for
# external libraries (such as GLUI) that are NOT in one of the pre-defined
# locations on linux, such as /usr/lib, /lib, etc.
export CXXLIBDIRS = -L$(LIBDIR) -L$(EXTDIR)/lib -L/usr/local/lib


# Define the list of include directories during compilation. Lines MUST end
# with a backslash (\). This syntax is the way to define multi-line variables
# in make.
#
# Using -isystem instead of -I tells the compiler to treat all includes in
# that directory as system includes, and suppress all resulting warnings from
# them. This is EXTREMELY useful when compiling external libraries (such as
# GLUI) that we do not have control over.
define CXXINCDIRS
-I$(SRCROOT) \
-isystem/usr/local/include \
-isystem$(GLUIDIR)/include \
-isystem$(JPEGDIR) \
-isystem$(PNGDIR)
endef
export CXXINCDIRS

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
# For graphics support, we also need to link with the Glut and OpenGL
# libraries.
# This is specified differently depending on whether we are on linux or OSX.
UNAME = $(shell uname)
ifeq ($(UNAME), Darwin) # Mac OSX
CXXLIBS += -limgtools # FIXME: UNCOMMENT THIS LINE WHEN LIMGTOOLS WORKS
CXXLIBS += -ljpeg -lpng -lz -framework glut -framework opengl -lglui 
else # LINUX
CXXLIBS += -limgtools # FIXME: UNCOMMENT THIS LINE WHEN LIMGTOOLS WORKS
CXXLIBS +=  -lpng -ljpeg -lz -lGL -lGLU -lglui -lglut 
CXXFLAGS += -fopenmp
endif

# On some lab machines the glut and opengl libraries are located in the
# directory
# where the nvidia graphics driver was installed rather than the default
# /usr/lib
# directory.  In this case, we need to tell the linker to search this nvidia
# directory
# for libraries as well.  Uncomment the line below.
#NVIDIA_LIB =  /usr/lib/nvidia-304  #or whichever nvidia driver number shows
# up in that dir
ifneq ($(NVIDIA_LIB), )
CXXLIBS += -L$(NVIDIA_LIB)
endif

export CXXLIBS

###############################################################################
# All targets
###############################################################################

# Phony targets: targets of this type will be run everytime by make (i.e. make
# does not assume that the target recipe will build the target name)
.PHONY: clean veryclean all documentation libimgtools FlashPhoto MIA install

# The default target which will be run if the user just types "make" without a
# target name
all: libimgtools FlashPhoto MIA

install: all
	$(MAKE) -C$(LIBIMGTOOLS_DIR)
	$(MAKE) -Csrc/app/MIA install
	$(MAKE) -Csrc/app/FlashPhoto install

libimgtools: | $(EXTDIR)/lib/libpng.a $(LIBDIR)
	$(MAKE) -C$(LIBIMGTOOLS_DIR) install

$(EXTDIR)/lib/libglui.a:
	$(MAKE) -C$(GLUIDIR) install
$(EXTDIR)/lib/libpng.a:
	$(MAKE) -C$(PNGDIR) install
$(EXTDIR)/lib/libjpeg.a:
	$(MAKE) -C$(JPEGDIR) install

FlashPhoto: $(EXTDIR)/lib/libglui.a $(EXTDIR)/lib/libpng.a $(EXTDIR)/lib/libjpeg.a libimgtools | $(BINDIR)
	$(MAKE) -Csrc/app/FlashPhoto
MIA: $(EXTDIR)/lib/libglui.a $(EXTDIR)/lib/libpng.a $(EXTDIR)/lib/libjpeg.a libimgtools | $(BINDIR)
	$(MAKE) -Csrc/app/MIA

# Bootstrap Bill. This creates all of the order-only prerequisites; that is,
# files/directories that have to be present in order for a given target build
# to succeed, but that make knows do not need to be remade each time their
# modification time is updated and they are newer than the target being built.
$(BINDIR) $(OBJDIR) $(LIBDIR) $(BUILDROOT):
	mkdir -p $@

# The Cleaner. Clean up the project, by removing ALL files generated during
# the build process to build the main target.
clean:
	@rm -rf $(BUILDROOT)
	@rm -rf $(TESTDIR)/tester.cc $(TESTDIR)/tester

# The Super Cleaner. Clean the project, but also clean all external libraries.
veryclean: clean
	@rm -rf $(BUILDROOT)
	@rm -rf $(EXTDIR)/lib
	@$(MAKE) -C$(GLUIDIR) clean
	@$(MAKE) -C$(PNGDIR) clean
	@$(MAKE) -C$(JPEGDIR) clean

# The Documenter. Generate documentation for the project.
documentation:
	cd $(DOCDIR) && doxygen Doxyfile
	cd ..
