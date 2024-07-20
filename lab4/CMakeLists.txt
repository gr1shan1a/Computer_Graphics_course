cmake_minimum_required(VERSION 3.25)
project(ComputerGraphic_4 C)

link_directories(${GTK3_LIBRARY_DIRS})

find_package(PkgConfig REQUIRED)
find_package(glfw3 3.3 REQUIRED)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
include_directories(/opt/homebrew/Cellar/glfw/3.3.8/include)

# Find GLEW
find_package(GLEW REQUIRED)

# Add GLEW include directories
include_directories(${GLEW_INCLUDE_DIRS})

# Add GLEW library to the target
target_link_libraries(ComputerGraphic_4 PRIVATE glfw ${GTK3_LIBRARIES} ${GLEW_LIBRARIES})

add_executable(ComputerGraphic_4 lab_4.c)

