#include <SFML/Graphics.hpp>
#include <iostream>
#include "Rain.hpp"

using namespace sf;
using namespace std;

int c = 0;
Color colorArray[] = 
{  
    Color::Green,
    Color::Blue,
    Color::Red,
    Color::Magenta,
    Color::Cyan,
    Color::Yellow
};

int main(int argc, char* argv[])
{
    unsigned int speed = 300;
    if(argc > 1) speed = stoi(argv[1]);
    if(argc > 2) Node::trail_length = stoi(argv[2]);
    if(argc > 3) Node::char_size = stoi(argv[3]);
    if(argc > 4) Node::char_margin = stoi(argv[4]);

    //get screen height
    Vector2u size {VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height};

    FloatRect visibleArea(0, 0, size.x, size.y);
    //create scalable window
    RenderWindow window(VideoMode(size.x / 2, size.y / 2), "Matrix", Style::Titlebar | Style::Close | Style::Resize);
    //framerate
    //window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(true);
    //disable repeat key press on hold
    window.setKeyRepeatEnabled(true);
    //Create rain
    Rain rain(window.getSize(), speed);

    Event event;
    //window loop
    while (window.isOpen())
    {
        //event loop
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                //close window if close button is pressed
                case Event::Closed:
                    window.close();
                    break;
                case Event::Resized:
                    visibleArea = FloatRect(0, 0, event.size.width, event.size.height);
                    window.setView(View(visibleArea));
                    rain.resize(window.getSize()); 
                    break;
                //switch case for key press
                case Event::KeyPressed:
                    switch(event.key.code)
                    {
                        //close window if ESC is pressed
                        case Keyboard::Escape:
                            window.close(); 
                            break;

                        case Keyboard::C:
                            c = (c + 1) % 6;    
                            rain.setColor(colorArray[c]);                        
                            break;
                        
                        case Keyboard::Down:
                            rain.setSpeed(rain.getSpeed() * 2);
                            break;
                        
                        case Keyboard::Up:
                            rain.setSpeed(rain.getSpeed() / 2 != 0 ? rain.getSpeed() / 2 : 1);
                            break;

                        default:
                            break;
                    }

                default:
                    break;
            }     
        }
        //call window tick from window object
        rain.update();
        //clear window
        window.clear(Color::Transparent);
        //draw clock
        window.draw(rain);
        //display everything
        window.display();
    } 
    return 0;  
}
