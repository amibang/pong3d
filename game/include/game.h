#pragma once
#include <glad/glad.h> 
#include "Camera.h"
#include "Shader.h"
#include "Ball.h"
#include "Paddle.h"
#include "Table.h"
#include <GLFW/glfw3.h>

class Game {
public:
    static const unsigned int SCR_WIDTH = 1096;
    static const unsigned int SCR_HEIGHT = 720;

    Game();
    ~Game();

    bool init();
    void run();

private:
    GLFWwindow* window;
    Camera camera;
    Shader* shader;
    Ball ball;
    Paddle playerPaddle;
    Paddle aiPaddle;
    Table table;

    unsigned int tableVAO;
    unsigned int paddleVAO;
    unsigned int ballVAO;
    unsigned int netVAO;

    bool keys[1024];
    float lastX;
    float lastY;
    bool firstMouse;

    bool initWindow();
    bool initGL();
    void createVAOs();
    void processInput(float deltaTime);
    void update(float deltaTime);
    void render();
    void cleanup();

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    static Game* getInstance(GLFWwindow* window);
};