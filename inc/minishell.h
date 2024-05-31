/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsuner <hsuner@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 02:22:49 by bbosnak           #+#    #+#             */
/*   Updated: 2024/01/24 14:00:20 by hsuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdarg.h>

# define BUFFER_SIZE 42
# define CTRL_C SIGINT
# define CTRL_SLASH SIGQUIT
# define C_VERTICAL_BAR 124
# define C_LESS 60
# define C_GREAT 62
# define C_DOLLAR 36
# define C_ONE_QUOTE 39
# define C_TWO_QUOTE 34

# define MSSG_INVALID_ARGS "Invalid arguments: Usage [./minishell]\n"
# define MSSG_MEMORY_ERROR "Memory error, please free space and attempt again\n"
# define MSSG_EXECUTOR_ERROR "Error during command execution\n"
# define MSSG_CMD_NOT_FOUND "command not found"
# define MSGG_NO_SUCH_FILE "No such file or directory"
# define MSGG_IS_A_DIR "is a directory"
# define MSSG_EXPORT_ERR "minishell: export: `%s': not a valid identifier\n"
# define MSSG_EXIT_NUM_ERR "minishell: exit: %s: numeric argument required\n"
# define MSSG_EXIT_ERR "minishell: exit: too many arguments\n"
# define MSSG_FORK_ERROR "minishell: fork error\n"
# define MSSG_ERR_NL "syntax error near unexpected token `newline'\n"
# define MSSG_ERR_PIPE "syntax error near unexpected token `|'\n"
# define MSSG_ERR_LESS "syntax error near unexpected token `<'\n"
# define MSSG_ERR_LESS_LESS "syntax error near unexpected token `<<'\n"
# define MSSG_ERR_GREAT "syntax error near unexpected token `>'\n"
# define MSSG_ERR_GREAT_GREAT "syntax error near unexpected token `>>'\n"
# define MSSG_SHLVL_ERR "minishell: warning: shell level (%d) too high, \
resetting to 1\n"

# define SYNTAX_ERR 42
# define SYNTAX_NL 0
# define SYNTAX_PIPE 1
# define SYNTAX_LESS 2
# define SYNTAX_GREAT 3
# define SYNTAX_LESS_LESS 4
# define SYNTAX_GREAT_GREAT 5

# define CMD_NO_ACCESS 126
# define CMD_NOT_FOUND 127
# define IS_A_DIR 400
# define NO_SUCH_FILE 401

# define FILE_IN 0
# define FILE_OUT 1
# define FT_EXIT 0
# define FT_RETURN 1

int	g_signal;

typedef enum s_redirect_type
{
	REDIRECT_NONE = 0,
	IN,
	HERE_DOC,
	OUT_TRUNC,
	OUT_APPEND,
}		t_type;

typedef enum s_token
{
	NONE = 0,
	PIPE,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS
}		t_token;

typedef struct s_quote
{
	int	two;
	int	one;
}		t_quote;

typedef struct s_lexer
{
	char			*word;
	t_token			token;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}		t_lex;

typedef struct s_in_out
{
	t_type			type;
	char			*file;
	struct s_in_out	*next;
}		t_io;

typedef struct s_cmd
{
	char			**args;
	t_io			*redirect;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}		t_cmd;

typedef struct s_pipe
{
	int		n_cmds;
	int		fd_in;
	int		fd_out;
	int		fd[2];
	int		dup_stdin;
	int		dup_stdout;
	pid_t	*pid;
	char	*path;
}		t_pipe;

typedef struct s_env
{
	char	**env;
	char	**export;
}		t_env;

t_env	*ft_add_env_export(char *str, t_env *env);
t_env	*ft_join_env_export(char *str, t_env *env);
t_env	*generate_env(char **envp);
t_env	*ft_dup_matrix_env(char **envp);
t_env	*ft_check_new_shlvl(t_env *dup, int i);
t_cmd	*parser_lstnew(void);
t_cmd	*parser_lstlast(t_cmd *lst);
t_io	*redirect_lstnew(void);
t_io	*redirect_lstlast(t_io *lst);
t_lex	*lexer_lstnew(void);
t_lex	*lexer_lstlast(t_lex *lst);

int		ft_cd(char **commands, char ***env);
int		ft_pwd(void);
int		quote_len1(char *data);
int		ft_env(char **env);
int		ignore_quote(char const *cmd, int i);
int		quote_check(char *data, int i);
int		parser_lstsize(t_cmd *lst);
int		ft_export(char **args, t_env *env);
int		ft_echo(char **command);
int		init_data(t_pipe *data, t_cmd *commands);
int		ft_test_options_echo(char **command, int *i);
int		is_builtin(t_cmd *commands);
int		calc_len_expan_file(char *str, char **env, int status);
int		calc_len_file(char *path);
int		fill_aux(char *path, char **file);
int		expand_vars_file(char **file, char **aux, char **env, int status);
int		rewrite_file(char *path, char **aux);
int		execute_commands(t_cmd *commands, t_env *envp, int *exit_s);
int		ft_strcmp_export(char *export, char *str);
int		ft_change_redirection(t_io *redirect, char *str);
int		exec_one_builtin(t_cmd *commands, t_pipe *data, \
t_env *envp, int *exit_s);
int		perror_return(t_pipe *data, int return_code, char *error);
int		check_format_export(char *str);
int		ft_omit_var(char *var);
int		calc_len_value_expan(char *str, char **env, int status, int *len);
int		calc_len_expan(char *str, char **env, int status);
int		expand_redirections(t_io *redir, char **env, int ex_s);
int		expansor_files(t_cmd *commands, char **env, int status);
int		check_tilde(char *w, int i);
int		check_dollar(char *word, int i);
int		ft_isliteral(char c, t_quote *quote);
int		search_extra_path(char *cmd, char *envp, char **path, int exit_status);
int		ft_change_command(t_cmd *command, int i, char *str);
int		expand_file(char *path, char **env, int exit);
int		string_to_command(char *str, t_cmd **commands, t_env *env, int *exit_s);
int		ft_unset(char **command, t_env *env);
int		directory_errors(char *cmd);
int		try_paths(char **full_path, char *cmd, char **path);
int		expansor(t_cmd *def, char **env, int ex_s);
int		try_local_path(char *cmd, char **path);
int		try_absolute_path(char *cmd, char **path);
int		ft_array_len(char **arr);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isspace(int c);
int		ft_numlen(int n);
int		ft_isquote(int c);
int		ft_test_write_fd(int test, int i);
int		ft_test_write(int test, int i);
int		ft_printchar_fd(int c, int fd);
int		ft_isreserved(int c);
int		ft_printchar(int c);
int		ft_printstr(char *str);
int		ft_printf(const char *str, ...);
int		ft_prints(va_list arg, char c);
int		ft_printnbr_fd(int n, int fd);
int		ft_printstr_fd(char *str, int fd);
int		ft_printnbr(int n);
int		ft_printpnt(unsigned long pointer);
int		ft_printuphex(unsigned int nb, int test);
int		ft_printpnt_fd(unsigned long pointer, int fd);
int		ft_printundhex_fd(unsigned int nb, int test, int fd);
int		ft_printuphex_fd(unsigned int nb, int test, int fd);
int		ft_printundhex(unsigned int nb, int test);
int		ft_printunnbr(unsigned int num, int test);
int		ft_printunnbr_fd(unsigned int num, int test, int fd);
int		ft_prints_fd(va_list arg, char c, int fd);
int		ft_printf_fd(const int fd, const char *str, ...);
int		search_path(char *cmd, char **envp, char **path);
int		create_token(char *str, int i, t_lex *new);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
int		create_word(char *str, int i, t_lex *new);
int		count_arguments(t_lex *lexer);
int		tokenizer(char *str, t_lex **lexer);
int		ft_tolower(int c);
int		valid_command(char *command);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_chdir(char *direct, char ***env);
int		initialize_lexer_node(t_lex *new, char *str, int i);
int		do_heredoc(int i, t_io *aux);
int		add_redirection(t_io **redirect, t_lex **head);
int		heredoc(t_cmd *commands);
int		ft_strlen_chr(char *str, char c);
int		init_signals(void);
int		contain_env(char **env, char *str);
int		do_oldpwd(char ***env);
int		ft_strcmp_nocase(char *s1, char *s2);
int		lexer_lstsize(t_lex *lst);
int		dup_custom_redirections(t_pipe *data, t_io *temp);
int		manage_redirections(t_cmd *commands, t_pipe *data, int out);
int		check_pipe_error(t_lex *lexer);
int		parser(t_cmd **commands, t_lex **lexer, int *exit_s);
int		create_simple_command(t_lex **head, t_cmd *cmd);
int		fill_command(t_lex **head, t_io **redirect, t_cmd *cmd);
int		check_duplicate_tokens(t_lex *lexer);
int		check_syntax_error(t_lex *lexer, int *exit_s);
int		ft_test_int(const char *str);
int		ft_strcmp_env(char *env, char *str);
int		redirect_lstsize(t_io *lst);
int		check_num(int num);
int		ft_strcmp_env2(char *env, char *str);
int		ft_only_dollar(char *args);

size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_len_line(const char *s);
size_t	ft_strlen(const char *s);

char	**ft_add_env(char *str, char **env);
char	**ft_free_matrix(char **matrix, int j);
char	*ft_strdup_join(char *str);
char	*ft_strjoin_env(char *s1, char *s2);
char	*obtain_oldpwd(char **env);
char	*obtain_pwd(char **env);
char	*ft_correct_shlvl(char *env);
char	**ft_join_export(char *str, char **export);
char	**ft_join_env(char *str, char **env);
char	*ft_strjoin_export(char *s1, char *s2);
char	*get_next_line(int fd);
char	*find_home(char **env);
char	*ft_strjoin_line(char *s1, char *s2);
char	**ft_add_export(char *str, char **export, int i);
char	*ft_joincolors(char *array, t_env *env);
char	*ft_strchr_line(const char *s, int c);
char	*obtain_var(char *str);
char	*ft_strrchr(const char *s, int c);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup_chr(char *str, char c);
char	*find_shlvl(char **envp);
char	*expand(char *str, char **env);
char	*create_value(char *word, int i, char **env, int exit);
char	*generate_entry(t_env *env);
char	*ft_strdup_export(char *envp);
char	**ft_split(char const *s, char c);

void	ft_exit(char **args, int *exit_s);
void	init_quote(t_quote	*quote);
void	parser_error(int error);
void	check_expand(char *word, int exit, char *str, char **env);
void	find_quote(t_quote *quote, int i, char *str);
void	parser_lstclear(t_cmd **lst);
void	ft_print_matrix(char **matrix, int i);
void	ft_print_export(char **matrix);
void	create_heredoc(char *delimiter, char *path);
void	ft_bzero(void *s, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	generate_terminal(t_env *env);
void	generate_terminal2(char *str, t_env *env, int exit_s, t_cmd *cmd);
void	unlink_heredocs(t_io *redirection);
void	close_pipe(int in, int out);
void	print_tokens(t_lex *lexer, char *str);
void	lexer_lstadd_back(t_lex **lst, t_lex *new);
void	lexer_lstclear(t_lex **lst);
void	*ft_memset(void *b, int c, size_t len);
void	ft_matrix_free(char **matrix);
void	ft_free_malloc_array(char **arr, int i);
void	check_expand_file(char *word, int exit, char *str, char **env);
void	parser_lstadd_back(t_cmd **lst, t_cmd *new);
void	dup_original_stds(int *in, int *out);
void	redirect_lstadd_back(t_io **lst, t_io *new);
void	redirect_lstclear(t_io **lst);
void	expand_var(char *word, char *value, char *str, int len);
void	wait_childs(t_pipe *data, int *exit_s);
void	new_command(t_cmd *commands, t_pipe *data, t_env *envp, int *exit_s);
void	execute_builtins(char **args, t_env *envp, int *exit_s, int exit_flag);
void	perror_exit(t_pipe *data, int exit_code, char *error);
void	error_exit(t_pipe *data, int exit_code, char *name, char *error);
void	ft_generate_new_env(char **command, char**str, int j, int i);

#endif
