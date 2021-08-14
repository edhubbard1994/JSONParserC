#include "token.h"

#include <stdlib.h>
#include <string.h>

Token *init_token(tok_type_t type, char *val){
    Token *tok = (Token *) malloc(sizeof(Token));
    tok->type = type;
    tok->value = val;
    return tok;
}


const char *tok_type_to_str(Token *token) {
    switch (token->type)
    {
    case OPN_BRACE:
        return "< { >";
    case CLSE_BRACE:
        return "< } >";
    case OPN_BRACKET:
        return "< [ >";
    case CLSE_BRACKET:
        return "< ] >";
    case DOUB_QUOTE:
        return "< \" >";
    case STR_T: { 
        // char *str = (char *) malloc(30) ;
        // strcat(str, (char *)"< string: ");
        // strcat(str, token->value);
        // strcat(str,(char *) " >");
        // const char * ret_val = (const char*) str;
        return "< string literal >";
    }
    case INT_T:
        return "< int >";
    case DOUBLE_T:
        return "< double >";
    case BOOL_T:
        return "< bool >";
    case COL:
        return "< colon >";

    default:
        return "< ERROR >";
    }
}