################################################################################
# Name            : Makefile
# Project         : Project
# Description     : Makefile Template
# Creation Date   : Fri May 16 14:59:49 2014
# Original Author : jharwell
#
# Note: This file is -j (parallel build) safe, provided you don't mess with it
# too much.
#
#  Products:
#  Make Target     Product                  Description
#  ===========     =======                  ===================
#  all             lib/libglui.a
#  clean           N/A                      Removes all compiled files/objects
################################################################################

###############################################################################
# Directory Definitions
###############################################################################
# src/      - Root of the source tree for the project
# lib/      - Directory where libraries are built, if applicable
# obj/      - Directory where all object files are built

SRCDIR          = ./src
OBJDIR          = ./obj
LIBDIR          = ./lib
INSTALLDIR      = ../lib

###############################################################################
# Definitions
###############################################################################

# Tell make we want to execute all commands using bash (otherwise it uses sh)
SHELL           = bash

###############################################################################
# C++ Compilation Options
###############################################################################

# We don't have control over GLUI, so suppress all compiler warnings its
# headers may generate
define CXXINCDIRS
-Iinclude
endef

CXXFLAGS = $(OPT) -w $(CXXINCDIRS)

CXX         = g++
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
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2)  $(filter $(subst *,%,$2),$d))

###############################################################################
# Target Definitions
###############################################################################
# Define what directories to search for source code
SOURCES    = $(SRCDIR)

# Define the list of files to compile for this project
SRC_CXX    = $(call rwildcard,$(SOURCES),*.cpp)

# For each of the .cpp files found above, determine the name of the
# corresponding .o file to create.
OBJECTS_CXX  = $(notdir $(patsubst %.cpp,%.o,$(SRC_CXX)))

# The target executable (what you are building)
TARGET = $(LIBDIR)/libglui.a

###############################################################################
# All targets
###############################################################################

# Phony targets: targets of this type will be run everytime by make (i.e. make
# does not assume that the target recipe will build the target name)
.PHONY: clean veryclean install uninstall

# The default target
all: $(TARGET)

# The installer
install: $(TARGET) | $(INSTALLDIR)
	cp $(TARGET) $(INSTALLDIR)

# The uninstaller
uninstall:
	rm -rf $(INSTALLDIR)/libglui.a

# The Target Library
$(addprefix $(OBJDIR)/, $(OBJECTS_CXX)): | $(OBJDIR)
$(TARGET): $(addprefix $(OBJDIR)/, $(OBJECTS_CXX)) | $(LIBDIR)
	ar -r $@ $(addprefix $(OBJDIR)/, $(OBJECTS_CXX))

# Bootstrap Bill. This creates all of the order-only prerequisites; that is,
# files/directories that have to be present in order for a given target build
# to succeed, but that make knows do not need to be remade each time their
# modification time is updated and they are newer than the target being built.
$(OBJDIR) $(LIBDIR) $(INSTALLDIR):
	@mkdir -p $@

# The Cleaner
clean:
	@rm -rf $(LIBDIR) $(OBJDIR)

###############################################################################
# Pattern Rules
###############################################################################
# For compiling the C++ source. Specify that any .o file in the object
# directory can be build
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@$(call make-depend-cxx,$<,$@,$(subst .o,.d,$@))
	$(CXX) $(CXXFLAGS) -c -o  $@ $<
