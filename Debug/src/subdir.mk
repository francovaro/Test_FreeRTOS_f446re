################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ledhardware.c \
../src/ledtask.c \
../src/main.c \
../src/peripheralinit.c \
../src/syscalls.c \
../src/system_stm32f4xx.c \
../src/taskhandler.c 

OBJS += \
./src/ledhardware.o \
./src/ledtask.o \
./src/main.o \
./src/peripheralinit.o \
./src/syscalls.o \
./src/system_stm32f4xx.o \
./src/taskhandler.o 

C_DEPS += \
./src/ledhardware.d \
./src/ledtask.d \
./src/main.d \
./src/peripheralinit.d \
./src/syscalls.d \
./src/system_stm32f4xx.d \
./src/taskhandler.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -I"C:/work/workspace_stm/Test_FreeRTOS_f446re/inc" -I"C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/include" -I"C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/CMSIS/core" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/CMSIS/device" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


