TARGET  = libucgui
SRC_C   = $(shell find GUI* -name "*.c")
OBJ_C   = $(patsubst %.c, %.o, $(SRC_C))
SRCS    = $(SRC_C) $(SRC_C)
OBJS    = $(OBJ_C)
CFLAGS += -I./GUI_X
CFLAGS += -I./GUI/WM
CFLAGS += -I./GUI/Core
CFLAGS += -I./GUI/Widget
CFLAGS += $(MOREFLAGS)

ifeq ($(MOD),)
    CFLAGS += -O2
    CFLAGS += -DUSE_SDL
    CFLAGS += -I/usr/include/SDL
    LDFLAGS = -lSDL
endif

.PHONY: all
all: $(TARGET).a $(TARGET).so

$(TARGET).a : $(OBJS)
	ar crv $(TARGET).a $(OBJS)

$(TARGET).so : $(OBJS)
	$(CC) -shared -fPIC $^ -o $@

%.o : %.c
	$(CC) -fPIC -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf $(TARGET).a $(TARGET).so
	find . -name "*.[od]" | xargs rm -rf
