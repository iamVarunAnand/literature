#ifndef LITERATURE_INCLUDE_RENDERER_HPP_
#define LITERATURE_INCLUDE_RENDERER_HPP_

#include <include/dtypes.hpp>
#include <unordered_map>
#include <string>

class Renderer {
    public: static const std::unordered_map<Suit, std::string> kSuitToString;
    public: static const std::unordered_map<Value, std::string> kValueToString;
};

#endif