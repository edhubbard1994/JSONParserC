#ifdef __CPLUSPLUS
extern "C" {
#endif


#ifndef JSON_H
#define JSON_H

#include "node.h"

#include <stdlib.h>


typedef enum{
    VALID = 0,
    FORMAT = 1,
    DUPLICATE_KEY = 2,
} json_status_t;

typedef volatile unsigned int itr_t ;


typedef struct {
    char current_char;
    itr_t itr;
    const char *string;
}  Lexer;


Lexer *init_lexer(const char* str);
void incr_lexer(Lexer *lexer);
void decr_lexer(Lexer *lexer);
void ignore_whitespace(Lexer *lexer);
char *get_string(Lexer *lexer);
char *get_int(Lexer *lexer);
char *get_double(Lexer *lexer);
Token *get_next_token(Lexer *lexer);
Token **tokenize(Lexer *lexer);




#endif

#ifdef __CPLUSPLUS
}
#endif