CFLAGS = -Wall -Wextra -Werror

CC = cc

all:
	$(CC) $(FLAGS) server.c -o server
	$(CC) $(FLAGS) client.c -o client

clean:
	rm -f server client

fclean:
	rm -f server client

re: fclean all

.PHONY: all clean fclean re
