#include "dyn_array.hpp"

#include <vector>

int main()
{
    std::vector<double> vec = {1, 2, 3};
    auto arr = DynArray(vec);

    std::cout << arr[0] << " " << arr[1] << " " << arr[2] << std::endl;

    auto arr_sqr = arr ^ 2;
    std::cout << arr_sqr[0] << " " << arr_sqr[1] << " " << arr_sqr[2] << std::endl;

    auto arr_mul = arr * 2;
    std::cout << arr_mul[0] << " " << arr_mul[1] << " " << arr_mul[2] << std::endl;

    auto arr_div = arr / 2;
    std::cout << arr_div[0] << " " << arr_div[1] << " " << arr_div[2] << std::endl;

    auto arr_add = arr + 15;
    std::cout << arr_add[0] << " " << arr_add[1] << " " << arr_add[2] << std::endl;

    auto arr_sub = arr - 15;
    std::cout << arr_sub[0] << " " << arr_sub[1] << " " << arr_sub[2] << std::endl;

    return (0);
}