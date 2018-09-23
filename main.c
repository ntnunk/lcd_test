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

#define APP_TIMER_PRESCALER     0
#define APP_TIMER_OP_QUEUE_SIZE 4

int main(void) {
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

    NRF_LOG_INFO("\r\nLCD Display Test");
    NRF_LOG_FLUSH();

    i2c_init();
    mcp_init();
    //lcd_init();

    while(true) {
        do {
            __WFE();
        } while(!is_i2c_xfer_done());
        NRF_LOG_FLUSH();
    }
}
