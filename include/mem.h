#ifndef __MEM_H
#define __MEM_H

#include "token.h"
#include "node.h"
#include "token_itr.h"


void delStart(Root *root);
void delBlock(Block *block);
void delArray(Array *array);
void delPair(Pair *pair);
void delValue(Value *value);
void delStringLiteral(StringLiteral *str);
void delInteger(IntegerLiteral *integer);

void deleteTokens(TokenArr *tokens);



#endif




