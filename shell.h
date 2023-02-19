

#ifndef SHELL_H_
#define SHELL_H_

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



#include <stdio.h> /* for printf*/
#include <unistd.h> /* for fork, execve*/
#include <stdlib.h>
#include <string.h> /* for strtok*/
#include <stddef.h>
#include <errno.h> /* for errno and perror */
#include <sys/types.h> /* for type pid */
#include <sys/wait.h> /* for wait */
#include <sys/stat.h> /* for use of stat function */
#include <signal.h> /* for signal management */
#include <fcntl.h> /* for open files*/

  /************* MACROS **************/

#include "macros.h" /* for msg help and prompt */

  /************* STRUCTURES **************/

  /**
   * struct info- struct for the program's data
   * @program_name: the name of the executable
   * @input_line: pointer to the input read for _getline
   * @command_name: pointer to the first command typed by the user
   * @exec_counter: number of excecuted comands
   * @file_descriptor: file descriptor to the input of commands
   * @tokens: pointer to array of tokenized input
   * @env: copy of the environ
   * @alias_list: array of pointers with aliases.
   */
  typedef struct info
{
		char *program_name;
		char *input_line;
		char *command_name;
		int exec_counter;
		int file_descriptor;
		char **tokens;
		char **env;
		char **alias_list;
} data_of_program;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(data_of_program *data);
} builtins;


/************* MAIN FUNCTIONS *************/


/*========  shell.c  ========*/

/* Inicialize the struct with the info of the program */
void inicialize_data(data_of_program *data, int arc, char *argv[], char **env);

/* Makes the infinite loop that shows the prompt*/
void sisifo(char *prompt, data_of_program *data);

/* Print the prompt in a new line */
void handle_ctrl_c(int opr UNUSED);


/*========  _getline.c  ========*/

/* Read one line of the standar input*/

/* split the each line for the logical operators if it exist */
int check_logic_ops(char *array_commands[], int i, char array_operators[]);


/*======== expansions.c ========*/

/* expand variables */
void expand_variables(data_of_program *data);

/* expand aliases */
void expand_alias(data_of_program *data);

/* append the string to the end of the buffer*/
int buffer_add(char *buffer, char *str_to_add);


/*======== str_tok.c ========*/

/* Separate the string in tokens using a designed delimiter */
void tokenize(data_of_program *data);

/* Creates a pointer to a part of a string */
char *_strtok(char *line, char *delim);


/*======== execute.c ========*/

/* Execute a command with its entire path */
int execute(data_of_program *data);


/*======== builtins_list.c ========*/

/* If match a builtin, executes it */
int builtins_list(data_of_program *data);


/*======== find_in_path.c ========*/

/* Creates an array of the path directories */
char **tokenize_path(data_of_program *data);

/* Search for program in path */
int find_program(data_of_program *data);


/************** HELPERS FOR MEMORY MANAGEMENT **************/


/*======== helpers_free.c ========*/

/* Frees the memory for directories */
void free_array_of_pointers(char **directories);

/* Free the fields needed each loop */
void free_recurrent_data(data_of_program *data);

/* Free all field of the data */
void free_all_data(data_of_program *data);


/************** BUILTINS **************/


/*======== builtins_more.c ========*/

/* Close the shell */
int builtin_exit(data_of_program *data);

/* Change the current directory */
int builtin_cd(data_of_program *data);

/* set the work directory */
int set_work_directory(data_of_program *data, char *new_dir);

/* show help information */
int builtin_help(data_of_program *data);

/* set, unset and show alias */
int builtin_alias(data_of_program *data);


/*======== builtins_env.c ========*/

/* Shows the environment where the shell runs */
int builtin_env(data_of_program *data);

/* create or override a variable of environment */
int builtin_set_env(data_of_program *data);

/* delete a variable of environment */
int builtin_unset_env(data_of_program *data);


/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/


/*======== env_management.c ========*/

/* Gets the value of an environment variable */
char *env_get_key(char *name, data_of_program *data);

/* Overwrite the value of the environment variable */
int env_set_key(char *key, char *value, data_of_program *data);

/* Remove a key from the environment */
int env_remove_key(char *key, data_of_program *data);

/* prints the current environ */
void print_environ(data_of_program *data);


/************** HELPERS FOR PRINTING **************/


/*======== helpers_print.c ========*/

/* Prints a string in the standar output */
int _print(char *string);

/* Prints a string in the standar error */
int _printe(char *string);

/* Prints a string in the standar error */
int _print_error(int errorcode, data_of_program *data);


/************** HELPERS FOR STRINGS MANAGEMENT **************/


/*======== helpers_string.c ========*/

/* Counts the number of characters of a string */
int str_length(char *string);

/* Duplicates an string */
char *str_duplicate(char *string);

/* Compares two strings */
int str_compare(char *string1, char *string2, int number);

/* Concatenates two strings */
char *str_concat(char *string1, char *string2);

/* Reverse a string */
void str_reverse(char *string);


/*======== helpers_numbers.c ========*/

/* Cast from int to string */
void long_to_string(long number, char *string, int base);

/* convert an string in to a number */
int _atoi(char *s);

/* count the coincidences of character in string */
int count_characters(char *string, char *character);


/*======== alias_management.c ========*/

/* print the list of alias */
int print_alias(data_of_program *data, char *alias);

/* get the alias name */
char *get_alias(data_of_program *data, char *alias);

/* set the alias name */
int set_alias(char *alias_string, data_of_program *data);





/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

	/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

	/* for convert_number() */
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
} list_t;

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
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*toem_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* toem_environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* toem_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);





#endif /* SHELL_H */
