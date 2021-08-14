#include <stdio.h>
#include "json.h"

JSONObject *test_from_string() {
    char * json_string =  "{\"hello\" : \"world\"}";
    return JSON_load(json_string);
}

int main(int argv, char **argc) {
    printf("hello world\n");

}