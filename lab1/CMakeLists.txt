cmake_minimum_required(VERSION 3.0)
project(ComputerGraphic C)

link_directories(${GTK3_LIBRARY_DIRS})
# Найти пакет pkg-config
find_package(PkgConfig REQUIRED)

# Использовать pkg-config для найти GTK+
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Указать пути к заголовочным файлам GTK+
include_directories(${GTK3_INCLUDE_DIRS})

# Создать исполняемый файл ComputerGraphic из lab_1.c
add_executable(ComputerGraphic lab_1.c)

# Линковать с библиотеками GTK+
target_link_libraries(ComputerGraphic ${GTK3_LIBRARIES})

