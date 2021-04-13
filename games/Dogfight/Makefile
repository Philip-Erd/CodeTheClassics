
CXXFLAGS = -O2 -I ./inc -I ./raylib/raylib-3.5.0_webassembly/include
CXXFLAGS += -s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=67108864 -s FORCE_FILESYSTEM=1 

OBJS = ./out/main.o

web : ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} ./raylib/raylib-3.5.0_webassembly/lib/libraylib.a -o ./out/web/index.html

./out/main.o : ./src/main.cpp
	${CXX} -c ${CXXFLAGS} ./src/main.cpp -o ./out/main.o


clean :
	rm ${OBJS}
	rm ./out/web/*
