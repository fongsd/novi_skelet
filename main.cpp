#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <rg/Shader.h>
#include <cmath>



void frame_buffer_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow *window = glfwCreateWindow(800, 600, "naslov", nullptr, nullptr);


    if (window == NULL){
        std:: cerr<<"greska\n";
        glfwTerminate();
        EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frame_buffer_callback);
    glfwSetKeyCallback(window, key_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shader("/home/dusan/CLionProjects/skelet/glad/include/shaders/vertexShaderSource.vs", "/home/dusan/CLionProjects/skelet/glad/include/shaders/fragmentShaderSource.fs");

    float vertices[] = {
            -0.5, -0.5, 0.0,
            0.5, -0.5, 0.0,
            0.5, 0.5, 0.0,
            -0.5, 0.5, 0.0
    };
    unsigned nodes[] = {
            0, 1, 2,
            0, 2, 3
    };
    unsigned int VBO, EBO, VAO;

    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(nodes), nodes, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 *sizeof (float), (void *)0);
    glEnableVertexAttribArray(0);



    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.2, 0.3, 0.5, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        shader.use();
        shader.setUniform4f("outColor", sin(glfwGetTime()/2 + 1), 0.3, 0.5, 0.0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
    }

}


void frame_buffer_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
