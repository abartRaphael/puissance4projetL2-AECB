#Project name (generate executable with this name)
TARGETS  = projet

CC       = gcc
#Compiling flags here
CFLAGS   = -Wall -I.

LINKER   = gcc
#Linking flags here
LFLAGS   = -Wall -I. -lm

#Change these to proper directories where each file should be
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin
TRGS	 := $(TARGETS:%=$(BINDIR)/%)

DIRS	 = $(OBJDIR) $(BINDIR) 

.PHONY: DIRS
all: $(DIRS) $(TRGS)

$(OBJDIR):
	mkdir -p $(OBJDIR)
$(BINDIR):
	mkdir -p $(BINDIR)

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
MAINS	 := $(TARGETS:%=$(OBJDIR)/%.o)


#Liste des fichiers .o sans ceux contenant un main
OBJS	 := $(filter-out $(MAINS),$(OBJECTS))
rm       = rm -f


#$(BINDIR)/$(TARGET): $(OBJECTS)
$(TRGS): $(OBJECTS)
	@$(LINKER) $(subst $(BINDIR),$(OBJDIR),$@).o $(OBJS) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGETS)
	@echo "Executable removed!"

.PHONY: doc
doc: 
	doxygen
	@echo "Doc complete"

