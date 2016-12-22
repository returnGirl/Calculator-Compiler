CC := gcc
SRCDIR := src
BUILDDIR := build
TESTDIR := test
TARGET := bin/Calc
TARGETDIR := bin

SRCEXT := c
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
INC := -I include
STATIC_ANALYZER := oclint
TESTLIB := -lgtest -lgtest_main -lpthread

$(TARGET) : $(OBJECTS)
	@echo " Linking "
	@mkdir -p bin
	@echo " $(CC) $^ -o $(TARGET) $(LIB) $(LINKER)"; $(CC) $^ -o $(TARGET)

$(BUILDDIR)/%.o : $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(INC) $(LIB) -c -o $@ $<"; $(CC) $(INC) -c -o $@ $<

static-analyze:
	$(STATIC_ANALYZER) $(SOURCES) -- -c $(INC) $(LIB)

clean:
	@echo " Cleaning... "
	@echo " rm -rf $(BUILDDIR) $(TARGETDIR)/*"; rm -rf $(BUILDDIR) $(TARGETDIR)/*


.PHONY: clean
