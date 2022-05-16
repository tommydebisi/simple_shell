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

/**
 * hsh_setenv - Changes or add to shell
 *
 * @shell: shell data
 * Return: 0 for success otherwise another integer
 */
int hsh_setenv(shell_t *shell)
{
	int i = 0;

	while (shell->argv[i])
		i++;

	if (i != 3)	/* handle number of arguments */
	{
		write(STDERR_FILENO, "Input 3 arguments\n", 19);
		return (0);
	}
	set_env(shell->argv[1], shell->argv[2]);
	return (0);
}

/**
 * hsh_unsetenv - Remove existing variables from shell
 * gives error if variable not found
 *
 * @shell: shell data
 * Return: 0 for success otherwise another integer
 */
int hsh_unsetenv(shell_t *shell)
{
	int i = 0;
	char *unset;

	while (shell->argv[i])
		i++;

	if (i != 2)	/* handle number of arguments */
	{
		write(STDERR_FILENO, "Input 2 arguments\n", 19);
		return (0);
	}
	unset = _getenv(shell->argv[1], 1);
	if (_strcmp("bad", unset) == 0)
		write(STDERR_FILENO, "Variable not in Environment\n", 29);
	return (0);
}
