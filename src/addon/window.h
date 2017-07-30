#ifndef WINDOW_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define WINDOW_H
#include <GLFW/glfw3.h>

int createWindow(int width, int height, const char* title);

#endif