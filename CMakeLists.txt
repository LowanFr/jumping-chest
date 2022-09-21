cmake_minimum_required( VERSION 3.7.0 )
project( main )
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB SOURCES "${SRC_DIR}/main.c" "${SRC_DIR}/fonctions_SDL.c")
add_executable(${PROJECT_NAME} ${SOURCES})

# Find installed packages with syntax: find_package(<PackageName>)
find_package( SDL2 )
# If the package is found, serveral variables associated to the
# library are created: ${SDL2_FOUND} if SDL2 is found in the system
# ${SDL2_INCLUDE_DIRS} contains the path of SDL2 include folder
# ${SDL2_LIBRARIES} contains the path of SDL2 lib
if( ${SDL2_FOUND})
    message(STATUS "Found SDL2")
    # Include directories to build the project
    include_directories(${SDL2_INCLUDE_DIRS})
    # Specify libraries for linking to the project
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} -lSDL2_ttf)
else()
    message(STATUS "Could not locate SDL2")
endif()