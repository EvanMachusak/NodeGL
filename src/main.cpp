#include "window.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main() {
    return createWindow(1024, 768, "OpenGL");
}