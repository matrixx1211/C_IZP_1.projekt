CC=gcc
CFLAGS= -std=c99 -Wall -Wextra -Werror

sheet: sheet.c
        $(CC) $(CFLAGS) sheet.c -o sheet