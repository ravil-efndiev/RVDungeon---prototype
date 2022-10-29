
#ifndef RPG_STATE_H
#define RPG_STATE_H

#include "dependencies.h"

class State
{
private:
    std::string type;

    void InitTextures();
    sf::Texture LoadTexture(std::string fileName);

protected:
    std::stack<State*> *states;
    sf::View* view;
    sf::RenderWindow* window;

    std::map<std::string, sf::Texture> textures;

public:
    bool close;

    State(sf::RenderWindow* window, std::string type, std::stack<State*> *states, sf::View* view);
    virtual ~State();

    virtual void CheckForClose();

    virtual void Update(const float& deltaTime) = 0;
    virtual void Render(sf::RenderTarget* target) = 0;

    virtual void EndState();

    virtual bool GetClose();
    virtual std::string GetType();
};


#endif //RPG_STATE_H
