cmake_minimum_required(VERSION 4.1)
project(juego_poo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Ejecutable ---
add_executable(juego_poo WIN32
        src/main.cpp
        src/core/Game.cpp
        src/core/AudioManager.cpp

        src/gameplay/Abilities.cpp
        src/gameplay/Abilities.cpp
        src/gameplay/ShootAbility.cpp
        src/gameplay/HealingAbility.cpp
        src/gameplay/DashAbility.cpp
        src/gameplay/ShieldAbility.cpp
        src/gameplay/Stats.cpp

        src/scenes/Pause.cpp
        src/scenes/menu.cpp
        src/scenes/Match.cpp
        src/scenes/GameOver.cpp
        src/scenes/settingsScene.cpp
        src/scenes/rankingScene.cpp

        src/ui/Hud.cpp

        src/world/Player.cpp
        src/world/Zombie.cpp
        src/world/Mapa.cpp
        src/world/Tree.cpp
)

target_include_directories(juego_poo PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

# --- SFML 3 ---
find_package(SFML REQUIRED COMPONENTS Graphics Window System Audio Main)
target_link_libraries(juego_poo
        PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
        SFML::Audio
        SFML::Main
)

add_custom_command(TARGET juego_poo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:juego_poo>/assets
)

add_custom_command(TARGET juego_poo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/data
            $<TARGET_FILE_DIR:juego_poo>/data
)

add_dependencies(juego_poo copy_assets)