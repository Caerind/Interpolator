#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Function.hpp"

template <typename T>
class Graph
{
    public:
        Graph()
        {
            mX.resize(2);
            mY.resize(2);

            mX[0].color = sf::Color::Black;
            mX[1].color = sf::Color::Black;
            mY[0].color = sf::Color::Black;
            mY[1].color = sf::Color::Black;

            mX[0].position = sf::Vector2f(-1000000.f,0.f);
            mX[1].position = sf::Vector2f( 1000000.f,0.f);
            mY[0].position = sf::Vector2f(0.f, -1000000.f);
            mY[1].position = sf::Vector2f(0.f,  1000000.f);

            setView(-10.f,10.f,-10.f,10.f);

            setCenter(sf::Vector2f(0,0));
        }

        void setView(float xmin, float xmax, float ymin, float ymax)
        {
            mView.setCenter((xmax-xmin) * 0.5f,(ymax-ymin) * 0.5f);
            mView.setSize(xmax-xmin,ymax-ymin);
            update();
        }

        void moveView(sf::Vector2f const& mvt)
        {
            mView.move(mvt);
            update();
        }

        void setCenter(sf::Vector2f const& center)
        {
            mView.setCenter(center);
            update();
        }

        void zoom(float factor)
        {
            mView.zoom(factor);
            update();
        }

        sf::View& getView() { return mView; }

        void addFunction(Function<T>* f)
        {
            if (f != nullptr)
            {
                mFunctions.push_back(f);
                T min = (T)(mView.getCenter().x - mView.getSize().x * 0.5f);
                T max = (T)(mView.getCenter().x + mView.getSize().x * 0.5f);
                f->update(min,max,(T)(0.01));
            }
        }

        void render(sf::RenderTarget& target)
        {
            target.setView(mView);

            target.draw(&mX[0],2,sf::Lines);
            target.draw(&mY[0],2,sf::Lines);

            for (std::size_t i = 0; i < mFunctions.size(); i++)
            {
                if (mFunctions[i] != nullptr)
                {
                    mFunctions[i]->render(target);
                }
            }
        }

        float getSpeed()
        {
            return mView.getSize().x * 1.5f;
        }

        void update()
        {
            for (std::size_t i = 0; i < mFunctions.size(); i++)
            {
                if (mFunctions[i] != nullptr)
                {
                    T min = (T)(mView.getCenter().x - mView.getSize().x * 0.5f);
                    T max = (T)(mView.getCenter().x + mView.getSize().x * 0.5f);
                    mFunctions[i]->update(min,max,(T)(0.01));
                }
            }
        }

    protected:
        sf::View mView;

        std::vector<Function<T>*> mFunctions;

        std::vector<sf::Vertex> mX;
        std::vector<sf::Vertex> mY;
};

#endif // GRAPH_HPP
