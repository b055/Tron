################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/Evaluate.o \
../src/Game.o \
../src/Grid.o \
../src/Human.o \
../src/Network.o \
../src/Player.o 

CPP_SRCS += \
../src/Cycles.cpp \
../src/MachineVsHuman.cpp 

OBJS += \
./src/Cycles.o \
./src/MachineVsHuman.o 

CPP_DEPS += \
./src/Cycles.d \
./src/MachineVsHuman.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


