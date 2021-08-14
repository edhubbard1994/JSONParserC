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
         char *str = (char *) calloc(1,30) ;
         strcat(str, "< string: ");
         strcat(str, token->value);
         strcat(str, " >");
         const char * ret_val = (const char*) str;
        return ret_val;
    }
    case INT_T:{
         char *str = (char *) calloc(1,30) ;
         strcat(str, "< int: ");
         strcat(str, token->value);
         strcat(str, " >");
         const char * ret_val = (const char*) str;
        return ret_val;
    }

        
    case DOUBLE_T:
        return "< double >";
    case BOOL_T:
        return "< bool >";
    case COL:
        return "< colon >";
    case NEGATE:
        return "< negative >";
    case COMMA:
        return "< comma >";

    default:
        return "< ERROR >";
    }
}