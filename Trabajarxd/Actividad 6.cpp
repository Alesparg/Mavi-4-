#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

class Enemy {
private:
    sf::Sprite sprite;
    static sf::Texture texture;
    float scaleFactor;

public:
    Enemy(float scaleFactor) : scaleFactor(scaleFactor) {

        if (texture.getSize().x == 0) {
            if (!texture.loadFromFile("C:\\Users\\Equipo\\Desktop\\Unidad4_Assets\\et.png")) {
                throw std::runtime_error("No se pudo cargar la textura de Enemy");
            }
        }
        sprite.setTexture(texture);
        sprite.setScale(scaleFactor, scaleFactor);
        setPositionRandomly();
    }

    void setPositionRandomly() {
        int x = std::rand() % (800 - static_cast<int>(texture.getSize().x * scaleFactor));
        int y = std::rand() % (600 - static_cast<int>(texture.getSize().y * scaleFactor));
        sprite.setPosition(x, y);
    }

    bool isClicked(const sf::Vector2i& mousePosition) const {
        return sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }
};

sf::Texture Enemy::texture;

class Crosshair {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    float scaleFactor;

public:
    Crosshair(const std::string& textureFile, float scaleFactor) : scaleFactor(scaleFactor) {
        if (!texture.loadFromFile(textureFile)) {
            throw std::runtime_error("No se pudo cargar la textura de Crosshair");
        }
        sprite.setTexture(texture);
        sprite.setScale(scaleFactor, scaleFactor);
    }

    void updatePosition(const sf::Vector2i& mousePosition) {
        sprite.setPosition(static_cast<sf::Vector2f>(mousePosition));
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }
};

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Caza de Enemigos");
    window.setMouseCursorVisible(false);
    std::srand(static_cast<unsigned>(std::time(nullptr)));


    Crosshair crosshair("C:\\Users\\Equipo\\Desktop\\Unidad4_Assets\\crosshair.png", 0.2f);
    std::vector<Enemy> enemies;
    const int targetEnemies = 5;
    int defeatedEnemies = 0;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                for (auto it = enemies.begin(); it != enemies.end(); ) {
                    if (it->isClicked(sf::Mouse::getPosition(window))) {
                        it = enemies.erase(it);
                        defeatedEnemies++;
                        if (defeatedEnemies == targetEnemies) {
                            window.close();
                        }
                    }
                    else {
                        ++it;
                    }
                }
            }
        }


        if (enemies.empty()) {
            enemies.push_back(Enemy(0.2f));
        }


        crosshair.updatePosition(sf::Mouse::getPosition(window));


        window.clear();
        for (auto& enemy : enemies) {
            enemy.draw(window);
        }
        crosshair.draw(window);
        window.display();
    }

    return 0;
}
