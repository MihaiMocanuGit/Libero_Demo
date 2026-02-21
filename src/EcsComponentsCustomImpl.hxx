// Ignore the errors, as this file will be injected at  the end of Libero/ECS/Components.hpp, this
// will actually compile just fine

// Not actually needed, but it reduces the number of false positive LSP errors.
enum class EnumTypes;
template <EnumTypes ComponentE>
struct Id2Type;

struct Drawable
{
    static constexpr EnumTypes id {EnumTypes::Controlable};
};
template <>
struct Id2Type<EnumTypes::Drawable>
{
    using Type = Drawable;
};

struct FrameUpdatable
{
    static constexpr EnumTypes id {EnumTypes::FrameUpdatable};
};
template <>
struct Id2Type<EnumTypes::FrameUpdatable>
{
    using Type = FrameUpdatable;
};
