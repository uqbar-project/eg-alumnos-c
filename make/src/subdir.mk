################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
./src/main.c \
./src/alumno.c \
./src/parcial.c \
./src/tipoAlumno.c 

OBJS += \
./src/main.o \
./src/alumno.o \
./src/parcial.o \
./src/tipoAlumno.o 

C_DEPS += \
./src/main.d \
./src/alumno.d \
./src/parcial.d \
./test/alumnoTest.d \
./src/tipoAlumno.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I"./test" -I"./src" -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


