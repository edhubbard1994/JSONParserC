#ifndef __MEM_H
#define __MEM_H

#include "token.h"
#include "node.h"
#include "token_itr.h"

Root *parse(Token **tokens);
Block *delBlock(TokenItr *itr);
Array *delArray(TokenItr *itr);
Pair *delPair(TokenItr *itr);
Value *delValue(TokenItr *itr);
StringLiteral *delStringLiteral(TokenItr *itr);
IntegerLiteral *delInteger(TokenItr *itr);
CompilerError *delError(char *message);


#endif




