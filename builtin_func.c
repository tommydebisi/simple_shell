#include "shell.h"

/**
 * hsh_exit - Exit shell
 *
 * @shell: shell data
 * Return: 0 for success otherwise another integer
 */
int hsh_exit(shell_t *shell)
{
	int stat;

	if (shell->argv[2])
	{
		shell->exitcode = 1;
		write(STDERR_FILENO, "hsh: exit: too many arguments\n", 31);
		return (0);
	}
	if (shell->argv[1])
	{
		if (!_isdigit(shell->argv[1]))
		{
			shell->exitcode = 2;
			write(STDERR_FILENO, "hsh: exit: numeric argument required\n", 38);
		}
		else
		{
			stat = _atoi(shell->argv[1]);
			printf("atoi: %d\n", stat);
			shell->exitcode = stat % 256;	/* max number is 255 */
		}
	}
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

/**
 * hsh_cd - changes directory
 *
 * @shell: shell data
 * Return: 0 for success otherwise another integer
 */
int hsh_cd(shell_t *shell)
{
	char *home, *pwd;

	if (!(shell->argv[1]) && shell->argv[0])
	{
		pwd = _strdup(_getenv("PWD", 0));
		home = _getenv("HOME", 0);
		chdir(home);
		set_env("PWD", home);
		set_env("OLD_PWD", pwd);
		free(pwd);
	}
	else if (_strcmp(shell->argv[1], "-") == 0)
		cd_prev();
	else
		cd_to(shell->argv[1], shell);

	return (0);
}
