#include "dyn_array.hpp"

#include <vector>

int main()
{
    std::vector<double> vec = {1, 2, 3, 5, 10, 15};
    auto arr = DynArray(vec);

    std::cout << arr << std::endl;

    auto arr_sqr = arr ^ 2;
    std::cout << arr_sqr << std::endl;

    auto arr_mul = arr * 2;
    std::cout << arr_mul << std::endl;

    auto arr_div = arr / 2;
    std::cout << arr_div << std::endl;

    auto arr_add = arr + 15;
    std::cout << arr_add << std::endl;

    auto arr_sub = arr - 15;
    std::cout << arr_sub << std::endl;

    arr += 5;
    std::cout << arr << std::endl;

    arr -= 5;
    std::cout << arr << std::endl;

    arr *= 100;
    std::cout << arr << std::endl;

    arr /= 5;
    std::cout << arr << std::endl;

    arr ^= 2;
    std::cout << arr << std::endl;

    auto arr2 = std::move(arr);
    std::cout << arr << std::endl;
    std::cout << arr2 << std::endl;

    arr.push_back(5);
    std::cout << arr << std::endl;
    std::cout << arr[5] << std::endl; // TODO check bounds
    // std::cout << arr[5.5] << std::endl;  // compiler error

    return (0);
}