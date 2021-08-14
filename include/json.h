#ifdef __CPLUSPLUS
extern "C" {
#endif


#ifndef JSON_H
#define JSON_H

#include "node.h"

#include <stdlib.h>


typedef enum{
    VALID = 0,
    FORMAT = 1,
    DUPLICATE_KEY = 2,
} json_status_t;

typedef volatile unsigned int itr_t ;


typedef struct {
    char current_char;
    itr_t itr;
    const char *string;
}  Lexer;



JSONObject *JSON_load(const char *contents);




#endif

#ifdef __CPLUSPLUS
}
#endif