##
##


CFLAGS=-g 
CPPFLAGS=
LDFLAGS=-g
LDLIBS=

CC=gcc

SRCS=main.c listTest.c
OBJS=$(subst .c,.o,$(SRCS))
TARGET=listTest

$(TARGET): $(OBJS)
	g++ $(LDFLAGS) -o $(TARGET) $(OBJS) 

%.o: %.c %.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	$(RM) *.*~
	$(RM) $(OBJS)
	$(RM) $(TARGET)