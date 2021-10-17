#include "parser.h"
#include <stdlib.h>




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




Root *parse(Token **tokens) {
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
    Pair **pairs = (Pair **) calloc(sizeof(Pair), count);
    while(itr->token->type == DOUB_QUOTE) {
       pairs[count] = visitPair(itr);
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
        size ++;
        values = (Value **) realloc(values, sizeof(Value));
    }
    return array;

}

Pair *visitPair(TokenItr *itr) {
    Pair *pair = (Pair *) calloc(sizeof(Pair), 1);
    pair->key = visitStringLiteral(itr);
    if (itr->token->type != COL) {
        free(pair);
        return 0;
    }
    pair->value = visitValue(itr);
    return pair;

}

Value *visitValue(TokenItr *itr) {
    Value *value = (Value *) calloc(sizeof(Value),1);
    switch(itr->token->type) {
        case INT_T: {
            value->value = visitInteger(itr);
            break;
        }
        case STR_T: {
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
            return 0;
        }     
    }
     return value;
}

StringLiteral *visitStringLiteral(TokenItr *itr) {
    StringLiteral *str = (StringLiteral *) calloc(sizeof(StringLiteral),1);
    str->openQuote = itr->token;
    advance_tok_itr(itr);
    str->value = itr->token;
    advance_tok_itr(itr);
    str->closeQuote = itr->token;
    advance_tok_itr(itr);
    return str;
}

IntegerLiteral *visitInteger(TokenItr *itr) {
    IntegerLiteral *integer = (IntegerLiteral *) calloc(sizeof(IntegerLiteral), 1);
    integer->value = itr->token;
    advance_tok_itr(itr);
    return integer;
}

CompilerError *visitError(char *message) {
    CompilerError *err = (CompilerError *) calloc(sizeof(CompilerError),1);
    err->message = message;
    return err;
}