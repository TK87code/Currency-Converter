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
    char *result; // result string
    char *insert_point; // next insert point
    char *tmp;
    int len_find; // length of the string to find
    int len_replace_with; // length of the string to replace
    int len_front; // distance between "find" and end of last "replace_with"
    int count; // number of replacements
    
    // sanity checks and initializations
    if(!src || !find) 
        return 0;
    
    len_find = strlen(find);
    if (len_find == 0) 
        return 0; // avoiding empty loop
    
    if (!replace_with) 
        replace_with = "";
    
    len_replace_with = strlen(replace_with);
    
    insert_point = src;
    
    // Count the number of replacements needed
    for (count = 0; (tmp = strstr(insert_point, find)); count++)
    {
        insert_point = tmp + len_find;
    }
    
    // Allocate memory for the new string
    result = tmp = malloc(strlen(src) + (len_replace_with - len_find) * count - 1);
    
    if (!result) 
        return 0;
    
    while(count--){
        insert_point = strstr(src, find); // set insert point at the beginning of the string to find.
        len_front = insert_point - src;
        tmp = strncpy(tmp, src, len_front) + len_front; // copy the front characters to temp, and move pointer. 
        tmp = strcpy(tmp, replace_with) + len_replace_with; // copy the string to replace with in tmp, then move the pointer at the end
        src += len_front + len_find; // move to the next "end of find"
    }
    
    strcpy(tmp, src); // After the replacements, copy the rest of src in temp;
    
    return result;
}

/* 
WARNING: Using malloc, make sure to free in the client code.
Take a string as a parameter, find a char, erase after of it (including the char).
    Return 0 when the func coud not find the character, and on errors;
*/

char* tkstr_erase_after_char(char *src, char find){
    char *result; // this contains the address of returning string
    char *p; // the position of the character 
    int len_result; // The length of result
    
    // Sanity check
    if (src == 0 || find == '\0')
        return (0);
    
    p = strchr(src, (int)find); // find the character and return it's position
    if (!p)
        return (0); //return 0 when can"t find the character
    
    len_result = p - src; // Calculate length of result
    
    
    result = malloc(len_result * sizeof(char));
    
    if (!result)
        return (0);
    
    result = strncpy(result, src, len_result);
    result[len_result] = '\0'; //Strncpy() does not insert '\0' 
    
    return result;
}

/*
WARNING: Using malloc, make sure to free in the client code.
Take a string as a parameter, find a char, erase words untill the char position(including the char).
    Return 0 when the func coud not find the character, and on errors;
*/
char* tkstr_erase_until_char(char *src, char find){
    char *result; // return value
    char *p; // the position of the character found
    int len_src; // length of the src
    int len_front; // length of the string untill the character(the position that shoulg be deleted)
    int len_result; // length of the result
    
    
    // Sanity check
    if (src == 0 || find == '\0')
        return (0);
    
    p = strchr(src, (int)find);
    
    if (!p) 
        return (0); //return 0 when can't find the character
    
    len_src = strlen(src);
    len_front = (p + 1) - src; // erase the character too
    len_result = len_src - len_front;
    
    result = malloc(len_result * sizeof(char));
    
    if (!result)
        return (0);
    
    result = strncpy(result, src + len_front, len_result);
    result[len_result] = '\0'; //Strncpy() does not insert '\0' 
    
    return result;
}