#include <iostream>
#include <array>

template <typename T>
struct grid2
{
  grid2(T x_step = 1, T y_step = 1) : x_step(x_step), y_step(y_step) {}
  grid2(T x_step, T y_step, T x_origin, T y_origin)
      : grid2(x_step, y_step), x_origin(x_origin), y_origin(y_origin) {}

  T x_step{1}, y_step{1};
  T x_origin{0}, y_origin{0};

  auto operator()(int i, int j) {
    return std::array<T, 2>{T(x_origin + i * x_step), T(y_origin + j * y_step)};
    }
};





int main()
{
    // auto a = grid2<double>(0.5,0.2)(3,5);
    // std::cout << a[0] << ' ' << a[1] << std::endl;
}