#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <iomanip>

template <typename T>
class Function
{
    public:
        Function() { mColor = sf::Color::Black; }

        virtual T value(T const& x) const { return T(); }
        virtual std::string toString(std::size_t precision = 3) const { return "0"; }

        virtual void derive() {}
        virtual void intergrate() {}

        void setColor(sf::Color const& color) { mColor = color; }
        sf::Color getColor() const { return mColor; }

        void render(sf::RenderTarget& target) { target.draw(&mVertexArray[0],mVertexArray.size(),sf::Lines); }
        void update(T const& xmin, T const& xmax, T const& d)
        {
            mVertexArray.clear();
            for (T x = xmin; x <= xmax; x += d)
            {
                mVertexArray.emplace_back(sf::Vector2f(x,-value(x)),mColor);
                if (x != xmin && x != xmax)
                {
                    mVertexArray.emplace_back(sf::Vector2f(x,-value(x)),mColor);
                }
            }
        }

    protected:
        std::vector<sf::Vertex> mVertexArray;
        sf::Color mColor;
};

#endif // FUNCTION_HPP
