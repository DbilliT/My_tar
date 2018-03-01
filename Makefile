SRC1	= src/main.c \
	  src/create_linked.c \
	  src/create_archive.c \
	  src/create_files.c \
	  src/get_next_line.c \
	  src/archive_info.c

NAME1	= my_tar

CFLAGS	= -W -Wall -Wextra -Werror -pedantic -I./include/

OBJ1	= $(SRC1:.c=.o)

CC	= gcc

RM	= rm -f

all: $(NAME1)

$(NAME1): $(OBJ1)
	$(CC) $(OBJ1) -o $(NAME1) $(LIB)

clean:
	$(RM) $(OBJ1)

fclean: clean
	$(RM) $(NAME1)

re: fclean all
