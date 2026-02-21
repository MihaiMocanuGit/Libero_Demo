// This file will be injected at the end of Libero/ECS/Components.hpp.

// Trick to have better LSP completion. Do ignore recursive false-positive error.
#include "Libero/HelpersSDL/SmartSDL.hpp"

#include <string>
// Appending into the namespace is important
namespace lbr::ecs::components
{

struct Drawable
{
    static constexpr EnumTypes id {EnumTypes::Drawable};
    lbr::hsdl::SmartSDL_Texture texture;
    utl::Vec2<uint16_t> posOnScreen;
    utl::Vec2<uint16_t> sizeOnScreen;
    bool isVisible;
};
template <>
struct Id2Type<EnumTypes::Drawable>
{
    using Type = Drawable;
};

struct Descriptive
{
    static constexpr EnumTypes id {EnumTypes::Descriptive};
    std::string name;
    std::string description;
};
template <>
struct Id2Type<EnumTypes::Descriptive>
{
    using Type = Descriptive;
};
} // namespace lbr::ecs::components
