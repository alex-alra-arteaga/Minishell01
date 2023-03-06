/*
** EPITECH PROJECT, 2022
** minishell01
** File description:
** Shell Programming
*/

#include "../includes/my.h"

int main(int argc, char **argv, char **env)
{
    (void)argv;
    if (argc != 1)
        return (84);
    input_loop(env);
}
