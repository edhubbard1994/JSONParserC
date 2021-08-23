#include "json.h"
#include "token.h"

#include <regex.h>
#include <string.h>
#include <stdio.h>



#define  OPEN_BRACE     '{'
#define  CLOSE_BRACE    '}'
#define  OPEN_BRACKET   '['
#define  CLOSE_BRACKET  ']'

#define  COLON_OPERATOR ':'
#define  COMMA_OPERATOR ','

#define  DOUBLE_QUOTE   '\"'


#define  WHITESPACE     ' '

#define NEGATIVE        '-'
#define NEW_LINE        '\n'
#define TAB             '\t'
#define RET             '\r'


#define MAX_INT "2147483647"



Lexer *init_lexer(const char* str) {
    Lexer *lex = (Lexer *) malloc(sizeof(Lexer));
    lex->string = str;
    lex->itr = 0;
    lex->current_char = lex->string[lex->itr];
    return lex;
}

void incr_lexer(Lexer *lexer) {
    if (lexer->current_char == '\0') { 
        lexer->current_char = 0;
        return;
    }
    lexer->itr ++;
    lexer->current_char = lexer->string[lexer->itr];
}

void decr_lexer(Lexer *lexer) {
    if (lexer->itr < 1) {
        return;
    }
    lexer->itr --;
    lexer->current_char = lexer->string[lexer->itr];
}

void ignore_whitespace(Lexer *lexer) {
    while (lexer->current_char == WHITESPACE) {
        incr_lexer(lexer);
    }
}


char *get_string(Lexer *lexer) {
    itr_t start = (lexer->itr) - 1;
    const void *start_index = &(lexer->string[start]);
    while(lexer->current_char != '\"' || lexer->current_char != '\0' || lexer->current_char != NULL) {
        if (lexer->current_char == '\"') {
            break;
        }
        incr_lexer(lexer);
    }
    itr_t end = lexer->itr;
    unsigned int diff = (end - start) ;
    char *string = (char *) malloc( diff);
    decr_lexer(lexer);
    return (char *) memcpy(string,start_index, diff); 
}

char *get_int(Lexer *lexer) {
    char *number = (char *) malloc(10);
    int place = 0;
    while( ((int) lexer->current_char) < 58 && ((int) lexer->current_char) > 47 ) {
        number[place] = lexer->current_char;
        place++;
        incr_lexer(lexer);
    }
    
    return number;
}

char *get_double(Lexer *lexer) {
    return  0;
}

Token *get_next_token(Lexer *lexer) {
    Token *token = NULL;
    switch (lexer->current_char)
    {
        case OPEN_BRACE :
            token = init_token( OPN_BRACE, &lexer->current_char);
            ignore_whitespace(lexer);
            break;
        case CLOSE_BRACE:
            token = init_token( CLSE_BRACE, &lexer->current_char);
            ignore_whitespace(lexer);
            break;
        case DOUBLE_QUOTE:
            token = init_token( DOUB_QUOTE, &lexer->current_char);
            break;
        case COLON_OPERATOR:
            token = init_token( COL, &lexer->current_char);
            ignore_whitespace(lexer);
            break;
        case COMMA_OPERATOR:
            token = init_token(COMMA, &lexer->current_char);
            break;
        case '0'...'9':
            token = init_token( INT_T,  get_int(lexer));
            break;

        case NEGATIVE:
            token = init_token(NEGATE, &lexer->current_char);
            break;
        case 'a'...'z':
        case 'A'...'Z':
            token = init_token( STR_T, get_string(lexer));
            break;
        case NEW_LINE:
        case RET:
        case WHITESPACE:
            incr_lexer(lexer);
            token = get_next_token(lexer);
            break;
        
        default:
            token = init_token( UNDEFINED, get_string(lexer));
            break;
        
    }
    incr_lexer(lexer);
    return token;
}

Token **tokenize(Lexer *lexer) {
    size_t arr_size = 20;
    Token **tokens = (Token **) calloc(arr_size,sizeof(Token));
    volatile itr_t count = 0;
    ignore_whitespace(lexer);
    while(lexer->current_char != 0) {
        if (count >= arr_size){
            arr_size *= 2;
            tokens = (Token **) realloc(tokens,(arr_size * sizeof(Token)) );
        }
        
        Token *current = get_next_token(lexer);
        tokens[count] = current;
        //printf("{ token type: %s }\n", tok_type_to_str(current) );
        count++;
    }
    return tokens;
}





