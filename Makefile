CC = gcc
CFLAGS = -std=c99 -Wall
CPPFLAGS = -I ../include
LDFLAGS = -L. -lgame -lgame2

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


testfw_avialar.o: test_avialar.c libs
	$(CC) -c $< $(CFLAGS) -DTESTFW -o $@
testfw_mgendron.o : test_mgendron.c libs
	$(CC) -c $< $(CFLAGS) -DTESTFW -o $@
testfw_walouini.o: test_walouini.c libs
	$(CC) $(CFLAGS) -c $< -DTESTFW -o $@
testfw_kleguen.o: test_kleguen.c libs
	$(CC) -c $< $(CFLAGS) -DTESTFW -o $@


libgame.a : game.o game_io.o
	ar rcs $@ $^
libgame2.a : game1.o game2.o game3.o game4.o game5.o game6.o game7.o game8.o game9.o game10.o game11.o game12.o game13.o game14.o game15.o game16.o game17.o game18.o  
	ar -rcs $@ $^


libs : libgame.a libtestfw.a libtestfw_main.a
net_text : net_text.o
	$(CC) $^ -o $@ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)

testfw: testfw_all testfw_all_bug
	./testfw_all -t 2 -o test.log -c


test: run_test_kleguen run_test_walouini run_test_avialar run_test_mgendron
 

testfw_all: testfw_avialar.o testfw_mgendron.o testfw_walouini.o testfw_kleguen.o libgame.a
	$(CC) $^ -o $@ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -ltestfw_main -ltestfw -ldl -rdynamic
testfw_all_bug: testfw_avialar.o testfw_mgendron.o testfw_walouini.o testfw_kleguen.o libgame2.a
	$(CC) $^ -o $@ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -ltestfw_main -ltestfw -ldl -rdynamic libgame2.a	



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
	./test_avialar empty

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
	rm net_text net_text.o testfw_*.o test_*.o libgame.a test_walouini test_kleguen test_avialar testfw_all test_mgendron *~ *.log
.PHONY : clean libs test
