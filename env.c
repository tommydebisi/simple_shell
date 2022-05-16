#include "shell.h"

static list_env *EnvVar;

/**
 * manage_env_list - initializes or frees the environment list
 *
 * @free_vars: If 1, free environment variables, otherwise initialize it.
 */
void manage_env_list(int free_vars)
{
	list_env *head = NULL, *last_node = NULL, *new_node, *current;
	char *token;
	int i;

	if (free_vars)
	{
		current = head = EnvVar;

		while (head != NULL)
		{
			current = current->next, free(head->name), free(head->content);
			free(head);
			head = current;	/* move to the next address */
		}
		EnvVar = NULL;
		return;
	}
	for (i = 0; environ[i] != NULL; i++)
	{
		token = NULL, new_node = NULL, new_node = malloc(sizeof(list_env));
		if (new_node == NULL)
			free(new_node), exit(1);

		token = strtok(environ[i], "=");
		if (token == NULL)
			free(new_node), exit(EXIT_FAILURE);

		new_node->name = _strdup(token);
		token = strtok(NULL, "\n");
		new_node->content = _strdup(token);
		new_node->next = NULL;

		head = head == NULL ? new_node : head;	/* add node at end of list */
		if (last_node != NULL)
			last_node->next = new_node;

		last_node = new_node;
	}
	EnvVar = head;
}

/**
 * env_to_array - create environment array from list
 *
 * Return: pointer to a malloced string of env variables
 */
char **env_to_array(void)
{
	list_env *node;
	int n = 0, i = 0, j;
	char **env = NULL;

	node = EnvVar;
	while (node != NULL)
	{
		n++;
		node = node->next;
	}
	node = EnvVar;
	env = malloc(sizeof(char *) * (n + 1));

	while (node != NULL)
	{
		n = 0;
		for (j = 0; node->name[j] != '\0'; j++)
			n++;
		n++;
		for (j = 0; node->content[j] != '\0'; j++)
			n++;
		env[i] = malloc(sizeof(char) * (n + 1));
		n = 0;
		for (j = 0; node->name[j] != '\0'; j++, n++)
			env[i][n] = node->name[j];
		env[i][n] = '=', n++;
		for (j = 0; node->content[j] != '\0'; j++, n++)
			env[i][n] = node->content[j];
		env[i][n] = '\0';
		node = node->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}
/**
 * set_env - changes enviroment variable and
 * adds variable to the end of the list
 *
 * @name: name of variable to add
 * @value: content of the variable
 */
void set_env(const char *name, const char *value)
{
	list_env *new_node, *current, *tail;

	current = EnvVar;

	/* traverse list and check if name is present */
	while (current != NULL)
	{
		if (strcmp(name, current->name) == 0)
		{
			free(current->content);
			current->content = strdup(value);
			return;
		}
		/* move to the next node */
		tail = current->next == NULL ? current : current->next;
		current = current->next;
	}
	/* tail is now the end node */
	new_node = malloc(sizeof(list_env));
	if (new_node == NULL)
	{
		free(new_node);
		exit(EXIT_FAILURE);
	}

	new_node->name = strdup(name);
	new_node->content = strdup(value);
	new_node->next = NULL;
	/* set next node address to new node */
	tail->next = new_node;
}

/**
 * _getenv - get the address of environment variable
 *
 * @name: value to check in the enviroment variable
 * @var: number passed in to unset env variable
 * Return: the address of environment variable or NULL if not there
 * or good if unset is successful and bad if not
 */
char *_getenv(const char *name, int var)
{
	/* Declare variables to be used */
	list_env *current, *previous;

	current = previous = EnvVar;

	if (var)
	{
		while (current && previous)
		{
			if (_strcmp(name, current->name) == 0)
			{
				previous->next = current->next;
				free(current->content);
				free(current->name);
				free(current);
				return ("good");
			}
			/* move to the next node */
			previous = current;
			current = current->next;
		}
		return ("bad");
	}
	/* traverse list and check if name is present */
	while (current != NULL)
	{
		if (strcmp(name, current->name) == 0)
			return (current->content);
			/* move to the next node */
		current = current->next;
	}

	return (NULL);
}

/**
 * hsh_env - prints env variables (builtin)
 *
 * @shell: shell data
 * Return: 0 for success otherwise another integer
 */
int hsh_env(shell_t *shell)
{
	list_env *current = EnvVar;
	char *list;
	int list_len;

	(void) shell;
	while (current != NULL)
	{
		list = _strcat2(current->name, "=", current->content);
		if (!list)
		{
			write(STDERR_FILENO, ": allocation error\n", 18);
			exit(EXIT_FAILURE);
		}

		list_len = _strlen(list);
		write(STDOUT_FILENO, list, list_len);
		write(STDOUT_FILENO, "\n", 2);
		free(list);
		current = current->next; /* move to next node */
	}

	return (0);
}
