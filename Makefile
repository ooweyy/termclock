all: multiline oneline print-dates streamclock alarm
clean:
	rm -f multiline oneline print-dates streamclock alarm
.PHONY: all clean

multiline: multiline.c
	${CC} -o $@ $<
oneline: oneline.c
	${CC} -o $@ $<
print-dates: print-dates.c
	${CC} -o $@ $<
streamclock: streamclock.c
	${CC} -o $@ $<
alarm: alarm.c
	${CC} -o $@ $<

