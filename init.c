#include "shell.h"

/**
 * initialize - setup shell variables
 *
 * @shell: shell data
 */
void initialize(shell_t *shell)
{
	shell->argv = NULL;
	shell->command = NULL;
	shell->exitcode = 0;
	shell->countP = 1;

	manage_env_list(0);	/* create list of env variables */
}

/**
 * uninitialize - frees shell data
 *
 * @shell: struct holding the array we are freeing
 */
void uninitialize(shell_t *shell)
{
	(void)shell;
	manage_env_list(1);

	/**
	* for (i = 0; shell->argv[i]; i++)
	*	free(shell->argv[i]);
	*free(shell->argv);
	*/
}
