# Juego POO – Proyecto Final C++

Este juego fue desarrollado como proyecto final para la materia **Programación Orientada a Objetos** de la carrera **Ingeniería Informática – UNL FICH**.

El proyecto está implementado en **C++** utilizando la biblioteca gráfica **SFML**.

El objetivo fue aplicar conceptos de:

- Programación Orientada a Objetos
- Manejo de archivos (binarios y texto)
- Gestión de escenas
- Sistema de entidades

---

# Características del juego

- Movimiento del jugador
- Sistema de habilidades
- Enemigos con comportamiento básico
- Obstáculos y colisiones
- Sistema de stamina y vida
- Sistema de ranking
- Guardado de datos en archivos
- Interfaz gráfica con HUD
- Menú principal y escenas del juego

---

# Tecnologías utilizadas

- **C++17 / C++20**
- **SFML**
- **Tiled (mapas)**
- **Git / GitHub**

---

# Estructura del proyecto

juego-poo/

|-- src/ # código fuente
| |-- main.cpp
| |-- core/ # lógica principal del juego
| |-- gameplay/ # sistema de habilidades
| |-- scenes/ # escenas del juego
| |-- ui/ # interfaz gráfica
| |-- world/ # entidades y objetos
|
|-- includes/ # headers del proyecto
|
|-- tests/ # pruebas
|
|-- assets/ # recursos del juego
| |-- fonts/
| |-- sounds/
| |-- textures/
|
|-- data/ # datos persistentes
| |-- config/
| |-- globalstats/
| |-- saves/
|
|-- build/ # ejecutables compilados
|
|-- README.md
|-- CREDITS.md


Asegurate de que las carpetas **assets/** y **data/** estén en el mismo directorio que el ejecutable.

---

# Guardado de datos

El juego utiliza archivos para almacenar:

- configuraciones
- ranking global
- partidas guardadas

Los datos se almacenan dentro de la carpeta:
data/

---

# Créditos

Este proyecto utiliza assets creados por artistas externos.

Ver:
CREDITS.md