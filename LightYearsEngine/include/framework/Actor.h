#pragma once

#include "framework/Object.h"
#include "SFML/Graphics/Sprite.hpp"
#include "framework/Core.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace ly
{
    class World;

    class Actor : public Object
    {
    public:
        Actor(World* owning_world, const std::string& texturePath = "");
        virtual ~Actor();
        void BeginPlayInternal();
        void TickInternal(float delta_time);
        virtual void BeginPlay();
        virtual void Tick(float delta_time);
        void SetTexture(const std::string& texturePath);
        void Render(sf::RenderWindow& window) const;
        
        void SetActorLocation(const sf::Vector2f& newLocation);
        void SetActorRotation(const sf::Angle& newRotation);
        void AddActorLocationOffset(const sf::Vector2f& offsetAmount);
        void AddActorRotationOffset(const sf::Angle& offsetAmount);
        
        sf::Vector2f GetActorLocation() const;
        sf::Angle GetActorRotation() const;
        sf::Vector2f GetActorForwardDirection() const;
        sf::Vector2f GetActorRightDirection() const;
        
        sf::Vector2u GetWindowSize() const;

    private:
        void CenterPivot();
        World* m_OwningWorld;
        bool m_BeganPlay;

        TOptional<sf::Sprite> m_Sprite;
        TSharedPtr<sf::Texture> m_Texture;
    };

    
}
