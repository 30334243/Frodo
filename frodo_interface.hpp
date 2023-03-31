#ifndef FRODO_INTERFACE_HPP
#define FRODO_INTERFACE_HPP

#include <vector>
#include <cinttypes>
#include <tuple>
#include <functional>

namespace Frodo {
   template<class... Args>
   using VecCheckers = std::vector<std::function<bool(Args...)>>;
   template<class... Args>
   using VecRunner = std::vector<std::function<void(Args...)>>;
}
#endif
