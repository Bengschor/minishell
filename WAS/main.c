#include "minishell.h"


int main(int argc, char **argv, char *envp[]) {
    t_shell shell;
    // (void)argc;
    // (void)argv;
    // (void)envp;

    shell.env = envp;
    while(1)
    {
        // init_shell(shell);
        shell.input = get_input();
        if (!shell.input)
        {
            printf("c'est la fin\n");
            return 0;
        }
        argv = ft_split(shell.input, ' ', &argc);
        if (if_same_word(argv[0], "pwd"))
            do_pwd(argc);
        else if (if_same_word(argv[0], "echo"))
            do_echo(argc, argv);
        else if (if_same_word(argv[0], "cd"))
            do_cd(argv[1], &shell);
        else if (if_same_word(argv[0], "env"))
            do_env(argc, shell.env);
        else if (if_same_word(argv[0], "exit"))
            do_exit();
        else if (if_same_word(argv[0], "export"))
            do_export(argc, argv, &shell.env);
        else if (if_same_word(argv[0], "unset"))
            do_unset(argv, argc, shell.env);
        else if (if_same_word(argv[0], "ls"))
            do_ls(shell.env);
        else if (if_same_word(argv[0], "clear"))
            do_clear(shell.env);
        else if (argv[0])
            printf("zsh: command not found: %s\n", shell.input);
        free(shell.input);
    }
    return 0;
}


