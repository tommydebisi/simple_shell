#ifndef SHELL_H
#define SHELL_H

#define BUFSIZE 1024
#define TOKEN_BUFSIZE 128
#define TOKEN_DELIM " \t\r\n\a"
#define EXIT_IND 2

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <limits.h>


/**
 * struct shell - shell data for current session
 *
 * @argv: argument vector
 * @command: input command
 * @exitcode: code to exit
 * @countP: count the processes done
 * @pName: Process name
 */
typedef struct shell
{
	char **argv;
	char *command;
	int exitcode;
	int countP;
	char *pName;
} shell_t;


/**
 * struct builtin - builtins
 *
 * @name: value of builtin
 * @handl: builtin handler
 */
typedef struct builtin
{
	char *name;
	int (*handl)(shell_t *shell);
} builtin_t;

/**
 * struct env - contains addresses of all environment variables
 *
 * @name: name of variable
 * @content: content of variable
 * @next: next address of node
 */
typedef struct env
{
	char *name;
	char *content;
	struct env *next;
} list_env;

extern char **environ;

/* setup */
void initialize(shell_t *shell);
void uninitialize(shell_t *shell);
void handl_signint(int sig);
void repl(shell_t *shell);

/* env */
void manage_env_list(int free_vars);
char **env_to_array(void);
void set_env(const char *name, const char *value);
char *_getenv(const char *name, int var);

/* env2 */
void free_env_arr(char **env);

/* executor */
int parse_command(shell_t *shell, char *command);
int execute(shell_t *shell);
int err_check(shell_t *shell, char *file);
int check_exe(char *path);

/* builtins */
int (*get_builtin_handl(const char *cmd))(shell_t *shell);
int hsh_exit(shell_t *shell);
int hsh_env(shell_t *shell);
int hsh_setenv(shell_t *shell);
int hsh_unsetenv(shell_t *shell);
int hsh_cd(shell_t *shell);

/* utils */
void prompt(void);
char *read_line(int *chr);
char **tokenize(char *s);

/* util.c */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_realloc2(char **ptr, unsigned int old_size, unsigned int new_size);
void cd_to(char *dir, shell_t *shell);
void cd_prev(shell_t *shell);

/* string functions */
char *_strdup(const char *s);
size_t _strlen(const char *s);
void *_memcpy(void *dest, const void *src, size_t n);
char *_strcat(char *dest, const char *src);
int _strcmp(const char *s1, const char *s2);
char *_strcpy(char *dest, char *src);
char *_strcat2(char *dest, char *src, char *s);
int _isdigit(char *str);
int _atoi(char *s);
char *itoa(int num, char *str, int base);
void rev_string(char *s, int len);

/* Error Handlers */
char *cd_error(shell_t *shell);
void write_err(shell_t *shell, int status);
char *exit_error(shell_t *shell);
void error_message(shell_t *shell, char *message, int status);

/* getline */
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t count);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/* Evaluate.c */
char *eval_cmd(shell_t *shell, char *cmd);
char *com_remover(char *s);

#endif /* SHELL_H */
