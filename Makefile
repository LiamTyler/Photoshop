CXX = g++
CXXINCDIRS = -I. -I./ext/glui/include
SRCDIR = ./src
OBJDIR = ./obj
INCDIR = ./include
EXE = brushwork
CXXFLAGS += $(CXXINCDIRS)
CXXFLAGS += -std=c++11
CXXLIBDIRS = -lglut -lGL -lGLU -lglui -L./ext/glui/lib

SRC_CXX = $(wildcard $(SRCDIR)/*.cc)
OBJECTS_CXX = $(patsubst $(SRCDIR)/%.cc, $(OBJDIR)/%.o, $(SRC_CXX))

# For dependency check
make-depend-cxx=$(CXX) -MM -MF $3 -MP -MT $2 $(CXXFLAGS) $1

# These are the targets that aren't actually files
.PHONY: clean all 

all: $(EXE)

# For dependency check
ifneq "$MAKECMDGOALS" "clean"
-include $(addprefix $(OBJDIR)/,$(notdir $(OBJECTS_CXX:.o=.d)))
endif

$(EXE): $(OBJECTS_CXX) | $(BINDIR)
	$(CXX) -o $@ $^	$(CXXLIBDIRS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cc | $(OBJDIR)
	@$(call make-depend-cxx,$<,$@,$(subst .o,.d,$@))
	$(CXX) $(CXXFLAGS) -c -o  $@ $<

$(BINDIR) $(OBJDIR):
	mkdir -p $@

clean:
	rm -rf $(OBJDIR)
