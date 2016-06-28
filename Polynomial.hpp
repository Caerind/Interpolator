#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <sstream>
#include <vector>
#include "Function.hpp"

template <typename T>
class Polynomial : public Function<T>
{
    public:
        Polynomial() : mFactors(1) {};
        Polynomial(std::vector<T>& factors) : mFactors(factors) {};
        Polynomial(Polynomial<T> const& other) : mFactors(other.mFactors) {};
        virtual ~Polynomial() {};

        T value(T const& x) const
        {
            T y = 0;
            const std::size_t degree = getDegree();
            if (!degree)
                return 0;
            for (std::size_t i=0; i < degree; ++i)
                y += mFactors[i] * pow(x, (T)(int)i);
            return y;
        }

        std::string toString(std::size_t precision = 3) const
        {
            std::string r;
            for (std::size_t i = 0; i < mFactors.size(); i++)
            {
                if (getDegree() == 1 && mFactors[i] == 0)
                {
                    return "0";
                }
                else if (mFactors[i] != 0)
                {
                    std::ostringstream oss;
                    oss << std::setprecision(precision) << mFactors[i];
                    if (mFactors[i] != 1.f || i == 0)
                    {
                        r += oss.str();
                    }
                    if (i != 0)
                    {
                        r += "x";
                        if (i != 1)
                        {
                            r += std::to_string(i);
                        }
                    }
                    r += " + ";
                }
            }
            if (r.size() >= 3)
                r.erase(r.size()-3);
            return r;
        }

        void derive()
        {
            if (mFactors.size() <= 1)
            {
                clear();
            }
            else
            {
                for (std::size_t i = 0; i < mFactors.size()-1; ++i)
                    mFactors[i] = mFactors[i+1] * (i+1);
                mFactors.pop_back();
            }
        }

        void integrate()
        {
            mFactors.push_back(0);
            for (std::size_t i = mFactors.size()-1; i > 0; --i)
                mFactors[i] = mFactors[i-1] / i;
        }

        void clear()
        {
            mFactors.clear();
            mFactors.push_back(T());
        }

        void setFactor(std::size_t const& pos, T const& val)
        {
            if (pos >= mFactors.size())
                mFactors.resize(pos+1);

            mFactors[pos] = val;
        }

        T getFactor(std::size_t const& pos)
        {
            if (pos < mFactors.size() && pos >= 0)
            {
                return mFactors[pos];
            }
            return T();
        }

        inline std::size_t getDegree() const { return mFactors.size(); }

        const Polynomial<T>& operator+=(T const& add)
        {
            (*this)[0] += add;
            return *this;
        }

        const Polynomial<T>& operator+=(Polynomial<T> const& other)
        {
            const std::size_t otherDegree = other.getDegree();
            if (otherDegree > getDegree())
                mFactors.resize(otherDegree);
            for (std::size_t i = 0; i < otherDegree; ++i)
            {
                setFactor(i, other.mFactors[i] + mFactors[i]);
            }
            return *this;
        }

        const Polynomial<T>& operator*=(T const& fac)
        {
            for (std::size_t i = 0; i < mFactors.size(); ++i)
                mFactors[i] *= fac;
            return *this;
        }

        const Polynomial<T>& operator*=(Polynomial<T>& other)
        {
            const std::size_t degree = getDegree();
            const std::size_t otherDegree = other.getDegree();
            std::vector<T> tmp(mFactors);
            mFactors.clear();
            mFactors.resize(degree + otherDegree - 1);
            for (std::size_t i = 0; i < degree; ++i)
            {
                for (std::size_t j = 0; j < otherDegree; ++j)
                {
                    setFactor(i+j, tmp[i] * other[j] + mFactors[i+j]);
                }
            }
            return *this;
        }

        const Polynomial<T>& operator/=(T const& div)
        {
            for (std::size_t i = 0; i < mFactors.size(); ++i)
                mFactors[i] /= div;
            return *this;
        }

        bool operator==(Polynomial<T> const& other)
        {
            return (mFactors == other.mFactors);
        }

        bool operator!=(Polynomial<T> const& other)
        {
            return (mFactors != other.mFactors);
        }

        const Polynomial<T>& operator=(Polynomial<T> const& other)
        {
            if (*this == other)
                return *this;
            mFactors = other.mFactors;
            return *this;
        }

        inline T operator()(T const& x) const { return value(x); }

        inline const T& operator[](std::size_t i) const { return mFactors[i]; }
        inline T& operator[](std::size_t i) { return mFactors[i]; }

    protected:
        std::vector<T> mFactors;
};

template <typename T>
inline Polynomial<T> operator+(Polynomial<T> const& pol, T const& fac)
{
    Polynomial<T> p = pol;
    p += fac;
    return p;
}

template <typename T>
inline Polynomial<T> operator+(Polynomial<T> const& left, Polynomial<T> const& right)
{
    Polynomial<T> p = left;
    left += right;
    return p;
}

template <typename T>
inline Polynomial<T> operator*(Polynomial<T> const& pol, T const& fac)
{
    Polynomial<T> p = pol;
    p *= fac;
    return p;
}

template <typename T>
inline Polynomial<T> operator*(Polynomial<T> const& left, Polynomial<T> const& right)
{
    Polynomial<T> p = left;
    left *= right;
    return p;
}

template <typename T>
inline Polynomial<T> operator/(Polynomial<T> const& pol, T const& fac)
{
    Polynomial<T> p = pol;
    p /= fac;
    return p;
}

#endif // POLYNOMIAL_HPP
