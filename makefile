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
# Separamos la "librería" (alumno/parcial/criterio) del main y de los tests.
# Esto permite que el demo no linkee cspec y que los tests no arrastren el main.
LIB_SRCS  := $(filter-out $(SRCDIR)/main.c,$(wildcard $(SRCDIR)/*.c))
MAIN_SRC  := $(SRCDIR)/main.c
TEST_SRCS := $(wildcard $(TESTDIR)/*.c)

LIB_OBJS  := $(LIB_SRCS:%.c=$(OBJDIR)/%.o)
MAIN_OBJ  := $(MAIN_SRC:%.c=$(OBJDIR)/%.o)
TEST_OBJS := $(TEST_SRCS:%.c=$(OBJDIR)/%.o)
DEPS      := $(LIB_OBJS:.o=.d) $(MAIN_OBJ:.o=.d) $(TEST_OBJS:.o=.d)

DEMO_BIN := eg-alumnos-c
TEST_BIN := eg-alumnos-c-tests

.PHONY: all run test clean

# ───── Regla por defecto ─────
all: $(DEMO_BIN)

# ───── Linkeo ─────
# Demo: solo la librería + main, sin cspec.
$(DEMO_BIN): $(LIB_OBJS) $(MAIN_OBJ)
	@echo "Linking $@"
	$(CC) $(LDFLAGS) -o $@ $^
	@echo "Done."

# Tests: librería + cspec + archivos de test.
$(TEST_BIN): $(LIB_OBJS) $(TEST_OBJS)
	@echo "Linking $@"
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)
	@echo "Done."

# ───── Compilación (aquí van los includes) ─────
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "Compiling $< → $@"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "OK."

# ───── Targets de conveniencia ─────
run: $(DEMO_BIN)
	./$(DEMO_BIN)

test: $(TEST_BIN)
	./$(TEST_BIN)

# ───── Dependencias automáticas ─────
-include $(DEPS)

# ───── Limpieza ─────
clean:
	@echo "Cleaning…"
	@rm -rf $(OBJDIR) $(DEMO_BIN) $(TEST_BIN)
	@echo "Clean complete."
