/*
 * lps22hb.c
 *
 *  Created on: Jul 17, 2025
 *      Author: 167297
 */
#include "stm32l4xx_hal.h"
#include <stdint.h>
#include <stdio.h>
#include "lps22hb.h"

extern I2C_HandleTypeDef hi2c2;

#define LPS22HB_ADDR         (0x5D << 1)  // 0xBA
#define LPS22HB_WHO_AM_I     0x0F
#define LPS22HB_CTRL_REG1    0x10
#define LPS22HB_WHO_AM_I_VAL 0xB1

uint8_t LPS22HB_Init(void)
{
    uint8_t reg;
    uint8_t data;

    //Send register address
    reg = LPS22HB_WHO_AM_I;
    if (HAL_I2C_Master_Transmit(&hi2c2, LPS22HB_ADDR, &reg, 1, HAL_MAX_DELAY) != HAL_OK)
        return 1;

    //reading WHO_AM_I value
    if (HAL_I2C_Master_Receive(&hi2c2, LPS22HB_ADDR, &data, 1, HAL_MAX_DELAY) != HAL_OK)
        return 2;

    if (data != LPS22HB_WHO_AM_I_VAL)
        return 3;

    uint8_t tx_data[2] = { LPS22HB_CTRL_REG1, 0x50 };
    if (HAL_I2C_Master_Transmit(&hi2c2, LPS22HB_ADDR, tx_data, 2, HAL_MAX_DELAY) != HAL_OK)
        return 4;

    HAL_Delay(100);

    return 0;
}

float LPS22HB_ReadPressure(void)
{
    uint8_t reg = 0x28 | 0x80;
    uint8_t data[3];

    if (HAL_I2C_Master_Transmit(&hi2c2, LPS22HB_ADDR, &reg, 1, HAL_MAX_DELAY) != HAL_OK)
        return -1;

    if (HAL_I2C_Master_Receive(&hi2c2, LPS22HB_ADDR, data, 3, HAL_MAX_DELAY) != HAL_OK)
        return -1;

    // Combine into 24-bit signed value (two's complement)
    int32_t raw_press = (int32_t)((data[2] << 16) | (data[1] << 8) | data[0]);

    // If MSB is set (bit 23), extend sign for negative value
    if (raw_press & 0x00800000)
        raw_press |= 0xFF000000;

    float pressure_hPa = raw_press / 4096.0f;

    return pressure_hPa;
}

