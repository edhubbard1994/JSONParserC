 
FROM alpine:latest


RUN env \
    && apk update && apk upgrade \
    && apk add --no-cache -q -f alpine-sdk git cmake make g++ lcov gettext-base jq curl gdb


RUN git clone  https://github.com/google/googletest.git /googletest
WORKDIR /googletest
RUN cmake . && make && make install
RUN rm -rf /googletest
 
RUN mkdir -p /code
WORKDIR /code

COPY ./src /code/
COPY ./include /code/
COPY ./test/lexer_test.cpp ./test/parser_test.cpp   /code/test/


  WORKDIR /code/test

  RUN g++  \
      /code/json.h \
      /code/json.c \
      /code/node.h \
      /code/node.c \
      /code/token.h \
      /code/token.c \
      /code/parser.h \
      /code/parser.c \
      \

    lexer_test.cpp -g -lgtest -lgtest_main -pthread -I /code/



  CMD ["./a.out"]

