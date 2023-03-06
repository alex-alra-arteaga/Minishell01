/*
** EPITECH PROJECT, 2022
** functions.c
** File description:
** Shell Programming
*/

#include <unistd.h>
#include "../includes/my.h"

void my_cd(char **path, linked_list_t *env_l, char **env)
{
    int i;
    int status;
    char *buf = NULL;
    size_t size = 0;
    static char *OLDPWD = NULL;

    if (!path[1] || (path[1][0] == '~' && path[1][1] == '\0' && !path[2])) {
        i = getenv_content(env, "HOME");
        char **content = my_split(env[i], '=');
        OLDPWD = getcwd(buf, size);
        status = chdir(content[1]);
    }
    if (path[1] && path[1][0] != '~'
    && path[1][0] != ' ' && path[1][0] != '-') {
        OLDPWD = getcwd(buf, size);
        status = chdir(get_path(path[1]));
    }
    if (path[1] && path[1][0] == '-' && !path[2])
        status = chdir(OLDPWD);
    print_cd_error(status, path);
}

void my_unsetenv(char **path, linked_list_t *env_l, char **env)
{
    for (int i = 0; env_l; i++) {
        (my_strcmp(path[1], env_l->data[0]) == 0)
        ? env_l->prev->next = env_l->next : 0;
        env_l = env_l->next;
    }
}

void my_setenv(char **path, linked_list_t *env_l, char **env)
{
    if (!path[1]) {
        my_env(path, env_l, env);
        return;
    }
    if (path[1][0] == '=') {
        my_putstr_stderr("setenv: Variable name must begin with a letter.\n");
        return;
    }
    if (my_arrlen(path) > 3) {
        my_putstr_stderr("setenv: Too many arguments.\n");
        return;
    }
    if (my_arrlen(path) == 3 || (my_arrlen(path) == 2))
        setenv_values(path, env_l);
}

void my_exit(char **path, linked_list_t *env_l, char **env)
{
    if (!path[1])
        exit(0);
    if (path[1] && !path[2])
        exit(my_getnbr(path[1]));
}

void my_env(char **path, linked_list_t *env_l, char **env)
{
    for (int i = 0; env_l; i++) {
        my_putstr(env_l->data[0]);
        my_putchar('=');
        my_putstr(env_l->data[1]);
        (env_l->data[1][0] == '\n') ? 0 : my_putchar('\n');
        env_l = env_l->next;
    }
}
