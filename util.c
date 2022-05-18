#include "shell.h"


/**
 * _realloc - reallocates a memory block.
 * @ptr: pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(newptr, ptr, new_size);
	else
		_memcpy(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}

/**
 * _realloc2 - reallocates a memory block of a double pointer.
 * @ptr: double pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
char **_realloc2(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		newptr[i] = ptr[i];

	free(ptr);

	return (newptr);
}

/**
 * cd_to - moves to a directory
 *
 * @dir: directory to move to
 */
void cd_to(char *dir)
{
	char *home, *pwd, cwd[PATH_MAX];
	int check;

	getcwd(cwd, sizeof(cwd));
	home = _strdup(cwd);
	check = chdir(dir);
	if (check == -1)
	{
		free(home);
		write(STDERR_FILENO, "/bin/sh: ", 10);
		write(STDERR_FILENO, "18: cd: can't cd to tim", 24);
		return;
	}
	getcwd(cwd, sizeof(cwd));
	pwd = _strdup(cwd);

	set_env("PWD", pwd);
	set_env("OLD_PWD", home);
	free(home);
	free(pwd);
}

/**
 * cd_prev - moves to previous directory
 */
void cd_prev(void)
{
	char *home, *pwd, cwd[PATH_MAX], *wd;

	pwd = _strdup(_getenv("PWD", 0));
	home = _getenv("OLD_PWD", 0);

	if (!home)	/* check if there's OLD_PWD */
	{
		getcwd(cwd, sizeof(cwd));
		wd = _strdup(cwd);
		set_env("OLD_PWD", wd);
		free(wd);
	}
	home = _getenv("OLD_PWD", 0);
	chdir(home);

	getcwd(cwd, sizeof(cwd));
	write(STDOUT_FILENO, cwd, _strlen(cwd));	/* write dir. path */
	write(STDOUT_FILENO, "\n", 2);

	set_env("PWD", home);
	set_env("OLD_PWD", pwd);
	free(pwd);
}
