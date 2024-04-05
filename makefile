a.out: ./Soup ./Boats ./Ecosystem ./Swarms main.cpp
	g++ main.cpp Soup/Src/*.cpp Boats/*.cpp Ecosystem/*.cpp Swarms/*.cpp -lsfml-system -lsfml-graphics -lsfml-window
