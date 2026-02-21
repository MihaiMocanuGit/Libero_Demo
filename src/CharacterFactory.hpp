#include "Libero/ECS/Lookup.hpp"
#include "Libero/HelpersSDL/Utils.hpp"

#include <expected>
#include <filesystem>

class CharacterFactory
{
    lbr::ecs::lookup::Lookup &m_ecsLookup;
    lbr::hsdl::SmartSDL_Renderer &m_renderer;

  public:
    CharacterFactory(lbr::ecs::lookup::Lookup &ecsLookup,
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

    using Return_t = std::expected<lbr::ecs::entity::eid, Error>;

    Return_t constructPlayer(const lbr::utl::Vec3f &position, std::string name,
                             const std::filesystem::path &texturePath) noexcept
    {
        using namespace lbr;
        using namespace lbr::ecs;

        auto texture {hsdl::loadTexture(m_renderer, texturePath)};
        if (not texture.has_value())
            return std::unexpected(
                Error {.type = Error::Type::TextureNotFound, .msg = texture.error()});

        components::Transform tr {.pos = position, .rot = {0}, .size = {0.3f, 0.2f, 1.8f}};
        components::Boundary bd {.type = components::Boundary::Type::CYLINDRICAL, .size = tr.size};
        // This needs to be manually set later
        components::Drawable dw {.texture = std::move(texture.value()),
                                 .posOnScreen = {(uint16_t)-1, (uint16_t)-1},
                                 .sizeOnScreen = {(uint16_t)-1, (uint16_t)-1},
                                 .isVisible = false};
        components::Descriptive ds {.name = name,
                                    .description = "This is you, for better or worse."};
        components::Controlable ct {.userControlled = true, .stepSize = {0.6f, 0.6f, 0.5f}};

        entity::Entity ent {m_ecsLookup.createEntity<true>()};
        m_ecsLookup.assignMultipleComponents<true>(ent.id, std::move(tr), std::move(bd),
                                                   std::move(dw), std::move(ds), std::move(ct));
        return ent.id;
    }
};
