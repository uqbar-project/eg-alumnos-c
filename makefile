# ───── Directorios ─────
SRCDIR  := src
TESTDIR := test
OBJDIR  := build

# ───── Herramientas ─────
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
  BREW := $(shell brew --prefix)
  # cspec usa nested functions + statement expressions (extensiones GCC).
  # Apple clang no las banca, así que necesitamos un gcc real de Homebrew.
  # Detectamos el mayor gcc-N instalado (ARM: /opt/homebrew, Intel: /usr/local)
  # para no clavar la versión: sobrevive a `brew upgrade gcc`.
  CC := $(shell ls /opt/homebrew/bin/gcc-[0-9]* /usr/local/bin/gcc-[0-9]* 2>/dev/null | sort -V | tail -1)
  ifeq ($(strip $(CC)),)
    $(error gcc de Homebrew no encontrado. Instalar con: brew install gcc)
  endif
else
  CC := gcc
endif

# ───── Paths de CSpecs ─────
# Aquí defines explícitamente dónde está cspecs
CSPEC_INC := /usr/local/include $(BREW)/include
CSPEC_LIB := /usr/local/lib    $(BREW)/lib

# ───── Flags de compilación ─────
CFLAGS := \
  -I$(SRCDIR) \
  -I$(TESTDIR) \
  $(foreach d,$(CSPEC_INC),-I$d) \
  -O0 -g -Wall -fPIC -MMD -MP

# ───── Flags de link ─────
LDFLAGS := $(foreach d,$(CSPEC_LIB),-L$d)
LIBS    := -lcspecs

# ───── Fuentes, objetos y deps ─────
SRCS   := $(wildcard $(SRCDIR)/*.c) $(wildcard $(TESTDIR)/*.c)
OBJS   := $(SRCS:%.c=$(OBJDIR)/%.o)
DEPS   := $(OBJS:.o=.d)

TARGET := eg-alumnos-c

.PHONY: all clean

# ───── Regla por defecto ─────
all: $(TARGET)

# ───── Linkeo (no headers aquí) ─────
$(TARGET): $(OBJS)
	@echo "Linking $@"
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)
	@echo "Done."

# ───── Compilación (aquí van los includes) ─────
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "Compiling $< → $@"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "OK."

# ───── Dependencias automáticas ─────
-include $(DEPS)

# ───── Limpieza ─────
clean:
	@echo "Cleaning…"
	@rm -rf $(OBJDIR) $(TARGET)
	@echo "Clean complete."
