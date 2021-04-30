
CXXFLAGS = -O3 -Werror -I ./inc -I ./raylib/raylib-3.5.0_webassembly/include -I ./raylib/raylib/src
CXXFLAGS += -s USE_GLFW=3 -s TOTAL_MEMORY=100663296 -s FORCE_FILESYSTEM=1 


OBJS = ./out/main.o ./out/game.o ./out/util.o ./out/player.o ./out/environment.o

web : ${OBJS}
	${CXX} -o ./out/web/index.html --shell-file ./raylib/raylib/src/shell.html --preload-file ./res ${CXXFLAGS} ${OBJS} ./raylib/raylib-3.5.0_webassembly/lib/libraylib.a

./out/main.o : ./src/main.cpp ./inc/game.h
	${CXX} -c ${CXXFLAGS} ./src/main.cpp -o ./out/main.o

./out/game.o : ./src/game.cpp ./inc/game.h
	${CXX} -c ${CXXFLAGS} ./src/game.cpp -o ./out/game.o

./out/player.o : ./src/player.cpp ./inc/player.h
	${CXX} -c ${CXXFLAGS} ./src/player.cpp -o ./out/player.o

./out/util.o : ./src/util.cpp ./inc/util.h
	${CXX} -c ${CXXFLAGS} ./src/util.cpp -o ./out/util.o


./out/environment.o : ./src/environment.cpp ./inc/environment.h
	${CXX} -c ${CXXFLAGS} ./src/environment.cpp -o ./out/environment.o	


clean :
	rm ${OBJS}
	rm -r ./out/web/*
