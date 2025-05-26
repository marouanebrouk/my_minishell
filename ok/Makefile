

CFLAGS = -Wall -Werror -Wextra
CC = cc

all : send rec

send : sender.c
	cc $(CFLAGS) sender.c -o send
rec : receiver.c
	cc $(CFLAGS) receiver.c -o rec
fclean :
	rm -rf send rec
re : fclean all
