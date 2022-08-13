#include "Node.hpp"
#include <iostream>
#include <string>

using std::to_string;

unsigned int Node::char_size = 30;
unsigned int Node::char_margin = 14;
unsigned int Node::trail_length = 30;
float Node::border_margin = 0;
Color Node::char_color = Color::Green;
Font Node::char_font;

Node::Node(unsigned int index) :
index{index},
head_position{0, 0},
active{false} {
    Text temp_text;
    temp_text.setCharacterSize(char_size);
    temp_text.setFillColor(char_color);
    temp_text.setString("0");
    temp_text.setFont(char_font);

    text_bounds = temp_text.getLocalBounds();
    temp_text.setOrigin(text_bounds.left, text_bounds.height + text_bounds.top);

    char_text = list<Text>(trail_length, temp_text);
    int i = 0;
    for(auto& ct : char_text) {
        ct.setString(to_string(rand() % 2));
        Color temp_color = char_color;
        temp_color.a = 255 - i * (255 / trail_length);
        ct.setFillColor(temp_color);
        i++;
    }
    std::cout << "Create" << std::endl;
    update(0);
}

Node::~Node() {
    std::cout << "Delete" << std::endl;
}

Vector2f Node::update(float delta) {
    head_position = {border_margin + index * (text_bounds.width + char_margin), head_position.y + delta};
    int i = 0;
    for(auto& ct : char_text) {
        ct.setPosition(head_position.x, head_position.y - (text_bounds.height + char_margin) * i);
        i++;
    }

    return head_position;
}

FloatRect Node::getBounds() {
    return text_bounds;
}

void Node::reset() {
    active = true;
    head_position.y = 0;
    update(0);
}

void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(!active)
        return;

    for(auto& ct : char_text)
        target.draw(ct);
}