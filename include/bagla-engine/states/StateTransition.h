#pragma once

#include "GameObject.h"
#include "MathExtensions.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

namespace bgl
{
  class StateTransition : public bgl::GameObject
  {
  public:
    StateTransition(sf::Vector2f screenSize) 
    {
      m_TransitionBackground = sf::RectangleShape(screenSize);
	    m_TransitionBackground.setFillColor(sf::Color(0,0,0,255));
	
    }
     
    virtual void update(const sf::Time& dt) override 
    {
	    if (m_TransitionClock.getElapsedTime() < m_TransitionDuration) 
      {
        float alpha = bgl::mapValue(m_TransitionClock.getElapsedTime().asSeconds(), 0.f, m_TransitionDuration.asSeconds(), 0.f, 255.f);
        m_TransitionBackground.setFillColor(sf::Color(0,0,0, alpha));
      }
    }
    
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
	    target.draw(m_TransitionBackground);
		}
		
		virtual void handleEvent(const sf::Event& event) override
		{
		  
		}
		
  private:  
    sf::RectangleShape m_TransitionBackground;
	  sf::Clock m_TransitionClock;
	  sf::Time m_TransitionDuration = sf::seconds(2.f);
  };
}
