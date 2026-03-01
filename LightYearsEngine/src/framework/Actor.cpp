#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathLibrary.h"
#include "framework/World.h"

namespace ly
{
    Actor::Actor(World* owning_world, const std::string& texturePath)
        : m_OwningWorld(owning_world),
          m_BeganPlay(false),
          m_Sprite{}
    {
        if (!texturePath.empty())
        {
            SetTexture(texturePath);
        }
    }

    Actor::~Actor()
    {
        LY_LOG("Actor destroyed");
    }

    void Actor::BeginPlayInternal()
    {
        if (!m_BeganPlay)
        {
            m_BeganPlay = true;
            BeginPlay();
        }
    }

    void Actor::TickInternal(float delta_time)
    {
        if (IsPendingDestroy()) return;
        Tick(delta_time);
    }

    void Actor::BeginPlay()
    {
    }

    void Actor::Tick(float delta_time)
    {
    }

    void Actor::SetTexture(const std::string& texturePath)
    {
        m_Texture = AssetManager::Get().LoadTexture(texturePath);
        if (!m_Texture) return;
        m_Sprite.emplace(*m_Texture);
        int textureWidth = static_cast<int>(m_Texture->getSize().x);
        int textureHeight = static_cast<int>(m_Texture->getSize().y);
        m_Sprite->setTextureRect(sf::IntRect{
            sf::Vector2i{}, sf::Vector2i{
                textureWidth, textureHeight
            }
        });
        CenterPivot();
    }

    void Actor::Render(sf::RenderWindow& window) const
    {
        if (IsPendingDestroy()) return;
        if (!m_Sprite.has_value()) return;
        window.draw(*m_Sprite);
    }

    void Actor::SetActorLocation(const sf::Vector2f& newLocation)
    {
        if (!m_Sprite.has_value()) return;
        m_Sprite->setPosition(newLocation);
    }

    void Actor::SetActorRotation(const sf::Angle& newRotation)
    {
        if (!m_Sprite.has_value()) return;
        m_Sprite->setRotation(newRotation);
    }

    void Actor::AddActorLocationOffset(const sf::Vector2f& offsetAmount)
    {
        SetActorLocation(GetActorLocation() + offsetAmount);
    }

    void Actor::AddActorRotationOffset(const sf::Angle& offsetAmount)
    {
        SetActorRotation(GetActorRotation() + offsetAmount);
    }

    sf::Vector2f Actor::GetActorLocation() const
    {
        if (!m_Sprite.has_value())return sf::Vector2f{0, 0};
        return m_Sprite->getPosition();
    }

    sf::Angle Actor::GetActorRotation() const
    {
        if (!m_Sprite.has_value()) return sf::degrees(0.f);
        return m_Sprite->getRotation();
    }

    sf::Vector2f Actor::GetActorForwardDirection() const
    {
        return RotationToVector(GetActorRotation().asDegrees());
    }

    sf::Vector2f Actor::GetActorRightDirection() const
    {
        return RotationToVector(GetActorRotation().asDegrees() + 90.f);
    }

    sf::Vector2u Actor::GetWindowSize() const
    {
        return m_OwningWorld->GetWindowSize();
    }

    sf::FloatRect Actor::GetActorGlobalBounds() const
    {
        return m_Sprite->getGlobalBounds();
    }

    bool Actor::IsActorOuOfWindowBounds() const
    {
        float windowWidth = GetWindowSize().x;
        float windowHeight = GetWindowSize().y;
        float width = GetActorGlobalBounds().size.x;
        float height = GetActorGlobalBounds().size.y;
        sf::Vector2f actorPos = GetActorLocation();
        if (actorPos.x < -width
            || actorPos.x > windowWidth + width
            || actorPos.y < -height
            || actorPos.y > windowHeight + height)
        {
            return true;
        }
        return false;
    }

    void Actor::CenterPivot()
    {
        if (!m_Sprite.has_value()) return;
        sf::FloatRect bound = m_Sprite->getGlobalBounds();
        m_Sprite->setOrigin(sf::Vector2f(bound.size.x / 2.f, bound.size.y / 2.f));
    }
}
