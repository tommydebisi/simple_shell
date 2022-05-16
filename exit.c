#include "shell.h"

/**
 * hsh_exit - Exit shell
 *
 * @shell: shell data
 * Return: 0 for success otherwise another integer
 */
int hsh_exit(shell_t *shell)
{
	(void) shell;
	return (EXIT_IND);
}
