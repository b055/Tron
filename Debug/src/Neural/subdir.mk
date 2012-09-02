################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/Neural/Network.o 

CPP_SRCS += \
../src/Neural/Network.cpp 

OBJS += \
./src/Neural/Network.o 

CPP_DEPS += \
./src/Neural/Network.d 


# Each subdirectory must supply rules for building sources it contributes
src/Neural/%.o: ../src/Neural/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


