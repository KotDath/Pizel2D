#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include <SFML/Graphics.hpp>

class RenderObject {
public:
    void SwitchPause();
    virtual void Draw(sf::RenderTarget&) = 0;
    virtual void Update(sf::RenderTarget&) = 0;
protected:
    bool isPause = false;
};

#endif // RENDEROBJECT_H
