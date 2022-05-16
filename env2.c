#include "shell.h"

/**
 * @env_to_array - convert env variables to array
 * 
 * Return: NULL terminated 2D array string of env variables
 */

char **env_to_array(void)
{
    int i = 0;
    char **env;

    for (i = 0; environ[i]; i++)
		;

	/* Make copy of the environs */
	env = malloc(sizeof(char *) * (i + 1));
	if (env == NULL)
	{
		write(STDERR_FILENO, "Error\n", 7);
		return (NULL);
	}
	for (i = 0; environ[i]; i++)
		env[i] = _strdup(environ[i]);
	env[i] = NULL;
    
    return (env);
}

/**
 * free_array_env - frees the array created
 *
 * @envr: pointer to the alloced space
 */
void free_array_env(char **env)
{
    int i;

    for (i = 0; env[i]; i++)
		free(env[i]);
	free(env);
}