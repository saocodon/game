#pragma once

#include <cstdint> // for std::uint32_t

#define entity std::uint32_t
#define properties std::uint32_t // use a bitmask to represent if an object has i-th property
#define componentType std::uint8_t

const entity MAX_ENTITIES = 5000;
const componentType MAX_COMPONENTS = 32;