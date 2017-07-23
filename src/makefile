GPPFlags=-lglfw3 -lGLEW -ldl -lGL -lGLU -lXrandr -lXext -lX11 -lXcursor -lXi -lpthread -lXinerama

main: main.cpp
	g++ -g main.cpp $(GPPFlags) -o main
	chmod +x main
run: clean main
	./main
clean:
	rm main