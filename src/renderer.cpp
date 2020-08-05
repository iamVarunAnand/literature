#include <include/renderer.hpp>
#include <include/dtypes.hpp>
#include <unordered_map>
#include <string>

const std::unordered_map<Suit, std::string> Renderer::kSuitToString(
    {
        {kSuitDefault, "X"},
        {kHearts, "\u2665"},
        {kSpades, "\u2660"},
        {kDiamonds, "\u2666"},
        {kClubs, "\u2663"}
    }
);

const std::unordered_map<Value, std::string> Renderer::kValueToString(
    {
        {kValueDefault, "X"},
        {kTwo, "2"},
        {kThree, "3"},
        {kFour, "4"},
        {kFive, "5"},
        {kSix, "6"},
        {kSeven, "7"},
        {kNine, "9"},
        {kTen, "10"},
        {kJack, "J"},
        {kQueen, "Q"},
        {kKing, "K"},
        {kAce, "A"},
    }
);