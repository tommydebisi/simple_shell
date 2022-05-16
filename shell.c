#include "shell.h"

/**
 * main - Runs the shell
 *
 * Return: 0
 */
int main(void)
{
	shell_t shell;

	initialize(&shell);
	signal(SIGINT, handl_signint);
	repl(&shell);
	uninitialize(&shell);

	return (0);
}
