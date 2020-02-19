################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/DIO.c \
../MCAL/ICU.c \
../MCAL/PWM.c \
../MCAL/Timer.c 

OBJS += \
./MCAL/DIO.o \
./MCAL/ICU.o \
./MCAL/PWM.o \
./MCAL/Timer.o 

C_DEPS += \
./MCAL/DIO.d \
./MCAL/ICU.d \
./MCAL/PWM.d \
./MCAL/Timer.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/%.o: ../MCAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


