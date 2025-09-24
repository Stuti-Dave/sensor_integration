/**
  ******************************************************************************
  * @file           : lcd.c
  * @brief          : LCD 16x2 Display APIs
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "lcd.h"

/* Private Variables --------------------------------------------------------*/
extern I2C_HandleTypeDef hi2c1;

const uint8_t lcd_i2c_addr  = (0x27 << 1);  // 0x4E
const uint8_t lcd_backlight = 0x08;         // Backlight
const uint8_t lcd_enable 	= 0x04;         // Enable
const uint8_t lcd_rw     	= 0x02;         // Read/Write
const uint8_t lcd_rs     	= 0x01;         // Register Select

/* Private FUnctions -------------------------------------------------------*/

// LCD data transfer function
void lcd_send(uint8_t data, uint8_t mode) {
    uint8_t high_nibble = data & 0xF0;
    uint8_t low_nibble = (data << 4) & 0xF0;
    uint8_t data_arr[4];

    // Send high nibble
    data_arr[0] = high_nibble | mode | lcd_backlight | lcd_enable;
    data_arr[1] = high_nibble | mode | lcd_backlight;
    // Send low nibble
    data_arr[2] = low_nibble | mode | lcd_backlight | lcd_enable;
    data_arr[3] = low_nibble | mode | lcd_backlight;

    HAL_I2C_Master_Transmit(&hi2c1, lcd_i2c_addr, data_arr, 4, HAL_MAX_DELAY);
    HAL_Delay(1);
}

// LCD command and data functions
void lcd_send_cmd(uint8_t cmd) {
    lcd_send(cmd, 0x00);
}

void lcd_send_data(uint8_t data) {
    lcd_send(data, lcd_rs);
}

// LCD initialization
void lcd_init(void) {
    HAL_Delay(50);  // Wait for LCD to power up

    // Init sequence
    lcd_send_cmd(0x30);
    HAL_Delay(5);
    lcd_send_cmd(0x30);
    HAL_Delay(1);
    lcd_send_cmd(0x30);
    HAL_Delay(10);

    lcd_send_cmd(0x20);  // 4-bit mode
    HAL_Delay(10);

    lcd_send_cmd(0x28);  // 2 line, 5x8 font
    lcd_send_cmd(0x08);  // Display off
    lcd_send_cmd(0x01);  // Clear display
    HAL_Delay(2);
    lcd_send_cmd(0x06);  // Entry mode set
    lcd_send_cmd(0x0C);  // Display on, cursor off
}

// Set cursor position
void lcd_set_cursor(uint8_t row, uint8_t col) {
    uint8_t address;

    switch (row) {
        case 0:
            address = 0x00 + col;
            break;
        case 1:
            address = 0x40 + col;
            break;
        case 2:
            address = 0x14 + col;
            break;
        case 3:
            address = 0x54 + col;
            break;
        default:
            address = 0x00 + col;
            break;
    }

    lcd_send_cmd(0x80 | address);  // Set 
}

// Print string on LCD
void lcd_print(char *str) {
    while (*str) {
        lcd_send_data(*str++);
    }
}

// Clear LCD display
void lcd_clear(void) {
    lcd_send_cmd(0x01);   // Clear display command
    HAL_Delay(2);
    lcd_set_cursor(0,0);   // Move cursor to initial position
    HAL_Delay(2);
}