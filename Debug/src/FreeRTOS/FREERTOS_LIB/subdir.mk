################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/croutine.c \
C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/event_groups.c \
C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/list.c \
C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/queue.c \
C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/stream_buffer.c \
C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/tasks.c \
C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/timers.c 

OBJS += \
./src/FreeRTOS/FREERTOS_LIB/croutine.o \
./src/FreeRTOS/FREERTOS_LIB/event_groups.o \
./src/FreeRTOS/FREERTOS_LIB/list.o \
./src/FreeRTOS/FREERTOS_LIB/queue.o \
./src/FreeRTOS/FREERTOS_LIB/stream_buffer.o \
./src/FreeRTOS/FREERTOS_LIB/tasks.o \
./src/FreeRTOS/FREERTOS_LIB/timers.o 

C_DEPS += \
./src/FreeRTOS/FREERTOS_LIB/croutine.d \
./src/FreeRTOS/FREERTOS_LIB/event_groups.d \
./src/FreeRTOS/FREERTOS_LIB/list.d \
./src/FreeRTOS/FREERTOS_LIB/queue.d \
./src/FreeRTOS/FREERTOS_LIB/stream_buffer.d \
./src/FreeRTOS/FREERTOS_LIB/tasks.d \
./src/FreeRTOS/FREERTOS_LIB/timers.d 


# Each subdirectory must supply rules for building sources it contributes
src/FreeRTOS/FREERTOS_LIB/croutine.o: C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/croutine.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -I"C:/work/workspace_stm/Test_FreeRTOS_f446re/inc" -I"C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/include" -I"C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/CMSIS/core" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/CMSIS/device" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/FreeRTOS/FREERTOS_LIB/event_groups.o: C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/event_groups.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -I"C:/work/workspace_stm/Test_FreeRTOS_f446re/inc" -I"C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/include" -I"C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/CMSIS/core" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/CMSIS/device" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/FreeRTOS/FREERTOS_LIB/list.o: C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/list.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -I"C:/work/workspace_stm/Test_FreeRTOS_f446re/inc" -I"C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/include" -I"C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/CMSIS/core" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/CMSIS/device" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/FreeRTOS/FREERTOS_LIB/queue.o: C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/queue.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -I"C:/work/workspace_stm/Test_FreeRTOS_f446re/inc" -I"C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/include" -I"C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/CMSIS/core" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/CMSIS/device" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/FreeRTOS/FREERTOS_LIB/stream_buffer.o: C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/stream_buffer.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -I"C:/work/workspace_stm/Test_FreeRTOS_f446re/inc" -I"C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/include" -I"C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/CMSIS/core" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/CMSIS/device" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/FreeRTOS/FREERTOS_LIB/tasks.o: C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/tasks.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -I"C:/work/workspace_stm/Test_FreeRTOS_f446re/inc" -I"C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/include" -I"C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/CMSIS/core" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/CMSIS/device" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/FreeRTOS/FREERTOS_LIB/timers.o: C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/timers.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -I"C:/work/workspace_stm/Test_FreeRTOS_f446re/inc" -I"C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/include" -I"C:/work/FreeRTOS/FreeRTOSv10.2.1/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/CMSIS/core" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/CMSIS/device" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


