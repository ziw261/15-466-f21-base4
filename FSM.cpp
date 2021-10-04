#include "FSM.hpp"
#include "gl_errors.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <random>

FSM::FSM() {
    std::ifstream file;
    file = std::ifstream(data_path("gameConsole.json"));
	if (file.is_open()) {
		file >> gameConsole;
	}
	else {
		throw std::runtime_error("Unable to open json file");
		abort();
	}

    file = std::ifstream(data_path("actionFigure.json"));
	if (file.is_open()) {
		file >> actionFigure;
	}
	else {
		throw std::runtime_error("Unable to open json file");
		abort();
	}

    file = std::ifstream(data_path("card.json"));
	if (file.is_open()) {
		file >> card;
	}
	else {
		throw std::runtime_error("Unable to open json file");
		abort();
	}

    file = std::ifstream(data_path("emotion.json"));
	if (file.is_open()) {
		file >> emotion;
	}
	else {
		throw std::runtime_error("Unable to open json file");
		abort();
	}
}

FSM::~FSM() {}

/**
 * transfer state based on action
 * 
 * @param action action 0 - 5
 */
void FSM::transferState(int action){

}

/**
 * execute on current state
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::executeState(std::vector<TextBlock>& texts){

}

/**
 * action for state 0
 * inital state
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::init(std::vector<TextBlock>& texts){
    texts[0].text = "Start";
}

/**
 * action for state 1
 * clear game info and random new game info
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::clearAndRand(std::vector<TextBlock>& texts){
	item = rand() % 3;
    item_level = rand() % 3;
	int add_on_price = rand() % (item_level * 20 + 10);

    // true price depends on item_level
	true_price = (item_level * 2 + 2) * (30 + add_on_price);

    // expect price is the 80 - 120% of true price
	expect_price = (80 + rand() % 40) * true_price / 100;
    
    // bid price is the 120 - 160% of expect price
	bid_price = (120 + rand() % 40) * expect_price / 100;
}

/**
 * action for state 2
 * display game console description and first bid price
 * display action for user to choose
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::gcDesc(std::vector<TextBlock>& texts){
    int step = (max_price - min_price) / 3;
    std::string descText = "";
    if (bid_price < step) 
        descText = gameConsole["description"]["low"];
    else if (bid_price >= step * 2)
        descText = gameConsole["description"]["high"];
    else
        descText = gameConsole["description"]["medium"];
    descText += std::to_string(bid_price);

    texts[1].text = descText;

    texts[3].text = "Current Profit: " + 
        std::to_string(total_gain) + " / " + std::to_string(target_gain);

    texts[9].text = "Current Customer: " + std::to_string(++current_customer);

    // use the middle three text blocks
    // show action
    texts[5].text = "View Item Detail";
    texts[6].text = "View Customer Emotion";
    texts[7].text = "Offer Price";

    texts[1].visible = true;
    texts[3].visible = true;
    texts[5].visible = true;
    texts[6].visible = true;
    texts[7].visible = true;
    texts[9].visible = true;
}

/**
 * action for state 3
 * display action figure description and first bid price
 * display action for user to choose
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::afDesc(std::vector<TextBlock>& texts){
    int step = (max_price - min_price) / 3;
    std::string descText = "";
    if (bid_price < step) 
        descText = actionFigure["description"]["low"];
    else if (bid_price >= step * 2)
        descText = actionFigure["description"]["high"];
    else
        descText = actionFigure["description"]["medium"];
    descText += std::to_string(bid_price);

    texts[1].text = descText;

    texts[3].text = "Current Profit: " + 
        std::to_string(total_gain) + " / " + std::to_string(target_gain);
    
    texts[9].text = "Current Customer: " + std::to_string(++current_customer);

    // use the middle three text blocks
    // show action
    texts[5].text = "View Item Detail";
    texts[6].text = "View Customer Emotion";
    texts[7].text = "Offer Price";

    texts[1].visible = true;
    texts[3].visible = true;
    texts[5].visible = true;
    texts[6].visible = true;
    texts[7].visible = true;
    texts[9].visible = true;
}

/**
 * action for state 4
 * display card description and first bid price
 * display action for user to choose
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::cardDesc(std::vector<TextBlock>& texts){
    int step = (max_price - min_price) / 3;
    std::string descText = "";
    if (bid_price < step) 
        descText = card["description"]["low"];
    else if (bid_price >= step * 2)
        descText = card["description"]["high"];
    else
        descText = card["description"]["medium"];
    descText += std::to_string(bid_price);

    texts[1].text = descText;

    texts[3].text = "Current Profit: " + 
        std::to_string(total_gain) + " / " + std::to_string(target_gain);

    texts[9].text = "Current Customer: " + std::to_string(++current_customer);

    // use the middle three text blocks
    // show action
    texts[5].text = "View Item Detail";
    texts[6].text = "View Customer Emotion";
    texts[7].text = "Offer Price";


    texts[1].visible = true;
    texts[3].visible = true;
    texts[5].visible = true;
    texts[6].visible = true;
    texts[7].visible = true;
    texts[9].visible = true;
}

/**
 * action for state 5
 * display game console detail
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::gcDetail(std::vector<TextBlock>& texts){
    std::string descText = "";
    if (item_level == 0) 
        descText = gameConsole["detail"]["low"];
    else if (item_level == 2)
        descText = gameConsole["detail"]["high"];
    else
        descText = gameConsole["detail"]["medium"];
    texts[1].text = descText;
    
    texts[6].text = "Back";

    texts[1].visible = true;
    texts[6].visible = true;
}

/**
 * action for state 6
 * display action figure detail
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::afDetail(std::vector<TextBlock>& texts){
    std::string descText = "";
    if (item_level == 0) 
        descText = actionFigure["detail"]["low"];
    else if (item_level == 2)
        descText = actionFigure["detail"]["high"];
    else
        descText = actionFigure["detail"]["medium"];
    texts[1].text = descText;
    
    texts[6].text = "Back";

    texts[1].visible = true;
    texts[6].visible = true;
}

/**
 * action for state 7
 * display card detail
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::cardDetail(std::vector<TextBlock>& texts){
    std::string descText = "";
    if (item_level == 0) 
        descText = card["detail"]["low"];
    else if (item_level == 2)
        descText = card["detail"]["high"];
    else
        descText = card["detail"]["medium"];
    texts[1].text = descText;
    
    texts[6].text = "Back";

    texts[1].visible = true;
    texts[6].visible = true;
}

/**
 * action for state 8
 * display emotion
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::emotionText(std::vector<TextBlock>& texts){
    int priceDiff = bid_price - expect_price;
    int maxDiff = true_price * (120 / 100) * (160 / 100) 
                    - true_price * (80 / 100);

    std::string descText = "";
    if (priceDiff > maxDiff / 2) 
        descText = card["emotion"]["high"][rand() % card["emotion"]["high"].size()];
    else 
        descText = card["emotion"]["low"][rand() % card["emotion"]["low"].size()];
    texts[1].text = descText;
    
    texts[6].text = "Back";

    texts[1].visible = true;
    texts[6].visible = true;
}

/**
 * action for state 9
 * offer price
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::offerPrice(std::vector<TextBlock>& texts){
    texts[1].text = "Choose your offer price";
    texts[4].text = "$" + std::to_string(bid_price);
    texts[5].text = "$" + std::to_string(bid_price * 0.8);
    texts[6].text = "$" + std::to_string(bid_price * 0.6);
    texts[7].text = "$" + std::to_string(bid_price * 0.4);
    texts[8].text = "$" + std::to_string(bid_price * 0.2);

    texts[1].visible = true;
    texts[4].visible = true;
    texts[5].visible = true;
    texts[6].visible = true;
    texts[7].visible = true;
    texts[8].visible = true;
}

/**
 * action for state 10
 * display NPC's second Bid
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::secondBid(std::vector<TextBlock>& texts){
    texts[1].text = "The customer does not agree with the price you offer ";
    texts[1].text += ", and offer a new price: $" + std::to_string(expect_price);
    texts[1].text += ". Do you accept or not?";

    texts[5].text = "Accept";
    texts[6].text = "Reject";

    texts[1].visible = true;
    texts[5].visible = true;
    texts[6].visible = true;
}

/**
 * action for state 11
 * display deal message
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::deal(std::vector<TextBlock>& texts){
    texts[1].text = "The deal has been made! Congrats on getting a new ";

    if (item == 0) texts[1].text += "game console.";
    if (item == 1) texts[1].text += "action figure.";
    if (item == 2) texts[1].text += "card.";

    texts[1].visible = true;
}

/**
 * action for state 12
 * display summary message
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::summary(std::vector<TextBlock>& texts){
    texts[1].text = "From the current item you obtained, ";

    int gain = offer_price - true_price;
    total_gain += gain;
    
    if (gain > 0)
        texts[1].text += "you received $" + std::to_string(gain);
    else if (gain < 0)
        texts[1].text += "you lost $" + std::to_string(gain);
    else
        texts[1].text += "you neither lose nor gain.";

    texts[1].visible = true;
}

/**
 * action for state 13
 * display win message
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::win(std::vector<TextBlock>& texts){
    texts[0].text = "Play Again";
    texts[1].text = "Congradulation! You win!";

    text[0].visible = true;
    text[1].visible = true;
}

/**
 * action for state 14
 * display lose message
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::lose(std::vector<TextBlock>& texts){
    texts[0].text = "Play Again";
    texts[1].text = "Unfortunately! You lost!";

    text[0].visible = true;
    text[1].visible = true;
}

/**
* Hide all textblocks
*
* @param texts  text boxs will be changed based on state
*/
void FSM::HideTextblocks(std::vector<TextBlock>& texts) {
    for (auto& block : texts) {
        block.visible = false;
    }
}