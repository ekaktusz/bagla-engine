#include "physics/DebugDraw.h"
#include <spdlog/spdlog.h>	
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include "physics/PhysicsWorld.h"

namespace bgl
{

	DebugDraw::DebugDraw(sf::RenderWindow& renderWindow) : m_RenderWindow(renderWindow)
	{

	}

	void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		sf::ConvexShape shape;
		shape.setPointCount(vertexCount);
		for (unsigned int i = 0; i < vertexCount; ++i)
		{
			shape.setPoint(i, { PhysicsWorld::scaleToGraphics(vertices[i].x), -PhysicsWorld::scaleToGraphics(vertices[i].y) });
		}
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(sf::Color::Red);
		shape.setOutlineThickness(2.f);
		m_RenderWindow.draw(shape);
	}

	void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		sf::ConvexShape shape;
		shape.setPointCount(vertexCount);
		for (unsigned int i = 0; i < vertexCount; ++i)
		{
			shape.setPoint(i, { PhysicsWorld::scaleToGraphics(vertices[i].x), -PhysicsWorld::scaleToGraphics(vertices[i].y) });
		}
		shape.setFillColor(sf::Color::Green);
		m_RenderWindow.draw(shape);
	}

	void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
	{
		spdlog::warn("DrawCircle");
	}

	void DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
	{
		spdlog::warn("DrawSolidCircle");
	}

	void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
	{
		spdlog::warn("DrawSegment");
	}

	void DebugDraw::DrawTransform(const b2Transform& xf)
	{
		spdlog::warn("DrawTransform");
	}

	void DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
	{
		spdlog::warn("DrawPoint");
	}

}