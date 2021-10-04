#include "FSM.hpp"
#include <glm/gtc/type_ptr.hpp>

#include <random>

FSM::FSM() {}

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
    
}

/**
 * action for state 1
 * clear game info and random new game info
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::clearAndRand(std::vector<TextBlock>& texts){
    
}

/**
 * action for state 2
 * display game console description and first bid price
 * display action for user to choose
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::gcDesc(std::vector<TextBlock>& texts){
    
}

/**
 * action for state 3
 * display action figure description and first bid price
 * display action for user to choose
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::afDesc(std::vector<TextBlock>& texts){
    
}

/**
 * action for state 4
 * display card description and first bid price
 * display action for user to choose
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::cardDesc(std::vector<TextBlock>& texts){
    
}

/**
 * action for state 5
 * display game console detail
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::gcDetail(std::vector<TextBlock>& texts){
    
}

/**
 * action for state 6
 * display action figure detail
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::afDetail(std::vector<TextBlock>& texts){
    
}

/**
 * action for state 7
 * display card detail
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::cardDetail(std::vector<TextBlock>& texts){
    
}

/**
 * action for state 8
 * display emotion
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::emotion(std::vector<TextBlock>& texts){
    
}

/**
 * action for state 9
 * offer price
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::offerPrice(std::vector<TextBlock>& texts){
    
}

/**
 * action for state 10
 * display NPC's second Bid
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::secondBid(std::vector<TextBlock>& texts){
    
}

/**
 * action for state 11
 * display deal message
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::deal(std::vector<TextBlock>& texts){
    
}

/**
 * action for state 12
 * display summary message
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::summary(std::vector<TextBlock>& texts){
    
}

/**
 * action for state 13
 * display win message
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::win(std::vector<TextBlock>& texts){
    
}

/**
 * action for state 14
 * display lose message
 * 
 * @param texts  text boxs will be changed based on state
 */
void FSM::lose(std::vector<TextBlock>& texts){
    
}