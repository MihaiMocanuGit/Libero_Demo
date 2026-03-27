#pragma once

// Recommended usage: 
// In the c++ header file in which you define your components, include the generated header at the
// end of the file, outside any namespaces.
// Example:
// namespace cmps  {
// struct Component1  {
//     float field;
// };
// } // end namespace cmps
//
// #include "generated.hxx"

// Not necessary to compile, but is needed to stop false positive LSP errors.
#include "EcsComponents.hpp"
#include "Libero/ECS/Components.hpp"

namespace cmps
{
enum class ETypes : lbr::ecs::SizeEType
{
    Transform = 0,
    Move = 1,
    Health = 2,
    Stamina = 3,
    DamageResistance = 4,
    Team = 5,
    Attacks = 6,
    Select = 7,
    Formation = 8,
    Boundary = 9,
    Draw = 10,
    Description = 11,
    countEType, // Important to be last
};
static_assert(lbr::ecs::EMetaType<ETypes>, "ETypes is not an EMetaType");
} // namespace cmps

// Appending into the namespace is important
namespace lbr::ecs
{

////////////////////////////////////////////////////////////////////////////////////////////////////
// TRANSFORM = 0
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

////////////////////////////////////////////////////////////////////////////////////////////////////
// MOVE = 1
template <>
struct EType2CType<cmps::ETypes, cmps::ETypes::Move>
{
    using CType = cmps::Move;
};
template <>
struct CType2EType<cmps::ETypes, cmps::Move>
{
    static constexpr cmps::ETypes EType = cmps::ETypes::Move;
};
static_assert(CType<cmps::Move, cmps::ETypes>, "Move is not a CType");

////////////////////////////////////////////////////////////////////////////////////////////////////
// HEALTH = 2
template <>
struct EType2CType<cmps::ETypes, cmps::ETypes::Health>
{
    using CType = cmps::Health;
};
template <>
struct CType2EType<cmps::ETypes, cmps::Health>
{
    static constexpr cmps::ETypes EType = cmps::ETypes::Health;
};
static_assert(CType<cmps::Health, cmps::ETypes>, "Health is not a CType");

////////////////////////////////////////////////////////////////////////////////////////////////////
// STAMINA = 3
template <>
struct EType2CType<cmps::ETypes, cmps::ETypes::Stamina>
{
    using CType = cmps::Stamina;
};
template <>
struct CType2EType<cmps::ETypes, cmps::Stamina>
{
    static constexpr cmps::ETypes EType = cmps::ETypes::Stamina;
};
static_assert(CType<cmps::Stamina, cmps::ETypes>, "Stamina is not a CType");

////////////////////////////////////////////////////////////////////////////////////////////////////
// DAMAGERESISTANCE = 4
template <>
struct EType2CType<cmps::ETypes, cmps::ETypes::DamageResistance>
{
    using CType = cmps::DamageResistance;
};
template <>
struct CType2EType<cmps::ETypes, cmps::DamageResistance>
{
    static constexpr cmps::ETypes EType = cmps::ETypes::DamageResistance;
};
static_assert(CType<cmps::DamageResistance, cmps::ETypes>, "DamageResistance is not a CType");

////////////////////////////////////////////////////////////////////////////////////////////////////
// TEAM = 5
template <>
struct EType2CType<cmps::ETypes, cmps::ETypes::Team>
{
    using CType = cmps::Team;
};
template <>
struct CType2EType<cmps::ETypes, cmps::Team>
{
    static constexpr cmps::ETypes EType = cmps::ETypes::Team;
};
static_assert(CType<cmps::Team, cmps::ETypes>, "Team is not a CType");

////////////////////////////////////////////////////////////////////////////////////////////////////
// ATTACKS = 6
template <>
struct EType2CType<cmps::ETypes, cmps::ETypes::Attacks>
{
    using CType = cmps::Attacks;
};
template <>
struct CType2EType<cmps::ETypes, cmps::Attacks>
{
    static constexpr cmps::ETypes EType = cmps::ETypes::Attacks;
};
static_assert(CType<cmps::Attacks, cmps::ETypes>, "Attacks is not a CType");

////////////////////////////////////////////////////////////////////////////////////////////////////
// SELECT = 7
template <>
struct EType2CType<cmps::ETypes, cmps::ETypes::Select>
{
    using CType = cmps::Select;
};
template <>
struct CType2EType<cmps::ETypes, cmps::Select>
{
    static constexpr cmps::ETypes EType = cmps::ETypes::Select;
};
static_assert(CType<cmps::Select, cmps::ETypes>, "Select is not a CType");

////////////////////////////////////////////////////////////////////////////////////////////////////
// FORMATION = 8
template <>
struct EType2CType<cmps::ETypes, cmps::ETypes::Formation>
{
    using CType = cmps::Formation;
};
template <>
struct CType2EType<cmps::ETypes, cmps::Formation>
{
    static constexpr cmps::ETypes EType = cmps::ETypes::Formation;
};
static_assert(CType<cmps::Formation, cmps::ETypes>, "Formation is not a CType");

////////////////////////////////////////////////////////////////////////////////////////////////////
// BOUNDARY = 9
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

////////////////////////////////////////////////////////////////////////////////////////////////////
// DRAW = 10
template <>
struct EType2CType<cmps::ETypes, cmps::ETypes::Draw>
{
    using CType = cmps::Draw;
};
template <>
struct CType2EType<cmps::ETypes, cmps::Draw>
{
    static constexpr cmps::ETypes EType = cmps::ETypes::Draw;
};
static_assert(CType<cmps::Draw, cmps::ETypes>, "Draw is not a CType");

////////////////////////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION = 11
template <>
struct EType2CType<cmps::ETypes, cmps::ETypes::Description>
{
    using CType = cmps::Description;
};
template <>
struct CType2EType<cmps::ETypes, cmps::Description>
{
    static constexpr cmps::ETypes EType = cmps::ETypes::Description;
};
static_assert(CType<cmps::Description, cmps::ETypes>, "Description is not a CType");

}
