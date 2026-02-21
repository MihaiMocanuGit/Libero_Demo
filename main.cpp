#include "src/Test.hpp"

#include <print>

int main()
{
    lbr::ecs::lookup::Lookup lk;
    lk.createEntity<true>();
    std::print("Hi there!\n");
    return 0;
}
