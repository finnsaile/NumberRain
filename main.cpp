#include <SFML/Graphics.hpp>
#include <iostream>
#include "Rain.hpp"

using namespace sf;
using namespace std;

Color colorArray[] = 
{  
    Color::Green,
    Color::Blue,
    Color::Red,
    Color::Magenta,
    Color::Cyan,
    Color::Yellow
};

int main()
{
    //antialiasing 
    ContextSettings settings;
    settings.antialiasingLevel = 0;
    //get screen height
    Vector2u size {VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height};

    FloatRect visibleArea(0, 0, size.x, size.y);
    //create non scalable window
    RenderWindow window(VideoMode(size.x / 2, size.y / 2), "Clock", Style::Titlebar | Style::Close | Style::Resize, settings);
    //enable V-Sync
    window.setFramerateLimit(60);
    //disable repeat key press on hold
    window.setKeyRepeatEnabled(true);
    //Create clock
    Rain rain(window.getSize());

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

                        // case Keyboard::C:    
                        //     colorCycle(clockObject);                        
                        //     break;

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
