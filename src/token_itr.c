#include <stdlib.h>
#include "token_itr.h"

TokenItr *init_tok_itr(TokenArr *tokens) {
    TokenItr *itr = (TokenItr *) calloc(sizeof(TokenItr),1);
    itr->itr = 0;
    itr->token_arr = tokens;
    itr->token = itr->token_arr->tokens[0];
    return itr;
}

void advance_tok_itr(TokenItr *itr) {
    if (itr->itr >= itr->token_arr->count) {
        return;
    }
    itr->itr ++;
    itr->token = itr->token_arr->tokens[itr->itr];
}
