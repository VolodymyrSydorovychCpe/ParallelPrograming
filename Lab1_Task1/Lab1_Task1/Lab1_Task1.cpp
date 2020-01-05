#include <iostream>
#include <time.h>
#include <windows.h>

using namespace std;
void ConvertTimeTToSystemTime(PSYSTEMTIME st, time_t* tt) {
	tm my_tm;
	localtime_s(&my_tm, tt);
	memset(st, 0, sizeof(SYSTEMTIME));
	st->wYear = my_tm.tm_year + 1900;
	st->wMonth = my_tm.tm_mon + 1;
	st->wDay = my_tm.tm_mday;
	st->wHour = my_tm.tm_hour;
	st->wMinute = my_tm.tm_min;
	st->wSecond = my_tm.tm_sec;
}

int main() {
	setlocale(LC_ALL, "Russian");

	struct tm {
		int tm_sec; /* seconds after the minute - [0,59] */
		int tm_min; /* minutes after the hour - [0,59] */
		int tm_hour; /* hours since midnight - [0,23] */
		int tm_mday; /* day of the month - [1,31] */
		int tm_mon; /* months since January - [0,11] */
		int tm_year; /* years since 1900 */
		int tm_wday; /* days since Sunday - [0,6] */
		int tm_yday; /* days since January 1 - [0,365] */
		int tm_isdst; /* daylight savings time flag */
	};

	SYSTEMTIME st;
	time_t tt = (time_t)0x7FFFFFFF;
	ConvertTimeTToSystemTime(&st, &tt);
	printf("%4.4d.%2.2d.%2.2d % 2.2d:%2.2d:%2.2d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	return 0;
}