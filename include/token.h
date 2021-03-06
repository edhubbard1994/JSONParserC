#ifdef __CPLUSPLUS
extern "C" {
#endif


#ifndef TOKEN_H
#define TOKEN_H


typedef enum {
    OPN_BRACE,
    CLSE_BRACE,
    OPN_BRACKET,
    CLSE_BRACKET,
    DOUB_QUOTE,
    COL,
    COMMA,
    STR_T,
    INT_T,
    BOOL_T,
    DOUBLE_T,
    UNDEFINED,
    NEGATE,
    END_OF_STR
} tok_type_t;

typedef struct {
    tok_type_t type;
    char *value;
} Token;


Token *init_token(tok_type_t type, char *val);
const char *tok_type_to_str(Token *token);





#endif

#ifdef __CPLUSPLUS
}
#endif