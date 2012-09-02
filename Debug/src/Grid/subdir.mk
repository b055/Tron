################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Grid/Grid.cpp \
../src/Grid/Voronoi.cpp 

OBJS += \
./src/Grid/Grid.o \
./src/Grid/Voronoi.o 

CPP_DEPS += \
./src/Grid/Grid.d \
./src/Grid/Voronoi.d 


# Each subdirectory must supply rules for building sources it contributes
src/Grid/%.o: ../src/Grid/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


