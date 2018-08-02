#ifndef STRING_FUNCS_H
#define STRING_FUNCS_H 

#define MAX_STRING 1024

char* string_double(char *str, char *response);

char* string_reverse(char *str, char *response);

char* string_delete(char* str, char *token_str, char *response);

char* string_replace(char *str, char *token_str, char *response);

char* string_encrypt(char *str, char *response);

char* string_decrypt(char *str, char *response);

int string_split(char *str, char *delimeter, int limit, char **tokens);

void string_trim(char *str);


#endif
