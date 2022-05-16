#include "shell.h"

static list_env *EnvVar;

/**
 * envir - adds environment variables to linked list
 *
 * Return: first node in the list
 */
void envir(void)
{
	list_env *head = NULL, *last_node = NULL, *new_node;
	char *token;
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		token = NULL;
		new_node = NULL;
		new_node = malloc(sizeof(list_env));
		if (new_node == NULL)
		{
			free(new_node);
			exit(1);
		}

		token = strtok(environ[i], "=");
		if (token == NULL)
		{
			free(new_node);
			exit(EXIT_FAILURE);
		}
		new_node->name = _strdup(token);

		token = strtok(NULL, "\n");
		new_node->content = _strdup(token);
		new_node->next = NULL;
		/* add node at the end of list */
		head = head == NULL ? new_node : head;
		if (last_node != NULL)
			last_node->next = new_node;
		last_node = new_node;
	}
	EnvVar = head;
}

/**
 * free_env - free list holding environment vairables
 *
 */

void free_env(void)
{
	list_env *current, *head;

	current = head = EnvVar;

	while (head != NULL)
	{
		current = current->next;
		free(head->name);
		free(head->content);
		free(head);
		/* move to the next address */
		head = current;
	}
	EnvVar = NULL;
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
 * Return: the address of environment variable or NULL if not there
 */
char *_getenv(const char *name)
{
	/* Declare variables to be used */
	list_env *current;

	current = EnvVar;

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
