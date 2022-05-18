#include "shell.h"

/**
 * main - Runs the shell
 *
 * @ac: number of arguments
 * @av: argument element
 * Return: 0
 */
int main(int ac __attribute__((unused)), char *av[] __attribute__ ((unused)))
{
	shell_t shell;

	shell.pName = av[0];

	initialize(&shell);
	signal(SIGINT, handl_signint);
	repl(&shell);
	uninitialize(&shell);
	return (shell.exitcode);
}
