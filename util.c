#include <stdio.h>
#include <string.h>
#include <ctype.h>

void str_trim(char *str) {
    if (str == NULL) return;

    char *start = str;
    
    // 1. Find the first non-whitespace character
    while (isspace((unsigned char)*start)) {
        start++;
    }

    // 2. Find the last non-whitespace character
    char *end = str + strlen(str) - 1;
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }

    // 3. Translate/shift the content to the beginning of the original pointer
    size_t length = (start <= end) ? (end - start + 1) : 0;
    if (start != str && length > 0) {
        memmove(str, start, length);
    }

    // 4. Null-terminate the string at its new length
    str[length] = '\0';
}

