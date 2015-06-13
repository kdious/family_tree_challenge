################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../unit_tests/FamilyTreeTest.cpp 

OBJS += \
./unit_tests/FamilyTreeTest.o 

CPP_DEPS += \
./unit_tests/FamilyTreeTest.d 


# Each subdirectory must supply rules for building sources it contributes
unit_tests/%.o: ../unit_tests/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/builduser/git/family_tree_challenge/includes" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


