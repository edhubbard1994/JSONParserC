#ifndef __TOKEN_ITR_H
#define __TOKEN_ITR_H

#include "token.h"

typedef struct {
    Token *token;
    unsigned int itr;
    TokenArr *token_arr;
}TokenItr;


TokenItr *init_tok_itr(TokenArr *tokens);
void advance_tok_itr(TokenItr *itr);


#endif