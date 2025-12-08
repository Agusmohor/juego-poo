#juego POO - Proyecto Final C++

Este juego es el proyecto final de Programacion Orientada a Objetos.
Juego desarrollado en C++ utilizando SFML para interfaz grafica

#estructura del juego

juego-poo/
|-src/
|  |-core/        # logica del juego (sin SFML)
|  |-gui/         # interfaz grafica (SFML)
|  |-main.cpp
|-tests/           # carpeta separada para pruebas
|-assets/          # texturas, sonidos, fuentes
|-data/            # saves y configuraciones
|-build/           # archivos compilados (ignorado por git)
|-README.md

{
    "version": "2.0.0",
    "tasks": [
        // ==========================
        // COMPILAR TODO EL JUEGO
        // ==========================
        {
            "label": "build-juego-poo",
            "type": "shell",
            "command": "C:/msys64/ucrt64/bin/g++.exe",
            "args": [
                "-std=c++20",
                "-Wall",
                "-Wextra",
                "-g",
                "-fdiagnostics-color=always",

                // compilar TODOS los .cpp
                "${workspaceFolder}/src/*.cpp",

                // includes
                "-I", "C:/msys64/ucrt64/include",
                "-I", "C:/SFML-3.0.2/include",

                // libs
                "-L", "C:/msys64/ucrt64/lib",
                "-L", "C:/SFML-3.0.2/lib",

                // enlazar SFML
                "-lsfml-graphics",
                "-lsfml-window",
                "-lsfml-system",

                // output
                "-o", "${workspaceFolder}/build/juego-poo.exe"
            ],
            "options": {
                "shell": {
                    "executable": "C:/Windows/System32/cmd.exe",
                    "args": ["/c"]
                }
            },
            "group": { "kind": "build", "isDefault": true },
            "problemMatcher": ["$gcc"],
            "detail": "Compila todo el proyecto del juego."
        },

        // ==========================
        // COMPILAR SOLO EL ARCHIVO ACTUAL
        // ==========================
        {
            "label": "build-active-file",
            "type": "shell",
            "command": "C:/msys64/ucrt64/bin/g++.exe",
            "args": [
                "-std=c++20",
                "-Wall",
                "-Wextra",
                "-g",
                "-fdiagnostics-color=always",

                // archivo actual
                "${file}",

                // incluye headers
                "-I", "C:/msys64/ucrt64/include",
                "-I", "C:/SFML-3.0.2/include",

                // libs
                "-L", "C:/msys64/ucrt64/lib",
                "-L", "C:/SFML-3.0.2/lib",

                // enlazar SFML
                "-lsfml-graphics",
                "-lsfml-window",
                "-lsfml-system",

                // output ejecutable
                "-o", "${fileDirname}/${fileBasenameNoExtension}.exe"
            ],
            "options": {
                "shell": {
                    "executable": "C:/Windows/System32/cmd.exe",
                    "args": ["/c"]
                }
            },
            "problemMatcher": ["$gcc"],
            "group": { "kind": "build" },
            "detail": "Compila solo el archivo abierto actualmente."
        }
    ]
}
