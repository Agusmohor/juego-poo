#include "scenes/Pause.hpp"
#include "scenes/Match.hpp"

#include <algorithm>
#include <iostream>
#include <random>

#include "core/Game.hpp"
#include "world/Mapa.hpp"
#include "scenes/GameOver.hpp"
#include <string>

match::match() :  m_hud(), t_waring(font){
    std::string pngpath ="../assets/textures/map/tiles.png" ; std::string ground = "../assets/textures/map/mapa_ground.csv"; std::string grass = "../assets/textures/map/mapa_grass.csv";

    if (!m_res.tree1.loadFromFile("../assets/textures/trees/tree1.png")) {throw std::runtime_error("ERROR:COULD_NOT_LOAD_TREE_TEXTURE_FROM_FILE");}
    if (!m_res.tree2.loadFromFile("../assets/textures/trees/tree2.png")) {throw std::runtime_error("ERROR:COULD_NOT_LOAD_TREE_TEXTURE_FROM_FILE");}
    if (!m_res.tree3.loadFromFile("../assets/textures/trees/tree3.png")) {throw std::runtime_error("ERROR:COULD_NOT_LOAD_TREE_TEXTURE_FROM_FILE");}
    if (!m_res.Player.loadFromFile("../assets/textures/entity/player/sprite.png")){throw std::runtime_error("ERROR:COULD_NOT_LOAD_PLAYER_TEXTURE_FROM_FILE");}
    if (!m_res.shadow.loadFromFile("../assets/textures/entity/player/plshadow.png")){throw std::runtime_error("ERROR:COULD_NOT_LOAD_SHADOW_TEXTURE_FROM_FILE");}
    if (!m_res.shield.loadFromFile("../assets/textures/entity/player/shield.png")){throw std::runtime_error("ERROR:COULD_NOT_LOAD_SHIELD_TEXTURE_FROM_FILE");}
    if (!m_res.fballskin.loadFromFile("../assets/textures/entity/player/fireball.png")){throw std::runtime_error("ERROR:COULD_NOT_LOAD_FIREBALL_TEXTURE_FROM_FILE");}
    if (!m_res.Zombie.loadFromFile("../assets/textures/entity/zombie/sprite.png")){throw std::runtime_error("ERROR:COULD_NOT_LOAD_ZOMBIE_TEXTURE_FROM_FILE");}
    if (!font.openFromFile("../assets/fonts/MineFont.ttf")){throw std::runtime_error("ERROR:COULD_NOT_LOAD_FONT_FROM_FILE");}

    WarningOverlay.setSize({10000,10000}); t_waring.setFont(font); WarningOverlay.setFillColor({0,0,0,0});
    WarningOverlay.setPosition({-1000,-1000});
    t_waring.setCharacterSize(40); t_waring.setFillColor(sf::Color::Red); t_waring.setStyle(sf::Text::Bold);
    t_waring.setString("WARNING\nGET BACK"); t_waring.setPosition({180,400}); t_waring.setOutlineColor(sf::Color::Black);
    t_waring.setOutlineThickness(1.1);

    m_mapa.load(pngpath,ground,grass);

    m_ply = std::make_unique<player>(m_res.Player,m_res.shadow,m_res.shield,m_res.fballskin);

}


void match::update(float delta,game &m_gam){
    time += delta;
    if (isRecentlyOpen) {
        isRecentlyOpen = false;
        if (m_gam.getPlayerSaves().time > 0 && m_gam.getPlayerSaves().time < 10000){time = m_gam.getPlayerSaves().time;}
        if (!(m_gam.getPlayerSaves().kills <= 0)){kills = m_gam.getPlayerSaves().kills;}
        m_ply->setSaves(m_gam.getPlayerSaves());
        m_zombieSave = m_gam.getZombieSaves();
        for (auto &z : m_zombieSave) {
            m_zombies.push_back(std::make_unique<zombie>(m_res.Zombie,m_res.shadow,sf::Vector2f(z.x,z.y)));
        }

        m_treeSave = m_gam.getTreeSaves();
        sf::Vector2f v;
        for (auto &t : m_treeSave) {
            v.x = t.x; v.y = t.y;
            m_obtacles.push_back(std::make_unique<tree>(v));
        }

        if (m_treeSave.size() <= 0) {
            spawnObstacle();
        }
        for (auto &trees : m_obtacles) {
            trees->random(m_res.tree1,m_res.tree2,m_res.tree3);
        }
    }
    callSaveAndQuit(m_gam);
    setPlayerKeyBinds(m_gam.getKeyBinds());

    spriteTimer += delta;
    if (spriteTimer >= spriteDur) {
        for (auto &tree : m_obtacles) {
            tree->update();
        }
        m_ply->updateTexture();
        for (auto &z : m_zombies) {
            z->updateTexture();
        }
        spriteTimer = 0.f;
    }
    //actualizado de hitbox obstaculos
    m_hitboxes.resize(m_obtacles.size());
    for (size_t i=0;i<m_obtacles.size();i++) {
        m_hitboxes[i] = m_obtacles[i]->getHitbox();
    }

    //update del player si esta vivo
    if (m_ply->isAlive()) {m_ply->setHitboxes(m_hitboxes);m_ply->update(delta,m_gam);}
    for (auto &z : m_zombies) {
        z->setHitboxes(m_hitboxes);
        if (z->isAlive()) {z->update(delta,m_gam);}
        if (z->getHealth() <= 0 && !z->killCounted()){kills++; z->markKillCounted();}
    }

    //play audios
    m_ply->playAudios(m_gam);
    for (auto &u : m_zombies) {
        u->playAudios(m_gam);
    }

    //elimina todos los z, q cumplan con la condicion q no vivo, funcion inline
    m_zombies.erase(std::remove_if(m_zombies.begin(),m_zombies.end(),[](const std::unique_ptr<zombie>& z){return z->isDeathOver();}),m_zombies.end());

    if (m_zombies.size() < z_spawn.getMinEnemies() || m_zombies.size() < z_spawn.getMaxEnemies() && z_spawn.spawnCooldownTimer <= 0.f ) {
        spawnEnemies(); z_spawn.spawnCooldownTimer = z_spawn.spawnCooldownDur;
    }
    z_spawn.spawnCooldownTimer -= delta;

    //si no esta vivo, y presiona enter, crea otro personaje :)
    if (!m_ply->isAlive() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && !ispressed) {
        isOver(); m_gam.setStats(m_stats);

        m_gam.setScene(new gameover); ispressed = true;
        // m_ply.reset(); m_ply = std::make_unique<player>(m_res.Player,m_res.shadow);
    }
    // if (!m_zombie->isAlive()){m_zombie.reset(); m_zombie = std::make_unique<zombie>();}

    hits();

    if (m_ply->isAlive()) {
        for (auto &z : m_zombies) {
           z->getPlyPos(m_ply->getPosition());
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K) && !spawn){spawnEnemies();}
    spawn = false;

    m_hud.checkPlayer(*m_ply);
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N) && !ispressed) {m_gam.setScene(new gameover); ispressed = true;}
    playerIsOutOfRange(delta);
}

void match::updateView(game &m_gam){
    m_winSize = m_gam.getWinSize();
    m_uiview = m_gam.getView();
    m_hud.update();
    m_hud.updateView();
}

void match::draw(sf::RenderWindow &m_win){
    render(m_win);
    m_win.draw(WarningOverlay);
    if (p_spawn.isOut)m_win.draw(t_waring);
}


void match::render(sf::RenderWindow &m_win){

    //view mapa centrado en el player
    normalView(m_win);

    //se dibuja el mapa
    m_mapa.draw(m_win);

    m_drawble.clear();
    m_drawble.push_back(m_ply.get());
    for (auto &z : m_zombies) {
        m_drawble.push_back(z.get());
    }
    for (auto &trees : m_obtacles) {
        m_drawble.push_back(trees.get());
    }

    std::sort(m_drawble.begin(),m_drawble.end(),[](drawble* a, drawble* b){
        return (a->getPosition().y + a->getGlobalBounds().size.y) <
               (b->getPosition().y + b->getGlobalBounds().size.y);
    });

    for (auto &p : m_drawble) {
        p->draw(m_win);
    }

    specialFunctions(m_win);

    //view de UI
    m_win.setView(m_uiview);

    m_hud.onResize(m_win.mapPixelToCoords(sf::Vector2i(m_uiview.getSize().x,m_uiview.getSize().y )));
    m_hud.draw(m_win);

}

void match::normalView(sf::RenderWindow& m_win) {
    m_view = m_win.getDefaultView();
    m_view.setSize(sf::Vector2f(m_winSize));
    m_view.setCenter(m_ply->getPosition());
    m_view.zoom(0.2);
    m_win.setView(m_view);
}

void match::ProcessEvent(game &game, sf::Event &event) {
    m_hud.ProcessEvent(game, event);
    if (event.is<sf::Event::KeyPressed>() && event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape) {
        game.Pause();
    }
    if (auto *evt = event.getIf<sf::Event::KeyPressed>()) {
        if (evt->code == sf::Keyboard::Key::F4){ drawHitbox = !drawHitbox; }
    }
}

void match::specialFunctions(sf::RenderWindow &win) {
    if (!drawHitbox){return;}
    for (auto &u : m_drawble) {
            u->drawHitbox(win);
    }

}

void match::hits() {
    for (auto &z : m_zombies) {
        sf::Vector2f dist = m_ply->getPosition() -  z->getPosition();
        float distance = sqrt((dist.x * dist.x + dist.y * dist.y));
        sf::Vector2f plyDir = m_ply->getScale();

        //golpes juagdor a enemigo
        if (plyDir.x < 0 && m_ply->getHitStatus() ) {
            if (dist.x > 0 && dist.x < 15 && distance < 15 && z->isAlive()) {
                z->recieveDamage();
                m_ply->setHitStatus(false);
            }
        }
        if (plyDir.x > 0 && m_ply->getHitStatus() ) {
            if (dist.x < 0 && dist.x > -15 && distance < 15 && z->isAlive()) {
                z->recieveDamage();
                m_ply->setHitStatus(false);
            }
        }

        //golpes enemigo a jugador
        if ((z->getScale().x < 0 && distance < 10 && distance > 0) || (z->getScale().x > 0 && distance < 10 && distance > 0))  {
            if (z->getHitStatus() == false && m_ply->isAlive()) {
                z->setHitStatus(true);
            }
            if (z->canDealDamage()) {m_ply->recieveDamage();z->consumeDamage();}
        }

        //fireball damage
        if (m_ply->getFireball().getGlobalBounds().findIntersection(z->getGlobalBounds()) && m_ply->getIsShot()){
            z->recieveDamage();
        }
   }


}


void match::spawnEnemies() {
        int tx = z_spawn.minTilex + std::rand()%( z_spawn.maxTilex-z_spawn.minTilex + 1);
        int ty = z_spawn.minTiley + std::rand()%( z_spawn.maxTiley-z_spawn.minTiley + 1);
        if (!(tx >= z_spawn.minNTilex && tx <= z_spawn.maxNTilex && ty >= z_spawn.minNTiley && ty <= z_spawn.maxNTiley)) {
            m_zombies.push_back(std::make_unique<zombie>(m_res.Zombie,m_res.shadow,sf::Vector2f(tx * 32,ty * 32)));
        }


}

void match::spawnObstacle() {
        for (int i=0;i<obs_spawn.maxTreeSpawn;i++) {
            //genera coordenadas en tiles random
            int tx = obs_spawn.minTilex + std::rand()%( obs_spawn.maxTilex-obs_spawn.minTilex + 1);
            int ty = obs_spawn.minTiley + std::rand()%( obs_spawn.maxTiley-obs_spawn.minTiley + 1);
            //chequea q no este en la zona de aparicion
            if (!(tx >= obs_spawn.minNTilex && tx <= obs_spawn.maxNTilex && ty >= obs_spawn.minNTiley && ty <= obs_spawn.maxNTiley)) {
                bool exists = false;
                sf::Vector2f t_pos(tx*32,ty*32);
                //si no existe ningun obstaculo en esas coords, entonces se crea
                for (auto &t : m_obtacles) {
                    if (t->getPosition() == t_pos) {exists = true; break;}
                }
                if (!exists) {m_obtacles.push_back(std::make_unique<tree>(sf::Vector2f(tx*32,ty*32)));}
            }
        }

}

void match::isOver() {
    m_stats.timeAlive = time;
    m_stats.kills = kills;
}

void match::setPlayerKeyBinds(const std::array<sf::Keyboard::Scancode,4>& keyBinds) {
    m_ply->setKey(keyBinds);
}

void match::callSaveAndQuit(game &gam) {
    if (gam.getSaveAndQuit()) {
        gam.setPlayerSaves(m_ply->getSaves());
        gam.clearTsaves(); gam.clearZsaves();
        for (auto &z : m_zombies) {
            gam.setZombieSaves(z->getSaves());
        }
        for (auto &o : m_obtacles) {
            gam.setTreeSaves(o->getSaves());
        }
        gam.setScene(new menu);
    }
}

void match::playerIsOutOfRange(float delta) {
    sf::Vector2f p = m_ply->getPosition();
    if (p.x < p_spawn.minTileX*32 || p.x > p_spawn.maxTileX*32 || p.y < p_spawn.minTileY*32 || p.y > p_spawn.maxTileY*32) {
        p_spawn.timer -= delta;
        p_spawn.isOut = true;
        if (p.x > p_spawn.maxTileX*32){p_spawn.dist = p.x - p_spawn.maxTileX*32 ;}
        else if (p.x < p_spawn.minTileX*32){p_spawn.dist = p_spawn.minTileX*32 - p.x;}
        else if (p.y < p_spawn.minTileY*32){p_spawn.dist = p_spawn.minTileY*32 - p.y;}
        else if (p.y > p_spawn.maxTileY*32){p_spawn.dist = p.y - p_spawn.maxTileY*32;}

        std::uint8_t alp = std::clamp((p_spawn.dist / p_spawn.maxDist) * 200,0.f,255.f);
        WarningOverlay.setFillColor({0,0,0,alp});
        if (p_spawn.cooldownTimer < 0.f && p_spawn.timer <= 0.f && m_ply->isAlive()) {
            m_ply->recieveDamage();
            p_spawn.cooldownTimer = p_spawn.cooldownDur;
        }
    }else{p_spawn.isOut = false; p_spawn.timer = 10;}
    t_waring.setString("           WARNING\nGET BACK "+std::to_string(p_spawn.timer));
    if (p_spawn.timer <= 0.f) {p_spawn.cooldownTimer -= delta;}
    if (p_spawn.timer <= 0.f){p_spawn.timer = 0.f;}
}
