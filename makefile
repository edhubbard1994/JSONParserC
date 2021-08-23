CC = gcc 
CFLAGS += -fPIC -Wall -Wextra -O2 -g 
LDFLAGS = -shared   
RM = rm -f   
TARGET_LIB = tecct.so

ODIR=object
SDIR=src
HDIR=include

SRCS = src/main.c   
OBJS = $(SRCS:.c=.o)
OBJ = $(patsubst %,$(ODIR)/%,$(OBJS))

.PHONY: lib
lib: ${TARGET_LIB}


$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

.PHONY: debug
debug: $(OBJS)
	$(CC) $(SRCS) -I $(HDIR)  -o build/debug

.PHONY: test
test: 
	cd test && docker-compose up --build

.PHONY: dtest
dtest:
	cd test && docker-compose build 
	cd test && docker-compose run test gdb /code/test/a.out

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d)