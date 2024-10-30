#include <SFML/Graphics.hpp>
#include <vector>

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Agregar Círculos con Sprites");


    sf::Texture texturaRoja, texturaAzul;
    if (!texturaRoja.loadFromFile("C:\\Users\\Equipo\\Desktop\\Unidad4_Assets\\rcircle.png") ||
        !texturaAzul.loadFromFile("C:\\Users\\Equipo\\Desktop\\Unidad4_Assets\\rcircleb.png")) {
        return -1;
    }


    std::vector<sf::Sprite> circulos;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();


            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Sprite circulo;


                if (event.mouseButton.button == sf::Mouse::Left) {
                    circulo.setTexture(texturaRoja);
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    circulo.setTexture(texturaAzul);
                }


                circulo.setPosition(static_cast<float>(event.mouseButton.x) - circulo.getGlobalBounds().width / 2,
                    static_cast<float>(event.mouseButton.y) - circulo.getGlobalBounds().height / 2);


                circulos.push_back(circulo);
            }
        }


        window.clear(sf::Color::White);
        for (const auto& circulo : circulos) {
            window.draw(circulo);
        }
        window.display();
    }

    return 0;
}
