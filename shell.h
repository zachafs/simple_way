#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_num() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} lis_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
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
	lis_t *env;
	lis_t *history;
	lis_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} struc_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(struc_t *);
} builtin_table;


/* toem shell_loop.c */
int mainshell_loop(struc_t *, char **);
int find_builtin(struc_t *);
void find_cmdPath(struc_t *);
void fork_cmd(struc_t *);

/* toem pars_exec.c */
int exec_cmd(struc_t *, char *);
char *duplicat_char(char *, int, int);
char *search_path(struc_t *, char *, char *);


/* toem 0x03-errors.c */
void _eputs(char *);
int _eputchar(char);
int put_fdescript(char c, int fd);
int puts_filedescript(char *str, int fd);

/* toem 0x07-string.c */
int lenGTH_str(char *);
int compar_str(char *, char *);
char *starts_with(const char *, const char *);
char *concat_2str(char *, char *);

/* toem 0x08-string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem the_exits.c */
char *ncpy_str(char *, char *, int);
char *ncat_str(char *, char *, int);
char *chr_str(char *, char);

/* toem token.c */
char **splits_strtow(char *, char *);
char **splits_strtow2(char *, char);

/* toem reallocate.c */
char *memory_set(char *, char, unsigned int);
void ffree(char **);
void *realloc_memory(void *, unsigned int, unsigned int);

/* toem memory.c */
int freeptr(void **);

/* toem convert_sti.c */
int is_active(struc_t *);
int is_delim(char, char *);
int is_alpha(int);
int convert_sti(char *);

/* toem 0x04-errors.c */
int err_convert(char *);
void msg_error(struc_t *, char *);
int print_modulo(int, int);
char *convert_num(long int, int, int);
void rm_comments(char *);

/* toem 0x01-built_in.c */
int my_exit(struc_t *);
int my_cd(struc_t *);
int my_help(struc_t *);

/* toem 0x02-built_in.c */
int my_story(struc_t *);
int my_alias(struc_t *);

/*toem_getline.c */
ssize_t get_input(struc_t *);
int _getline(struc_t *, char **, size_t *);
void sigintHandler(int);

/* toem get-info.c */
void clear_info(struc_t *);
void set_info(struc_t *, char **);
void free_info(struc_t *, int);

/* toem environment.c */
char *get_env(struc_t *, const char *);
int my_env(struc_t *);
int let_setenv(struc_t *);
int my_unsetenv(struc_t *);
int env_linkedlist(struc_t *);

/* toem get-env.c */
char **get_environ(struc_t *);
int unset_env(struc_t *, char *);
int set_env(struc_t *, char *, char *);

/* toem_history.c */
char *get_fstory(struc_t *strct);
int wr_story(struc_t *strct);
int rd_story(struc_t *strct);
int build_liststory(struc_t *strct, char *buf, int linecount);
int reset_story(struc_t *strct);

/* toem 0x05-lists.c */
lis_t *s_addnode(lis_t **, const char *, int);
lis_t *add_node_e(lis_t **, const char *, int);
size_t print_list_str(const lis_t *);
int deletenode_index(lis_t **, unsigned int);
void free_nodelist(lis_t **);

/* toem 0x06-lists1.c */
size_t list_len(const lis_t *);
char **list_to_strings(lis_t *);
size_t print_list(const lis_t *);
lis_t *nodestarts_with(lis_t *, char *, char);
ssize_t getnode_index(lis_t *, lis_t *);

/* toem variable.c */
int is_chain(struc_t *, char *, size_t *);
void check_chain(struc_t *, char *, size_t *, size_t, size_t);
int replace_alias(struc_t *);
int replace_vars(struc_t *);
int replace_string(char **, char *);

#endif
