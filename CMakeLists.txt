cmake_minimum_required(VERSION 3.7)
project(tetris_cpp_sdl2)

set(CMAKE_CXX_STANDARD 14)


include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

set(SOURCE_FILES src/main.cpp src/sdl/Window.cpp src/sdl/Window.hpp src/sdl/App.cpp src/sdl/App.hpp src/sdl/error/SdlError.cpp src/sdl/error/SdlError.hpp src/TetrisApp.cpp src/TetrisApp.hpp src/sdl/Delay.cpp src/sdl/Delay.hpp src/sdl/Texture.cpp src/sdl/Texture.hpp src/sdl/error/SdlImgError.cpp src/sdl/error/SdlImgError.hpp src/TetrisWindow.cpp src/TetrisWindow.hpp src/Piece.cpp src/Piece.hpp src/Pieces.cpp src/Pieces.hpp src/sdl/Timer.cpp src/sdl/Timer.hpp src/Tetromino.cpp src/Tetromino.hpp src/sdl/error/SdlTtfError.cpp src/sdl/error/SdlTtfError.hpp src/TetrominoBag.cpp src/TetrominoBag.hpp src/sdl/Font.cpp src/sdl/Font.hpp src/engine/Resources.cpp src/engine/Resources.hpp src/language/NonCopyableMoveable.hpp src/sdl/Renderer.cpp src/sdl/Renderer.hpp src/TetrisGame.cpp src/TetrisGame.hpp)
add_executable(tetris_cpp_sdl2 ${SOURCE_FILES})

target_link_libraries(tetris_cpp_sdl2 ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})

configure_file(resources/images/tetromino.png resources/images/tetromino.png COPYONLY)
configure_file(resources/images/tetromino_ghost.png resources/images/tetromino_ghost.png COPYONLY)
configure_file(resources/images/board.png resources/images/board.png COPYONLY)
configure_file(resources/images/dim_screen.png resources/images/dim_screen.png COPYONLY)
configure_file(resources/images/instructions.png resources/images/instructions.png COPYONLY)

configure_file(resources/fonts/ubuntu-font-family-0.83/Ubuntu-R.ttf resources/fonts/ubuntu-font-family-0.83/Ubuntu-R.ttf COPYONLY)