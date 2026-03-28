NAME = minishell
cc = cc
CFLAGS = -Wall -Wextra -Werror -g
SRC =  parser_start.c signals.c env_list.c main.c expand_vars.c parsing_prep.c custom_split.c custom_split_utils.c parser_utils.c \
error_handling.c char_checks.c heredoc.c execution_start.c built_in_utils.c free_functions.c  cd.c echo.c exit.c export.c \
pwd.c unset.c export_empty.c path_checks.c exec_cmd.c parser_calc_utils.c parser_utils_two.c handle_redir.c quote_parsing.c parser_utils_three.c \
single_parsing.c parser_utils_four.c parsing.c exit_status.c execution_utils.c execution_utils2.c free_functions2.c free_functions3.c parser_utils_five.c \
token_merge.c check_forempty.c export_utils.c heredoc_one.c heredoc_two.c heredoc_utils.c build_envp.c exit_utils.c shllvl.c parsing_expansions.c \
heredoc_pars_u.c parser_utils_seven.c parser_utils_six.c redir_utils.c parser_utils_eight.c
RM = rm -rf
OBJ_DIR = obj
OBJS =  $(OBJ_DIR)/parsing.o $(OBJ_DIR)/expand_vars.o  $(OBJ_DIR)/signals.o $(OBJ_DIR)/parsing_prep.o $(OBJ_DIR)/env_list.o $(OBJ_DIR)/parser_utils.o $(OBJ_DIR)/main.o \
$(OBJ_DIR)/char_checks.o $(OBJ_DIR)/custom_split.o $(OBJ_DIR)/custom_split_utils.o $(OBJ_DIR)/error_handling.o $(OBJ_DIR)/heredoc.o $(OBJ_DIR)/execution_start.o \
$(OBJ_DIR)/free_functions.o  $(OBJ_DIR)/built_in_utils.o $(OBJ_DIR)/cd.o $(OBJ_DIR)/echo.o $(OBJ_DIR)/env.o \
$(OBJ_DIR)/exit.o $(OBJ_DIR)/export.o $(OBJ_DIR)/pwd.o $(OBJ_DIR)/unset.o $(OBJ_DIR)/export_empty.o $(OBJ_DIR)/path_checks.o $(OBJ_DIR)/exec_cmd.o \
$(OBJ_DIR)/parser_calc_utils.o $(OBJ_DIR)/parser_utils_two.o $(OBJ_DIR)/handle_redir.o $(OBJ_DIR)/parser_utils_three.o $(OBJ_DIR)/single_parsing.o \
$(OBJ_DIR)/parser_utils_four.o $(OBJ_DIR)/quote_parsing.o $(OBJ_DIR)/exit_status.o $(OBJ_DIR)/execution_utils.o $(OBJ_DIR)/execution_utils2.o \
$(OBJ_DIR)/free_functions2.o $(OBJ_DIR)/free_functions3.o $(OBJ_DIR)/parser_utils_five.o $(OBJ_DIR)/token_merge.o $(OBJ_DIR)/check_forempty.o \
$(OBJ_DIR)/export_utils.o $(OBJ_DIR)/heredoc_one.o $(OBJ_DIR)/heredoc_two.o $(OBJ_DIR)/heredoc_utils.o $(OBJ_DIR)/build_envp.o $(OBJ_DIR)/exit_utils.o \
$(OBJ_DIR)/shllvl.o $(OBJ_DIR)/parsing_expansions.o $(OBJ_DIR)/heredoc_pars_u.o $(OBJ_DIR)/parser_utils_seven.o  $(OBJ_DIR)/parser_utils_six.o \
$(OBJ_DIR)/redir_utils.o $(OBJ_DIR)/parser_utils_eight.o
LIBFT_PATH = ./libft/
LIBFT_LIB = $(LIBFT_PATH)libft.a
LFLAGS = -L$(LIBFT_PATH) -lft -lreadline
GREEN = \033[32m
RED = \033[31m
RESET = \033[0m

all: $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN) ⭐️ COMPILING MINISHELL ⭐️$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	@make -C $(LIBFT_PATH) > /dev/null 2>&1
	@echo "$(GREEN)      🌟 Linking 🌟$(RESET)"
	@$(CC) $(CFLAGS) $(LFLAGS) -o $(NAME) $(OBJS) $(LIBFT_LIB) 
	@echo "$(GREEN)💫 Compiled successfully! 💫$(RESET)"


clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(RED)     🚀  Cleaning 🚀$(RESET)"
	@make clean -C $(LIBFT_PATH) > /dev/null 2>&1
	@echo "$(GREEN)       🛸 Done! 🛸$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT_PATH) > /dev/null 2>&1
	@echo "$(RED)     🚀  Fcleaning 🚀$(RESET)"
	@echo "$(GREEN)       🛸 Done! 🛸$(RESET)"

re: fclean all

.PHONY: all clean fclean re libftp