TARGET  = libucgui
SRC_C   = $(shell find . -name "*.c")
OBJ_C   = $(patsubst %.c, %.o, $(SRC_C))
SRCS    = $(SRC_C) $(SRC_C)
OBJS    = $(OBJ_C) 
CFLAGS  = -I./GUI_X -I./GUI/Core -I./GUI/WM -I./GUI/Widget -I/usr/include/SDL
LDFLAGS = -lSDL

.PHONY: all
all: $(TARGET).a

$(TARGET).a : $(OBJS)
	ar crv $(TARGET).a $(OBJS) 

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o  $@

.PHONY: clean
clean:
	rm -rf $(TARGET) *.a
	find . -name "*.[od]" | xargs rm -rf
