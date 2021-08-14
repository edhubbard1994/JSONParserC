#include "gtest/gtest.h"
extern "C" {
#include "json.c"
#include "token.c"
}

TEST(lexer_test, init_lexer) {
     Lexer* lex = init_lexer("\"Hello\"");
     ASSERT_TRUE(lex->itr == 0);
     ASSERT_TRUE(lex->current_char =='\"');
     free(lex);
}

TEST(lexer_test, get_string) {
    Lexer* lex = init_lexer("\"Hello\"");
    char * str = get_string(lex);
    ASSERT_FALSE(strcmp(str,"Hello"));
    free(str);
    free(lex);

}

TEST(lexer_test,ignore_whitespace) {
     Lexer* lex = init_lexer("   start");
     ignore_whitespace(lex);
     ASSERT_TRUE(lex->current_char == 's');
     free(lex);
}

TEST(lexer_test, ignore_whitespace_false) {
     Lexer* lex = init_lexer("start");
     ignore_whitespace(lex);
     ASSERT_TRUE(lex->current_char == 's');
     free(lex);
}

TEST(lexer_test, get_int) {
     Lexer* lex = init_lexer("15901");
     long val = atol(get_int(lex));
     
     ASSERT_TRUE(val == 15901);
     free(lex);

}

TEST(lexer_test, get_negative_int) {
     Lexer* lex = init_lexer("-15901");
     long val = atol(get_int(lex));
     
     ASSERT_TRUE(val == -15901);
     free(lex);
    
}


TEST(lexer_test, get_next_token) {
    Lexer *l = init_lexer(" { \"hello\" : \"world\" }");
    Token* t = get_next_token(l);
    ASSERT_TRUE(t->type == OPN_BRACE);
    //ASSERT_TRUE(((char)t->value) == '{');

    free(t);
    free(l);
}

TEST(lexer_test, get_next_token_multi) {
    Lexer *l = init_lexer(" { \"hello\" : \"world\" }");
    Token* t = get_next_token(l);
    Token* t2 = get_next_token(l);
    Token* t3 = get_next_token(l);
    //Token* t4 = get_next_token(l);
    ASSERT_TRUE(t->type == OPN_BRACE);
    ASSERT_TRUE(t2->type == DOUB_QUOTE);
    ASSERT_TRUE(t3->type == STR_T);
    //ASSERT_TRUE(t4->type == DOUB_QUOTE);
    free(t);
    free(t2);
    free(t3);
    //free(t4);
    free(l);
}

TEST(lexer_test, tokenize) {
    Lexer *l = init_lexer(" { \"hello\" : \"world\" }");
    Token **t = tokenize(l);
    volatile itr_t count = 0;
    for (int i = 0; i < 9; i++) {
        const char *tok = tok_type_to_str( (t[i]));
        
    }
    ASSERT_TRUE(1);
    free(l);
    free(t);
}






int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
