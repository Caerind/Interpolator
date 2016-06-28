#ifndef LAGRANGE_HPP
#define LAGRANGE_HPP

#include "Polynomial.hpp"

template <typename T>
Polynomial<T> lagrange(std::vector<sf::Vector2<T>> const& list)
{
    Polynomial<T> res;
    Polynomial<T> p, fac;
    fac.setFactor(1, 1);
    for (std::size_t i = 0; i < list.size(); ++i)
    {
        p.clear();
        p.setFactor(0, 1);
        for (std::size_t j = 0; j < list.size(); ++j)
        {
            if (i != j)
            {
                fac.setFactor(0, -list[j].x);
                p *= fac;
            }
        }
        res += (p / p.value(list[i].x)) * (-list.at(i).y);
    }
    return res;
}

#endif // LAGRANGE_HPP
