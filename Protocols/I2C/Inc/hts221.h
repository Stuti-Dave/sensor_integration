/*
 * hts221.h
 *
 *  Created on: Jul 17, 2025
 *      Author: 167297
 */

#ifndef INC_HTS221_H_
#define INC_HTS221_H_
#include "main.h"

int8_t HTS221_Init(void);
int8_t HTS221_ReadTempHum(volatile double *temperature, volatile double *humidity);

#endif /* INC_HTS221_H_ */
