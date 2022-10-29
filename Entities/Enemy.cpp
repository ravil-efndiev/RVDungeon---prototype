#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy() 
{

}

void Enemy::SetLightSource(sf::Vector2f source)
{
    this->lightPos = source;
}

void Enemy::SetLightTiles(std::vector<sf::Vector2f> sources)
{
    this->lightSources = sources;
}

void Enemy::Update(const float& deltaTime)
{}

void Enemy::Render(sf::RenderTarget* targer, sf::Shader* shader, const bool showHitbox)
{}
