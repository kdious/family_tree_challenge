################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/FamilyTreeClass.cpp \
../src/FamilyTreeMain.cpp 

OBJS += \
./src/FamilyTreeClass.o \
./src/FamilyTreeMain.o 

CPP_DEPS += \
./src/FamilyTreeClass.d \
./src/FamilyTreeMain.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/builduser/git/family_tree_challenge/includes" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


