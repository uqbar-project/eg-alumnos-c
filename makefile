# ───── Directorios ─────
SRCDIR  := src
TESTDIR := test
OBJDIR  := build

# ───── Herramientas ─────
UNAME    := $(shell uname)
ifeq ($(UNAME), Darwin)
  BREW := $(shell brew --prefix)
  CC   := $(BREW)/Cellar/gcc/14.2.0_1/bin/gcc-14
else
  CC   := gcc
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
