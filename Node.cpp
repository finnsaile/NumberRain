#include "Node.hpp"
#include <iostream>
#include <string>

using std::to_string;

Rain* Node::main_rain = nullptr;
unsigned int Node::char_size = 30;
unsigned int Node::char_margin = 15;
unsigned int Node::trail_length = 30;
float Node::border_margin = 0;
Color Node::char_color = Color::Green;
Font Node::char_font;

Node::Node(unsigned int index) :
index{index},
current_tail_index{1},
head_position{0, 0},
sample_text{createTempText()},
active{false} {
    Text temp_text = sample_text;
    temp_text.setString(to_string(rand() % 2));
    char_text.push_back(temp_text);
}

Node::~Node() {}

bool Node::update(float delta) {
    //advance all elements by the correct amount
    head_position = {border_margin + index * (text_bounds.width + char_margin), char_text.front().getPosition().y + delta};
    int i = 0;
    for(auto& ct : char_text) {
        ct.setPosition(head_position.x, head_position.y - (text_bounds.height + char_margin) * i);
        i++;
    }

    //Delete all elements from the node that have left the screen
    std::list<Text>::iterator iter = char_text.begin();
    while(iter != char_text.end())
    {
        if(iter->getPosition().y > main_rain->getSize().y + text_bounds.height) {
            iter++;
            char_text.pop_front();
        }
        else
            break;
    }

    //add all elements to the node, so that the screen is full unless the node length is reached
    iter = --char_text.end();
    while(iter != char_text.end()) {
        if(iter->getPosition().y > text_bounds.height && current_tail_index < trail_length) {
            Text temp_text = sample_text;
            temp_text.setString(to_string(rand() % 2));
            
            Color temp_color = Node::char_color;
            temp_color.a = 255 - current_tail_index * (255 / Node::trail_length);
            temp_text.setFillColor(temp_color);

            temp_text.setPosition(head_position.x, iter->getPosition().y - (text_bounds.height + char_margin));
            char_text.push_back(temp_text);
            iter++;
            current_tail_index++;
        }
        else
            break;
    }
    //return whether the node has left the screen completely
    return static_cast<bool>(char_text.size());
}

FloatRect Node::getBounds() {
    return text_bounds;
}

void Node::reset() {
    Text temp_text = sample_text;
    temp_text.setString(to_string(rand() % 2));
    temp_text.setFillColor(char_color);
    
    char_text.push_back(temp_text);
    
    active = true;
    head_position.y = 0;
    current_tail_index = 0;
}

void Node::updateColor() {
    int i = current_tail_index - char_text.size();
    i = i < 0 ? 0 : i;
    
    Color temp_color = char_color;
    for(auto& ct : char_text) {
        temp_color.a = 255 - i * (255 / trail_length);
        ct.setFillColor(temp_color);
        i++;
    }
}

void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for(auto& ct : char_text)
        target.draw(ct);
}

Text Node::createTempText() {
    Text temp_text;
    temp_text.setCharacterSize(Node::char_size);
    temp_text.setFillColor(Node::char_color);
    temp_text.setString("0");
    temp_text.setFont(Node::char_font);

    text_bounds = temp_text.getLocalBounds();
    temp_text.setOrigin(text_bounds.left, text_bounds.height + text_bounds.top);
    temp_text.setFillColor(Node::char_color);

    return temp_text;
}