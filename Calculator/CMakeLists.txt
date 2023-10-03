# CMakeList.txt: проект CMake для Calculator; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
project ("Calculator")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Calculator "Calculator.cpp" "Calculator.h" "Operator.h" "Loader.h" "Loader.cpp" "Operations.h" "Operations.cpp" "Parser.h" "Parser.cpp")


configure_file(${PROJECT_SOURCE_DIR}/plugins/DynamicLib4.dll ${PROJECT_BINARY_DIR}/plugins/DynamicLib4.dll COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/plugins/DynamicLib5.dll ${PROJECT_BINARY_DIR}/plugins/DynamicLib5.dll COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/plugins/DynamicLib6.dll ${PROJECT_BINARY_DIR}/plugins/DynamicLib6.dll COPYONLY)
# TODO: Добавьте тесты и целевые объекты, если это необходимо.
