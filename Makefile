NAME=ft_ls
NAME_DBG=ft_lsdbg
SRC_NAME=main.c arg_opt.c usage.c permissions.c list.c io.c path.c error.c path_sort.c list_fmt.c\
		stat.c ext_attr.c path_sort2.c list_fmt2.c
SRC=$(addprefix src/, $(SRC_NAME))
OBJ=$(patsubst src/%.c, obj/%.o, $(SRC))
OBJ_DBG=$(patsubst src/%.c, obj_dbg/%.o, $(SRC))
CC=clang
LIBS=-Llibft/ -lft -L/Users/briviere/.brew/lib -lprofiler -ltcmalloc
LIBS_DBG=-Llibft -lftdbg
CFLAGS=-Wall -Werror -Wextra -Iinclude -Ilibft/include -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/ all
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS)

$(NAME_DBG): $(OBJ_DBG)
	@make -C libft/ debug
	$(CC) $(CFLAGS) -o $(NAME_DBG) $(OBJ_DBG) $(LIBS_DBG)

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c -o $@ $<

obj_dbg/%.o: src/%.c
	@mkdir -p obj_dbg
	$(CC) $(CFLAGS) -g -c -o $@ $<

debug: $(NAME_DBG)

lldb: $(NAME_DBG)
	@lldb $(NAME_DBG)

leaks: $(NAME_DBG)
	@valgrind --leak-check=full --track-origins=yes $(NAME_DBG)

norme: $(SRC)
	@norminette $(SRC)
	@norminette include/ft_ls.h

clean:
	@make -C libft/ clean
	@rm -rf obj
	@rm -rf obj_dbg

fclean: clean
	@make -C libft/ fclean
	@rm -f $(NAME)
	@rm -f $(NAME_DBG)

re: fclean all
