cmake_minimum_required(VERSION 3.25)
project(ComputerGraphic_5 C)

find_package(PkgConfig REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(
        ${GTK3_INCLUDE_DIRS}
        /opt/homebrew/Cellar/glfw/3.3.8/include
        /opt/homebrew/Cellar/glew/2.2.0_1/include
        /opt/homebrew/Cellar/glm/0.9.9.8/include/glm/
)

link_directories(
        ${GTK3_LIBRARY_DIRS}
)

add_executable(ComputerGraphic_5 lab_5.c)

# Link libraries
target_link_libraries(ComputerGraphic_5 PRIVATE glfw ${GTK3_LIBRARIES} GLEW::GLEW ${GLM_INCLUDE_DIRS})
