#ifndef NODE_H
#define NODE_H

#include <list>
#include <SFML/Graphics.hpp>

#include "Rain.hpp"

using std::list;
using sf::Vector2f, sf::Font, sf::Text, sf::Color, sf::FloatRect;

class Rain;

class Node : public sf::Drawable {
public:
    static Rain* main_rain;
    static unsigned int char_size;
    static unsigned int trail_length;
    static unsigned int char_margin;
    static float border_margin;
    static Color char_color;
    static Font char_font;
private:
    const unsigned int index;
    unsigned int current_tail_index;
    Vector2f head_position;
    FloatRect text_bounds;
    Text sample_text;
    //font and string for digital clock
    list<Text> char_text;

    Text createTempText();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    Node(unsigned int index);
    virtual ~Node();
    void reset();
    bool update(float delta);
    void updateColor();

    FloatRect getBounds();

    bool active;
};

#endif