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
	void SetText(const std::string& text);
	void ClearText();
	void ClearTextureMap();

public:
	FontSource() = delete;
	~FontSource();
	FontSource(const std::string font);
	void DrawText(const std::string& text, glm::vec2 anchor, glm::u8vec4 color);
};