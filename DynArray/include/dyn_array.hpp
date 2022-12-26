#ifndef DYN_ARRAY_HPP_
#define DYN_ARRAY_HPP_

// #include <eigen3/Eigen/Dense>

#include <algorithm>
#include <cmath>
#include <execution>
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

    // for integral types only
    template <typename Integer, std::enable_if_t<std::is_integral<Integer>::value, bool> = true>
    T &operator[](Integer i)
    {
        return array_[i];
    }

    template <typename Integer, std::enable_if_t<std::is_integral<Integer>::value, bool> = true>
    const T &operator[](Integer i) const
    {
        return array_[i];
    }

    template <typename type> DynArray<C, T> &operator^=(type pow)
    {
        std::for_each(std::execution::par, array_.begin(), array_.end(),
                      [&](auto &element) { element = std::pow(element, pow); });
        return *this;
    }

    template <typename type> DynArray<C, T> &operator*=(type num)
    {
        auto number = static_cast<T>(num);
        std::for_each(std::execution::par, array_.begin(), array_.end(), [&](auto &element) { element *= number; });
        return *this;
    }

    template <typename type> DynArray<C, T> &operator/=(type num)
    {
        auto number = static_cast<T>(num);
        std::for_each(std::execution::par, array_.begin(), array_.end(), [&](auto &element) { element /= number; });
        return *this;
    }

    template <typename type> DynArray<C, T> &operator+=(type num)
    {
        auto number = static_cast<T>(num);
        std::for_each(std::execution::par, array_.begin(), array_.end(), [&](auto &element) { element += number; });
        return *this;
    }

    template <typename type> DynArray<C, T> &operator-=(type num)
    {
        auto number = static_cast<T>(num);
        std::for_each(std::execution::par, array_.begin(), array_.end(), [&](auto &element) { element -= number; });
        return *this;
    }

    template <typename type> DynArray<C, T> operator^(type pow)
    {
        std::vector<T> array_temp(array_.begin(), array_.end());
        auto number = static_cast<T>(pow);
        std::for_each(std::execution::par, array_temp.begin(), array_temp.end(),
                      [&](auto &element) { element = std::pow(element, number); });
        return DynArray(array_temp);
    }

    template <typename type> DynArray<C, T> operator*(type num)
    {
        std::vector<T> array_temp(array_.begin(), array_.end());
        auto number = static_cast<T>(num);
        std::for_each(std::execution::par, array_temp.begin(), array_temp.end(),
                      [&](auto &element) { element *= number; });
        return DynArray(array_temp);
    }

    template <typename type> DynArray<C, T> operator/(type num)
    {
        std::vector<T> array_temp(array_.begin(), array_.end());
        auto number = static_cast<T>(num);
        std::for_each(std::execution::par, array_temp.begin(), array_temp.end(),
                      [&](auto &element) { element /= number; });
        return DynArray(array_temp);
    }

    template <typename type> DynArray<C, T> operator+(type num)
    {
        std::vector<T> array_temp(array_.begin(), array_.end());
        auto number = static_cast<T>(num);
        std::for_each(std::execution::par, array_temp.begin(), array_temp.end(),
                      [&](auto &element) { element += number; });
        return DynArray(array_temp);
    }

    template <typename type> DynArray<C, T> operator-(type num)
    {
        std::vector<T> array_temp(array_.begin(), array_.end());
        auto number = static_cast<T>(num);
        std::for_each(std::execution::par, array_temp.begin(), array_temp.end(),
                      [&](auto &element) { element -= number; });
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

    void push_back(T &&value)
    {
        array_.push_back(std::move(value));
    }

    void push_back(const T &value)
    {
        array_.push_back(value);
    }

  private:
    std::vector<T> array_;
};

#endif