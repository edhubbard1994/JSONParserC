#ifdef __CPLUSPLUS
extern "C" {
#endif


#ifndef JSON_NODE_H
#define JSON_NODE_H

typedef enum {
    False = 0,
    True = 1
} boolean;

typedef struct {
    void *child;
    void *next;
} JSONObject;

typedef struct {
    void *start;
    void *next;
} JSONArray;


struct Str {
    char *key;
    char *value;
    void *next;
};

struct Int {
    char *key;
    int value;
    void *next;
};

struct Double {
    char *key;
    double value;
    void *next;
};

struct Bool {
    char *key;
    boolean value;
    void *next;
};



#endif

#ifdef __CPLUSPLUS
}
#endif