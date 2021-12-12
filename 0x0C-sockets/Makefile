.PHONY: all clean re

TMPDIR = trash/
CFLAGS = -Wall -Wextra -Werror -pedantic -g

FILE0 = rest_0.c server.c
O_FILE0 = $(addprefix $(TMPDIR), $(FILE0:%.c=%.o))
FILE1 = rest_1.c server.c
O_FILE1 = $(addprefix $(TMPDIR), $(FILE1:%.c=%.o))
FILE2 = rest_2.c server.c
O_FILE2 = $(addprefix $(TMPDIR), $(FILE2:%.c=%.o))
FILE3 = rest_3.c server.c
O_FILE3 = $(addprefix $(TMPDIR), $(FILE3:%.c=%.o))

all : todo_api_0

todo_api_0: $(TMPDIR) $(O_FILE0)
	gcc $(CFLAGS) -o $@ $(O_FILE0)
todo_api_1: $(TMPDIR) $(O_FILE1)
	gcc $(CFLAGS) -o $@ $(O_FILE1)
todo_api_2: $(TMPDIR) $(O_FILE2)
	gcc $(CFLAGS) -o $@ $(O_FILE2)
todo_api_3: $(TMPDIR) $(O_FILE3)
	gcc $(CFLAGS) -o $@ $(O_FILE3)

$(TMPDIR)%.o: %.c server_aux.h ops.h
	gcc $(CFLAGS) -c $< -o $@

$(TMPDIR):
	mkdir $(TMPDIR)

clean:
	-rm -rf $(TMPDIR)

re: clean all
