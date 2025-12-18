cmake_minimum_required(VERSION 3.10)
project(pong3d)

set(CMAKE_CXX_STANDARD 17)

# Исходные файлы
set(SRCS
    game/game.cpp
    game/camera.cpp
    game/shader.cpp
    game/ball.cpp
    game/paddle.cpp
    game/table.cpp
)

# Исполняемый файл
add_executable(pong3d ${SRCS})

# Подключаем заголовки
target_include_directories(pong3d PRIVATE
    game/include
    biblioteki/glfw-3.4.bin.WIN64/include
    biblioteki/glad/include
    biblioteki/glm
)

# GLAD
add_library(glad STATIC biblioteki/glad/src/glad.c)
target_include_directories(glad PUBLIC biblioteki/glad/include)

# Линковка
target_link_libraries(pong3d
    glad
    ${CMAKE_SOURCE_DIR}/libs/glfw3.lib
    opengl32
)

# Копируем DLL
add_custom_command(TARGET pong3d POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/libs/glfw3.dll
    $<TARGET_FILE_DIR:pong3d>
)

# Копируем шейдеры
add_custom_command(TARGET pong3d POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/game/shaders
    $<TARGET_FILE_DIR:pong3d>/shaders
)

add_custom_command(TARGET pong3d POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/biblioteki/glfw-3.4.bin.WIN64/lib-vc2022/glfw3.dll
    $<TARGET_FILE_DIR:pong3d>
)