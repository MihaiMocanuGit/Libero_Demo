#include "Libero/ECS/Components.hpp"
#include "Libero/HelpersSDL/SmartSDL.hpp"
#include "Libero/Utilities/Vec.hpp"

#include <string>
// Appending into the namespace is important
namespace lbr::ecs::components
{
enum class ETypes : SizeEType
{
    Transform = 0, // The first field must start at 0. An enum with only countEType = 0 is also
                   // valid, albeit untested.
    Boundary,
    Controllable,
    Drawable,
    Descriptive,
    countEType, // Important to be just before void
    voidEType,  // Other values can be defined after countEType, but the ECS module won't know about
                // them.

};
static_assert(EMetaType<ETypes>, "ETypes is not an EMetaType");

struct Transform
{
    utl::Vec3f pos;
    // uint8_t padding1;
    utl::Vec3f rot;
    // uint8_t padding2;
    utl::Vec3f size;
    // uint8_t padding2;
};
template <>
struct EType2CType<ETypes, ETypes::Transform>
{
    using CType = Transform;
};
template <>
struct CType2EType<ETypes, Transform>
{
    static constexpr ETypes EType = ETypes::Transform;
};
static_assert(CType<Transform, ETypes>, "Transform is not a CType");

struct Boundary
{
    enum class Type
    {
        BOX,              // lengths equal to size
        CYLINDRICAL,      // r=max(x1,x2), h=x3
        ELIPTIC_CYLINDER, // a=x1, b=x2, h=x3
    } type;
    utl::Vec3f size;
};
template <>
struct EType2CType<ETypes, ETypes::Boundary>
{
    using CType = Boundary;
};
template <>
struct CType2EType<ETypes, Boundary>
{
    static constexpr ETypes EType = ETypes::Boundary;
};
static_assert(CType<Boundary, ETypes>, "Boundary is not a CType");

struct Controllable
{
    bool userControlled;
    utl::Vec3f stepSize;
};
template <>
struct EType2CType<ETypes, ETypes::Controllable>
{
    using CType = Controllable;
};
template <>
struct CType2EType<ETypes, Controllable>
{
    static constexpr ETypes EType = ETypes::Controllable;
};
static_assert(CType<Controllable, ETypes>, "Boundary is not a CType");

struct Drawable
{
    lbr::hsdl::SmartSDL_Texture texture;
    utl::Vec2f posOnScreen;
    utl::Vec2<int> sizeOnScreen;
    bool isVisible;
};
template <>
struct EType2CType<ETypes, ETypes::Drawable>
{
    using CType = Drawable;
};
template <>
struct CType2EType<ETypes, Drawable>
{
    static constexpr ETypes EType = ETypes::Drawable;
};
static_assert(CType<Drawable, ETypes>, "Drawable is not a CType");

struct Descriptive
{
    std::string name;
    std::string description;
};
template <>
struct EType2CType<ETypes, ETypes::Descriptive>
{
    using CType = Descriptive;
};
template <>
struct CType2EType<ETypes, Descriptive>
{
    static constexpr ETypes EType = ETypes::Descriptive;
};
static_assert(CType<Descriptive, ETypes>, "Descriptive is not a CType");
} // namespace lbr::ecs::components
