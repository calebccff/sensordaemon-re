OUT := sensordaemon
CC = gcc

CFLAGS += -Wall -g -O2 -I/usr/include
LDFLAGS += -lqrtr -ludev -lpthread

SRCS := qmi_sensordaemon.c sensordaemon.c
OBJS := $(SRCS:.c=.o)

$(OUT): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.c: %.qmi
	qmic -k < $<

clean:
	rm -f $(OUT) $(OBJS)

