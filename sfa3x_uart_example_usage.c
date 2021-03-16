/*
 * SHDLC-Generator: 0.8.2
 * Yaml Version: 0.1.0
 * Template Version: 0.7.0
 */
/*
 * Copyright (c) 2021, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>  // printf

#include "sensirion_common.h"
#include "sensirion_uart_hal.h"
#include "sfa3x_uart.h"

/**
 * TO USE CONSOLE OUTPUT (PRINTF) AND PLATFORM
 */
//#define printf(...)

// TODO: DRIVER_GENERATOR Add missing commands and make prints more pretty

int main(void) {
    int16_t error = 0;

    error = sensirion_uart_hal_init();
    if (error) {
        printf("Error initializing UART: %i\n", error);
        return error;
    }

    // Start Measurement

    error = sfa3x_start_continuous_measurement();

    if (error) {
        printf("Error executing sfa3x_start_continuous_measurement(): %i\n",
               error);
    }

    for (;;) {
        // Read Measurement
        // TODO: DRIVER_GENERATOR check and update measurement interval
        sensirion_uart_hal_sleep_usec(1000000);
        // TODO: DRIVER_GENERATOR Add scale and offset to printed measurement
        // values
    }

    error = sfa3x_stop_measurement();

    if (error) {
        printf("Error executing sfa3x_stop_measurement(): %i\n", error);
    }

    return 0;
}
