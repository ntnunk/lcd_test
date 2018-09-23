#include <stdbool.h>
#include "boards.h"

#ifndef _MCP23017_H_
#define _MCP23017_H_

#define MCP_I2C_ADDR        0x20    // i2c bus address
#define I2C_SCL_PIN         12
#define I2C_SDA_PIN         11

// MCP23017 Register Defines
#ifndef _IOCON_BANK_1

#define IODIRA                      0x00
#define IODIRB                      0x01
#define IPOLA                       0x02
#define IPOLB                       0x03
#define GPINTENA                    0x04
#define GPINTENB                    0x05
#define DEFVALA                     0x06
#define DEFVALB                     0x07
#define INTCONA                     0x08
#define INTCONB                     0x09
#define IOCON                       0x0a
//#define IOCON  0x0b - IOCON is common
#define GPPUA                       0x0c
#define GPPUB                       0x0d
#define INTFA                       0x0e
#define INTFB                       0x0f
#define INTCAPA                     0x10
#define INTCAPB                     0x11
#define GPIOA                       0x12
#define GPIOB                       0x13
#define OLATA                       0x14
#define OLATB                       0x15

#else

#define IODIRA                      0x00
#define IODIRB                      0x10
#define IPOLA                       0x01
#define IPOLB                       0x11
#define GPINTENA                    0x02
#define GPINTENB                    0x12
#define DEFVALA                     0x03
#define DEFVALB                     0x13
#define INTCONA                     0x04
#define INTCONB                     0x14
#define IOCON                       0x05
//#define IOCON  0x15 - IOCON is common
#define GPPUA                       0x06
#define GPPUB                       0x16
#define INTFA                       0x07
#define INTFB                       0x17
#define INTCAPA                     0x08
#define INTCAPB                     0x18
#define GPIOA                       0x09
#define GPIOB                       0x19
#define OLATA                       0x0a
#define OLATB                       0x1a

#endif

// Public function prototypes
ret_code_t i2c_write(uint8_t reg, uint8_t data);
ret_code_t i2c_read(uint8_t reg, uint8_t * data);
void i2c_init(void);
bool is_i2c_xfer_done();
void mcp_init();

#endif // _MCP23017_H_
