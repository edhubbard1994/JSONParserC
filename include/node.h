#ifdef __CPLUSPLUS
extern "C" {
#endif


#ifndef JSON_NODE_H
#define JSON_NODE_H

#include "token.h"

typedef struct {
    Token *openQuote;
    Token *closeQuote;
    Token *value;
}StringLiteral;

typedef struct {
    Token *boolValue;
}Boolean;

typedef enum {
    INTEG,
    DOUB
}number_type_t;

typedef struct {
    number_type_t type;
    Token *negative;
    Token *value;
}Number;

typedef struct {
    Token *value;
}IntegerLiteral;

typedef struct {
    char* message;
}CompilerError;

typedef enum {
    ROOT_BLOCK,
    ROOT_ARR
}root_type_t;

typedef struct {
    root_type_t type;
    void *start;
}Root;


typedef enum {
    VAL_BLOCK,
    VAL_ARR,
    VAL_NUM,
    VAL_STRING
}value_type_t;


typedef struct {
    value_type_t type;
    void *value;
}Value;

typedef struct {
    StringLiteral *key;
    Value *value;
}Pair;

typedef struct {
    unsigned int pair_length;
    Token *openBrace;
    Token *closeBrace;
    Pair  **pairs;
}Block;

typedef struct {
    unsigned int length;
    Token *openBracket;
    Token *closeBracket;
    Value *values;
}Array;













#endif

#ifdef __CPLUSPLUS
}
#endif