#include "main.h"
#include "myquote.h"

void handle_ctrl_c(int sig __attribute__((unused))) {
    fflush(stdin);;
    write(STDERR_FILENO, "\nshell$ ", 8);
    fflush(stdout);
}

int command_processor(store_info_t *shell_info)
{
    char **tokenize, *token;
    size_t count = 0;
    command_lst *command = shell_info->cmd = _update_the_cmd(shell_info->line);

    while (command)
    {
        if (!command->tokens)
        {
            command = command->link;
            del_cmd_at_pos(&(shell_info->cmd), count);
            continue;
        }

        tokenize = command->tokens;
        for (token = *tokenize; token; token = *(++tokenize))
        {
            *tokenize = remove_quotes(token);
            free_all(1, token);
        }
        command = command->link;
        ++count;
    }

    return (count);
}

int main(int ac, char **av)
{
    store_info_t *shell_info;
    shell_info = init_prmpt(av, ac);
    signal(2, handle_ctrl_c);

    while (read_usr_input(shell_info))
    {
        command_processor(shell_info);
        while ((shell_info->tokens = remove_cmd(&(shell_info->cmd))))
        {
            executeShellCommand(shell_info);
            release_mem(&(shell_info->tokens));
        }
        free_all(1, shell_info->line);
        shell_info->line = NULL;
    }
    if (shell_info->interactive)
		write(STDOUT_FILENO, "\n", 1);

	if (shell_info->file)
		close(shell_info->fileno);

	exit(release_store_infomation(shell_info));
}