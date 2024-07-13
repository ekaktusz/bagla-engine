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

  // currently only fade in and out, lets work on it later
  class StateTransition : public bgl::GameObject
  {
  public:
    StateTransition() 
    {
      m_TransitionBackground = sf::RectangleShape({1270, 720}); //TODO(ekaktusz): how to get screensize here
	    m_TransitionBackground.setFillColor(sf::Color(0,0,0,0));
    }

    void start() 
    {
      m_TransitionStarted = true;
    }
     
    virtual void update(const sf::Time& dt) override 
    {
	    if (m_TransitionStarted && !isTransitionOver()) 
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

    bool isTransitionOver() 
    {
      return m_TransitionClock.getElapsedTime() > m_TransitionDuration;
    }

    enum class Type { Open, Close };
		
  private:
    sf::RectangleShape m_TransitionBackground;
	  sf::Clock m_TransitionClock;
	  sf::Time m_TransitionDuration = sf::seconds(2.f);

    bool m_TransitionStarted = false;
  };
}
