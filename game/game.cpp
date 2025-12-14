#include "Game.h"
#include <iostream>

Game* Game::getInstance(GLFWwindow* window) {
    return static_cast<Game*>(glfwGetWindowUserPointer(window));
}

void Game::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    Game* game = getInstance(window);
    if (!game) return;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS)
            game->keys[key] = true;
        else if (action == GLFW_RELEASE)
            game->keys[key] = false;
    }
}

void Game::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    Game* game = getInstance(window);
    if (!game) return;

    if (game->firstMouse) {
        game->lastX = xpos;
        game->lastY = ypos;
        game->firstMouse = false;
    }

    float xoffset = xpos - game->lastX;
    float yoffset = game->lastY - ypos;

    game->lastX = xpos;
    game->lastY = ypos;

    game->camera.processMouse(xoffset, yoffset);
}

void Game::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    Game* game = getInstance(window);
    if (!game) return;

    game->camera.zoom(yoffset);
}

Game::Game() :
    window(nullptr),
    shader(nullptr),
    playerPaddle(false, glm::vec3(-8.0f, 1.0f, 0.0f)),
    aiPaddle(true, glm::vec3(8.0f, 1.0f, 0.0f)),
    lastX(SCR_WIDTH / 2.0f),
    lastY(SCR_HEIGHT / 2.0f),
    firstMouse(true) {
    for (int i = 0; i < 1024; i++) keys[i] = false;
}

Game::~Game() {
    cleanup();
}

bool Game::init() {
    if (!initWindow()) return false;
    if (!initGL()) return false;

    camera.setScreenSize(SCR_WIDTH, SCR_HEIGHT);

    try {
        shader = new Shader("shaders/shader.vert", "shaders/shader.frag");
    }
    catch (...) {
        std::cout << "Failed to load shaders" << std::endl;
        return false;
    }

    createVAOs();
    return true;
}

bool Game::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Pong 3D", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return true;
}

bool Game::initGL() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glEnable(GL_DEPTH_TEST);
    glfwSwapInterval(1);

    return true;
}

void Game::createVAOs() {
    //создаем VAO (для объектов-кубов)
    auto createCubeVAO = [](glm::vec3 color) -> unsigned int {
        float vertices[] = {
            // Позиции           // Цвет
            -0.5f, -0.5f, -0.5f, color.r, color.g, color.b,
             0.5f, -0.5f, -0.5f, color.r, color.g, color.b,
             0.5f,  0.5f, -0.5f, color.r, color.g, color.b,
             0.5f,  0.5f, -0.5f, color.r, color.g, color.b,
            -0.5f,  0.5f, -0.5f, color.r, color.g, color.b,
            -0.5f, -0.5f, -0.5f, color.r, color.g, color.b,

            -0.5f, -0.5f,  0.5f, color.r, color.g, color.b,
             0.5f, -0.5f,  0.5f, color.r, color.g, color.b,
             0.5f,  0.5f,  0.5f, color.r, color.g, color.b,
             0.5f,  0.5f,  0.5f, color.r, color.g, color.b,
            -0.5f,  0.5f,  0.5f, color.r, color.g, color.b,
            -0.5f, -0.5f,  0.5f, color.r, color.g, color.b,

            -0.5f,  0.5f,  0.5f, color.r, color.g, color.b,
            -0.5f,  0.5f, -0.5f, color.r, color.g, color.b,
            -0.5f, -0.5f, -0.5f, color.r, color.g, color.b,
            -0.5f, -0.5f, -0.5f, color.r, color.g, color.b,
            -0.5f, -0.5f,  0.5f, color.r, color.g, color.b,
            -0.5f,  0.5f,  0.5f, color.r, color.g, color.b,

             0.5f,  0.5f,  0.5f, color.r, color.g, color.b,
             0.5f,  0.5f, -0.5f, color.r, color.g, color.b,
             0.5f, -0.5f, -0.5f, color.r, color.g, color.b,
             0.5f, -0.5f, -0.5f, color.r, color.g, color.b,
             0.5f, -0.5f,  0.5f, color.r, color.g, color.b,
             0.5f,  0.5f,  0.5f, color.r, color.g, color.b,

            -0.5f, -0.5f, -0.5f, color.r, color.g, color.b,
             0.5f, -0.5f, -0.5f, color.r, color.g, color.b,
             0.5f, -0.5f,  0.5f, color.r, color.g, color.b,
             0.5f, -0.5f,  0.5f, color.r, color.g, color.b,
            -0.5f, -0.5f,  0.5f, color.r, color.g, color.b,
            -0.5f, -0.5f, -0.5f, color.r, color.g, color.b,

            -0.5f,  0.5f, -0.5f, color.r, color.g, color.b,
             0.5f,  0.5f, -0.5f, color.r, color.g, color.b,
             0.5f,  0.5f,  0.5f, color.r, color.g, color.b,
             0.5f,  0.5f,  0.5f, color.r, color.g, color.b,
            -0.5f,  0.5f,  0.5f, color.r, color.g, color.b,
            -0.5f,  0.5f, -0.5f, color.r, color.g, color.b
        };

        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        return VAO;
        };

    tableVAO = createCubeVAO(table.color);
    paddleVAO = createCubeVAO(playerPaddle.color);
    ballVAO = createCubeVAO(ball.color); //используем VAO для кубов
    netVAO = createCubeVAO(table.netColor);
}

void Game::processInput(float deltaTime) {
    float paddleSpeed = 20.0f * deltaTime;

    if (keys[GLFW_KEY_UP])
        playerPaddle.move(0, -paddleSpeed, table.getWidth(), table.getDepth());
    if (keys[GLFW_KEY_DOWN])
        playerPaddle.move(0, paddleSpeed, table.getWidth(), table.getDepth());
    if (keys[GLFW_KEY_LEFT])
        playerPaddle.move(-paddleSpeed, 0, table.getWidth(), table.getDepth());
    if (keys[GLFW_KEY_RIGHT])
        playerPaddle.move(paddleSpeed, 0, table.getWidth(), table.getDepth());
}

void Game::update(float deltaTime) {
    ball.update(deltaTime);
    aiPaddle.update(deltaTime, &ball);

    //столкновения с ракетками
    if (playerPaddle.checkCollision(ball)) {
        ball.velocity.x = abs(ball.velocity.x) * 1.1f;
        ball.velocity.z = (ball.position.z - playerPaddle.position.z) * 5.0f;
        ball.position.x = playerPaddle.position.x + playerPaddle.size.x / 2 + ball.radius;
    }

    if (aiPaddle.checkCollision(ball)) {
        ball.velocity.x = -abs(ball.velocity.x) * 1.1f;
        ball.velocity.z = (ball.position.z - aiPaddle.position.z) * 5.0f;
        ball.position.x = aiPaddle.position.x - aiPaddle.size.x / 2 - ball.radius;
    }

    //столкновение со стенками
    if (abs(ball.position.z) > table.getDepth() / 2 - ball.radius) {
        ball.position.z = glm::sign(ball.position.z) * (table.getDepth() / 2 - ball.radius);
        ball.velocity.z = -ball.velocity.z * 0.9f;
    }

    //перезапуск, если мяч вылетит за стол
    if (ball.checkTableCollision(table.getWidth(), table.getHeight(), table.getDepth())) {
        ball.reset();
    }
}

void Game::render() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->use();
    shader->setMat4("view", camera.getViewMatrix());
    shader->setMat4("projection", camera.getProjectionMatrix());

    auto renderObject = [this](unsigned int VAO, glm::vec3 position, glm::vec3 scale) {
        glBindVertexArray(VAO);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::scale(model, scale);
        shader->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        };

    renderObject(tableVAO, glm::vec3(0.0f, -0.25f, 0.0f),
        glm::vec3(table.getWidth(), table.getHeight(), table.getDepth()));

    renderObject(netVAO, glm::vec3(0.0f, 0.1f, 0.0f),
        glm::vec3(1.0f, 0.0f, table.getDepth()));

    renderObject(paddleVAO, playerPaddle.position, playerPaddle.size);
    renderObject(paddleVAO, aiPaddle.position, aiPaddle.size);

    renderObject(ballVAO, ball.position, glm::vec3(ball.radius * 2));
}

void Game::run() {
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(deltaTime);
        update(deltaTime);
        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Game::cleanup() {
    if (shader) delete shader;
    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

int main() {
    setlocale(LC_ALL, "Ru");
    Game game;

    if (!game.init()) {
        std::cout << "Не удалось инициализировать игру" << std::endl;
        return -1;
    }

    game.run();

    return 0;
}