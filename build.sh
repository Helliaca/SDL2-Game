# compile under Ubuntu with SDL2 installed
g++ main.cpp base.cpp gamemaster.cpp assets/*.cpp assets/BOSS/*.cpp assets/NAV/*.cpp -std=c++11 -I/usr/include/SDL2/ -I. -Iassets/ -Iassets/BOSS/ -Iassets/NAV/ -lSDL2main -lSDL2 -lSDL2_image -o helliaca
