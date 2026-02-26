#ifndef JUEGO_POO_KEYS_H
#define JUEGO_POO_KEYS_H

struct configKeys {
    sf::Keyboard::Key shieldKey,dashKey,fireKey,healKey;
};

enum class action {
    shield,
    dash,
    fire,
    heal,
};

#endif