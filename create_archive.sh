name=$1;
tar -cf ${name:=TMA1C}.tar.gz game.c game_io.c net_text.c test_avialar.c test_kleguen.c test_mgendron.c test_walouini.c game.h game_io.h CMakeLists.txt;
