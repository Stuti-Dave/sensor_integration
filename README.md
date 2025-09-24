Description: Reads data from 3 sensors and displays on the 16x2 LCD.

Build and Flash on command line by on STM32L475:

build:

mkdir build;cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/gcc-arm-none-eabi.cmake ..

make -j$(nproc)

flash:

arm-none-eabi-objcopy -O binary sensors_integration.elf sensors_integration.bin

st-flash --connect-under-reset --reset write sensors_integration.bin 0x08000000
