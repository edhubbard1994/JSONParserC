#include "parser.h"
#include <stdlib.h>
#include <stdio.h>


void parse_error(char *error) {
    printf("Parser Error:\n %s\n",error);
}






Root *parse(TokenArr *tokens) {
    TokenItr *itr = init_tok_itr(tokens);
    return 0;

}





Root *visitRoot(TokenItr *itr) {
    /**
     * @brief 
     * Start of the visiter pattern tree traversal. All objects initialized with a root node.
     * @param itr
     */
    Root *root = (Root *) calloc(sizeof(Root),1);
    if (itr->token->type == OPN_BRACE) {  
        root->type = ROOT_BLOCK;     
        root->start = visitBlock(itr);

    } else if (itr->token->type == OPN_BRACKET) {
        root->type = ROOT_ARR;
        root->start = visitArray(itr);
    } else {
        root->start = visitError("JSON object must start with a { or [");
    }
    return root;
}


Block *visitBlock(TokenItr *itr) {
    Block *block = (Block *) calloc(sizeof(Block), 1);
    block->openBrace = itr->token;
    advance_tok_itr(itr);
    if (itr->token->type != DOUB_QUOTE) {
        free(block);
        return 0;
    }
    int count= 0;
    int size = 1;
    Pair **pairs = (Pair **) calloc(sizeof(Pair), size);
    while(itr->token->type == DOUB_QUOTE) {
       pairs[count] = visitPair(itr);
       count ++;
       if (count >= size) {
           size *= 2;
           pairs = (Pair **) realloc(pairs,size * sizeof(Pair));
       }
       block->pair_length = count + 1;

    }
    block->pairs = pairs;
    block->closeBrace = itr->token;
    return block;
}

Array *visitArray(TokenItr *itr) {
    Array * array = (Array *) calloc(sizeof(Array), 1);
    int  size = 1;
    int count = 0;

    array->openBracket = itr->token;
    advance_tok_itr(itr);
    Value **values = (Value **) calloc(sizeof(Value), size);
    while(itr->token->type != CLSE_BRACKET) {
        if (itr->token->type == COMMA) {
            advance_tok_itr(itr);
        } else if (itr->token->type == CLSE_BRACKET) {
            break;
        }
        values[count] = visitValue(itr);   
        count ++;
        if (count >= size) {
            size *= 2;
            values = (Value **) realloc(values, size * sizeof(Value));
        }   
    }
    array->closeBracket = itr->token;
    array->length = count + 1;
    return array;

}

Pair *visitPair(TokenItr *itr) {
    Pair *pair = (Pair *) calloc(sizeof(Pair), 1);
    pair->key = visitStringLiteral(itr);
    if (itr->token->type != COL) {
        parse_error("expected ':' separator in key value pair");
        free(pair);
        return 0;
    }
    advance_tok_itr(itr);
    pair->value = visitValue(itr);
    return pair;

}

Value *visitValue(TokenItr *itr) {
    Value *value = (Value *) calloc(sizeof(Value),1);
    switch(itr->token->type) {
        case NEGATE: {
            value->value = visitInteger(itr);
        }
        case INT_T: {
            value->value = visitInteger(itr);
            break;
        }
        case DOUB_QUOTE: {
            value->value = visitStringLiteral(itr);
            break;
        }
        case DOUBLE_T: {
             break;
        }
        case OPN_BRACKET: {
            value->value = visitArray(itr);
             break;
        }
        case OPN_BRACE: {
            value->value = visitBlock(itr);
             break;
        }
        default: {
            parse_error("expected primitive data type or object for json value");
            free(value);
            return 0;
        }     
    }
     advance_tok_itr(itr);
     return value;
}

StringLiteral *visitStringLiteral(TokenItr *itr) {
    StringLiteral *str = (StringLiteral *) calloc(sizeof(StringLiteral),1);
    if (itr->token->type != DOUB_QUOTE) {
        parse_error("strings must start with \" char ");
        free(str);
        return NULL;
    }
    str->openQuote = itr->token;
    advance_tok_itr(itr);
    if (itr->token->type != STR_T) {
        free(str);
        return NULL;
    }
    str->value = itr->token;
    advance_tok_itr(itr);

    if (itr->token->type != DOUB_QUOTE) {
        parse_error("strings must end with \" char ");
        free(str);
        return NULL;
    }
    str->closeQuote = itr->token;
    advance_tok_itr(itr);
    return str;
}

Number *visitNumber(TokenItr *itr) {
    Number *number = (Number *) calloc(sizeof(Number), 1);
    char *temp_value;
    if (itr->token->type == NEGATE) {
        number->negative = itr->token;
        advance_tok_itr(itr);
    } 
    if (itr->token->type != INT_T) {
        free(number);
        parse_error("Expected Number Type");
        return 0;
    }
    number->value = itr->token;
    advance_tok_itr(itr);
    if (itr->token->type == PERIOD) {
        // additional parsing if number is a double
        number->type = DOUB;
        number->decimal = itr->token;
        advance_tok_itr(itr);
        if (itr->token->type != INT_T) {

            free(number);
            parse_error("expected value in double value.");
            return 0;

        }
        number->decimal_value = itr->token;
        advance_tok_itr(itr);
        return number;

    }
    number->type = INTEG;
    advance_tok_itr(itr);
    return number;
}

IntegerLiteral *visitInteger(TokenItr *itr) {
    IntegerLiteral *integer = (IntegerLiteral *) calloc(sizeof(IntegerLiteral), 1);
    int isNegative = 0;
    char *temp_value;
    if (itr->token->type == NEGATE) {
        isNegative = 1;
        advance_tok_itr(itr);
    }
    temp_value = itr->token->value;
    //integer->value
    advance_tok_itr(itr);
    return integer;
}

CompilerError *visitError(char *message) {
    CompilerError *err = (CompilerError *) calloc(sizeof(CompilerError),1);
    err->message = message;
    return err;
}


