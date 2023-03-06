/*
** EPITECH PROJECT, 2022
** remove_spaces.c
** File description:
** Removes all the spaces moving them non-spaces to the left
*/

#include <string.h>
#include <ctype.h>
#include "../../../includes/my.h"

bool is_space(char c)
{
    if (c == '\t' || c == ' ')
        return true;
    return false;
}

void remove_spaces(char *str)
{
    int i;
    int j;
    int len = my_strlen(str);

    for (i = 0, j = 0; i < len; i++)
        if (!is_space(str[i]) || (i > 0 && !is_space(str[i - 1])))
            str[j++] = str[i];
    while (j > 0 && is_space(str[j - 1]))
        j--;
    str[j] = '\0';
}
