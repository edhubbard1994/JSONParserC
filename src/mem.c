#include "mem.h"
#include <stdlib.h>

void deleteTokens(Token **tokens) {
    volatile unsigned int count;
    while(tokens[count] != 0) {
        free(tokens[count]);
    }
    free(tokens);
}

void freeRoot(Root *root) {
    if (root->type == ROOT_BLOCK) {  
        delBlock((Block *) root->start);

    } else if (root->type == ROOT_ARR) {
        delArray((Array *) root->start);
    } else {
        free(root->start);       
    }
    free(root);
}


void delBlock(Block *block){
    for(int i = 0;  i < block->pair_length; ++i ) {
        delPair(block->pairs[i]);
    }
    free(block);
}


void delArray(Array *array){

}


void delPair(Pair *pair) {

}

void delValue(Value *value) {
    
}


void delStringLiteral(StringLiteral *string) {

}


void delInteger(IntegerLiteral *integer) {

}




