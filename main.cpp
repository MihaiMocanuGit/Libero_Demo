#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
// Keep SDL imports at the beginning.
#include "Libero/ECS/Components.hpp"
#include "Libero/ECS/Entity.hpp"
#include "Libero/ECS/Lookup.hpp"
#include "Libero/Utilities/Vec.hpp"
#include "src/UnitFactory.hpp"

struct AppState
{
    lbr::ecs::Lookup<cmps::ETypes> ecsLookup;
    lbr::hsdl::SmartSDL_Renderer renderer {};
    lbr::hsdl::SmartSDL_Window window {};
    uint16_t desiredFrameRate {90};
    const bool *keyState;
    uint64_t prevTick {0};
};

SDL_AppResult SDL_AppInit(void **appstate, [[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    using namespace lbr;
    using namespace cmps;
    constexpr unsigned ENTITY_CAP {1'000};
    constexpr unsigned COMPONENT_CAP {100};
    constexpr unsigned WINDOW_W {1280};
    constexpr unsigned WINDOW_H {720};

    static AppState state {.ecsLookup = ecs::Lookup<ETypes> {ENTITY_CAP, COMPONENT_CAP},
                           .keyState = SDL_GetKeyboardState(nullptr)};
    *appstate = &state;

    SDL_SetAppMetadata("Libero", "0.0.0", "com.libero.demo");

    if (not SDL_Init(SDL_INIT_VIDEO))
    {
        // SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    if (not SDL_CreateWindowAndRenderer("Libero Demo", WINDOW_W, WINDOW_H, SDL_WINDOW_RESIZABLE,
                                        &state.window.res, &state.renderer.res))
    {
        // SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    if (not SDL_SetRenderLogicalPresentation(state.renderer.res, WINDOW_W, WINDOW_H,
                                             SDL_LOGICAL_PRESENTATION_LETTERBOX))
    {
        // SDL_Log("Couldn't set render logical presentation: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    UnitFactory fct {state.ecsLookup, state.renderer};
    auto knight {fct.constructKnight({0, 0}, 0)};
    if (not knight.has_value())
    {
        SDL_Log("Couldn't initialize the player: %s", knight.error().msg.data());
        return SDL_APP_FAILURE;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    using namespace lbr;
    [[maybe_unused]] AppState &state = *reinterpret_cast<AppState *>(appstate);
    if (event->type == SDL_EVENT_QUIT)
    {
        // SDL_Log("Bye");
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    uint64_t startMs {SDL_GetTicks()};
    using namespace lbr;
    using namespace cmps;
    [[maybe_unused]] AppState &state = *reinterpret_cast<AppState *>(appstate);
    utl::Rect<float, 2> seenWorldRegion {.ur = utl::Vec2f {256, 256},
                                         .ll = utl::Vec2f {-256, -256}};
    utl::Vec2<int> windowSize;
    SDL_GetRenderLogicalPresentation(state.renderer.res, &windowSize[0], &windowSize[1], nullptr);

    SDL_SetRenderDrawColor(state.renderer.res, 127, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(state.renderer.res);

    state.ecsLookup.readGroupOfComponents<false, Transform, Draw>(
        [&](ecs::Entity, const Transform &tr, const Draw &dr)
        {
            utl::Vec2f posOnScreen = {(tr.pos[0] - seenWorldRegion.ll[0]) * windowSize[0] /
                                          (seenWorldRegion.ur[0] - seenWorldRegion.ll[0]),
                                      (tr.pos[1] - seenWorldRegion.ll[1]) * windowSize[1] /
                                          (seenWorldRegion.ur[1] - seenWorldRegion.ll[1])};
            utl::Vec2<int> sizeOnScreen = {dr.texture.res->w, dr.texture.res->w};
            // SDL_Log("%s", std::format("World Space: x = {}, y = {}", tr.pos[0],
            // tr.pos[1]).c_str());
            SDL_FRect dstRect {.x = posOnScreen[0],
                               .y = posOnScreen[1],
                               .w = static_cast<float>(sizeOnScreen[0]),
                               .h = static_cast<float>(sizeOnScreen[1])};
            SDL_RenderTexture(state.renderer.res, dr.texture.res, nullptr, &dstRect);
        });
    SDL_RenderPresent(state.renderer.res);
    uint64_t endMs {SDL_GetTicks()};
    state.prevTick = endMs;
    uint64_t elapsed {endMs - startMs};
    uint64_t desiredFrameTime = 1000 / state.desiredFrameRate;
    if (desiredFrameTime > elapsed)
    {
        uint64_t sleepFor = desiredFrameTime - elapsed;
        SDL_Delay(sleepFor);
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, [[maybe_unused]] SDL_AppResult result)
{
    [[maybe_unused]] AppState &state = *reinterpret_cast<AppState *>(appstate);
};
