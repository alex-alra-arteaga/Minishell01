/*
** EPITECH PROJECT, 2022
** minishell01
** File description:
** Shell Programming
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include "../includes/my.h"

void setenv_values(char **path, linked_list_t *env_l)
{
    bool encountered = false;
    bool passed = false;
    linked_list_t *prev;
    char *(values[2]) = {path[1], (!path[2]) ? path[2] = "\n" : path[2]};
    for (int i = 0; env_l->next; i++) {
        prev = env_l;
        (my_strcmp(path[1], env_l->data[0]) == 0)
        ? env_l->data[1] = path[2], encountered = true : 0;
        if (!encountered && !env_l->next && !passed) {
            env_l = malloc(sizeof(linked_list_t));
            passed = true;
        }
        env_l = env_l->next;
    }
    if (!encountered) {
        env_l->prev = prev;
        env_l->data = my_arrdup(values, 2);
        env_l->next = NULL;
    }
}
