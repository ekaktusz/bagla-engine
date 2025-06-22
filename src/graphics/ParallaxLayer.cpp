#include "graphics/ParallaxLayer.h"

namespace bgl
{

ParallaxLayer::ParallaxLayer(const sf::Texture& backgroundTexture, float distanceFromCamera, float offsetY) :
	_texture(backgroundTexture),
	_distanceFromCamera(distanceFromCamera),
	_offsetY(offsetY)
{
	_texture.setRepeated(true);
	_sprite.setTexture(_texture);
	_sprite.setPosition(0.f, 0.f);
	_parallaxShader.loadFromMemory("uniform float offsetx;"
								   "uniform float offsety;"

								   "void main() {"
								   "    gl_position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
								   "    gl_TexCoord[0] = gl_textureMatrix[0] * gl_MultiTexCoord0;"
								   "    gl_TexCoord[0].x = gl_TexCoord[0].x + offsetx;" // magic
								   "    gl_TexCoord[0].y = gl_TexCoord[0].y + offsety;" // magic
								   "    gl_FrontColor = gl_Color;"
								   "}",
		sf::Shader::Vertex);
}

void ParallaxLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, &_parallaxShader);
}

void ParallaxLayer::update(sf::Vector2f cameraPosition)
{
	_sprite.setPosition(cameraPosition.x, cameraPosition.y);
	_parallaxShader.setUniform("offsetx", cameraPosition.x * _distanceFromCamera * 0.0001f);
	//_parallaxShader.setUniform("offsety", cameraPosition.y * 1 / _distanceFromCamera * 0.001f);
	_parallaxShader.setUniform("offsety", 0.f);
}

void ParallaxLayer::setScale(sf::Vector2f scale)
{
	_sprite.setScale(scale);
}

void ParallaxLayer::setPosition(sf::Vector2f position)
{
	_sprite.setPosition(position);
}

sf::FloatRect ParallaxLayer::getGlobalBounds() const
{
	return _sprite.getGlobalBounds();
}

}