/*
** EPITECH PROJECT, 2022
** minishell01
** File description:
** Shell Programming
*/

#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "../includes/my.h"

void signal_handling(int status)
{
    if (WIFSIGNALED(status)) {
        if (WCOREDUMP(status))
            my_putstr_stderr("Segmentation fault (core dumped)\n");
        if (SIGFPE == status)
            my_putstr_stderr("Floating exception (coredumped)\n");
        if (SIGFPE == status && WCOREDUMP(status)) {
            my_putstr_stderr("Segmentation fault (core dumped) && Floating ");
            my_putstr_stderr("Point exception\n");
        }
    }
}

bool is_executable(char **input)
{
    char *cwd_buff = NULL;
    size_t len = 0;
    char *dir_cwd = my_strcat(getcwd(cwd_buff, len), "/");
    char *cwd = my_strcat(dir_cwd, input[0]);
    if (access(cwd, X_OK) == 0) {
        return true;
    }
    return false;
}

int getenv_content(char **env, char *var)
{
    bool is_found = false;
    int i = 0;
    while (env[i] && !is_found) {
        if (env[i][0] == var[0] && env[i][1] == var[1]
            && env[i][2] == var[2] && env[i][3] == var[3])
            is_found = true;
        i++;
    }
    return (i - 1);
}

char *is_in_path(char **input, char **env)
{
    if (!input || !input[0])
        exit(84);
    int i = getenv_content(env, "PATH");
    char **content = my_split(env[i], '=');
    char **paths = my_split(content[1], ':');
    i = 0;
    while (paths[i]) {
        my_strcat(paths[i], "/");
        my_strcat(paths[i], input[0]);
        if (access(paths[i], X_OK) == 0) {
            return paths[i];
        }
        i++;
    }
    return NULL;
}

char *get_path(char *input)
{
    char *buf = NULL; size_t size = 0;
    char *path;
    if (input[0] == '.' && input[1] == '/') {
        if (!(buf = getcwd(buf, size)))
            exit(84);
        path = malloc(sizeof(char) * my_strlen(buf) * my_strlen(input));
        for (int i = 0; i != my_strlen(buf); i++)
            path[i] = buf[i];
        for (int j = 1; j != my_strlen(input); j++)
            path[j + my_strlen(buf) - 1] = input[j];
        return (path);
    } else if (input[0] == '/')
        return (input);
    if (input[0] != '/') {
        (!(buf = getcwd(buf, size))) ? exit(84) : 0;
        my_strcat(buf, "/");
        my_strcat(buf, input);
        return (buf);
    }
    return (NULL);
}
