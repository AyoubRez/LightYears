#include "player/PlayerSpaceship.h"

#include "framework/MathLibrary.h"
#include "weapon/BulletShooter.h"


namespace ly
{
    PlayerSpaceship::PlayerSpaceship(World* owningWorld, const std::string& texturePath)
        : Spaceship(owningWorld, texturePath),
          mMoveInput(),
          mSpeed(500.f),
          mShooter(new BulletShooter(this,0.15f))
    {
    }

    void PlayerSpaceship::Tick(float delta_time)
    {
        Spaceship::Tick(delta_time);
        HandleInput();
        ConsumeInput(delta_time);
    }

    void PlayerSpaceship::Shoot()
    {
        if (mShooter)
        {
            mShooter->Shoot();
        }
    }

    void PlayerSpaceship::HandleInput()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
        {
            mMoveInput.y = -1.f;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            mMoveInput.y = 1.f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
        {
            mMoveInput.x = -1.f;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            mMoveInput.x = 1.f;
        }
        ClampInputOnEdge();
        NormalizeInput();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            Shoot();
    }

    void PlayerSpaceship::ConsumeInput(float delta_time)
    {
        SetVelocity(mMoveInput * mSpeed);
        mMoveInput.x = mMoveInput.y = 0.f;
    }

    void PlayerSpaceship::NormalizeInput()
    {
        NormalizeVector(mMoveInput);
    }

    void PlayerSpaceship::ClampInputOnEdge()
    {
        sf::Vector2f actorLocation = GetActorLocation();
        if (actorLocation.x < 0.f && mMoveInput.x < 0.f)
        {
            mMoveInput.x = 0.f;
        }

        if (actorLocation.x > GetWindowSize().x && mMoveInput.x > 0.f)
        {
            mMoveInput.x = 0.f;
        }

        if (actorLocation.y < 0.f && mMoveInput.y < 0.f)
        {
            mMoveInput.y = 0.f;
        }

        if (actorLocation.y > GetWindowSize().y && mMoveInput.y > 0.f)
        {
            mMoveInput.y = 0.f;
        }
    }
}
