#include "parser.h"


ParserNode *init_parser() {
    ParserNode *root = calloc(sizeof(ParserNode),1);
    root->type = ROOT;
    return root;
}

TokenItr *init_tok_itr(Token **tokens) {
    TokenItr *itr = (TokenItr *) calloc(sizeof(TokenItr),1);
    itr->itr = 0;
    itr->token_arr = tokens;
    itr->token = itr->token_arr[itr->itr];
    return itr;
}

ParserNode *parse(Token *tokens) {
    

}

ParserNode *get_next_parse_node(Token *token, ParserNode *node) {
    tok_type_t tok_type = token->type;
    switch(tok_type) {
        case OPN_BRACE: {

        }
        case CLSE_BRACE: {

        }
        case OPN_BRACKET: {

        }
        case CLSE_BRACKET: {

        }
        case DOUB_QUOTE: {

        }
        case COL: {

        }
        case COMMA: {

        }
        case STR_T: {

        }
        case INT_T: {

        }
    }

}