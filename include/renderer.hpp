#ifndef LITERATURE_INCLUDE_RENDERER_HPP_
#define LITERATURE_INCLUDE_RENDERER_HPP_

#include <string>
#include <unordered_map>

#include "../include/dtypes.hpp"

class Renderer {
   public:
    static const std::unordered_map<Suit, std::string> kSuitToString;
    static const std::unordered_map<Value, std::string> kValueToString;
};

#endif