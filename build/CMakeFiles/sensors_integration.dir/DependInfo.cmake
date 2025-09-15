
# Consider dependencies only in project.
set(CMAKE_DEPENDS_IN_PROJECT_ONLY OFF)

# The set of languages for which implicit dependencies are needed:
set(CMAKE_DEPENDS_LANGUAGES
  "ASM"
  )
# The set of files for implicit dependencies of each language:
set(CMAKE_DEPENDS_CHECK_ASM
  "/home/stutidave/sensor_integration/startup_stm32l475xx.s" "/home/stutidave/sensor_integration/build/CMakeFiles/sensors_integration.dir/startup_stm32l475xx.s.obj"
  )
set(CMAKE_ASM_COMPILER_ID "GNU")

# Preprocessor definitions for this target.
set(CMAKE_TARGET_DEFINITIONS_ASM
  "DEBUG"
  "STM32L475xx"
  "USE_HAL_DRIVER"
  )

# The include file search paths:
set(CMAKE_ASM_TARGET_INCLUDE_PATH
  "../Protocols/I2C/Inc"
  "../cmake/stm32cubemx/../../Core/Inc"
  "../cmake/stm32cubemx/../../Drivers/STM32L4xx_HAL_Driver/Inc"
  "../cmake/stm32cubemx/../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy"
  "../cmake/stm32cubemx/../../Drivers/CMSIS/Device/ST/STM32L4xx/Include"
  "../cmake/stm32cubemx/../../Drivers/CMSIS/Include"
  )

# The set of dependency files which are needed:
set(CMAKE_DEPENDS_DEPENDENCY_FILES
  "/home/stutidave/sensor_integration/Core/Src/main.c" "CMakeFiles/sensors_integration.dir/Core/Src/main.c.obj" "gcc" "CMakeFiles/sensors_integration.dir/Core/Src/main.c.obj.d"
  "/home/stutidave/sensor_integration/Core/Src/stm32l4xx_hal_msp.c" "CMakeFiles/sensors_integration.dir/Core/Src/stm32l4xx_hal_msp.c.obj" "gcc" "CMakeFiles/sensors_integration.dir/Core/Src/stm32l4xx_hal_msp.c.obj.d"
  "/home/stutidave/sensor_integration/Core/Src/stm32l4xx_it.c" "CMakeFiles/sensors_integration.dir/Core/Src/stm32l4xx_it.c.obj" "gcc" "CMakeFiles/sensors_integration.dir/Core/Src/stm32l4xx_it.c.obj.d"
  "/home/stutidave/sensor_integration/Core/Src/syscalls.c" "CMakeFiles/sensors_integration.dir/Core/Src/syscalls.c.obj" "gcc" "CMakeFiles/sensors_integration.dir/Core/Src/syscalls.c.obj.d"
  "/home/stutidave/sensor_integration/Core/Src/sysmem.c" "CMakeFiles/sensors_integration.dir/Core/Src/sysmem.c.obj" "gcc" "CMakeFiles/sensors_integration.dir/Core/Src/sysmem.c.obj.d"
  "/home/stutidave/sensor_integration/Protocols/I2C/Src/hts221.c" "CMakeFiles/sensors_integration.dir/Protocols/I2C/Src/hts221.c.obj" "gcc" "CMakeFiles/sensors_integration.dir/Protocols/I2C/Src/hts221.c.obj.d"
  "/home/stutidave/sensor_integration/Protocols/I2C/Src/lcd.c" "CMakeFiles/sensors_integration.dir/Protocols/I2C/Src/lcd.c.obj" "gcc" "CMakeFiles/sensors_integration.dir/Protocols/I2C/Src/lcd.c.obj.d"
  "/home/stutidave/sensor_integration/Protocols/I2C/Src/lps22hb.c" "CMakeFiles/sensors_integration.dir/Protocols/I2C/Src/lps22hb.c.obj" "gcc" "CMakeFiles/sensors_integration.dir/Protocols/I2C/Src/lps22hb.c.obj.d"
  )

# Targets to which this target links.
set(CMAKE_TARGET_LINKED_INFO_FILES
  )

# Fortran module output directory.
set(CMAKE_Fortran_TARGET_MODULE_DIR "")
