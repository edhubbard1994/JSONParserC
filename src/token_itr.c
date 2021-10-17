#include "token_itr.h"

TokenItr *init_tok_itr(Token **tokens) {
    TokenItr *itr = (TokenItr *) calloc(sizeof(TokenItr),1);
    itr->itr = 0;
    itr->token_arr = tokens;
    itr->token = itr->token_arr[itr->itr];
    return itr;
}

void advance_tok_itr(TokenItr *itr) {
    itr->itr ++;
    itr->token = itr->token_arr[itr->itr];
}
