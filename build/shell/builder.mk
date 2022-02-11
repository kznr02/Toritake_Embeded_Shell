CFLAGS := -c --apcs=interwork --cpu Cortex-M4.fp --li --c99 -D__MICROLIB -O0 --split_sections --diag_suppress=1 --diag_suppress=1295 -g -I.\Core\Inc -I.\Drivers\STM32F4xx_HAL_Driver\Inc -I.\Drivers\STM32F4xx_HAL_Driver\Inc\Legacy -I.\Drivers\CMSIS\Device\ST\STM32F4xx\Include -I.\Drivers\CMSIS\Include -I.\MDK-ARM\RTE\_shell -I.\.eide\deps -DUSE_HAL_DRIVER -DSTM32F411xE
CXXFLAGS := -c --cpp --apcs=interwork --cpu Cortex-M4.fp --li -D__MICROLIB -O0 --split_sections --diag_suppress=1 --diag_suppress=1295 -g -I.\Core\Inc -I.\Drivers\STM32F4xx_HAL_Driver\Inc -I.\Drivers\STM32F4xx_HAL_Driver\Inc\Legacy -I.\Drivers\CMSIS\Device\ST\STM32F4xx\Include -I.\Drivers\CMSIS\Include -I.\MDK-ARM\RTE\_shell -I.\.eide\deps -DUSE_HAL_DRIVER -DSTM32F411xE
ASMFLAGS := --apcs=interwork --cpu Cortex-M4.fp --li --pd "__MICROLIB SETA 1" -g -I.\Core\Inc -I.\Drivers\STM32F4xx_HAL_Driver\Inc -I.\Drivers\STM32F4xx_HAL_Driver\Inc\Legacy -I.\Drivers\CMSIS\Device\ST\STM32F4xx\Include -I.\Drivers\CMSIS\Include -I.\MDK-ARM\RTE\_shell -I.\.eide\deps
LDFLAGS := --cpu Cortex-M4.fp --library_type=microlib --scatter "c:/Users/Public/Other/CodeDIR/stm32/shell/build/shell/shell.sct" --strict --summary_stderr --info summarysizes --map --xref --callgraph --symbols --info sizes --info totals --info unused --info veneers --list .\build\shell\shell.map
LDLIBS := 
