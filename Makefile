flags=-Werror -pedantic -Wall -g
link=-lasound -lm
include=src/gwave/gwave.c src/note/note.c

all:
	gcc main.c $(include) -o play $(flags)  $(link)
