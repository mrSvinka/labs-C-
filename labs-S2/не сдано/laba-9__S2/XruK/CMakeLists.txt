cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME sfml_sample)
project("${PROJECT_NAME}")


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


add_definitions(-DSFML_STATIC)

include_directories("ext/SFML/include/")
include_directories("inc/")
link_directories("ext/SFML/lib/")

add_executable(${PROJECT_NAME}
    main.cpp
    pig.cpp
    potato.cpp
    map.cpp
)


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/Textures"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/Textures
)


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/Fonts"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/Fonts
)


target_link_libraries("${PROJECT_NAME}" 
                          sfml-graphics-s-d
						  sfml-window-s-d
						  sfml-system-s-d
						  opengl32
						  freetype
						  winmm
						  gdi32
						  sfml-audio-s-d
						  openal32
						  flac
						  vorbisenc
						  vorbisfile
						  vorbis
						  ogg)