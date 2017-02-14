# 6Harmonics Inc.
# by Qige: qige@6harmonics.com, qige.zhao@6wilink.com
# 2017.02.14 v1.0-1 Apply 6Harmonics Linux C Coding Rules 2017

APP=gws-abb

all: $(APP)

$(APP): *.c
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -I. -Iiwinfo -liwinfo -o $@ $^ -L.

clean:
	rm -f $(APP)

