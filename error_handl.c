#include "shell.h"

/**
 * error_message - writes error message
 * @shell: shell data
 */
void error_message(shell_t *shell)
{
	int len = _strlen(shell->pName), len2, len3;
	char *s, st[PATH_MAX];

	len3 = _strlen(shell->argv[0]);
	s = itoa(shell->countP, st, 10);
	len2 = _strlen(s);

	write(STDERR_FILENO, shell->pName, len);
	write(STDERR_FILENO, ": ", 3);
	write(STDERR_FILENO, s, len2);
	write(STDERR_FILENO, ": ", 3);
	write(STDERR_FILENO, shell->argv[0], len3);
	write(STDERR_FILENO, ": not found\n", 13);
}
