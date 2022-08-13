#ifndef RAIN_H
#define RAIN_H

#include <list>
#include <SFML/Graphics.hpp>

#include "Node.hpp"

using std::list;
using sf::Vector2u, sf::Clock;

class Node;

class Rain : public sf::Drawable {
private:
    list<Node> nodes;
    Vector2u size;
    unsigned int letter_count;

    //variables for calculating movement
    Clock clock;
    double accumulator;
    unsigned int speed;

public:
    Rain(Vector2u size);
    virtual ~Rain();
    void resize(Vector2u size);
    void update();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif