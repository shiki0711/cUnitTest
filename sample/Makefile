CFLAGS += -g -Wall -fmessage-length=0 -I../include

DEPEND_FILE = depend.txt

SRCS = sample.c

OBJS = $(SRCS:.c=.o)

LIBS =

TARGET = sample.exe

%.o: *%.c
	$(CC) -c $(CFLAGS) $<

$(TARGET): depend $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

.PHONY: all clean depend

all: $(TARGET)

depend:
	-$(RM) $(DEPEND_FILE)
	-@for i in $(SRCS); do \
		echo "Creating header dependencies: $$i..."; \
		$(CC) $(CFLAGS) -MM $$i | sed "s/\ [_a-zA-Z0-9][_a-zA-Z0-9]*\.c//g" >> $(DEPEND_FILE); \
	done
	
-include $(DEPEND_FILE)

clean:
	rm -f $(OBJS) $(TARGET) $(DEPEND_FILE)
