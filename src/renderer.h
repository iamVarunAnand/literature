#ifndef LITERATURE_RENDERER_H
#define LITERATURE_RENDERER_H

#include "dtypes.h"
#include <unordered_map>
#include <string>

class Renderer {
    public: static const std::unordered_map<Suit, std::string> kSuitToString;
    public: static const std::unordered_map<Value, std::string> kValueToString;
};

#endif