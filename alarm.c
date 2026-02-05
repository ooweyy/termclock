#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RESET     "\033[0m"
#define BOLD      "\033[1m"
#define UNDERLINE "\033[4m"
#define BLINK     "\033[5m"
#define RED       "\033[31m"
#define GREEN     "\033[32m"
#define YELLOW    "\033[33m"
#define BLUE      "\033[34m"
#define MAGENTA   "\033[35m"
#define CYAN      "\033[36m"
#define WHITE     "\033[37m"

#define FMT_DATE  "%Y-%m-%d (%a)"
#define FMT_TIME  "%H:%M:%S"

typedef unsigned int uint;

void
main(int argc, char *argv[])
{
	if (0) {
error:
		printf("%s Interval Remainder\n", argv[0]);
		return;
	}

	if (argc != 3)
		goto error;

	const uint interval = atoi(argv[1]);
	const uint remainder = atoi(argv[2]);
	if (!interval || interval <= remainder)
		goto error;

	struct timespec ts = {.tv_sec = 1, .tv_nsec = 0};
	struct tm *tm;
	char date_buf[20], time_buf[20];

	printf("\e]0;Alarm %d %d\a", interval, remainder);
	printf("\033[?25l");
	do {
		printf("\033[2J\033[;1H");

		time_t now = time(NULL);

		tm = localtime(&now);
		strftime(time_buf, sizeof(date_buf), FMT_TIME, tm);
		strftime(date_buf, sizeof(time_buf), FMT_DATE, tm);
		printf(WHITE " %s " BOLD CYAN "%s" RESET "\n", date_buf, time_buf);

		if (now % interval == remainder)
			printf("\e]0;%s\a\a", time_buf);

		fflush(stdout);
	} while (nanosleep(&ts, NULL) == 0);
}
