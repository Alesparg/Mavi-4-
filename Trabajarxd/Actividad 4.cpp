#include <SFML/Graphics.hpp>

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Control de Sprite con SFML");


    sf::Texture textureSquare, textureCircle;
    if (!textureSquare.loadFromFile("C:\\Users\\Equipo\\Desktop\\Unidad4_Assets\\cuad_yellow.png") || !textureCircle.loadFromFile("C:\\Users\\Equipo\\Desktop\\Unidad4_Assets\\rcircleg.png")) {
        return -1;
    }

    sf::Sprite sprite;
    sprite.setTexture(textureSquare);


    sf::Vector2f desiredSize(100.0f, 100.0f);
    sf::Vector2u squareSize = textureSquare.getSize();
    sf::Vector2u circleSize = textureCircle.getSize();
    sprite.setScale(desiredSize.x / squareSize.x, desiredSize.y / squareSize.y);


    sprite.setOrigin(squareSize.x / 2, squareSize.y / 2);
    sprite.setPosition(400, 300);


    const float moveSpeed = 5.0f;
    bool isCircle = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                isCircle = !isCircle;
                sprite.setTexture(isCircle ? textureCircle : textureSquare);


                sf::Vector2u currentSize = isCircle ? circleSize : squareSize;
                sprite.setScale(desiredSize.x / currentSize.x, desiredSize.y / currentSize.y);
                sprite.setOrigin(currentSize.x / 2, currentSize.y / 2);
            }
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (sprite.getPosition().x - moveSpeed > desiredSize.x / 2)
                sprite.move(-moveSpeed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (sprite.getPosition().x + moveSpeed < window.getSize().x - desiredSize.x / 2)
                sprite.move(moveSpeed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (sprite.getPosition().y - moveSpeed > desiredSize.y / 2)
                sprite.move(0, -moveSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (sprite.getPosition().y + moveSpeed < window.getSize().y - desiredSize.y / 2)
                sprite.move(0, moveSpeed);
        }

        // Renderizado
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}

