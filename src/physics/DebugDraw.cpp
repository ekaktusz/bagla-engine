#include "physics/DebugDraw.h"
#include <spdlog/spdlog.h>	
#include <SFML/Graphics/RenderWindow.hpp>

namespace bgl
{

	DebugDraw::DebugDraw(sf::RenderWindow& renderWindow) : m_RenderWindow(renderWindow)
	{

	}

	void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		spdlog::warn("The method or operation is not implemented.");
	}

	void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		spdlog::warn("The method or operation is not implemented.");
	}

	void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
	{
		spdlog::warn("The method or operation is not implemented.");
	}

	void DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
	{
		spdlog::warn("The method or operation is not implemented.");
	}

	void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
	{
		spdlog::warn("The method or operation is not implemented.");
	}

	void DebugDraw::DrawTransform(const b2Transform& xf)
	{
		spdlog::warn("The method or operation is not implemented.");
	}

	void DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
	{
		spdlog::warn("The method or operation is not implemented.");
	}

}