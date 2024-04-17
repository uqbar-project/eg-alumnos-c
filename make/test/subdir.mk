################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
./test/tests.c 

OBJS += \
./test/tests.o 

C_DEPS += \
./test/tests.d 


# Each subdirectory must supply rules for building sources it contributes
test/%.o: test/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
ifeq ($(UNAME), Darwin)
	$(CCMAC) -I /usr/local/include -L /usr/local/lib/ -I"./test" -I"./src" -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<" 
else
	gcc -I"./test" -I"./src" -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<" 
endif
	@echo 'Finished building: $<'
	@echo ' '


