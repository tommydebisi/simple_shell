#include "shell.h"

/**
 * remove_comment - removes comments from s.
 *
 * @s: Given string
 * Return: String without comment
 * If there is no string return NULL
 */
char *com_remover(char *s)
{
	unsigned int len, i = 0;

	for (len = 0, i = 0; s[len]; len++)
	{
		if (s[len] == '#')
		{
			if (len == 0)
			{
				free(s);
				return (NULL);
			}
			if (s[len - 1] == ' ' || s[len - 1] == '\t')
				i = len;
		}
	}

	if (i != 0)
	{
		s = _realloc(s, len, i + 1);	/* create comment free string */
		s[i] = '\0';
	}

	return (s);
}

/**
 * eval_cmd - evaluates commands and perfroms them
 * on string
 * @shell: shell data
 * @cmd: command inputted
 * Return: String without comment
 * If there is no string return NULL
 */
char *eval_cmd(shell_t *shell, char *cmd)
{
	(void) shell;

	cmd = com_remover(cmd);
	if (!cmd)
		return (NULL);

	return (cmd);
}
