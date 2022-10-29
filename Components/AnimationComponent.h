
#ifndef RPG_ANIMATIONCOMPONENT_H
#define RPG_ANIMATIONCOMPONENT_H

#include <SFML/Graphics.hpp>
#include <map>

class AnimationComponent
{
private:
    class Animation
    {
    public:
        sf::Sprite& sprite;
        sf::Texture& textureSheet;
        int width, height;
        float speed;
        float animTimer, timer;
        bool done;

        sf::IntRect startRect, endRect, currentRect;

        Animation(sf::Sprite& sprite, sf::Texture& texture_sheet,
                  float animation_timer,
                  int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
                : sprite(sprite), textureSheet(texture_sheet),
                  animTimer(animation_timer), timer(0.f), done(false),
                  width(width), height(height)
        {
            startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
            currentRect = startRect;
            endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

            sprite.setTexture(textureSheet, true);
            sprite.setTextureRect(startRect);
        }


        void play(const float& deltaTime)
        {
            done = false;
            timer += 100.f * deltaTime;
            if (timer >= animTimer)
            {
                timer = 0;

                if (currentRect != endRect)
                {
                    currentRect.left += width;
                }
                else
                {
                    currentRect.left = startRect.left;
                    done = true;
                }
                sprite.setTextureRect(currentRect);
            }
        }

        void restart()
        {
            timer = 0;
            currentRect = startRect;
        }
    };

    sf::Sprite &animTarget;
    sf::Texture &textureSheet;

    std::map<std::string, Animation*> animations;
    Animation* currentAnimation;

public:

    bool IsDone();

    AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
    virtual ~AnimationComponent();

    void Play(std::string animation, const float& deltaTime);
    void AddAnimation(std::string animation,
                      float animation_timer,
                      int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height
                  );
};


#endif
