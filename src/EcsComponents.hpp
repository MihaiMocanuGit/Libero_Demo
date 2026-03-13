#include "Libero/ECS/Components.hpp"
#include "Libero/HelpersSDL/SmartSDL.hpp"
#include "Libero/Utilities/Vec.hpp"

#include <string>
namespace cmps
{
enum class ETypes : lbr::ecs::SizeEType
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
static_assert(lbr::ecs::EMetaType<ETypes>, "ETypes is not an EMetaType");

struct Transform
{
    lbr::utl::Vec3f pos;
    // uint8_t padding1;
    lbr::utl::Vec3f rot;
    // uint8_t padding2;
    lbr::utl::Vec3f size;
    // uint8_t padding2;
};

struct Boundary
{
    enum class Type
    {
        BOX,              // lengths equal to size
        CYLINDRICAL,      // r=max(x1,x2), h=x3
        ELIPTIC_CYLINDER, // a=x1, b=x2, h=x3
    } type;
    lbr::utl::Vec3f size;
};

struct Controllable
{
    bool userControlled;
    lbr::utl::Vec3f stepSize;
};

struct Drawable
{
    lbr::hsdl::SmartSDL_Texture texture;
    lbr::utl::Vec2f posOnScreen;
    lbr::utl::Vec2<int> sizeOnScreen;
    bool isVisible;
};

struct Descriptive
{
    std::string name;
    std::string description;
};
} // namespace cmps

// Appending into the namespace is important
namespace lbr::ecs
{

template <>
struct EType2CType<cmps::ETypes, cmps::ETypes::Transform>
{
    using CType = cmps::Transform;
};

template <>
struct CType2EType<cmps::ETypes, cmps::Transform>
{
    static constexpr cmps::ETypes EType = cmps::ETypes::Transform;
};
static_assert(CType<cmps::Transform, cmps::ETypes>, "Transform is not a CType");

template <>
struct EType2CType<cmps::ETypes, cmps::ETypes::Boundary>
{
    using CType = cmps::Boundary;
};
template <>
struct CType2EType<cmps::ETypes, cmps::Boundary>
{
    static constexpr cmps::ETypes EType = cmps::ETypes::Boundary;
};
static_assert(CType<cmps::Boundary, cmps::ETypes>, "Boundary is not a CType");

template <>
struct EType2CType<cmps::ETypes, cmps::ETypes::Controllable>
{
    using CType = cmps::Controllable;
};
template <>
struct CType2EType<cmps::ETypes, cmps::Controllable>
{
    static constexpr cmps::ETypes EType = cmps::ETypes::Controllable;
};
static_assert(CType<cmps::Controllable, cmps::ETypes>, "Boundary is not a CType");

template <>
struct EType2CType<cmps::ETypes, cmps::ETypes::Drawable>
{
    using CType = cmps::Drawable;
};
template <>
struct CType2EType<cmps::ETypes, cmps::Drawable>
{
    static constexpr cmps::ETypes EType = cmps::ETypes::Drawable;
};
static_assert(CType<cmps::Drawable, cmps::ETypes>, "Drawable is not a CType");

template <>
struct EType2CType<cmps::ETypes, cmps::ETypes::Descriptive>
{
    using CType = cmps::Descriptive;
};
template <>
struct CType2EType<cmps::ETypes, cmps::Descriptive>
{
    static constexpr cmps::ETypes EType = cmps::ETypes::Descriptive;
};
static_assert(CType<cmps::Descriptive, cmps::ETypes>, "Descriptive is not a CType");
} // namespace lbr::ecs
