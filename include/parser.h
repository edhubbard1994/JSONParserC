#ifndef __PARSER_H
#define __PARSER_H



#include "token.h"
#include "pair.h"
#include "node.h"
#include "token_itr.h"


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
    INT,
    DOUBLE
}node_type_t;




Root *parse(TokenArr *tokens);
Block *visitBlock(TokenItr *itr);
Array *visitArray(TokenItr *itr);
Pair *visitPair(TokenItr *itr);
Value *visitValue(TokenItr *itr);
StringLiteral *visitStringLiteral(TokenItr *itr);
IntegerLiteral *visitInteger(TokenItr *itr);
CompilerError *visitError(char *message);




#endif