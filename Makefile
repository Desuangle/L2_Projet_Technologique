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

test: run_test_kleguen

run_test_kleguen: test_kleguen
	 		./test_kleguen success
			./test_kleguen set_piece
	    ./test_kleguen empty



test_kleguen : test_kleguen.c libgame.a
	$(CC) $^ $(CFLAGS) $(CPPFLAGS) -o test_kleguen

test_walouini: test_walouini.o libgame.a
	$(CC) $(CFLAGS)  $(CPPFLAGS) $^ $(LDFLAGS) -o $@

run_test_walouini: test_walouini
	./test_walouini success
	./test_walouini empty

test: run_test_walouini

clean :
	rm net_text net_text.o test_walouini.o *.a test_walouini
.PHONY : clean libs test
