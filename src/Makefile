CXX = g++
CXXINCDIRS = -I. -I./ext/glui/include
SRCDIR = ./src
OBJDIR = ./obj
INCDIR = ./include
BINDIR = ./bin
EXE = $(BINDIR)/FlashPhoto
CXXFLAGS += $(CXXINCDIRS)
CXXFLAGS += -std=c++11 -isystem./ext/glui/include -isystem./ext/jpeg-9a -isystem./ext/libpng-1.6.16
CXXLIBDIRS = -lglut -lGL -lGLU -L./ext/lib -lglui -lpng -ljpeg -lz

SRC_CXX = $(wildcard $(SRCDIR)/*.cc)
OBJECTS_CXX = $(patsubst $(SRCDIR)/%.cc, $(OBJDIR)/%.o, $(SRC_CXX))

# For dependency check
make-depend-cxx=$(CXX) -MM -MF $3 -MP -MT $2 $(CXXFLAGS) $1

# These are the targets that aren't actually files
.PHONY: all clean veryclean

all: $(EXE)

# For dependency check
ifneq "$MAKECMDGOALS" "clean"
-include $(addprefix $(OBJDIR)/,$(notdir $(OBJECTS_CXX:.o=.d)))
endif

$(EXE): $(OBJECTS_CXX) | $(BINDIR) gluimake
	$(MAKE) -C./ext/jpeg-9a all install
	$(CXX) -o $@ $^	$(CXXLIBDIRS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cc | $(OBJDIR)
	@$(call make-depend-cxx,$<,$@,$(subst .o,.d,$@))
	$(CXX) $(CXXFLAGS) -c -o  $@ $<

$(BINDIR) $(OBJDIR):
	mkdir -p $@

gluimake:
	$(MAKE) -C ./ext/glui

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

veryclean: clean
	$(MAKE) -C ./ext/glui clean
