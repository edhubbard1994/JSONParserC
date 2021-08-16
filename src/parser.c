#include "parser.h"
#include "node.h"


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

void advance_tok_itr(TokenItr *itr) {
    itr->itr ++;
    itr->token = itr->token_arr[itr->itr];
}

ParserNode *init_root() {
    ParserNode *root = (ParserNode *) calloc(sizeof(ParserNode), 1);
    Root *rootNode = (Root *) calloc(sizeof(Root), 1);
    root->type = ROOT;
    root->node = (void *) rootNode;
    return root;
}


Root *parse(Token **tokens) {
    TokenItr *itr = init_tok_itr(tokens);
    ParserNode *root_node = init_root();
    

}

ParserNode *get_next_parse_node(TokenItr *itr, ParserNode *node) {
    node_type_t node_type = node->type;
     ParserNode *nextNode = calloc(sizeof(ParserNode), 1);
    switch(node_type) {
        case ROOT: {
            nextNode->node
        }

        default:
            return 0;
    }

}




Root *visitRoot(TokenItr *itr) {
    Root *root = calloc(sizeof(Root),1);
    if (itr->token->type == OPN_BRACE) {  
        root->type = BLOCK;     
        root->start = visitBlock(itr);

    } else if (itr->token->type == OPN_BRACKET) {
        root->type = ARRAY;
        root->start = visitArray(itr);
    } else {
        root->start = visitError("JSON object must start with a { or [");
    }
}


Block *visitBlock(TokenItr *itr) {
    Block *block = calloc(sizeof(Block), 1);
    block->openBrace = itr->token;
    advance_tok_itr(itr);
    if (itr->token->type != DOUB_QUOTE) {
        return 0;
    }
}

Array *visitArray(TokenItr *itr) {

}

Pair *visitPair(TokenItr *itr) {

}

Value *visitValue(TokenItr *itr) {

}

StringLiteral *visitStringLiteral(TokenItr *itr) {

}

IntegerLiteral *visitInteger(TokenItr *itr) {

}

CompilerError *visitError(char *message) {
    CompilerError *err = calloc(sizeof(CompilerError),1);
    err->message = message;
    return err;
}