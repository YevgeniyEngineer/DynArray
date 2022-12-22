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
    DynArray<C, T>(DynArray<C, T> &&other) noexcept
    {
        if (this == &other)
        {
            return;
        }
        this->array_ = std::move(other.array_);
    }

    ~DynArray() = default;

    // copy assignment
    DynArray<C, T> &operator=(const DynArray<C, T> &other)
    {
        // Guard self assignment
        if (this == &other)
        {
            return *this;
        }
        this->array_ = other->array_;
        return *this;
    }

    // move assignment
    DynArray<C, T> &operator=(DynArray<C, T> &&other) noexcept
    {
        // Guard self assignment
        if (this == &other)
        {
            return *this;
        }

        this->array_ = std::move(other->array_);
        return *this;
    }

    T &operator[](int i)
    {
        return array_[i];
    }

    const T &operator[](int i) const
    {
        return array_[i];
    }

    template <typename type> DynArray<C, T> &operator^=(type pow)
    {
#pragma omp parallel for private(i) shared(array_, pow)
        for (int i = 0; i < array_.size(); ++i)
        {
            array_[i] = std::pow(array_[i], pow);
        }
        return *this;
    }

    template <typename type> DynArray<C, T> &operator*=(type num)
    {
        auto number = static_cast<T>(num);
#pragma omp parallel for private(i) shared(array_, number)
        for (int i = 0; i < array_.size(); ++i)
        {
            array_[i] *= number;
        }
        return *this;
    }

    template <typename type> DynArray<C, T> &operator/=(type num)
    {
        auto number = static_cast<T>(num);
#pragma omp parallel for private(i) shared(array_, number)
        for (int i = 0; i < array_.size(); ++i)
        {
            array_[i] /= number;
        }
        return *this;
    }

    template <typename type> DynArray<C, T> &operator+=(type num)
    {
        auto number = static_cast<T>(num);
#pragma omp parallel for private(i) shared(array_, number)
        for (int i = 0; i < array_.size(); ++i)
        {
            array_[i] += number;
        }
        return *this;
    }

    template <typename type> DynArray<C, T> &operator-=(type num)
    {
        auto number = static_cast<T>(num);
#pragma omp parallel for private(i) shared(array_, number)
        for (int i = 0; i < array_.size(); ++i)
        {
            array_[i] -= number;
        }
        return *this;
    }

    template <typename type> DynArray<C, T> operator^(type pow)
    {
        std::vector<T> array_temp;
        array_temp.resize(array_.size());
#pragma omp parallel for private(i) shared(array_, array_temp, pow)
        for (int i = 0; i < array_.size(); ++i)
        {
            array_temp[i] = std::pow(array_[i], pow);
        }
        return DynArray(array_temp);
    }

    template <typename type> DynArray<C, T> operator*(type number)
    {
        auto num = static_cast<T>(number);
        std::vector<T> array_temp;
        array_temp.resize(array_.size());
#pragma omp parallel for private(i) shared(array_, array_temp, num)
        for (int i = 0; i < array_.size(); ++i)
        {
            array_temp[i] = array_[i] * num;
        }
        return DynArray(array_temp);
    }

    template <typename type> DynArray<C, T> operator/(type number)
    {
        auto num = static_cast<T>(number);
        std::vector<T> array_temp;
        array_temp.resize(array_.size());
#pragma omp parallel for private(i) shared(array_, array_temp, num)
        for (int i = 0; i < array_.size(); ++i)
        {
            array_temp[i] = array_[i] / num;
        }
        return DynArray(array_temp);
    }

    template <typename type> DynArray<C, T> operator+(type number)
    {
        auto num = static_cast<T>(number);
        std::vector<T> array_temp;
        array_temp.resize(array_.size());
#pragma omp parallel for private(i) shared(array_, array_temp, num)
        for (int i = 0; i < array_.size(); ++i)
        {
            array_temp[i] = array_[i] + num;
        }
        return DynArray(array_temp);
    }

    template <typename type> DynArray<C, T> operator-(type number)
    {
        auto num = static_cast<T>(number);
        std::vector<T> array_temp;
        array_temp.resize(array_.size());
#pragma omp parallel for private(i) shared(array_, array_temp, num)
        for (int i = 0; i < array_.size(); ++i)
        {
            array_temp[i] = array_[i] - num;
        }
        return DynArray(array_temp);
    }

    template <typename type> friend std::ostream &operator<<(std::ostream &os, const DynArray<type> &obj)
    {
        const auto &v = obj.array_;
        os << "[";
        for (int i = 0; i < v.size(); ++i)
        {
            os << v[i];
            if (i != v.size() - 1)
                os << ", ";
        }
        os << "]";
        return os;
    }

  private:
    std::vector<T> array_;
};

#endif