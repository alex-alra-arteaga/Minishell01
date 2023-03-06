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

void execute_logic(char *input,  char **env, linked_list_t *env_l)
{
    int lines;
    char *path;
    char **orders;
    char **input_split;

    lines = present_lines(input);
    if (lines != 0) {
        orders = my_substr_split(input, "\\n");
        for (int i = 0; i < lines - 1; i++) {
            input_split = my_split(orders[i], ' ');
            path = is_in_path(input_split, env);
            execute_commands(input_split, env, env_l, path);
        }
    } else {
        input_split = my_split(input, ' ');
        path = is_in_path(input_split, env);
        execute_commands(input_split, env, env_l, path);
    }
}

void input_loop(char **env)
{
    char *input = NULL;
    size_t len = 0;
    linked_list_t *env_l = init_env(env);

    while (1) {
        my_putstr("$> ");
        if (getline(&input, &len, stdin) != -1) {
            remove_spaces(input);
            execute_logic(input, env, env_l);
        } else {
            free(input);
            (isatty(0) == 0) ? exit(0) : exit(2);
        }
    }
}

void trigger_command(char *path, char **input_split, char **env)
{
    int status;
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(84);
    } else if (pid == 0) {
        status = execve(path, input_split, env);
        (status == -1) ? print_not_found(input_split[0]) : 0;
        exit(0);
    } else {
        wait(&status);
        signal_handling(status);
    }
}

bool is_select_function(char **input_split, char **env, linked_list_t *env_l)
{
    const t_func func[] = {
            {"cd", &my_cd},
            {"setenv", &my_setenv},
            {"unsetenv", &my_unsetenv},
            {"env", &my_env},
            {"exit", &my_exit}
    };
    for (int i = 0; i < 5; i++) {
        if (my_strcmp(func[i].comm, input_split[0]) == 0) {
            func[i].selec_func(input_split, env_l, env);
            return (true);
        }
    }
    return (false);
}

void execute_commands
(char **input_split, char **env, linked_list_t *env_l, char *path)
{
    if (is_select_function(input_split, env, env_l))
        return;
    else if (!path) {
        path = get_path(input_split[0]);
        trigger_command(path, input_split, env);
    } else {
        trigger_command(path, input_split, env);
    }
}
