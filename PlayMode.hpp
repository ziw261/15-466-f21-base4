#include "Mode.hpp"

#include "Scene.hpp"
#include "Sound.hpp"
#include "FontSource.hpp"
#include "data_path.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <deque>

struct PlayMode : Mode {
	PlayMode();
	virtual ~PlayMode();

	//functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	//----- game state -----
	struct TextBlock
	{
		bool visible = true;
		glm::vec2 anchor;
		glm::vec2 dims;
		std::string text;
		glm::u8vec4 font_color;
		std::shared_ptr<FontSource> source;
		ShapeTextureProgram::BoxDrawable box;
		glm::u8vec4 box_color;

		TextBlock() = default;
		TextBlock(std::string font_name_,
			unsigned int size,
			glm::vec2 anchor_,
			glm::vec2 dims_,
			glm::u8vec4 font_color_,
			glm::u8vec4 box_color_,
			std::string text_) :
			anchor(anchor_),
			dims(dims_),
			font_color(font_color_),
			box_color(box_color_),
			text(text_)
		{
			source = std::make_shared<FontSource>(data_path(font_name_), size);
			assert(source != nullptr);
			shape_texture_program->SetBox(box, glm::vec4(
				anchor.x,
				anchor.y + dims.y,
				anchor.x + dims.x,
				anchor.y
			), box_color);
		}
	};

	TextBlock block;

	//input tracking:
	struct Button {
		uint8_t downs = 0;
		uint8_t pressed = 0;
	} left, right, down, up;

	//local copy of the game scene (so code can change it during gameplay):
	Scene scene;

	//hexapod leg to wobble:
	Scene::Transform *hip = nullptr;
	Scene::Transform *upper_leg = nullptr;
	Scene::Transform *lower_leg = nullptr;
	glm::quat hip_base_rotation;
	glm::quat upper_leg_base_rotation;
	glm::quat lower_leg_base_rotation;
	float wobble = 0.0f;

	glm::vec3 get_leg_tip_position();

	//music coming from the tip of the leg (as a demonstration):
	std::shared_ptr< Sound::PlayingSample > leg_tip_loop;
	
	//camera:
	Scene::Camera *camera = nullptr;

};
