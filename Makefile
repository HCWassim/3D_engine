# Makefile pour 3D_engine (moteur 3D en C avec SDL2)
#
# Structure attendue :
#   src/*.c, src/*.h   -> code source
#   include/SDL.h     -> en-têtes SDL2 (les sources incluent "../include/SDL.h")
#   lib/              -> bibliothèques SDL2 (Windows / MinGW uniquement)
#
# Usage :
#   make            compile le programme
#   make run        compile puis lance le programme
#   make debug      recompile avec les symboles de debug
#   make clean      supprime les fichiers générés
#   make rebuild    clean puis all

CC      ?= gcc
SRC_DIR := src
SRCS    := $(wildcard $(SRC_DIR)/*.c)
OBJS    := $(SRCS:.c=.o)
DEPS    := $(SRCS:.c=.d)

OPT     ?= -O2

WARNINGS := -Wall -Wextra -Wno-unused-parameter

ifeq ($(OS),Windows_NT)
  # Windows (MinGW) : SDL2 fourni dans include/ et lib/ à la racine
  TARGET   := prgm.exe
  RUN      := $(TARGET)
  RM       := del /Q
  FixPath   = $(subst /,\,$(1))
  SDL_INC  := -I include
  SDL_LIB  := -L lib -lmingw32 -lSDL2main -lSDL2
else
  # Linux : SDL2 installée via le gestionnaire de paquets (libsdl2-dev)
  TARGET   := prgm
  RUN      := ./$(TARGET)
  RM       := rm -f
  FixPath   = $(1)
  SDL_INC  := $(shell pkg-config --cflags sdl2 2>/dev/null)
  SDL_LIB  := $(shell pkg-config --libs sdl2 2>/dev/null || echo -lSDL2)
endif

# -fcommon : les variables globales sont définies dans des en-têtes (.h) ;
# GCC 10+ refuse ce comportement par défaut (erreur "multiple definition").
CFLAGS  += -std=gnu11 -fcommon $(WARNINGS) $(OPT) -I$(SRC_DIR) $(SDL_INC) -MMD -MP
LDLIBS  := $(SDL_LIB) -lm

.PHONY: all run debug clean rebuild

all: $(TARGET)

# Recompiler tout si le Makefile change (ex. changement de flags)
$(OBJS): Makefile

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	$(RUN)

debug:
	$(MAKE) clean
	$(MAKE) OPT="-g -O0 -DDEBUG" all

clean:
	-$(RM) $(call FixPath,$(OBJS) $(DEPS)) $(TARGET)

rebuild: clean all

-include $(DEPS)
