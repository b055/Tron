################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Evaluate/Evaluate.cpp 

OBJS += \
./src/Evaluate/Evaluate.o 

CPP_DEPS += \
./src/Evaluate/Evaluate.d 


# Each subdirectory must supply rules for building sources it contributes
src/Evaluate/%.o: ../src/Evaluate/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


