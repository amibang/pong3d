# Pong3D
3D версия классической игры Pong

# Управление
- Управление ракеткой: Стрелки вправо/влево/вверх/вниз 
- Управление камерой - Мышь
- Выход - Esc

# Структура проекта
- biblioteki - нужные библиотеки OpenGL 
- game - исходный код игры

# Сборка
```bash
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Debug
```
