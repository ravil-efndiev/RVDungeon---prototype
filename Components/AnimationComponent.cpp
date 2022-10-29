
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite &sprite, sf::Texture &texture_sheet)
    : animTarget(sprite), textureSheet(texture_sheet)
{

}

AnimationComponent::~AnimationComponent()
{
    for (auto &animation : animations)
    {
        delete animation.second;
    }
}

void AnimationComponent::Play(std::string animation, const float& deltaTime)
{
    if (animations[animation] != NULL)
    {
        currentAnimation = animations[animation];
        animations[animation]->play(deltaTime);
    }
    else throw std::string("no such animation");
}

void AnimationComponent::AddAnimation(std::string animation,
                                      float animation_timer, int start_frame_x, int start_frame_y, int frames_x,
                                      int frames_y, int width, int height)
{
    animations.emplace(animation, new Animation(
                this->animTarget, this->textureSheet,
                animation_timer, start_frame_x, start_frame_y,
                frames_x, frames_y, width, height
            ));
}

bool AnimationComponent::IsDone()
{
    return currentAnimation->done;
}
