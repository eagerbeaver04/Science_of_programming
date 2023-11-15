# CMakeList.txt: проект CMake для Source; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
project ("Source")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Source "Source.cpp" "Engine.h" "Wrapper.h" )

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
