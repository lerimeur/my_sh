##
## EPITECH PROJECT, 2018
## 42sh
## File description:
## Makefile of 42sh
##

SRC		=	main/main.c					\
			src/builtins_hub_bis.c				\
			src/minishell_hub.c				\
			src/utils.c					\
			src/cleanstr.c					\
			src/alias/alias.c				\
			src/alias/edit_alias.c				\
			src/alias/alias_utils.c				\
			src/alias/alias_find.c				\
			src/alias/alias_cmd.c				\
			src/alias/load_alias.c				\
			src/cmds/exit.c					\
			src/cmds/cd.c					\
			src/cmds/echo.c					\
			src/cmds/set.c					\
			src/cmds/set_utils.c				\
			src/cmds/where.c				\
			src/cmds/exec.c					\
			src/cmds/exec_errors.c				\
			src/env/env.c					\
			src/env/setenv_utils.c					\
			src/env/setenv.c				\
			src/env/unsetenv.c				\
			src/env/edit_env.c				\
			src/env/env_utilities.c				\
			src/history/find_in_files.c			\
			src/history/history.c				\
			src/history/put_in_files.c			\
			src/history/history_key.c			\
			src/parser/lr_tools.c				\
			src/parser/parser_lr_build.c			\
			src/parser/parser_get_search.c			\
			src/parser/parser_separator.c			\
			src/parser/parser_dollars.c			\
			src/parser/parser_creation_error.c		\
			src/parser/parser_get_node.c			\
			src/prompt/key_comb_next.c				\
			src/prompt/key_comb.c				\
			src/prompt/prompt.c					\
			src/prompt/parsing.c				\
			src/prompt/print_prompt.c			\
			src/prompt/termios.c				\
			src/prompt/utils.c					\
			src/prompt/globbing.c				\
			src/prompt/autocompletion.c			\
			src/prompt/empty_env_prompt.c		\
			src/prompt/print_key_to_prompt.c	\
			src/prompt/autocompletion_utils.c	\
			src/prompt/prompt_utils.c			\
			src/prompt/handle_backspace.c			\
			src/redirect/redirect.c				\
			src/cmds/exec_tools.c				\
			src/cmds/cd_tools.c					\
			src/hub_tools.c						\
			src/hub_check_history.c

TESTSRC		=	src/minishell_hub.c					\
			src/builtins_hub_bis.c			\
			src/cleanstr.c				\
			src/utils.c				\
			src/hub_tools.c				\
			src/hub_check_history.c			\
			src/cmds/cd.c							\
			src/cmds/echo.c							\
			src/cmds/exec.c							\
			src/cmds/exec_errors.c					\
			src/cmds/exit.c							\
			src/cmds/set.c							\
			src/cmds/set_utils.c					\
			src/cmds/where.c						\
			src/cmds/exec_tools.c				\
			src/cmds/cd_tools.c					\
			src/env/edit_env.c						\
			src/env/env.c							\
			src/env/setenv.c						\
			src/env/setenv_utils.c					\
			src/env/unsetenv.c						\
			src/env/env_utilities.c					\
			src/parser/lr_tools.c					\
			src/parser/parser_get_search.c			\
			src/parser/parser_lr_build.c			\
			src/parser/parser_separator.c			\
			src/parser/parser_dollars.c				\
			src/parser/parser_creation_error.c		\
			src/parser/parser_get_node.c			\
			src/redirect/redirect.c					\
			src/alias/alias.c						\
			src/alias/load_alias.c					\
			src/alias/alias_cmd.c					\
			src/alias/alias_utils.c					\
			src/alias/alias_find.c					\
			src/alias/edit_alias.c					\
			src/prompt/key_comb_next.c					\
			src/prompt/key_comb.c					\
			src/prompt/prompt.c						\
			src/prompt/parsing.c					\
			src/prompt/print_prompt.c				\
			src/prompt/termios.c					\
			src/prompt/utils.c						\
			src/prompt/globbing.c					\
			src/prompt/autocompletion.c				\
			src/prompt/empty_env_prompt.c		\
			src/prompt/print_key_to_prompt.c	\
			src/prompt/autocompletion_utils.c	\
			src/prompt/prompt_utils.c			\
			src/prompt/handle_backspace.c			\
			src/history/find_in_files.c				\
			src/history/history_key.c			\
			src/history/history.c					\
			src/history/put_in_files.c				\
			tests/ut/alias/t_alias.c				\
			tests/ut/alias/t_alias_utils.c			\
			tests/ut/alias/t_load_alias.c			\
			tests/ut/alias/t_edit_alias.c			\
			tests/ut/alias/t_alias_cmd.c			\
			tests/ut/cmds/t_cd.c					\
			tests/ut/cmds/t_set.c					\
			tests/ut/cmds/t_set_utils.c				\
			tests/ut/cmds/t_echo.c					\
			tests/ut/cmds/t_exit.c				\
			tests/ut/env/t_edit_env.c			\
			tests/ut/env/t_env.c				\
			tests/ut/env/t_env_utilities.c			\
			tests/ut/env/t_setenv.c				\
			tests/ut/env/t_unsetenv.c				\
			tests/ut/prompt/t_parsing.c			\
			tests/ut/prompt/t_print_prompt.c		\
			tests/ut/prompt/t_utils.c			\
			tests/ut/prompt/t_autocompletion.c		\
			tests/ut/history/t_history.c			\
			tests/ut/history/t_find_in_files.c		\
			tests/ut/t_cleanstr.c					\
			tests/ut/t_minishell_hub.c					\

PYTHON_TEST	=	tests/ft/test_simple_commands.py	\
			tests/ft/test_builtins.py		\
			tests/ft/test_parser.py			\
			tests/my.py				\

CC		=	gcc

CFLAGS		=	-Wextra -Wall -W

CPPFLAGS	=	-I./include

LIB		=	-L./lib/my -lmy -lncurses

OBJ		=	$(SRC:.c=.o)

NAME		=	42sh

all:			$(NAME) sign

$(NAME):		$(OBJ)
				make  --silent -C lib/my
				$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(LIB)

debug:			CFLAGS += -g
debug:			fclean $(NAME)

tests_run:	 	fclean
				make --silent -C lib/my
				gcc -o unit_tests -DUNIT_TEST -Iinclude $(TESTSRC) $(LIB) -lcriterion --coverage
				./unit_tests
				@mv t_*.gc* tests
				gcovr -b --exclude-directories tests
				gcovr -r . --exclude-directories tests
				make --silent fclean -C lib/my

py_run:			CFLAGS += -DUNIT_TEST
py_run:			fclean $(OBJ)
				@make  --silent -C lib/my
				@$(CC) -o $(NAME) $(CFLAGS) $(OBJ) $(LIB)
				python3 -m pytest -v $(PYTHON_TEST)

clean:
				make --silent clean -C lib/my
				@rm -f $(OBJ)
				@rm -f a.out
				@rm -f *.gc*
				rm -f tests/*.gc*

fclean:			clean
				make fclean -C lib/my
				@rm -f unit_tests
				@rm -f $(NAME)
				@rm -rf bonus/

re:				fclean all

sign:
				@echo ""
				@echo "MONNERY Paul"
				@echo "TITREN Loïc"
				@echo "ASSOULINE Yohann"
				@echo "BRASSEUR Gregoire"
				@echo "VEYRENC Quentin"
				@echo ""
				@echo "EPITECH, 2019"
				@echo ""

.PHONY:			all clean fclean re tests_run py_run valgrind_run bonus sign

#			src/alias/alias_find.c					\
