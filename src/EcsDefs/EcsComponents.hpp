#pragma once

#include "Libero/HelpersSDL/SmartSDL.hpp"
#include "Libero/Utilities/Vec.hpp"

#include <string>
#include <vector>
namespace cmps
{
struct Transform
{
    lbr::utl::Vec2f pos;
    float rotation;
    lbr::utl::Vec3f size;
    // float padding;
};

struct Move
{
    lbr::utl::Vec2f queuedMove;
    float slowStepSize;
    float slowStaminaCost;
    float fastStepSize;
    float fastStaminaCost;
};

struct Health
{
    float health;
    float healthCap;
};

struct Stamina
{
    float stamina;
    float staminaCap;
    float staminaRegen;
};

struct DamageResistance
{
    float armor;
    float armorCap;
    float baseResistance;
};

struct Team
{
    uint32_t id;
};

struct Attacks
{
    struct AttackAbility
    {
        float directDamage;
        float areaDamage;
        float directRange;
        float areaRadius;
        float speed;
        float cooldown;
        bool stopOnFirstHit;
        float staminaCost;
        enum class CastType
        {
            RAY_PROJECTILE,    // pistol buller
            ARCHED_PROJECTILE, // bow arrow, catapult stone
            RAY_SWEEP,         // spear
            CIRCULAR_SWEEP,    // sword
        } castType;
    };

    std::vector<AttackAbility> abilities;
};

struct Select
{
    bool selected;
};

struct Formation
{
    uint32_t id;
    uint32_t index;
};

struct Boundary
{
    lbr::utl::Vec3f size;
    enum class Type
    {
        BOX,              // lengths equal to size
        CYLINDRICAL,      // r=max(x1,x2), h=x3
        ELIPTIC_CYLINDER, // a=x1, b=x2, h=x3
    } type;
};

struct Draw
{
    lbr::hsdl::SmartSDL_Texture texture;
    float globalScale;    // zoom-in/out or ui global scale
    bool scaleToDistance; // ui shouldn't scale with camera distance, but troops should.
};

struct Description
{
    // Only holds views into a string that's owned by another class/system.
    // Reasoning: there's no reason to repeat unit names/descriptions, when there can be only one
    // string that's referenced by all units.
    std::string_view name;
    std::string_view description;
};

} // namespace cmps

#include "EcsBoilerplate.hxx"
