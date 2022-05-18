#include "shell.h"

/**
 * error_message - displays error message to terminal
 * @shell: shell data
 * @message: error message
 * @status: error code
 */
void error_message(shell_t *shell, char *message, int status)
{
	int len = _strlen(shell->pName), len2, len3, len4;
	char *count, st[PATH_MAX];

	count = itoa(shell->countP, st, 10);
	len2 = _strlen(count);
	len3 = _strlen(shell->argv[0]);
	len4 = _strlen(message) + 1;

	write(STDERR_FILENO, shell->pName, len);
	write(STDERR_FILENO, ": ", 3);
	write(STDERR_FILENO, count, len2);
	write(STDERR_FILENO, ": ", 3);
	write(STDERR_FILENO, shell->argv[0], len3);
	write(STDERR_FILENO, message, len4);

	shell->exitcode = status % 256;
}

/**
 * write_err - write errors
 * @shell: the command
 * @status: error code
 */
void write_err(shell_t *shell, int status)
{
	char *message = NULL;

	switch (status)
	{
		case 126: /* Permission */
			message = _strdup(": Permission denied\n");
			break;
		case 127: /* Not found */
			message = _strdup(": not found\n");
			break;
		case 2:
			if (_strcmp(shell->argv[0], "exit") == 0)
				message = exit_error(shell);
			else if (_strcmp(shell->argv[0], "cd") == 0)
				message = cd_error(shell);
			break;
		default:
			message = _strdup(": not found\n");

	}

	if (message)
	{
		error_message(shell, message, status);
		free(message);
	}
}

/**
 * cd_error - patch the error message for cd
 * @shell: shell data
 * Return: error message
 */
char *cd_error(shell_t *shell)
{
	char *message, *template = ": cd can't cd to ";
	int len, len2;

	len = _strlen(template);
	len2 = _strlen(shell->argv[1]);
	message = malloc(sizeof(char) * (len + len2 + 2));
	if (!message)
		return (NULL);

	_strcpy(message, template);
	_strcat(message, shell->argv[1]);
	_strcat(message, "\n\0");

	return (message);
}

/**
 * exit_error - patch the error message for cd
 * @shell: shell data
 * Return: error message
 */
char *exit_error(shell_t *shell)
{
	char *message, *template = ": Illegal number: ";
	int len, len2;

	len = _strlen(template);
	len2 = _strlen(shell->argv[1]);
	message = malloc(sizeof(char) * (len + len2 + 2));
	if (!message)
		return (NULL);

	_strcpy(message, template);
	_strcat(message, shell->argv[1]);
	_strcat(message, "\n\0");

	return (message);
}
