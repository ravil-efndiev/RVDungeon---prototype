
#include "Player.h"

Player::Player() {}
Player::Player(sf::Texture& textureSheet, sf::Texture& primalTexture)
{
    sprite.setTexture(primalTexture);
    inFight = false;
    InitComponents(textureSheet);

    ownedWeapons.emplace("sword", new Sword(animationComponent));
    currentWeapon = ownedWeapons["sword"];
    fightComponent->SetWeapon(currentWeapon);

    GenerateAnimations();
    direction = MoveDirections::down;
}

Player::~Player() 
{
    for (auto &weapon : ownedWeapons)
    {
       delete weapon.second;
    }
}

void Player::InitComponents(sf::Texture& textureSheet)
{
    movementComponent = new MovementComponent(150.f, sprite, 15.f, 4.3f);
    animationComponent = new AnimationComponent(sprite, textureSheet);
    fightComponent = new FightComponent(animationComponent);
    hitboxComponent = new HitboxComponent(&sprite, 29, 56, 38, 80);
}

void Player::Update(const float& deltaTime)
{
    try
    {
        UpdateInput(deltaTime);
        if (!fightComponent->GetAttack()) movementComponent->Update(deltaTime);

        hitboxComponent->Update();
        fightComponent->FixedUpdate(deltaTime);

        if (fightComponent->GetAttack())
        {
            fightComponent->Update(direction, deltaTime);
        }
        else
        {
            switch (direction)
            {
                case MoveDirections::right:
                    AnimateByDirection("WALK_RIGHT", "RUN_RIGHT", "IDLE_RIGHT", deltaTime);
                    break;
                case MoveDirections::left:
                    AnimateByDirection("WALK_LEFT", "RUN_LEFT", "IDLE_LEFT", deltaTime);
                    break;
                case MoveDirections::down:
                    AnimateByDirection("WALK_DOWN", "RUN_DOWN", "IDLE_DOWN", deltaTime);
                    break;
                case MoveDirections::up:
                    AnimateByDirection("WALK_UP", "RUN_UP", "IDLE_UP", deltaTime);
                    break;
            }
        }
    }
    catch(std::string exception)
    {
        std::cout << exception << std::endl;
    }
}

void Player::Render(sf::RenderTarget *target, sf::Shader *shader, const bool showHitbox)
{
    if (shader)
    {
        std::vector<sf::Vector2f> sources = lightTiles;
        sources.push_back(GetCenterPosition());

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
        
    if (showHitbox)
        hitboxComponent->Render(target);
}

void Player::UpdateInput(const float &deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        inFight = !inFight;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !fightComponent->GetAttack())
        fightComponent->Start();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        movementComponent->Move(0, -1);
        direction = MoveDirections::up;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        movementComponent->Move(0, 1);
        direction = MoveDirections::down;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        movementComponent->Move(1, 0);
        direction = MoveDirections::right;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        movementComponent->Move(-1, 0);
        direction = MoveDirections::left;
    }
}

void Player::AnimateByDirection(std::string walkAnim, std::string runAnim, std::string idleAnim, const float& deltaTime)
{
    if (movementComponent->IsMoving())
    {
        if (inFight)
        {
            movementComponent->EditValues(200.f, 20.f, 5.f);
            animationComponent->Play(runAnim, deltaTime);
        }
        else
        {
            movementComponent->ResetValues();
            animationComponent->Play(walkAnim, deltaTime);
        }
    }
    else
    {
        movementComponent->ResetValues();
        animationComponent->Play(idleAnim, deltaTime);
    }
}

void Player::GenerateAnimations()
{
    animationComponent->AddAnimation("WALK_LEFT", 12.f, 4, 2, 9, 2, 32, 64);
    animationComponent->AddAnimation("WALK_RIGHT", 12.f, 4, 1, 9, 1, 32, 64);
    animationComponent->AddAnimation("WALK_DOWN", 12.f, 4, 0, 9, 0, 32, 64);
    animationComponent->AddAnimation("WALK_UP", 12.f, 4, 3, 9, 3, 32, 64);

    animationComponent->AddAnimation("RUN_RIGHT", 10.f, 0, 4, 5, 4, 32, 32);
    animationComponent->AddAnimation("RUN_LEFT", 10.f, 0, 5, 5, 5, 32, 32);
    animationComponent->AddAnimation("RUN_DOWN", 10.f, 0, 8, 5, 8, 32, 32);
    animationComponent->AddAnimation("RUN_UP", 10.f, 0, 11, 5, 11, 32, 32);

    animationComponent->AddAnimation("IDLE_DOWN", 25.f, 0, 0, 4, 0, 32, 64);
    animationComponent->AddAnimation("IDLE_UP", 25.f, 0, 3, 4, 3, 32, 64);
    animationComponent->AddAnimation("IDLE_LEFT", 25.f, 0, 2, 4, 2, 32, 64);
    animationComponent->AddAnimation("IDLE_RIGHT", 25.f, 0, 1, 4, 1, 32, 64);
}

void Player::InitLightTiles(std::vector<sf::Vector2f> lightTiles)
{
    this->lightTiles = lightTiles;
}
