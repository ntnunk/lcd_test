#include <stdio.h>
#include "nrf52.h"
#include "boards.h"
#include "app_util_platform.h"
#include "app_timer.h"
#include "nrf_drv_clock.h"
#include "app_error.h"
#include "nrf_twi.h"
#include "nrf_drv_twi.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "bsp.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "mcp23017.h"
#include "sdk_config.h"

#define I2C_INSTANCE_ID 0

static volatile bool i2c_xfer_done = false;
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(I2C_INSTANCE_ID);

static void i2c_event_handler(nrf_drv_twi_evt_t const * p_event, void * p_context) {
    switch(p_event->type) {
        case NRF_DRV_TWI_EVT_DONE:
            if(p_event->xfer_desc.type == NRF_DRV_TWI_XFER_RX) {
                NRF_LOG_INFO("Receive Event Done");
            }
            i2c_xfer_done = true;
            break;
        case NRF_DRV_TWI_EVT_DATA_NACK:
            NRF_LOG_INFO("Data NACK received");
            break;
        case NRF_DRV_TWI_EVT_ADDRESS_NACK:
            NRF_LOG_INFO("Address NACK received");
            break;
        default:
            break;
    }
}

ret_code_t i2c_write(uint8_t reg, uint8_t data) {
    uint8_t buffer[2];
    buffer[0] = reg;
    buffer[1] = data;

    i2c_xfer_done = false;
    ret_code_t err_code = nrf_drv_twi_tx(&m_twi, MCP_I2C_ADDR, buffer, sizeof(buffer), false);
    while(!is_i2c_xfer_done());

    return err_code;
}

ret_code_t i2c_read(uint8_t reg, uint8_t * data) {
    i2c_xfer_done = false;
    ret_code_t err_code = nrf_drv_twi_tx(&m_twi, MCP_I2C_ADDR, &reg, 1, true);
    if(err_code == NRF_SUCCESS) {
        err_code = nrf_drv_twi_rx(&m_twi, MCP_I2C_ADDR, data, 1);
    }

    return err_code;
}

bool is_i2c_xfer_done() {
    if(i2c_xfer_done) {
        return true;
    }
    else {
        return false;
    }
}

void mcp_init() {
    NRF_LOG_INFO("Initializing MCP23017");
    NRF_LOG_FLUSH();
    // Set all the bank A I/O pins to outputs
    i2c_write(IODIRA, 0x00);

    uint8_t buffer;
    i2c_read(IOCON, &buffer);
}

void i2c_init() {
    NRF_LOG_INFO("Initializing I2C");
    NRF_LOG_FLUSH();
    ret_code_t err_code;

    const nrf_drv_twi_config_t mcp_i2c_config = {
        .scl = 12,
        .sda = 11,
        .frequency = NRF_TWI_FREQ_100K,
        .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
        .clear_bus_init = false
    };

    err_code = nrf_drv_twi_init(&m_twi, &mcp_i2c_config, i2c_event_handler, NULL);
    APP_ERROR_CHECK(err_code);
    nrf_drv_twi_enable(&m_twi);
}
