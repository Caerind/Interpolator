#include "Polynomial.hpp"
#include "Lagrange.hpp"
#include "Graph.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode(800,600),"Interpolator");

    sf::Font f;
    if (!f.loadFromFile("coolveticca.ttf"))
    {
        std::cerr << "font" << std::endl;
    }

    sf::Text pT("p = ",f,15);
    sf::Text xT("x = ",f,15);
    sf::Text yT("y = ",f,15);
    pT.setPosition(10,10);
    xT.setPosition(10,30);
    yT.setPosition(10,50);
    pT.setColor(sf::Color::Black);
    xT.setColor(sf::Color::Black);
    yT.setColor(sf::Color::Black);

    Polynomial<float> p;
    p.setColor(sf::Color::Red);

    Graph<float> g;
    g.addFunction(&p);

    std::vector<sf::Vector2f> pos;
    std::vector<sf::CircleShape> points;

    sf::Clock c;
    while (window.isOpen())
    {
        sf::Vector2f mPos = window.mapPixelToCoords(sf::Mouse::getPosition(window),g.getView());

        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }
            if (e.type == sf::Event::MouseWheelScrolled && e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                if (e.mouseWheelScroll.delta < 1)
                {
                    g.zoom(1.2f);
                }
                else
                {
                    g.zoom(0.8f);
                }
            }

            if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)
            {
                pos.push_back(mPos);
                points.push_back(sf::CircleShape(0.1f));
                points.back().setPosition(mPos);
                points.back().setFillColor(sf::Color::Red);
                p = lagrange<float>(pos);
                g.update();
            }
        }

        sf::Vector2f mvt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            mvt.y--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            mvt.x--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            mvt.y++;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            mvt.x++;
        g.moveView(mvt * c.restart().asSeconds() * g.getSpeed());

        pT.setString("p = " + p.toString());
        xT.setString("x = " + std::to_string(mPos.x));
        yT.setString("y = " + std::to_string(mPos.y));

        window.clear(sf::Color::White);
        g.render(window);

        for (std::size_t i = 0; i < points.size(); i++)
            window.draw(points[i]);
        window.setView(window.getDefaultView());
        window.draw(pT);
        window.draw(xT);
        window.draw(yT);
        window.display();
    }

    std::cout << "p(x) = " << p.toString() << std::endl;

    return 0;
}
