#include "shell.h"


/**
 * _which - find the file for a command
 *
 * @command: command input
 * Return: 0 on failure otherwise 1
 */
char *_which(char *command)
{
	char *path, *path_dup, *spath, *file;
	struct stat st;

	path = _getenv("PATH", 0);
	if (!path)
		return (NULL);

	if (command[0] == '/')
	{
		if (stat(command, &st) == 0)
			return (_strdup(command));
	}

	path_dup = _strdup(path);
	spath = strtok(path_dup, ":");
	while (spath != NULL)
	{
		file = _strcat2(spath, "/", command);
		if (!file)
		{
			free(path_dup);
			write(STDERR_FILENO, ": allocation error\n", 18);
			exit(EXIT_FAILURE);
		}
		if (stat(file, &st) == 0)
		{
			free(path_dup);
			return (file);
		}
		free(file);
		spath = strtok(NULL, ":");
	}
	free(path_dup);

	return (NULL);
}

/**
 * check_exe - check if a path can be executed
 *
 * @path: path
 * Return: 0 on success otherwise 1
 */
int check_exe(char *path)
{
	struct stat st;
	int i;

	for (i = 0; path[i]; i++) /* is a valid path */
	{
		if (path[i] == '.')
		{
			if (path[i + 1] == '/')
				i++;
			else if (path[i + 1] == '.' && path[i + 2] == '/')
				i += 2;
			else
				return (1);
		}
	}

	if (stat(path, &st) == 0)
	{
		return (0);
	}

	return (1);
}

/**
 * err_check - check for possible errors for file to be executed
 *
 * @shell: shell data
 * @file: file to be execute
 * Return: 0 for success otherwise 1
 */
int err_check(shell_t *shell, char *file)
{
	if (file == NULL)
	{
		write_err(shell, 127);
		return (1);
	}

	if (access(file, X_OK) == -1)
	{
		write_err(shell, 126);
		return (1);
	}

	return (0);
}

/**
 * execute - executes a command
 *
 * @shell: shell data
 * Return: 0 on success otherwise 1
 */
int execute(shell_t *shell)
{
	pid_t pid;
	int sys, flag;
	char *file, **env = env_to_array();

	flag = check_exe(shell->argv[0]);
	if (flag == 0)
	{
		file = _strdup(shell->argv[0]);
	}
	else
	{
		file = _which(shell->argv[0]);
		if (!file)
		{
			write_err(shell, 127);
			return (1);
		}
	}
	if (err_check(shell, file) == 1)
		return (1);

	pid = fork();
	if (pid == 0)
	{
		execve(file, shell->argv, env);
	}
	else if (pid < 0)
	{
		perror(shell->argv[0]);
		return (1);
	}
	else
	{
		do {
			waitpid(pid, &sys, WUNTRACED); /* return status of child */
		} while (!WIFEXITED(sys) && !WIFSIGNALED(sys));
	}
	shell->exitcode = sys / 256, free_env_arr(env);
	free(file);
	return (1);
}
