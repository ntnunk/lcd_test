#include "boards.h"

#ifndef _LCD_H_
#define _LCD_H_

// Register Select Bit - 0 is IR, 1 is Data Register
#define RS_BIT 0

// Read/Write Select - 0 is write, 1 is read
#define RW_BIT 1

// Enable bit. When low, LCD ignores Register Select, Read/Write and Data lines.
#define EN_BIT 2

/**
 * @brief Trigger an enable
 */
void lcd_enable(void);

/**
 * @brief Read busy flag and address register
 * [in] uint8_t * p_adx_buff - a pointer to a buffer to return the address
 * [ret] boolead busy
 */
bool read_busy_and_adx(uint8_t * p_adx_buff);

void lcd_init(void);

#endif // _LCD_H_
