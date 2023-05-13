#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>


/* read/write buffer */
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1
#define WRITE_BUF_SIZE 1024

/* convert_number() */
#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2

/* chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* 1 getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @str: a string
 * @next: points to the next node
 * @num: the number fix
 */
typedef struct liststr
{
	char *str;
	int num;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @err_num: error code for exit()s
 * @linecount_flag: on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: history node
 * @alias: alias node
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @env_changed: on if environ was changed
 * @status: return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @path: a string path for the current command
 * @argc: argument count
 * @line_count: error count
 * @readfd: fd from which to read line input
 * @histcount: history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains string and related function
 * @func: function
 * @type: builtin command flag
 */
typedef struct builtin
{
	int (*func)(info_t *);
	char *type;
} builtin_table;


/* toem_shloop.c */
void fork_cmd(info_t *);
int find_builtin(info_t *);
void find_cmd(info_t *);
int hsh(info_t *, char **);
void fork_cmd(info_t *);

/* toem_parser.c */
char *find_path(info_t *, char *, char *);
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
int _eputchar(char);
int _putfd(char c, int fd);
void _eputs(char *);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
int _strlen(char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strcpy(char *, char *);


/* toem_exits.c */
char *_strchr(char *, char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);

/* toem_tokenizer.c */
char **strtow2(char *, char);
char **strtow(char *, char *);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_errors1.c */
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
int _erratoi(char *);
void remove_comments(char *);

/* toem_builtin.c */
int _mycd(info_t *);
int _myexit(info_t *);
int _myhelp(info_t *);

/* toem_atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_builtin1.c */
int _myalias(info_t *);
int _myhistory(info_t *);

/*toem_getline */
void sigintHandler(int);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);

/* toem_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* toem_environ.c */
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
char *_getenv(info_t *, const char *);
int populate_env_list(info_t *);

/* toem_vars.c */
int is_chain(info_t *, char *, size_t *);
int replace_string(char **, char *);
int replace_alias(info_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_vars(info_t *);

/* toem_getenv.c */
int _setenv(info_t *, char *, char *);
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);

/* toem_history.c */
int write_history(info_t *info);
int read_history(info_t *info);
char *get_history_file(info_t *info);
int renumber_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);

/* toem_lists.c */
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
void free_list(list_t **);

/* toem_lists1.c */
size_t print_list(const list_t *);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

#endif
