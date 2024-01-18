#pragma once

#include <cstdint> // for std::uint32_t
#include <bitset>

#define entity std::uint32_t
#define componentType std::uint8_t
#define Signature std::bitset<MAX_COMPONENTS>

const entity MAX_ENTITIES = 5000;
const componentType MAX_COMPONENTS = 32;
const int MAX_PLAYING_KEYS = 5;

const int FPS = 60;
const int frameDelay = 1000 / FPS;
const int SPRINT_SPEED = 5;