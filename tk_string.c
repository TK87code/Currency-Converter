#include <string.h>
#include <stdlib.h>

#include "tk_string.h"

/* 
WARNING: Using malloc, make sure to free in the client code.
Take a string as a parameter, find the string passed in the parameter, replace the substring with the string given.
    Return 0 on errors;
*/
char* tkstr_replace(char *src, char *find, char *replace_with)
{
    char *result;         /* result string to return */
    char *insert_point;   /* next insert point */
    char *tmp;
    int len_find;         /* length of the string to find */
    int len_replace_with; /* length of the string to replace */
    int len_front;        /* distance between "find" and end of last "replace_with" */
    int count;            /* number of replacements */
    
    /* sanity checks and initializations */
    if(!src || !find) 
        return 0;
    
    len_find = strlen(find);
    if (len_find == 0) 
        return 0; /* avoiding infinit loop */
    
    if (!replace_with) 
        replace_with = "";
    
    len_replace_with = strlen(replace_with);
    
    insert_point = src;
    
    /* Count the number of replacements needed */
    for (count = 0; (tmp = strstr(insert_point, find)); count++)
    {
        insert_point = tmp + len_find;
    }
    
    /* Allocate memory for the new string */
    result = tmp = malloc(strlen(src) + (len_replace_with - len_find) * count - 1);
    
    if (!result) 
        return 0;
    
    while(count--){
        insert_point = strstr(src, find); 
        len_front = insert_point - src;
        tmp = strncpy(tmp, src, len_front) + len_front; 
        tmp = strcpy(tmp, replace_with) + len_replace_with;
        src += len_front + len_find;  
    }
    
    strcpy(tmp, src); 
    
    return result;
}

/* 
Take a pointer of a string as a parameter, find a char, erase after of it (including the char).
    Return 0 on success, -1 on errors;
*/

int tkstr_erase_after_char(char **src, char find){
    char *tmp;   /* this contains the address of returning string */
    char *p;        /* the position of the character */
    int len_tmp; /* The length of tmp */
    
    /* Sanity check */
    if (*src == 0 || find == '\0')
        return -1;
    
    p = strchr(*src, (int)find); 
    if (!p)
        return -1; 
    
    len_tmp = p - *src; 
    
    tmp = malloc(len_tmp * sizeof(char));
    
    if (!tmp)
        return -1;
    
    tmp = strncpy(tmp, *src, len_tmp);
    tmp[len_tmp] = '\0'; 
    memcpy(*src, tmp, sizeof(*tmp));
    
    free(tmp);
    
    return 0;
}

/*
Take a pointer of a string as a parameter, find a char, erase words untill the char position(including the char).
    Return 0 on success, -1 on error;
*/
int tkstr_erase_until_char(char **src, char find){
    char *tmp;     /* return value */
    char *p;       /* the position of the character found */
    int len_src;   /* length of the src */
    int len_front; /* length of the string untill the character(the position that shoulg be deleted) */
    int len_tmp;   /* length of the result */
    
    
    /* Sanity check */
    if (*src == 0 || find == '\0')
        return -1;
    
    p = strchr(*src, (int)find);
    
    if (!p) 
        return -1;
    
    len_src = strlen(*src);
    len_front = (p + 1) - *src;
    len_tmp = len_src - len_front;
    
    tmp = malloc(len_tmp * sizeof(char));
    
    if (!tmp)
        return -1;
    
    tmp = strncpy(tmp, *src + len_front, len_tmp);
    tmp[len_tmp] = '\0'; /* Strncpy() does not insert '\0' */
    
    memcpy(*src, tmp, sizeof(*tmp));
    
    free(tmp);
    
    return 0;
}