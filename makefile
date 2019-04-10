################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include makefile.init
BASEDIR="$(CURDIR)"
RM := rm -rf

# All of the sources participating in the build are defined here
-include make/sources.mk
-include make/objects.mk
-include make/src/subdir.mk
-include make/test/subdir.mk


ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: eg-alumnos-c

# Tool invocations
eg-alumnos-c: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Linker'
	gcc -o "eg-alumnos-c" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) eg-alumnos-c
	-@echo ' '

.PHONY: all clean dependents

-include makefile.targets
