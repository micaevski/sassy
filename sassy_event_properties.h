#pragma once
#include <cstddef>

namespace sassy
{
namespace properties
{
template <typename T>
struct Indexed
{
  size_t index = generate_index();

private:
  static size_t generate_index()
  {
    static size_t index = 0;
    return index++;
  }
};
} // namespace properties

} // namespace sassy