#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

int main()
{
    cout << "running" << endl;
    if (!glfwInit())
    {
        cerr << "failed" << endl;
        return -1;
    }
    else
    {
        cout << "glfwInit succeeded" << endl;
        GLFWwindow *window; // (In the accompanying source code, this variable is global for simplicity)
        window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);
        if (window == NULL)
        {
            cerr << "Failed to initialize window." << endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window); // Initialize GLEW
        glewExperimental = true;        // Needed in core profile
        if (glewInit() != GLEW_OK)
        {
            fprintf(stderr, "Failed to initialize GLEW\n");
            return -1;
        }
        else
        {
            glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
            do
            {
                // Draw nothing, see you in tutorial 2 !

                // Swap buffers
                glfwSwapBuffers(window);
                glfwPollEvents();

            } // Check if the ESC key was pressed or the window was closed
            while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
                   glfwWindowShouldClose(window) == 0);
        }
    }
    return 0;
}
