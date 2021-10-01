#include "ShapeTextureProgram.hpp"

#include "gl_compile_program.hpp"
#include "gl_errors.hpp"


#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] ( " << error << " ) : " << function << " " << file << ": " << line << std::endl;
		return false;
	}
	return true;
}

Load< ShapeTextureProgram > shape_texture_program(LoadTagEarly);

static uint8_t default_index_buffer_content[]{0, 1, 2, 1, 2, 3};
static GLuint default_index_buffer{ 0 };
static GLuint default_texture{ 0 };

static Load<void> load_default_index_buffer(LoadTagEarly, []() {
	GLCall(glGenBuffers(1, &default_index_buffer));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, default_index_buffer));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint8_t), default_index_buffer_content, GL_STATIC_DRAW));
});

static Load<void> load_default_texture(LoadTagEarly, []() {
	GLCall(glGenTextures(1, &default_texture));
	GLCall(glBindTexture(GL_TEXTURE_2D, default_texture));
	std::vector< glm::u8vec4 > tex_data(1, glm::u8vec4(0xff));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_data.data()));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
});

ShapeTextureProgram::ShapeTextureProgram() 
{
	GLCall(program = gl_compile_program(
		//vertex shader:
		"#version 330\n"
		"in vec4 Position;\n"
		"in vec4 Color;\n"
		"in vec2 TexCoord;\n"
		"out vec4 color;\n"
		"out vec2 texCoord;\n"
		"void main() {\n"
		"	gl_Position = Position;\n"
		"	color = Color;\n"
		"	texCoord = TexCoord;\n"
		"}\n"
		,
		//fragment shader:
		"#version 330\n"
		"uniform sampler2D TEX;\n"
		"in vec4 color;\n"
		"in vec2 texCoord;\n"
		"out vec4 fragColor;\n"
		"void main() {\n"
		"	fragColor = texture(TEX, texCoord) * color;\n"
		"}\n"
	));

	GLCall(Position_vec4 = glGetAttribLocation(program, "Position"));
	GLCall(Color_vec4 = glGetAttribLocation(program, "Color"));
	GLCall(TexCoord_vec2 = glGetAttribLocation(program, "TexCoord"));

	GLCall(GLuint TEX_sampler2D = glGetUniformLocation(program, "TEX"));

	GLCall(glUseProgram(program));

	GLCall(glUniform1i(TEX_sampler2D, 0));

	GLCall(glUseProgram(0));
}

GLuint ShapeTextureProgram::GetVao(GLuint vertex_buffer) const 
{
	GLuint vao;
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer));

	GLCall(glEnableVertexAttribArray(Position_vec4));
	GLCall(glVertexAttribPointer(Position_vec4, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position)));
	
	GLCall(glEnableVertexAttribArray(Color_vec4));
	GLCall(glVertexAttribPointer(Color_vec4, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (const void*)offsetof(Vertex, Color)));

	GLCall(glEnableVertexAttribArray(TexCoord_vec2));
	GLCall(glVertexAttribPointer(TexCoord_vec2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoord)));

	return vao;
}

ShapeTextureProgram::~ShapeTextureProgram()
{
	GLCall(glDeleteProgram(program));
	program = 0;
}
