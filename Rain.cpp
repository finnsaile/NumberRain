#include "Rain.hpp"
#include <iostream>
#include <cmath>
#include <random>

Rain::Rain(Vector2u size, unsigned int speed) :
size{size},
letter_count{0},
speed{speed} {
    srand(time(NULL));
    Node::char_font.loadFromFile("OCRAEXT.TTF");
    resize(size);
}

Rain::~Rain() {}

void Rain::update() {
    double frame_time = clock.restart().asSeconds();

    for(auto& N : nodes) {
        if(N.active) {
            Vector2f pos = N.update(frame_time * speed);
            if((pos.y - (Node::trail_length + 1) * (N.getBounds().height + Node::char_margin)) > size.y)
                N.active = false;
        }
        else {
            if((rand() % (int)((3000/(frame_time * speed)) + 1)) == 1)
                N.reset();
        }
    }
}

void Rain::resize(Vector2u size) {
    this->size = size;

    //create test node to get node size
    Node test_node(0);
    FloatRect test_bounds = test_node.getBounds();

    //calculate new letter count and border margins
    float new_let_count = size.x / (test_bounds.width + Node::char_margin);
    float total_border = (size.x - ((int)new_let_count * (test_bounds.width + Node::char_margin) - Node::char_margin));
    //if border margins are large enough to fit another letter
    if(total_border - (test_bounds.width + Node::char_margin) > 0) {
        total_border -= (test_bounds.width + Node::char_margin);
        new_let_count++;
    } 

    Node::border_margin = total_border / 2;

    unsigned int count_dif = labs((int)new_let_count - (int)letter_count);

    //loop over dif amount. if new amount is smaller delete nodes, otherwise add new nodes
    for(unsigned int i = 0; i < count_dif; i++) {
        if((int)new_let_count > letter_count)
            nodes.push_back({letter_count + i});
        else
            nodes.pop_back();
    }

    letter_count = new_let_count;

    //update position of all nodes
    for(auto& N : nodes)
        N.update(0);
}

void Rain::setColor(sf::Color c) {
    Node::char_color = c;
    for(auto& n : nodes)
        n.updateColor();
}

void Rain::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for(auto& N : nodes) {
        if(N.active) target.draw(N);
    }
}