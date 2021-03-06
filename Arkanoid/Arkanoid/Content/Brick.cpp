#include "pch.h"
#include "Brick.h"
#include "GameIDs.h"

using namespace Engine;
using namespace DirectX;

Brick::Brick()
	: Physics::PhysicsObject(GameData::ID_BRICK)
	, m_rectBrick(GameEngine::Instance()->GetSquareMeshData())
	, m_Life(1)
{
	m_rectBrick.SetParent(this);
	XMFLOAT3 scale(1.0f, 0.5f, 0.25f);
	m_rectBrick.SetLocalScale(scale);
	Physics::BoundingBox b(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.4f, 1.0f, 1.0f));
	SetBoundingBox(b);
}


Brick::~Brick()
{
}


Engine::Material Brick::GetMaterial() const
{
	return m_rectBrick.GetMaterial();
}


void Brick::SetMaterial(const Engine::Material& material)
{
	m_rectBrick.SetMaterial(material);
}

float Brick::GetWidth()
{
	return m_rectBrick.GetLocalScale().x * GetLocalScale().x;
}

float Brick::GetHeight()
{
	return m_rectBrick.GetLocalScale().y * GetLocalScale().y;
}

void Brick::doStart() 
{
	Physics::PhysicsObject::doStart();
	m_rectBrick.Start();
}

void Brick::doUpdate(DX::StepTimer const& timer)
{
	Physics::PhysicsObject::doUpdate(timer);
	m_rectBrick.Update(timer);
}

void Brick::doRender()
{
	Physics::PhysicsObject::doRender();
	m_rectBrick.Render();
}

void Brick::Hit()
{
	NotifyEvent(GameData::EVE_BRICK_HIT, nullptr);
}
