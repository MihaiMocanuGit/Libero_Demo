#include <print>
#include "Libero/ECS/Lookup.hpp"

int main(){
    lbr::ecs::lookup::Lookup lk;
    lk.createEntity<true>();
    std::print("Hi there!");
    return 0;
}
