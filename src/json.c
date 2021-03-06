#include "json.h"
#include "token.h"

#include <regex.h>
#include <string.h>
#include <stdio.h>



#define OPEN_BRACE     '{'
#define CLOSE_BRACE    '}'
#define OPEN_BRACKET   '['
#define CLOSE_BRACKET  ']'

#define COLON_OPERATOR ':'
#define COMMA_OPERATOR ','
#define DOT            '.'

#define  DOUBLE_QUOTE  '"'


#define  WHITESPACE    ' '

#define NEGATIVE       '-'
#define NEW_LINE       '\n'
#define TAB            '\t'
#define RET            '\r'

#define EOS '\0'


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
    itr_t start = (lexer->itr);
    itr_t end = start;
    unsigned int diff = 0;
    char *str_mem;
    char *ret_ptr;
    const void *copy_start = &(lexer->string[start]);

    printf("str start: %c\n", lexer->current_char);
    while (lexer->string[end] != '"' 
            && lexer->string[end] != '\0'
            && lexer->string[end] != NULL) {
                end ++;
                incr_lexer(lexer);
            }
    diff = end - start;
    str_mem = (char *) calloc(diff, sizeof(char));
    ret_ptr = (char *) memcpy(str_mem, copy_start, diff);
    printf("the string is: %s\n", ret_ptr);
    return ret_ptr;

}

char *get_number(Lexer *lexer) {
    itr_t start = (lexer->itr);
    itr_t end = start;
    unsigned int diff = 0;
    char *str_mem;
    char *ret_ptr;
    const void *copy_start = &(lexer->string[start]);

    printf("str start: %c\n", lexer->current_char);
    while ((int) lexer->string[end] > 47 && (int) lexer->string[end] < 58 ) {
                end ++;
                incr_lexer(lexer);
            }
    diff = end - start;
    str_mem = (char *) calloc(diff, sizeof(char));
    ret_ptr = (char *) memcpy(str_mem, copy_start, diff);
    printf("the string is: %s\n", ret_ptr);
    return ret_ptr;
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
            
            break;
        case CLOSE_BRACE:
            token = init_token( CLSE_BRACE, &lexer->current_char);      

            break;
        case DOUBLE_QUOTE:
            token = init_token( DOUB_QUOTE, &lexer->current_char);     
            printf("double quotes \n");
            break;
        case COLON_OPERATOR:
            token = init_token( COL, &lexer->current_char);
            printf("colon separator\n");
            break;
        case COMMA_OPERATOR:
            token = init_token(COMMA, &lexer->current_char);
            printf("comma \n");
            break;
        case '0'...'9':
            token = init_token( INT_T,  get_int(lexer));
            break;

        case NEGATIVE:
            printf("negative\n");
            token = init_token(NEGATE, &lexer->current_char);
            break;
        case 'a'...'z':
        case 'A'...'Z':
            token = init_token( STR_T, get_string(lexer));
            break;
        case NEW_LINE:
        case RET:
        case TAB:
        case WHITESPACE:
            printf("space\n");
            incr_lexer(lexer);
            return get_next_token(lexer);
            break;

        case EOS:
            token = init_token( END_OF_STR, "00");
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
       
        count++;
    }
    // so delete itr's do not seg fault
    tokens = (Token **) realloc(tokens,sizeof(Token)); 
    return tokens;
}





