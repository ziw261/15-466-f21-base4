#pragma once

#include "GL.hpp"
#include "Load.hpp"
#include "Scene.hpp"

struct ShapeTextureProgram
{
	ShapeTextureProgram();
	~ShapeTextureProgram();

	GLuint program = 0;

	GLuint Position_vec4 = -1U;
	GLuint Color_vec4 = -1U;
	GLuint TexCoord_vec2 = -1U;

	struct Vertex
	{
		glm::vec2 Position;
		glm::u8vec4 Color;
		glm::vec2 TexCoord;
	};

	struct BoxDrawable
	{
		GLuint vertex_array{ 0 };
		GLuint vertex_buffer{ 0 };

		void Clear();
	};

	struct FontDrawable
	{
		GLuint vertex_array{ 0 };
		GLuint vertex_buffer{ 0 };
		GLuint texture_id{ 0 };

		void Clear();
	};

	static_assert(sizeof(Vertex) == 2 * 4 + 4 * 1 + 2 * 4);

	GLuint GetVao(GLuint vertex_buffer) const;
	void SetBox(BoxDrawable& drawable, const glm::vec4& box, const glm::u8vec4 color) const;
	void DrawBox(const BoxDrawable& drawable) const;
	void SetFont(FontDrawable& drawable);
	void DrawFont(FontDrawable& drawable) const;
};

extern Load < ShapeTextureProgram > shape_texture_program;