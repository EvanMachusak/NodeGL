GPPFlags=-lglfw3 -lGLEW -ldl -lGL -lGLU -lXrandr -lXext -lX11 -lXcursor -lXi -lpthread -lXinerama
OBJRoot=./build/obj
BINRoot=./build/bin

main: window bindir
	g++ $(GPPFlags) -c main.cpp -o $(OBJRoot)/main.o 
	g++ -o $(BINRoot)/main $(OBJRoot)/main.o $(OBJRoot)/window.o $(GPPFlags)
	chmod +x $(BINRoot)/main
run: clean main
	$(BINRoot)/main
clean:
	rm -rf $(BINRoot)
	rm -rf $(OBJRoot)
bindir: 
	mkdir -p $(BINRoot)
objdir:
	mkdir -p $(OBJRoot)
window: objdir window.h window.cpp
	g++ $(GPPFlags) -c window.cpp -o $(OBJRoot)/window.o

node:
	node-gyp build
