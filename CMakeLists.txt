cmake_minimum_required(VERSION 3.7)
project(tetris_cpp_sdl2)

set(CMAKE_CXX_STANDARD 14)


include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp sdl/Window.cpp sdl/Window.hpp sdl/App.cpp sdl/App.hpp sdl/SdlError.cpp sdl/SdlError.hpp TetrisApp.cpp TetrisApp.hpp sdl/Surface.cpp sdl/Surface.hpp sdl/Delay.cpp sdl/Delay.hpp sdl/Texture.cpp sdl/Texture.hpp sdl/SdlImgError.cpp sdl/SdlImgError.hpp TetrisWindow.cpp TetrisWindow.hpp Piece.cpp Piece.hpp Pieces.cpp Pieces.hpp sdl/Timer.cpp sdl/Timer.hpp Tetromino.cpp Tetromino.hpp sdl/SdlTtfError.cpp sdl/SdlTtfError.hpp)
add_executable(tetris_cpp_sdl2 ${SOURCE_FILES})

target_link_libraries(tetris_cpp_sdl2 ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})

configure_file(img/tetromino.png ./ COPYONLY)
configure_file(img/tetromino_ghost.png ./ COPYONLY)
configure_file(img/board.png ./ COPYONLY)