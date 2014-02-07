FLAGS=-o -ggdb -Wall
DEFS= -D USE_OPEN_GL -D MACOS 

LIBS= -framework OpenGL -framework GLUT -lm -L/usr/local/lib

UNAME= $(shell uname)
ifeq ($(UNAME), Linux)
LIBS= -lGL -lGLU -lglut
DEFS= -D USE_OPEN_GL
endif


all:dstar main

dstar: Dstar.h Dstar.cpp DstarDraw.cpp 
	g++ ${FLAGS} Dstar.cpp DstarDraw.cpp drawutils.cpp -o dstar ${LIBS} ${DEFS}

main: common.h Dstar.h Dstar.cpp
	g++ $(FLAGS) Dstar.cpp main.cpp drawutils.cpp -o main $(LIBS) $(DEFS) 
astar: common.h Astar.h Astar.cpp
	g++ $(FLAGS) Astar.cpp main_a.cpp drawutils.cpp -o astar $(LIBS) $(DEFS) -D DEBUG
time: common.h Astar.h Astar.cpp  Dstar.h Dstar.cpp
	g++ -pg $(FLAGS) Astar.cpp Dstar.cpp timeCompare.cpp drawutils.cpp -o time $(LIBS) $(DEFS) 
qps: common.h Astar.h Astar.cpp  Dstar.h Dstar.cpp
	g++ -pg $(FLAGS) Astar.cpp Dstar.cpp qpsCompare.cpp drawutils.cpp -o qps $(LIBS) $(DEFS) 
clean:
	rm -f dstar main
