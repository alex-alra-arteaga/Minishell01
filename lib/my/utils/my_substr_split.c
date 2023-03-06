/*
** EPITECH PROJECT, 2022
** my_str_to_word_array
** File description:
** splits a string into words
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../../includes/my.h"

char **my_substr_split(char* str, char* delimiter)
{
    int orders = present_lines(str);
    char** parts = malloc((orders + 1) * sizeof(char*));
    char* token = strtok(str, delimiter);
    int i = 0;
    while (token != NULL) {
        parts[i] = token;
        i++;
        if (i == orders) {
            break;
        }
        token = strtok(NULL, delimiter);
    }
    return parts;
}
