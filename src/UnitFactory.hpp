#pragma once

#include "EcsDefs/EcsComponents.hpp"
#include "Libero/ECS/Entity.hpp"
#include "Libero/ECS/Lookup.hpp"
#include "Libero/HelpersSDL/Utils.hpp"

#include <cstdint>
#include <expected>
#include <filesystem>
#include <string_view>

class UnitFactory
{
    lbr::ecs::Lookup<cmps::ETypes> &m_ecsLookup;
    lbr::hsdl::SmartSDL_Renderer &m_renderer;
    static std::filesystem::path m_knightTexturePath;

  public:
    UnitFactory(lbr::ecs::Lookup<cmps::ETypes> &ecsLookup,
                lbr::hsdl::SmartSDL_Renderer &renderer) noexcept
        : m_ecsLookup {ecsLookup}, m_renderer {renderer}
    {
    }

    struct Error
    {
        enum class Type
        {
            TextureNotFound,
            UnexpectedError,
            NotImplemented,
        } type;
        std::string_view msg;
    };

    using Return_t = std::expected<lbr::ecs::Entity::eid, Error>;

    Return_t constructKnight(const lbr::utl::Vec2f &position, uint32_t teamId) noexcept
    {
        using namespace lbr;
        using namespace lbr::ecs;
        using namespace cmps;

        auto texture {hsdl::loadTexture(m_renderer, m_knightTexturePath)};
        if (not texture.has_value())
            return std::unexpected(
                Error {.type = Error::Type::TextureNotFound, .msg = texture.error()});

        utl::Vec3f size = {0.5, 0.25, 1.8};

        Entity ent {m_ecsLookup.createEntity<true>()};
        m_ecsLookup.assignComponents<true>(
            ent.id, Transform {.pos = position, .rotation = 0, .size = size},
            Boundary {.size = size, .type = Boundary::Type::CYLINDRICAL},
            Move {.queuedMove = {},
                  .slowStepSize = 1.0,
                  .slowStaminaCost = 0.75,
                  .fastStepSize = 2.0,
                  .fastStaminaCost = 2.5},
            Health {.health = 100, .healthCap = 100},
            Stamina {.stamina = 100, .staminaCap = 100, .staminaRegen = 5},
            DamageResistance {.armor = 100, .armorCap = 100, .baseResistance = 1.1},
            Team {.id = teamId},
            Attacks {.abilities = {Attacks::AttackAbility {
                         .directDamage = 25,
                         .areaDamage = 0,
                         .directRange = 2,
                         .areaRadius = 0,
                         .speed = 1,
                         .cooldown = 1,
                         .stopOnFirstHit = true,
                         .staminaCost = 25,
                         .castType = Attacks::AttackAbility::CastType::CIRCULAR_SWEEP}}},
            Select {.selected = false}, Formation {.id = -1u, .index = -1u},
            Draw {
                .texture = std::move(texture.value()), .globalScale = 1.0, .scaleToDistance = true},
            Description {.name = "Sir Bartolomew the Knight",
                         .description = "No mightier lord on this earth than him"});
        return ent.id;
    }
};
