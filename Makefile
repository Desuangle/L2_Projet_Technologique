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

test_walouini: test_walouini.o libgame.a
	$(CC) $(CFLAGS)  $(CPPFLAGS) $^ $(LDFLAGS) -o $@

run_test_walouini: test_walouini
	./test_walouini success
	./test_walouini empty

test: run_test_walouini

clean :
	rm net_text net_text.o test_walouini.o *.a test_walouini
.PHONY : clean libs test
