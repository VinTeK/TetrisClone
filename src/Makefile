CPP=ccache g++
CFLAGS=-Wall -pedantic -std=c++11
LSFML=-lsfml-system -lsfml-window -lsfml-graphics
OBJS=Grid.o MainInit.o Renderer.o Tetrimino.o TetriminoQueue.o Game.o
EXE=tetris

$(EXE): $(OBJS)
	$(CPP) $(CFLAGS) $(OBJS) $(LSFML) -o $@

%.o: %.cpp
	$(CPP) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(EXE)
