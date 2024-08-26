#include "graphics/ParallaxLayer.h"

namespace bgl 
{

	ParallaxLayer::ParallaxLayer(const sf::Texture& backgroundTexture, float distanceFromCamera, float offsetY)
		: m_Texture(backgroundTexture),
		m_DistanceFromCamera(distanceFromCamera),
		m_OffsetY(offsetY)
	{
		m_Texture.setRepeated(true);
		m_Sprite.setTexture(m_Texture);
		m_Sprite.setPosition(0.f, 0.f);
		m_ParallaxShader.loadFromMemory(
			"uniform float offsetx;"
			"uniform float offsety;"

			"void main() {"
			"    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
			"    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
			"    gl_TexCoord[0].x = gl_TexCoord[0].x + offsetx;" // magic
			"    gl_TexCoord[0].y = gl_TexCoord[0].y + offsety;" // magic
			"    gl_FrontColor = gl_Color;"
			"}"
			, sf::Shader::Vertex);
	}

	void ParallaxLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_Sprite, &m_ParallaxShader);
	}

	void ParallaxLayer::update(sf::Vector2f cameraPosition)
	{
		m_Sprite.setPosition(cameraPosition.x, cameraPosition.y);
		m_ParallaxShader.setUniform("offsetx", cameraPosition.x * m_DistanceFromCamera * 0.0001f);
		//m_ParallaxShader.setUniform("offsety", cameraPosition.y * 1 / m_distanceFromCamera * 0.001f);
		m_ParallaxShader.setUniform("offsety", 0.f);
	}

	void ParallaxLayer::setScale(sf::Vector2f scale)
	{
		m_Sprite.setScale(scale);
	}

	void ParallaxLayer::setPosition(sf::Vector2f position)
	{
		m_Sprite.setPosition(position);
	}

	sf::FloatRect ParallaxLayer::getGlobalBounds() const
	{
		return m_Sprite.getGlobalBounds();
	}

}