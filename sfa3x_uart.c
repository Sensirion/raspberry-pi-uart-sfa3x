/*
 * THIS FILE IS AUTOMATICALLY GENERATED
 *
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

#include "sfa3x_uart.h"
#include "sensirion_common.h"
#include "sensirion_shdlc.h"
#include "sensirion_uart_hal.h"

#define SFA3X_UART_ADDRESS 0x00

int16_t sfa3x_start_continuous_measurement(void) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[12];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x00, SFA3X_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x00);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(10000);

    error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    return error;
}

int16_t sfa3x_stop_measurement(void) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[12];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x01, SFA3X_UART_ADDRESS,
                                0);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(10000);

    error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    return error;
}

int16_t sfa3x_read_measured_values_ticks(int16_t* hcho,
                                         int16_t* relative_humidity,
                                         int16_t* temperature) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[24];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x03, SFA3X_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x02);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(100000);

    error = sensirion_shdlc_rx_inplace(&frame, 6, &header);
    if (error) {
        return error;
    }
    *hcho = sensirion_common_bytes_to_int16_t(&buffer[0]);
    *relative_humidity = sensirion_common_bytes_to_int16_t(&buffer[2]);
    *temperature = sensirion_common_bytes_to_int16_t(&buffer[4]);
    return NO_ERROR;
}

int16_t sfa3x_read_measured_values(float* hcho, float* humidity,
                                   float* temperature) {
    int16_t error;
    int16_t hcho_ticks;
    int16_t humidity_ticks;
    int16_t temperature_ticks;

    error = sfa3x_read_measured_values_ticks(&hcho_ticks, &humidity_ticks,
                                             &temperature_ticks);
    if (error) {
        return error;
    }

    *hcho = (float)hcho_ticks / 5.0f;
    *humidity = (float)humidity_ticks / 100.0f;
    *temperature = (float)temperature_ticks / 200.0f;

    return NO_ERROR;
}

int16_t sfa3x_get_device_marking(unsigned char* device_marking,
                                 uint8_t device_marking_size) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[76];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0xD0, SFA3X_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x06);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(10000);

    error = sensirion_shdlc_rx_inplace(&frame, 32, &header);
    if (error) {
        return error;
    }
    sensirion_common_copy_bytes(&buffer[0], device_marking,
                                device_marking_size);
    return NO_ERROR;
}

int16_t sfa3x_device_reset(void) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[12];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0xD3, SFA3X_UART_ADDRESS,
                                0);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(10000);

    error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    if (error) {
        return error;
    }
    sensirion_uart_hal_sleep_usec(200000);
    return NO_ERROR;
}
