CC = gcc
CFLAGS = -std=c99 -Wall
CPPFLAGS = -I ../include
LDFLAGS = -L. -lgame

all : libs net_text

net_text.o : net_text.c libgame.a
	$(CC) -c $< $(CFLAGS)
test_avialar.o: test_avialar.c libs
	$(CC) -c $< $(CFLAGS)
test_mgendron.o : test_mgendron.c libs
	$(CC) -c $< $(CFLAGS)
test_walouini.o: test_walouini.c libs
	$(CC) $(CFLAGS) -c $<
test_kleguen.o: test_kleguen.c libs
	$(CC) -c $< $(CFLAGS)
libgame.a : game.o game_io.o
	ar rcs $@ $^

libs : libgame.a
net_text : net_text.o
	$(CC) $^ -o $@ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)

test: run_test_kleguen run_test_walouini run_test_avialar run_test_mgendron

run_test_kleguen: test_kleguen
	./test_kleguen set_piece
	./test_kleguen game_new_game
	./test_kleguen shuffle_dir
	./test_kleguen game_height

run_test_avialar: test_avialar
	./test_avialar is_game_over
	./test_avialar game_width
	./test_avialar rotate_piece_one
	./test_avialar rotate_piece
	./test_avialar set_piece_current_dir

run_test_mgendron: test_mgendron
	./test_mgendron delete
	./test_mgendron get_piece
	./test_mgendron current_dir
	./test_mgendron restart

run_test_walouini: test_walouini
	./test_walouini is_edge_coordinates
	./test_walouini is_edge
	./test_walouini opposite_dir
	./test_walouini copy_game


test_kleguen : test_kleguen.o
	$(CC) $(CFLAGS)  $(CPPFLAGS) $^ $(LDFLAGS) -o $@

test_avialar: test_avialar.o
	$(CC) $^ -o $@ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)

test_walouini: test_walouini.o
	$(CC) $(CFLAGS)  $(CPPFLAGS) $^ $(LDFLAGS) -o $@

test_mgendron : test_mgendron.o
	$(CC) $^ -o $@ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)


clean :
	rm net_text net_text.o test_*.o *.a test_walouini test_kleguen test_avialar test_mgendron
.PHONY : clean libs test
