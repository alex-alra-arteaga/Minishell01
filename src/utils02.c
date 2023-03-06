/*
** EPITECH PROJECT, 2022
** minishell01
** File description:
** Shell Programming
*/

#include "../includes/my.h"

int present_lines(char *input_split)
{
    int lines = 0;

    for (int i = 0; input_split[i]; i++)
        (input_split[i] == '\\' && input_split[i + 1] == 'n') ? lines++ : 0;
    return ((lines != 0) ? lines + 1 : 0);
}

linked_list_t *init_env(char **env)
{
    linked_list_t *env_l = malloc(sizeof(linked_list_t));
    linked_list_t *head = env_l;
    env_l->prev = NULL;
    for (int i = 0; env[i]; i++) {
        env_l->data = my_split(env[i], '=');
        if (env[i + 1]) {
            env_l->next = malloc(sizeof(linked_list_t));
            env_l->next->prev = env_l;
        } else
            env_l->next = NULL;
        env_l = env_l->next;
    }
    return head;
}

void print_not_found(char *command)
{
    my_putstr_stderr(command);
    my_putstr_stderr(": Command not found.\n");
}

void print_cd_error(int status, char **path)
{
    if (status == -1) {
        my_putstr_stderr(path[1]);
        my_putstr_stderr(": No such file or directory.\n");
    }
}
