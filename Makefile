common_sources = sensirion_config.h sensirion_common.h sensirion_common.c
uart_sources = sensirion_uart_hal.h sensirion_shdlc.h sensirion_shdlc.c
sfa3x_sources = sfa3x_uart.h sfa3x_uart.c

uart_implementation ?= sensirion_uart_hal.c

CFLAGS = -Os -Wall -fstrict-aliasing -Wstrict-aliasing=1 -Wsign-conversion -fPIC -I.

ifdef CI
    CFLAGS += -Werror
endif

.PHONY: all clean

all: sfa3x_uart_example_usage

sfa3x_uart_example_usage: clean
	$(CC) $(CFLAGS) -o $@ ${sfa3x_sources} ${uart_sources} \
		${uart_implementation} ${common_sources} sfa3x_uart_example_usage.c

clean:
	$(RM) sfa3x_uart_example_usage
