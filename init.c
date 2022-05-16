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

	envir();
}

/**
 * uninitialize - frees shell data
 *
 * @shell: shell data
 */
void uninitialize(shell_t *shell)
{
	(void) shell;
	free_env();

	/**
	* for (i = 0; shell->argv[i]; i++)
	*	free(shell->argv[i]);
	*free(shell->argv);
	*/
}
