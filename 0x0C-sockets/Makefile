.PHONY: all clean re

TMPDIR = trash/
CFLAGS = -Wall -Wextra -Werror -pedantic -g

FILE0 = rest_0.c server.c
O_FILE0 = $(addprefix $(TMPDIR), $(FILE0:%.c=%.o))

all : todo_api_0

todo_api_0: $(TMPDIR) $(O_FILE0)
	gcc $(CFLAGS) -o $@ $(O_FILE0)

$(TMPDIR)%.o: %.c server_aux.h crud.h
	gcc $(CFLAGS) -c $< -o $@

$(TMPDIR):
	mkdir $(TMPDIR)

clean:
	-rm -rf $(TMPDIR)

re: clean all
