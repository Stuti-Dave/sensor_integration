/*
 * lps22hb.h
 *
 *  Created on: Jul 17, 2025
 *      Author: 167297
 */

#ifndef INC_LPS22HB_H_
#define INC_LPS22HB_H_

#include "main.h"

#define LPS22HB_ADDR         (0x5D << 1)  // 0xBA
#define LPS22HB_WHO_AM_I     0x0F
#define LPS22HB_CTRL_REG1    0x10
#define LPS22HB_WHO_AM_I_VAL 0xB1

uint8_t LPS22HB_Init(void);
float LPS22HB_ReadPressure(void);

#endif /* INC_LPS22HB_H_ */
