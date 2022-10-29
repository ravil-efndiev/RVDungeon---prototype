
#ifndef RPG_GAMESTATE_H
#define RPG_GAMESTATE_H

#include "State.h"
#include "Entities/Player.h"
#include "Entities/Zombie.h"
#include "Progress/progress.h"

class GameState : public State
{
private:
    std::stack<Level*> levels;
    Player* player;
    std::vector<Enemy*> enemies;
    sf::Shader coreShader;

    void CameraFollow(Entity* entity, const float& deltaTime);
    void InitShaders();

public:
    GameState(sf::RenderWindow *window, std::string type, std::stack<State*> *states, sf::View* view);
    virtual ~GameState();

    void Update(const float& deltaTime) override;
    void Render(sf::RenderTarget* target) override;
};


#endif //RPG_GAMESTATE_H
