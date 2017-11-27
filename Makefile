NAME=ft_ls
NAME_DBG=ft_lsdbg
SRC_NAME=main.c arg_opt.c usage.c ft_ls.c permissions.c io.c path.c
SRC=$(addprefix src/, $(SRC_NAME))
OBJ=$(patsubst src/%.c, obj/%.o, $(SRC))
OBJ_DBG=$(patsubst src/%.c, obj_dbg/%.o, $(SRC))
CC=clang
LIBS=-Llibft/ -lft
LIBS_DBG=-Llibft -lftdbg
CFLAGS=-Wall -Werror -Wextra -Iinclude -Ilibft/include

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS)

$(NAME_DBG): $(OBJ_DBG)
	$(CC) $(CFLAGS) -o $(NAME_DBG) $(OBJ_DBG) $(LIBS_DBG)

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c -o $@ $<

obj_dbg/%.o: src/%.c
	@mkdir -p obj_dbg
	$(CC) $(CFLAGS) -g -c -o $@ $<

debug: $(NAME_DBG)
	@lldb $(NAME_DBG)

clean:
	@rm -rf obj
	@rm -rf obj_dbg

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME_DBG)

re: fclean all
