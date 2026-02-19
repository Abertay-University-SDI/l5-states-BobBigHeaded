#pragma once
#include "Framework/GameObject.h"
class Player :
    public GameObject
{
public:
    Player();

    void handleInput(float dt) override;
    void update(float dt) override;
    void collisionResponse(GameObject& collider) override;
private:
    sf::Texture m_texture;
    sf::Vector2f m_acceleration;

    sf::Vector2f m_oldPos;

    bool m_isOnGround = false;

    const float COEFF_RESTITUTION = 0.9f;
    const float JUMP_FORCE = 5.f;
    const float GRAVITY = 10.f;
    const float SPEED = 10.f;
};

