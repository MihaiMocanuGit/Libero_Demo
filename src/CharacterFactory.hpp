#include "EcsComponents.hpp"
#include "Libero/ECS/Lookup.hpp"
#include "Libero/HelpersSDL/Utils.hpp"

#include <expected>
#include <filesystem>

class CharacterFactory
{
    lbr::ecs::Lookup<cmps::ETypes> &m_ecsLookup;
    lbr::hsdl::SmartSDL_Renderer &m_renderer;

  public:
    CharacterFactory(lbr::ecs::Lookup<cmps::ETypes> &ecsLookup,
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
        } type;
        std::string_view msg;
    };

    using Return_t = std::expected<lbr::ecs::Entity::eid, Error>;

    Return_t constructPlayer(const lbr::utl::Vec3f &position, std::string name,
                             const std::filesystem::path &texturePath) noexcept
    {
        using namespace lbr;
        using namespace lbr::ecs;
        using namespace cmps;

        auto texture {hsdl::loadTexture(m_renderer, texturePath)};
        if (not texture.has_value())
            return std::unexpected(
                Error {.type = Error::Type::TextureNotFound, .msg = texture.error()});

        Transform tr {.pos = position, .rot = {0}, .size = {0.3f, 0.2f, 1.8f}};
        Boundary bd {.type = Boundary::Type::CYLINDRICAL, .size = tr.size};
        // This needs to be manually set later
        Drawable dw {.texture = std::move(texture.value()),
                     .posOnScreen = {(uint16_t)-1, (uint16_t)-1},
                     .sizeOnScreen = {(uint16_t)-1, (uint16_t)-1},
                     .isVisible = false};
        Descriptive ds {.name = name, .description = "This is you, for better or worse."};
        Controllable ct {.userControlled = true, .stepSize = {0.3f, 0.3f, 0.2f}};

        Entity ent {m_ecsLookup.createEntity<true>()};
        m_ecsLookup.assignComponents<true>(ent.id, std::move(tr), std::move(bd), std::move(dw),
                                           std::move(ds), std::move(ct));
        return ent.id;
    }
};
