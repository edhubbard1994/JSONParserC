#ifndef __PARSER_H
#define __PARSER_H

#ifdef __CPLUSPLUS
extern "C" {
#endif

#include "token.h"
#include "pair.h"

typedef struct {
    Token *openBrace;
    Token *closeBrace;
} ObjectBlock;




#ifdef __CPLUSPLUS
}
#endif

#endif