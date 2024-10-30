#include <SFML/Graphics.hpp>
#include <vector>

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Sniper^4 - Arrastrar Puntos");
    std::vector<sf::CircleShape> puntos(4);


    std::vector<sf::Vector2f> posiciones = {
        sf::Vector2f(0, 0),
        sf::Vector2f(800, 0),
        sf::Vector2f(0, 600),
        sf::Vector2f(800, 600)
    };


    for (int i = 0; i < 4; ++i) {
        puntos[i].setRadius(10);
        puntos[i].setFillColor(sf::Color::Red);
        puntos[i].setOrigin(puntos[i].getRadius(), puntos[i].getRadius());
        puntos[i].setPosition(posiciones[i]);
    }

    bool isDragging = false;
    int puntoSeleccionado = -1;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();


            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                for (int i = 0; i < 4; ++i) {

                    if (puntos[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        isDragging = true;
                        puntoSeleccionado = i;
                        break;
                    }
                }
            }


            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                isDragging = false;
                puntoSeleccionado = -1;
            }


            if (isDragging && puntoSeleccionado != -1) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                puntos[puntoSeleccionado].setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            }
        }


        window.clear(sf::Color::Black);
        for (const auto& punto : puntos) {
            window.draw(punto);
        }
        window.display();
    }

    return 0;
}
