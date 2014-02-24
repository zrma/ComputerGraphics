#pragma once

enum KeyStatus
{
	KEY_STATUS_NONE,

	KEY_STATUS_DOWN,
	KEY_STATUS_PRESSED,
	KEY_STATUS_UP,
	KEY_STATUS_NOT_PRESSED,

	KEY_STATUS_MAX
};

enum TransType
{
	TRANSE_TYPE_NONE,

	TRANSE_TYPE_TRANSLATE_X,
	TRANSE_TYPE_TRANSLATE_Y,
	TRANSE_TYPE_TRANSLATE_Z,

	TRANSE_TYPE_ROTATE_X,
	TRANSE_TYPE_ROTATE_Y,
	TRANSE_TYPE_ROTATE_Z,

	TRANSE_TYPE_MAX
};

enum PlanetType
{
	PLANET_TYPE_NONE,

	PLANET_TYPE_UNIVERSE,
	PLANET_TYPE_SUN,
	PLANET_TYPE_MERCURY,
	PLANET_TYPE_VENUS,
	PLANET_TYPE_EARTH,
	PLANET_TYPE_MOON,
	PLANET_TYPE_MARS,

	PLANET_TYPE_MAX
};