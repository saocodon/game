#pragma once

#include <cstdint> // for std::uint32_t
#include <bitset>

#define entity std::uint32_t
#define componentType std::uint8_t

const entity MAX_ENTITIES = 5000;
const componentType MAX_COMPONENTS = 32;

const int FPS = 60;
const int frameDelay = 1000 / FPS;

const int KEY_STATES = 4;
enum {
	MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN

	//4
};

#define Signature std::bitset<MAX_COMPONENTS>