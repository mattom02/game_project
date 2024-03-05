cmake_minimum_required(VERSION 3.16)
project(game_project)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(SOURCE_FILES
        src/Player.cpp
        src/PlayerGUI.cpp
        src/PowerUp.cpp
        src/Enemy.cpp
        src/GroupOfEnemies.cpp
        src/MainMenu.cpp
        src/DeathScreen.cpp
        src/ScoreText.cpp
        )

include_directories(include)

add_executable(game_project ${SOURCE_FILES} main.cpp)
target_link_libraries(game_project PRIVATE sfml-graphics)
target_compile_features(game_project PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
            TARGET game_project
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:game_project>
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/font.ttf $<TARGET_FILE_DIR:game_project>
            VERBATIM)
endif()

install(TARGETS game_project)