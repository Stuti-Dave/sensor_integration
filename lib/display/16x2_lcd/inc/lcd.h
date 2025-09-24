/*
 * lcd.h
 *
 *  Created on: Jul 17, 2025
 *      Author: 167297
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_
#include "main.h"


void lcd_send(uint8_t data, uint8_t mode);
void lcd_send_cmd(uint8_t cmd);
void lcd_send_data(uint8_t data);
void lcd_init(void);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_print(char *str);
void lcd_clear(void);

#endif /* INC_LCD_H_ */
