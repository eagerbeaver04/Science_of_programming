# CMakeList.txt: проект CMake для Source; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
project ("Source")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Source "Source.cpp" "Node.h" "Node.cpp" "Iterator.cpp" "Tree.h" "Tree.cpp" "Resource.h" "Resource.cpp" )

configure_file(input.txt input.txt)
configure_file(output.txt output.txt)
# TODO: Добавьте тесты и целевые объекты, если это необходимо.
