#include <stdio.h>
#include <stdlib.h>

typedef struct _date {
	int day;
	int month;
	int year;
} Date;

int daysInMonth(Date d) {
	int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 30, 31, 31, 30, 31};

	return daysInMonth[d.month-1]; // subtracting one because accessing 1 will correspond to jan but the second value in daysinmonth arr
	

}

int isLeapYear(Date d) {
	int yr = d.year;
	
	if (yr % 4 == 0 && yr % 100 != 0) || (yr % 400 == 0) {
		return 1;
	}
	return 0;
}

