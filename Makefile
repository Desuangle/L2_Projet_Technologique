CC = gcc
CFLAGS = -std=c99 -Wall
CPPFLAGS = -I ../include
LDFLAGS = -L. -lgame

all : libs net_text
net_text.o : net_text.c libgame.a
	$(CC) -c $< $(CFLAGS)
libgame.a : game.o game_io.o
	ar rcs $@ $^
libs : libgame.a

net_text : net_text.o
	$(CC) $^ -o $@ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)


clean :
	rm net_text net_text.o *.a
.PHONY : clean libs test


test: run_test_first

run_test_first: test_kleguen
	 		./test_kleguen success
			./test_kleguen set_piece
	    ./test_kleguen empty



test_kleguen : test_kleguen.c libgame.a
	$(CC) $^ $(CFLAGS) $(CPPFLAGS) -o test_kleguen
