#include <SFML/Graphics.hpp>

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Ventana con Crosshair");


    sf::Texture crosshairTexture;
    if (!crosshairTexture.loadFromFile("C:\\Users\\Equipo\\Desktop\\Unidad4_Assets\\crosshair.png")) {
        return -1;
    }


    sf::Sprite crosshairSprite;
    crosshairSprite.setTexture(crosshairTexture);
    crosshairSprite.setOrigin(crosshairTexture.getSize().x / 2, crosshairTexture.getSize().y / 2);
    crosshairSprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }


        window.clear(sf::Color::Black);
        window.draw(crosshairSprite);
        window.display();
    }

    return 0;
}









