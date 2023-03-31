#ifndef FRODO_HPP
#define FRODO_HPP

#include <type_traits>
#include <utility>
#include <tuple>
#include "frodo_interface.hpp"

// NAMESPACE FRODO
namespace Frodo {
   // TRUE
   template<class Head, class... Tail>
      auto True(Head head, Tail... tail) {
         return [head, tail...] (auto&&... args) {
            VecRunner<decltype(args)...> funcs{head};
            (funcs.push_back(tail),...);
            for (auto func : funcs) {
               func(std::forward<decltype(args)>(args)...);
            }
            return true;
         };
      }
	// RUNNER
	template<class Head, class... Tail>
      auto Runner(Head head, Tail... tail) {
         return [head, tail...] (auto&&... args) {
            VecRunner<decltype(args)...> funcs{head};
            (funcs.push_back(tail),...);
            for (auto func : funcs) {
               func(std::forward<decltype(args)>(args)...);
            }
         };
      }
   // NAMESPACE OR ALL
   namespace OrAll {
      // CHECKER
      template<class Head, class... Tail>
         auto Checker(bool const r, Head head, Tail... tail) {
            return [r, head, tail...] (auto&&... args) {
               VecCheckers<decltype(args)...> funcs{head};
               (funcs.push_back(tail),...);
               bool ret{};
               for (auto func : funcs) {
                  ret |= r == func(std::forward<decltype(args)>(args)...);
               }
               return ret;
            };
         }
   }
   // NAMESPACE OR
   namespace Or {
      // CHECKER
      template<class Head, class... Tail>
         auto Checker(Head head, Tail... tail) {
            return [head, tail...] (auto&&... args) {
               VecCheckers<decltype(args)...> funcs{head};
               (funcs.push_back(tail),...);
               for (auto func : funcs) {
                  if (func(std::forward<decltype(args)>(args)...)) {
                     return true;
                  }
               }
               return false;
            };
         }
   }
   // NAMESPACE AND
   namespace And {
      // CHECKER
		template<class Head, class... Tail>
         auto Checker(Head head, Tail... tail) {
            return [head, tail...] (auto&&... args) {
               VecCheckers<decltype(args)...> funcs{head};
               (funcs.push_back(tail),...);
               for (auto func : funcs) {
                  if (!func(std::forward<decltype(args)>(args)...)) {
                     return false;
                  }
               }
               return true;
            };
         }
   }
	// NAMESPACE NOT
	namespace Not::And {
		// CHECKER
		template<class Head, class... Tail>
			auto Checker(Head head, Tail... tail) {
				return [head, tail...] (auto&&... args) {
					return !(Frodo::And::Checker(head, tail...)
								(std::forward<decltype(args)>(args)...));
				};
			}
	}
	// NAMESPACE NOT
	namespace Not::Or {
		// CHECKER
		template<class Head, class... Tail>
			auto Checker(Head head, Tail... tail) {
				return [head, tail...] (auto&&... args) {
					return !(Frodo::Or::Checker(head, tail...)
								(std::forward<decltype(args)>(args)...));
				};
			}
	}
}
#endif
