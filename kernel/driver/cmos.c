#include "./include/cmos.h"

uint8_t cmos_read(uint8_t reg)
{
	outb(CMOS_ADDRESS, reg);
	return insb(CMOS_DATA);
}

bool cmos_is_update_inprogress()
{
	outb(CMOS_ADDRESS, 0x0A);
	return (insb(CMOS_DATA) & 0x80);
}

void cmos_get_datetime(cmos_t *datetime)
{
	while (cmos_is_update_inprogress())
		;

	datetime->seconds = cmos_read(CMOS_SEC_REG);
	datetime->minutes = cmos_read(CMOS_MIN_REG);
	datetime->hours = cmos_read(CMOS_HOUR_REG);
	datetime->week_day = cmos_read(CMOS_WDAY_REG);
	datetime->day_of_month = cmos_read(CMOS_DOM_REG);
	datetime->month = cmos_read(CMOS_MONTH_REG);
	datetime->year = cmos_read(CMOS_YEAR_REG);

	// Convert BCD (Binary Coded Decimal) to binary
	datetime->seconds =
		(datetime->seconds & 0x0F) + ((datetime->seconds / 16) * 10);
	datetime->minutes =
		(datetime->minutes & 0x0F) + ((datetime->minutes / 16) * 10);
	datetime->hours =
		(datetime->hours & 0x0F) + ((datetime->hours / 16) * 10);
	datetime->day_of_month = (datetime->day_of_month & 0x0F) +
				 ((datetime->day_of_month / 16) * 10);
	datetime->month =
		(datetime->month & 0x0F) + ((datetime->month / 16) * 10);
	datetime->year = (datetime->year & 0x0F) + ((datetime->year / 16) * 10);

	qemu_write_string("%s CMOS data obtained\n", POSITIVE_OUTPUT);
}

static const char *cmos_enum_to_month_str(cmos_month_enum_t month)
{
	switch (month) {
	case JANUARY:
		return "JAN";
	case FEBRUARY:
		return "FEB";
	case MARCH:
		return "MARCH";
	case APRIL:
		return "APRIL";
	case MAY:
		return "MAY";
	case JUNE:
		return "JUNE";
	case JULY:
		return "JULY";
	case AUGUST:
		return "AUG";
	case SEPTEMBER:
		return "SEP";
	case OCTOBER:
		return "OCT";
	case NOVEMBER:
		return "NOV";
	case DECEMBER:
		return "DEC";
	default:
		return "Invalid Month";
	}
}

void cmos_display_date_ddmmyyyy_hhmmss()
{
	cmos_t cmos; // Declare a cmos_t variable directly, not a pointer
	cmos_get_datetime(&cmos);

	printf("Date: %d %s %d\nLogin Time: %d:%d:%d\n\n", cmos.day_of_month,
	       cmos_enum_to_month_str(cmos.month), cmos.year, cmos.hours,
	       cmos.minutes, cmos.seconds);
	qemu_write_string("%s Date: %d/%d/%d\n", INFORMATION_OUTPUT,
			  cmos.day_of_month, cmos.month, cmos.year);
}
