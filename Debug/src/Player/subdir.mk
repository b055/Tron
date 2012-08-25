################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Player/Human.cpp \
../src/Player/Player.cpp \
../src/Player/Random.cpp \
../src/Player/ReinfPlayer.cpp 

OBJS += \
./src/Player/Human.o \
./src/Player/Player.o \
./src/Player/Random.o \
./src/Player/ReinfPlayer.o 

CPP_DEPS += \
./src/Player/Human.d \
./src/Player/Player.d \
./src/Player/Random.d \
./src/Player/ReinfPlayer.d 


# Each subdirectory must supply rules for building sources it contributes
src/Player/%.o: ../src/Player/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


