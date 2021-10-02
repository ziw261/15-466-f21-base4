#include "FontSource.hpp"
#include <iostream>

#define FONT_SIZE 64


FontSource::FontSource(const std::string font) 
{
	FT_Error ft_error;
	if ((ft_error = FT_Init_FreeType(&ft_library)))
	{
		std::cerr << "FT_Library initialization failed." << std::endl;
		abort();
	}

	if ((ft_error = FT_New_Face(ft_library, font.c_str(), 0, &ft_face)))
	{
		std::cerr << "FT_Face creation failed." << std::endl;
		abort();
	}

	if ((ft_error = FT_Set_Char_Size(ft_face, FONT_SIZE * 64, FONT_SIZE * 64, 0, 0)))
	{
		std::cerr << "FT set size failed." << std::endl;
		abort();
	}

	if ((ft_error = FT_Err_Unknown_File_Format))
	{
		std::cerr << "Font file not supported." << std::endl;
		abort();
	}

	InitializeGlyaphMap();
}

FontSource::~FontSource() {
	ClearText();
	ClearTextureMap();
}

void FontSource::InitializeGlyaphMap() 
{
	for (unsigned char c = 32; c <= 127; c++)
	{
		FT_Error error = FT_Load_Char(ft_face, c, FT_LOAD_RENDER);
		if (error)
		{
			std::cerr << "Failed to load " << c << std::endl;
			continue;
		}

		auto& bit_map = ft_face->glyph->bitmap;

		GLuint texture_id = shape_texture_program->GetTextureId(bit_map);

		glyph_map.insert(std::pair<char, GLuint>(c,texture_id));
	}
}

void FontSource::DrawText(const std::string& text, glm::vec2 anchor, glm::u8vec4 color) 
{
	SetText(text);

	ShapeTextureProgram::Vertex vertexes[]{
			{{0.0f, 0.0f}, color, {0, 0}},
			{{0.0f, 0.0f}, color, {1, 0}},
			{{0.0f, 0.0f}, color, {0, 1}},
			{{0.0f, 0.0f}, color, {1, 1}} };

	shape_texture_program->DrawFont(vertexes, glyph_map[text[0]]);
}

void FontSource::SetText(const std::string& text) 
{
	ClearText();

	hb_font = hb_ft_font_create(ft_face, nullptr);
	hb_buffer = hb_buffer_create();
	hb_buffer_add_utf8(hb_buffer, text.c_str(), -1, 0, -1);

	hb_buffer_set_direction(hb_buffer, HB_DIRECTION_LTR);
	hb_buffer_set_script(hb_buffer, HB_SCRIPT_LATIN);
	hb_buffer_set_language(hb_buffer, hb_language_from_string("en", -1));
	hb_shape(hb_font, hb_buffer, nullptr, 0);
	glyph_info = hb_buffer_get_glyph_infos(hb_buffer, nullptr);
	glyph_pos = hb_buffer_get_glyph_positions(hb_buffer, nullptr);
}

void FontSource::ClearText() 
{
	if (hb_buffer)
	{
		hb_buffer_destroy(hb_buffer);
		hb_buffer = nullptr;
	}

	if (hb_font)
	{
		hb_font_destroy(hb_font);
		hb_font = nullptr;
	}
}

void FontSource::ClearTextureMap()
{
	for (auto& pair : glyph_map)
	{
		shape_texture_program->DeleteTextureId(pair.second);
	}
}