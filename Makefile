NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBS = -lreadline
SRCS = main.c \
		utils/utils.c \
		utils/utils2.c \
		utils/utils3.c \
		utils/utils4.c \
		utils/utils5.c \
		entry/entry.c \
		signal/signals.c \
		built_ins/built_ins.c \
		built_ins/built_ins2.c \
		built_ins/built_ins3.c \
		built_ins/utils_pwd.c \
		built_ins/utils_export.c \
		expansor/expansor.c \
		expansor/expansor_utils.c \
		expansor/expansor_utils2.c \
		expansor/expand_files.c \
		expansor/expand_files_utils.c \
		expansor/expansor_utils_redirect.c \
		lexer/tokenizer.c \
		lexer/tokenizer_utils.c \
		lexer/tokenizer_lists.c \
		parser/parser.c \
		parser/parser_syntax.c \
		parser/cmd_lists.c \
		parser/redirect_lists.c \
		executor/executor.c \
		executor/executor_utils.c \
		executor/executor_utils2.c \
		executor/find_path.c \
		executor/find_path_utils.c \
		executor/redirections.c \
		heredoc/heredoc.c \
		libft_utils/get_next_line.c \
		libft_utils/get_next_line_utils.c \
		libft_utils/ft_tolower.c \
		libft_utils/ft_test_int.c \
		libft_utils/ft_substr.c \
		libft_utils/ft_strrchr.c \
		libft_utils/ft_strncmp.c \
		libft_utils/ft_strchr.c \
		libft_utils/ft_strlen.c \
		libft_utils/ft_strlcpy.c \
		libft_utils/ft_strlcat.c \
		libft_utils/ft_strjoin.c \
		libft_utils/ft_strdup.c \
		libft_utils/ft_split.c \
		libft_utils/ft_putstr_fd.c \
		libft_utils/ft_printfnbr_fd.c \
		libft_utils/ft_printf.c \
		libft_utils/ft_printfnbr.c \
		libft_utils/ft_printf_fd.c \
		libft_utils/ft_numlen.c \
		libft_utils/ft_memset.c \
		libft_utils/ft_itoa.c \
		libft_utils/ft_isdigit.c \
		libft_utils/ft_isalpha.c \
		libft_utils/ft_isalnum.c \
		libft_utils/ft_hex.c \
		libft_utils/ft_hex_fd.c \
		libft_utils/ft_free_malloc_array.c \
		libft_utils/ft_bzero.c \
		libft_utils/ft_atoi.c \
		libft_utils/ft_array_len.c \
		libft_utils/ft_strcat.c \

OBJS = $(SRCS:.c=.o)

GREEN = \x1b[32;01m
RED = \x1b[31;01m
BLUE = \033[34;1m
RESET = \x1b[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME) 
	@printf "$(GREEN) Executable named minishell created$(RESET)\n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@printf "$(BLUE) deleting object files$(RESET)\n"

fclean: clean
	@rm -rf $(NAME)
	@printf "$(RED) deleting executable minishell$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re