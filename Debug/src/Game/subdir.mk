################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/Game/Game.o 

CPP_SRCS += \
../src/Game/Game.cpp 

OBJS += \
./src/Game/Game.o 

CPP_DEPS += \
./src/Game/Game.d 


# Each subdirectory must supply rules for building sources it contributes
src/Game/%.o: ../src/Game/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


