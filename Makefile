CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

all: client server

$(NAME): server client

client: client.c
	$(CC) $(CFLAGS) client.c -o client

server: server.c
	$(CC) $(CFLAGS) server.c -o server
	
clean:
	$(RM) server client

fclean:
	$(RM) server client
	
re: fclean all
