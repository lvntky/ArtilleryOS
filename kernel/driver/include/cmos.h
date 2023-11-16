#ifndef _CMOS_H_
#define _CMOS_H_

#define CMOS_ADDRESS 0x70
#define CMOS_DATA 0x71

#define CMOS_SEC_REG 0x00
#define CMOS_MIN_REG 0x02
#define CMOS_HOUR_REG 0x04
#define CMOS_WDAY_REG 0x06
#define CMOS_DOM_REG 0x07
#define CMOS_MONTH_REG 0x08
#define CMOS_YEAR_REG 0x09

#include <stdint.h>
#include <stdbool.h>
#include "../../include/io_port.h"
#include "../../include/qemu_debug.h"
#include "../../libc/include/stdio.h"

typedef struct cmos {
	uint8_t seconds; // 0...59
	uint8_t minutes; // 0...59
	uint8_t hours; // 0...23
	uint8_t week_day; // 1...7
	uint8_t day_of_month; // 1...31
	uint8_t month; // 1...12
	uint8_t year; // 0...xxxx

} __attribute__((packed)) cmos_t;

typedef enum cmos_month_enum {
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
} cmos_month_enum_t;

bool cmos_is_update_inprogress();
uint8_t cmos_read(uint8_t);
void cmos_get_datetime(cmos_t *);
void cmos_display_date_ddmmyyyy_hhmmss();

#endif