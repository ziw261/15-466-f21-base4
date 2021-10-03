#pragma once

#include "ShapeTextureProgram.hpp"


#include <hb.h>
#include <hb-ft.h>
#include <map>


class FontSource
{
private:
	// A map that stores the texture_id for each char
	std::map<char, GLuint> glyph_map;

	// FreeType variables
	FT_Face ft_face;
	FT_Library ft_library;

	// Harfbuzz variables
	hb_font_t* hb_font = nullptr;
	hb_buffer_t* hb_buffer = nullptr;
	hb_glyph_info_t* glyph_info = nullptr;
	hb_glyph_position_t* glyph_pos = nullptr;

	void InitializeGlyaphMap();
	void ClearText();
	void ClearTextureMap();

	std::string displayedText;

	inline float AnchorToScreen(float pos, int size) {
		return (pos + 1) * size / 2.0f;
	}

	inline float ScreenToAnchor(float pos, int size) {
		return (2 * pos) / size - 1;
	}

public:
	FontSource() = delete;
	~FontSource();
	FontSource(const std::string font);
	void SetText(const std::string& text);
	void DrawText(const glm::uvec2& drawable_size, const std::string& text, glm::vec2 anchor, glm::u8vec4 color);
};