#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>
#include <signal.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct data - struct that carries all associated data on runtime
 * @av: the argument vector
 * @input: the command line written by user
 * @args: tokens of the command line
 * @status: the last status of the shell
 * @counter: the lines counter
 * @_environ: the environment variable
 * @pid: the process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} shell_info;

/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} second_list;

/**
 * struct line_list_s - single linked list
 * @line: represent command line
 * @next: represent next node
 * Description: this is single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} draw_list;

/**
 * struct r_var_list - the single linked list
 * @len_var: the length of the variable
 * @val: the value of the variable
 * @len_val: the length of the value
 * @next: represent next node
 * Description: the single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var_l;

/**
 * struct builtin_s - Builtin struct for the command args.
 * @name: The name of the command builtin i.e for cd, exit, env
 * @f: data type for pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(shell_info *shinfo);
} builtin_t;

/* tha_lists.c */
second_list *add_sep_node_end(second_list **head, char sep);
void free_sep_list(second_list **head);
draw_list *add_line_node_end(draw_list **head, char *line);
void free_line_list(draw_list **head);

/* tha_lists2.c */
r_var_l *add_rvar_node(r_var_l **head, int lvar, char *var, int lval);
void free_rvar_list(r_var_l **head);

/* tha_mem.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* tha_strings.c */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* tha_strings2.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* tha_strings3.c */
void rev_string(char *s);

/* check_syntax_errors.c */
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(shell_info *shinfo, char *input, int i, int bool);
int check_syntax_error(shell_info *shinfo, char *input);

/* shell_loops.c */
char *without_comment(char *in);
void shell_loop(shell_info *shinfo);

/* read_line.c */
char *read_line(int *i_eof);

/* splits.c */
char *swap_char(char *input, int bool);
void add_nodes(second_list **head_s, draw_list **head_l, char *input);
void go_next(second_list **list_s, draw_list **list_l, shell_info *shinfo);
int split_commands(shell_info *shinfo, char *input);
char **split_line(char *input);

/* rep_vars.c */
void check_env(r_var_l **h, char *in, shell_info *data);
int check_vars(r_var_l **h, char *in, char *st, shell_info *data);
char *replaced_input(r_var_l **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, shell_info *shinfo);

/* get_line.c */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* exec_line */
int exec_line(shell_info *shinfo);

/* cmd_execs.c */
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(shell_info *shinfo);
int check_error_cmd(char *dir, shell_info *shinfo);
int cmd_exec(shell_info *shinfo);

/* environs1.c */
char *_getenv(const char *name, char **_environ);
int _env(shell_info *shinfo);

/* environs2.c */
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, shell_info *shinfo);
int _setenv(shell_info *shinfo);
int _unsetenv(shell_info *shinfo);

/* cd.c */
void cd_dot(shell_info *shinfo);
void cd_to(shell_info *shinfo);
void cd_previous(shell_info *shinfo);
void cd_to_home(shell_info *shinfo);

/* cd_shell.c */
int cd_shell(shell_info *shinfo);

/* get_builtin */
int (*get_builtin(char *cmd))(shell_info *shinfo);

/* exit_shell.c */
int exit_shell(shell_info *shinfo);

/* tha_stdlibs.c */
int get_len(int n);
char *tha_itoa(int n);
int _atoi(char *s);

/* tha_errors1.c */
char *strcat_cd(shell_info *, char *, char *, char *);
char *error_get_cd(shell_info *shinfo);
char *error_not_found(shell_info *shinfo);
char *error_exit_shell(shell_info *shinfo);

/* tha_errors2.c */
char *error_get_alias(char **args);
char *error_env(shell_info *shinfo);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(shell_info *shinfo);


/* get_error.c */
int get_error(shell_info *shinfo, int eval);

/* get_sigint.c */
void get_sigint(int signal);

/* tha_help.c */
void tha_help_env(void);
void tha_help_setenv(void);
void tha_help_unsetenv(void);
void tha_help_general(void);
void tha_help_exit(void);

/* tha_help2.c */
void tha_help(void);
void tha_help_alias(void);
void tha_help_cd(void);

/* get_help.c */
int get_help(shell_info *shinfo);

#endif

