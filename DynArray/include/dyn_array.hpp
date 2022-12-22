#ifndef DYN_ARRAY_HPP_
#define DYN_ARRAY_HPP_

// #include <eigen3/Eigen/Dense>

#include <cmath>
#include <iostream>
#include <iterator>
#include <ostream>
#include <type_traits>
#include <utility>
#include <vector>

template <typename C, typename T = typename C::value_type> class DynArray
{
  public:
    DynArray(const C &container) : array_(container.begin(), container.end()){};
    ~DynArray() = default;

    T &operator[](int i)
    {
        return array_[i];
    }

    const T &operator[](int i) const
    {
        return array_[i];
    }

    template <typename type> std::vector<T> operator^(type pow)
    {
        std::vector<T> array_temp;
        array_temp.resize(array_.size());
#pragma omp parallel for private(i) shared(array_, array_temp, pow)
        for (int i = 0; i < array_.size(); ++i)
        {
            array_temp[i] = std::pow(array_[i], pow);
        }
        return array_temp;
    }

    template <typename type> std::vector<T> operator*(type number)
    {
        auto num = static_cast<T>(number);
        std::vector<T> array_temp;
        array_temp.resize(array_.size());
#pragma omp parallel for private(i) shared(array_, array_temp, num)
        for (int i = 0; i < array_.size(); ++i)
        {
            array_temp[i] = array_[i] * num;
        }
        return array_temp;
    }

    template <typename type> std::vector<T> operator/(type number)
    {
        auto num = static_cast<T>(number);
        std::vector<T> array_temp;
        array_temp.resize(array_.size());
#pragma omp parallel for private(i) shared(array_, array_temp, num)
        for (int i = 0; i < array_.size(); ++i)
        {
            array_temp[i] = array_[i] / num;
        }
        return array_temp;
    }

    template <typename type> std::vector<T> operator+(type number)
    {
        auto num = static_cast<T>(number);
        std::vector<T> array_temp;
        array_temp.resize(array_.size());
#pragma omp parallel for private(i) shared(array_, array_temp, num)
        for (int i = 0; i < array_.size(); ++i)
        {
            array_temp[i] = array_[i] + num;
        }
        return array_temp;
    }

    template <typename type> std::vector<T> operator-(type number)
    {
        auto num = static_cast<T>(number);
        std::vector<T> array_temp;
        array_temp.resize(array_.size());
#pragma omp parallel for private(i) shared(array_, array_temp, num)
        for (int i = 0; i < array_.size(); ++i)
        {
            array_temp[i] = array_[i] - num;
        }
        return array_temp;
    }

  private:
    std::vector<T> array_;
};

#endif