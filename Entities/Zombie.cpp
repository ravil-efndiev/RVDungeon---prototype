#include "Zombie.h"

Zombie::Zombie(sf::Texture& textureSheet, sf::Texture& primalTexture, Player& player)
    : player(player), Enemy()
{
    sprite.setTexture(primalTexture);
    InitComponents(textureSheet);

    GenerateAnimations();
    direction = MoveDirections::down;

    followAi = new FollowAI(this->player, *this);
}

Zombie::~Zombie()
{
    delete followAi;
}

void Zombie::InitComponents(sf::Texture& textureSheet)
{
    movementComponent = new MovementComponent(150.f, sprite, 15.f, 4.3f);
    animationComponent = new AnimationComponent(sprite, textureSheet);
    hitboxComponent = new HitboxComponent(&sprite, 29, 56, 38, 80);
}

void Zombie::GenerateAnimations()
{
    animationComponent->AddAnimation("WALK_LEFT", 12.f, 4, 2, 9, 2, 32, 64);
    animationComponent->AddAnimation("WALK_RIGHT", 12.f, 4, 1, 9, 1, 32, 64);
    animationComponent->AddAnimation("WALK_DOWN", 12.f, 4, 0, 9, 0, 32, 64);
    animationComponent->AddAnimation("WALK_UP", 12.f, 4, 3, 9, 3, 32, 64);

    animationComponent->AddAnimation("IDLE_DOWN", 25.f, 0, 0, 4, 0, 32, 64);
    animationComponent->AddAnimation("IDLE_UP", 25.f, 0, 3, 4, 3, 32, 64);
    animationComponent->AddAnimation("IDLE_LEFT", 25.f, 0, 2, 4, 2, 32, 64);
    animationComponent->AddAnimation("IDLE_RIGHT", 25.f, 0, 1, 4, 1, 32, 64);
}

void Zombie::Update(const float& deltaTime)
{
    try
    {
        movementComponent->Update(deltaTime);
        followAi->Update(deltaTime);
        hitboxComponent->Update();

        UpdateDirections();

        switch (direction)
        {
            case MoveDirections::right:
                AnimateByDirection("WALK_RIGHT", "IDLE_RIGHT", deltaTime);
                break;
            case MoveDirections::left:
                AnimateByDirection("WALK_LEFT", "IDLE_LEFT", deltaTime);
                break;
            case MoveDirections::down:
                AnimateByDirection("WALK_DOWN", "IDLE_DOWN", deltaTime);
                break;
            case MoveDirections::up:
                AnimateByDirection("WALK_UP", "IDLE_UP", deltaTime);
                break;
        }
    }
    catch(std::string exception)
    {
        std::cout << exception << std::endl;
    }
}

void Zombie::UpdateDirections()
{
    if (player.GetPosition().x > sprite.getPosition().x && GetDistanceBtwEtities(this, &player, 'x') >= 30 && GetDistanceBtwEtities(this, &player, 'y') <= 100)
    {
        direction = MoveDirections::right;
    }
    else if (player.GetPosition().x < sprite.getPosition().x && GetDistanceBtwEtities(this, &player, 'x') >= 30 && GetDistanceBtwEtities(this, &player, 'y') <= 100)
    {
        direction = MoveDirections::left;
    }
    else if (player.GetPosition().y > sprite.getPosition().y)
    {
        direction = MoveDirections::down;
    }
    else if (player.GetPosition().y < sprite.getPosition().y)
    {
        direction = MoveDirections::up;
    }
    
}

void Zombie::Render(sf::RenderTarget* target, sf::Shader* shader, const bool showHitbox)
{
    if (shader)
    {

        std::vector<sf::Vector2f> sources = lightSources;
        sources.push_back(lightPos);

        sf::Vector2f actualPositions[2];

        for (int i = 0; i < sources.size(); i++)
        {
            actualPositions[i] = sources[i];
        }

        shader->setUniform("hasTexture", true);
        shader->setUniformArray("lightPos", actualPositions, 2);
        target->draw(sprite, shader);
    }
    else
        target->draw(sprite);
}

void Zombie::AnimateByDirection(std::string walkAnim, std::string idleAnim, const float& deltaTime)
{
    if (movementComponent->IsMoving())
    {
        movementComponent->ResetValues();
        animationComponent->Play(walkAnim, deltaTime);
    }
    else
    {
        movementComponent->ResetValues();
        animationComponent->Play(idleAnim, deltaTime);
    }
}
