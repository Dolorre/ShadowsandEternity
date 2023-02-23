#pragma once

/**** FX data header generated by fxdata-build.py tool version 1.14 ****/

using uint24_t = __uint24;

// Initialize FX hardware using  FX::begin(FX_DATA_PAGE); in the setup() function.

constexpr uint16_t FX_DATA_PAGE  = 0xffeb;
constexpr uint24_t FX_DATA_BYTES = 5234;

constexpr uint24_t dolorreLogo = 0x000000;
constexpr uint16_t dolorreLogoWidth  = 128;
constexpr uint16_t dolorreLogoHeight = 64;

constexpr uint24_t saeTitle = 0x000404;
constexpr uint16_t saeTitleWidth  = 128;
constexpr uint16_t saeTitleHeight = 64;

constexpr uint24_t selectionLine = 0x000808;
constexpr uint16_t selectionLineWidth  = 14;
constexpr uint16_t selectionLineHeight = 2;

constexpr uint24_t helpText = 0x000828;
constexpr uint16_t helpTextWidth  = 128;
constexpr uint16_t helpTextHeight = 64;

constexpr uint24_t creditsText = 0x000C2C;
constexpr uint16_t creditsTextWidth  = 128;
constexpr uint16_t creditsTextHeight = 64;

constexpr uint24_t theEnd = 0x001030;
constexpr uint16_t theEndWidth  = 128;
constexpr uint16_t theEndHeight = 64;

constexpr uint24_t gti = 0x001434;
