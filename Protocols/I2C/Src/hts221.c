/*
 * hts221.c
 *
 *  Created on: Jul 17, 2025
 *      Author: 167297
 */

#include"hts221.h"

extern I2C_HandleTypeDef hi2c2;

// HTS221 Sensor Variables
const uint8_t hts_addr      = (0x5F << 1);   // 0xBE
const uint8_t hts_who_am_i  = 0x0F;
const uint8_t hts_ctrl_reg1 = 0x20;
const uint8_t hts_hum_out_l = 0x28;
const uint8_t hts_temp_out_l= 0x2A;

//HTS221 helper functions
int8_t HTS221_Init(void)
{
    uint8_t reg = hts_who_am_i;
    uint8_t who_am_i = 0;

    // Send register address
    if (HAL_I2C_Master_Transmit(&hi2c2, hts_addr, &reg, I2C_MEMADD_SIZE_8BIT, HAL_MAX_DELAY) != HAL_OK)
        return -1;

    // Read the WHO_AM_I register
    if (HAL_I2C_Master_Receive(&hi2c2, hts_addr, &who_am_i, I2C_MEMADD_SIZE_8BIT, HAL_MAX_DELAY) != HAL_OK)
        return -1;

    if (who_am_i != 0xBC)
        return -1;

    // Write to CTRL_REG1 (0x20)
    uint8_t data[2] = { hts_ctrl_reg1, 0x85 };  // Register address + data
    if (HAL_I2C_Master_Transmit(&hi2c2, hts_addr, data, 2, HAL_MAX_DELAY) != HAL_OK)
        return -1;

    HAL_Delay(100); // Allow sensor to power up

    return 0;
}


int8_t HTS221_ReadTempHum(volatile float *temperature, volatile float *humidity)
{
    volatile uint8_t reg = 0x30 | 0x80;
    uint8_t calib[22] = {0};

    //Send register address (0x30)
    if (HAL_I2C_Master_Transmit(&hi2c2, hts_addr, &reg, 1, HAL_MAX_DELAY) != HAL_OK)
        return reg;

    //Read 22 bytes of calibration data
    if (HAL_I2C_Master_Receive(&hi2c2, hts_addr, calib, 22, HAL_MAX_DELAY) != HAL_OK)
        return -1;

    // Extract calibration values
    uint16_t H0_rh_0 = calib[0];
    uint16_t H1_rh_0 = calib[1];
    float H0_rh = H0_rh_0 / 2.0f;
    float H1_rh = H1_rh_0 / 2.0f;

    uint8_t T0_degC_x8_LSB = calib[2];
    uint8_t T1_degC_x8_LSB = calib[3];
    uint8_t T0_T1_MSB = calib[5];

    uint16_t T0_degC_x8 = ((T0_T1_MSB & 0x03) << 8) | T0_degC_x8_LSB;
    uint16_t T1_degC_x8 = ((T0_T1_MSB & 0x0C) << 6) | T1_degC_x8_LSB;

    float T0_degC = T0_degC_x8 / 8.0f;
    float T1_degC = T1_degC_x8 / 8.0f;

    int16_t H0_T0_OUT = (int16_t)(calib[6] | (calib[7] << 8));
    int16_t H1_T0_OUT = (int16_t)(calib[10] | (calib[11] << 8));
    int16_t T0_OUT    = (int16_t)(calib[12] | (calib[13] << 8));
    int16_t T1_OUT    = (int16_t)(calib[14] | (calib[15] << 8));

    // Step 3: Read temperature raw data (TEMP_OUT_L and TEMP_OUT_H)
    reg = 0x2A | 0x80;  // auto-increment
    uint8_t temp_raw[2];
    if (HAL_I2C_Master_Transmit(&hi2c2, hts_addr, &reg, 1, HAL_MAX_DELAY) != HAL_OK)
        return -1;
    if (HAL_I2C_Master_Receive(&hi2c2, hts_addr, temp_raw, 2, HAL_MAX_DELAY) != HAL_OK)
        return -1;

    // Step 4: Read humidity raw data (HUMIDITY_OUT_L and _H)
    reg = 0x28 | 0x80;
    uint8_t hum_raw[2];
    if (HAL_I2C_Master_Transmit(&hi2c2, hts_addr, &reg, 1, HAL_MAX_DELAY) != HAL_OK)
        return -1;
    if (HAL_I2C_Master_Receive(&hi2c2, hts_addr, hum_raw, 2, HAL_MAX_DELAY) != HAL_OK)
        return -1;

    /*
    if (HAL_I2C_Master_Transmit(&hi2c2, HTS221_ADDR, &reg, 1, HAL_MAX_DELAY) != HAL_OK)
        return -1;
    if (HAL_I2C_Master_Receive(&hi2c2, HTS221_ADDR, hum_raw, 2, HAL_MAX_DELAY) != HAL_OK)
        return -1;*/

    // Combine MSB and LSB
    int16_t T_OUT = (int16_t)(temp_raw[0] | (temp_raw[1] << 8));
    int16_t H_T_OUT = (int16_t)(hum_raw[0] | (hum_raw[1] << 8));

    //if ((T1_OUT - T0_OUT) == 0 || (H1_T0_OUT - H0_T0_OUT) == 0)
        //return -1;

    // Linear interpolation
    *temperature = (float)((((T_OUT - T0_OUT) * (T1_degC - T0_degC))/ (T1_OUT - T0_OUT)) + T0_degC);
    *humidity = (float)((((H_T_OUT - H0_T0_OUT) * (H1_rh - H0_rh))/ (H1_T0_OUT - H0_T0_OUT)) + H0_rh);

    return 0;
}

