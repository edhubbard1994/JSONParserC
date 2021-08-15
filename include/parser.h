#ifndef __PARSER_H
#define __PARSER_H

#ifdef __CPLUSPLUS
extern "C" {
#endif

#include "token.h"
#include "pair.h"

typedef struct {
    node_type_t type;
    void *node;
} ParserNode;

typedef struct {
    Token *token;
    unsigned int itr;
    Token **token_arr;
}TokenItr;

typedef enum {
    ROOT,
    BLOCK,
    ARRAY,
    PAIR,
    KEY,
    VALUE,
    NUMBER,
    STRING,
    NEGATION,
    COLON,
    COMMA
}node_type_t;


ParserNode *init_parser();
ParserNode *parse(Token *tokens);



#ifdef __CPLUSPLUS
}
#endif

#endif