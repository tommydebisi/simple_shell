#include "shell.h"

/**
 * repl - Read-Eval-Print-Loop for the shell
 *
 * @shell: shell data
 */
void repl(shell_t *shell)
{
	char *cmd;
	int chr, flag, isLoop;

	do {
		isLoop = 1;
		prompt();

		cmd = read_line(&chr);
		if (chr == -1)
		{
			free(cmd);
			free_env();	/* free list */
			write(STDOUT_FILENO, "\n", 2);
			exit(EXIT_SUCCESS);
		}

		if (cmd == NULL)
			continue;

		flag = parse_command(shell, cmd);
		if (flag == EXIT_IND)
			isLoop = 0;
	} while (isLoop);
}
