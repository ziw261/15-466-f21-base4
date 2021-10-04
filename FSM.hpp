#include <vector>
#include <deque>
#include "FontSource.hpp"
#include "data_path.hpp"

#include <glm/glm.hpp>

struct TextBlock
{
    bool visible = true;
    glm::vec2 anchor;
    glm::vec2 dims;
    glm::vec2 margins;
    glm::u8vec4 font_color;
    glm::u8vec4 box_color;
    std::string text;
    std::shared_ptr<FontSource> source;
    ShapeTextureProgram::BoxDrawable box;

    TextBlock() = default;
    TextBlock(std::string font_name_,
        unsigned int size,
        glm::vec2 anchor_,
        glm::vec2 dims_,
        glm::vec2 margins_,
        glm::u8vec4 font_color_,
        glm::u8vec4 box_color_,
        std::string text_) :
        anchor(anchor_),
        dims(dims_),
        margins(margins_),
        font_color(font_color_),
        box_color(box_color_),
        text(text_)
    {
        source = std::make_shared<FontSource>(data_path(font_name_), size);
        assert(source != nullptr);
        shape_texture_program->SetBox(box, glm::vec4(
            anchor.x - margins.x,
            anchor.y + dims.y + margins.y,
            anchor.x + dims.x + margins.x,
            anchor.y - margins.y
        ), box_color);
    }
};

class FSM {
public:
    int cur_state = 0;
    
    int true_price = 0;
    int expect_price = 0;
    int bid_price = 0;
    int total_gain = 0;

    int total_customer = 10;
    int current_customer = 0;

	// DFA
	// {state_id : {group : next state}}
	vector<unordered_map<string, int>> dfa = {
		{{"digit", 1}, {"sign", 2}, {"dot", 3}},
		{{"digit", 1}, {"dot", 4}, {"exponent", 5}},
		{{"digit", 1}, {"dot", 3}},
		{{"digit", 4}},
		{{"digit", 4}, {"exponent", 5}},
		{{"digit", 7}, {"sign", 6}},
		{{"digit", 7}},
		{{"digit", 7}}
	};
}
