#include "PlayMode.hpp"

#include "LitColorTextureProgram.hpp"

#include "DrawLines.hpp"
#include "Mesh.hpp"
#include "Load.hpp"
#include "gl_errors.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <random>

PlayMode::PlayMode() {
	// Set up textblock vector
	{
		// Start Button
		blocks.emplace_back(TextBlock("Pacifico.ttf",
							80,
							{ -0.2f, 0.2f },
							{ 0.4f, 0.2f },
							{ 0.03f, 0.03f },
							{ 0x00, 0x00, 0x00, 0xff },
							{ 0xff, 0xff, 0xff, 0x00 },
							"Start"
		));

		// Customer Name tag

	}

	fsm = FSM();
}

PlayMode::~PlayMode() {
}

bool PlayMode::handle_event(SDL_Event const &evt, glm::uvec2 const &window_size) {
	if (evt.type == SDL_MOUSEMOTION) {
		mouse_pos = glm::vec2(
			evt.motion.x / float(window_size.x) * 2 - 1.0f,
			-evt.motion.y / float(window_size.y) * 2 + 1.0f
		);

		//std::cout << "Mouse motion: x: " << mouse_pos.x << ", y: " << mouse_pos.y << "\n";
		CheckMouseHover();
		return true;
	}

	return false;
}

void PlayMode::CheckMouseHover() {
	for (auto& block : blocks) {
		if (mouse_pos.x > block.anchor.x && mouse_pos.x < block.anchor.x + block.dims.x
			&& mouse_pos.y > block.anchor.y && mouse_pos.y < block.anchor.y + block.dims.y) {
			selected_block_idx = static_cast<int>(&block - &blocks[0]);
			return;
		}
	}

	selected_block_idx = -1;
}

void PlayMode::update(float elapsed) {

}

void PlayMode::draw(glm::uvec2 const &drawable_size) {
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClearDepth(1.0f); //1.0 is actually the default value to clear the depth buffer to, but FYI you can change it.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	for (auto& block : blocks) {
		if (block.visible) {
			if (selected_block_idx > -1 && &block - &blocks[0] == selected_block_idx) {
				shape_texture_program->DrawBox(block.box);
				block.source->DrawText(drawable_size, block.text, block.anchor, block.dims, { 0xff, 0xff, 0xff, 0xff });
			}
			else {
				shape_texture_program->DrawBox(block.box);
				block.source->DrawText(drawable_size, block.text, block.anchor, block.dims, block.font_color);
			}			
		}
	}

	GL_ERRORS();
}
