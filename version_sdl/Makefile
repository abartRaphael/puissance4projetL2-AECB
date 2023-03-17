#Project name (generate executable with this name)
TARGETS  = puissance4_sdl

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
LIBDIR = lib
TRGS	 := $(TARGETS:%=$(BINDIR)/%)

DIRS	 = $(OBJDIR) $(BINDIR) 

#répertoires de SDL2
SDL_DIR=${HOME}/SDL2
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include/

LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I${SDL_INC_DIR} 

.PHONY: DIRS
all: $(DIRS) $(TRGS)

$(OBJDIR):
	mkdir -p $(OBJDIR)
$(BINDIR):
	mkdir -p $(BINDIR)

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(LIBDIR)/*.h)
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
	@$(CC) $(CFLAGS) -c $< -o $@ ${LIBS} ${INCLUDES}
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
	doxygen Doxyfile
	@echo "Doc complete !"
	

