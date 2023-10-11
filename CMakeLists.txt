cmake_minimum_required(VERSION 3.0.0)
project(graflib VERSION 0.1.0)

set(CPP_FILES main.cpp Game.cpp grafLib/CordinatSystem.cpp grafLib/ExponentFunction.cpp grafLib/LinesFunction.cpp)

set(SFML_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/SFML/include)
set(SFML_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/SFML/lib)
set(SFML_DIR ${CMAKE_SOURCE_DIR}/SFML/lib/cmake/SFML)

message(STATUS "SFML Include dir: "${SFML_INCLUDE_DIR})

include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIBRARY_DIR})

if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/Content")
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Content)
endif()

file(COPY ${CMAKE_SOURCE_DIR}/SFML/bin/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/Content DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Content)

add_executable(graflib ${CPP_FILES})
target_link_libraries(graflib sfml-graphics sfml-audio sfml-network sfml-window sfml-system)