#include "stdafx.h"
#include "BombIcon.h"

BombIcon::BombIcon(const std::string& name)
	: GameObject(name)
{
}

void BombIcon::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	drawnicon.setPosition(position);

}

void BombIcon::SetRotation(float angle)
{
	rotation = angle;
}

void BombIcon::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void BombIcon::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(drawnicon, originPreset);
	}
}

void BombIcon::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	drawnicon.setOrigin(origin);
}

void BombIcon::Init()
{
}

void BombIcon::Release()
{
}

void BombIcon::Reset()
{

	auto& tex = TEXTURE_MGR.Get(textureId);
	icon.setTexture(tex);
	mask.setPrimitiveType(sf::PrimitiveType::TriangleFan);
	mask.resize(5);
	sf::Vector2f iconsize = icon.getLocalBounds().getSize();
	float radius = Utils::Magnitude(iconsize * 0.5f);
	mask[0].position = iconsize * 0.5f;
	mask[0].color = sf::Color({ 90,90,90,0 });
	int vac = mask.getVertexCount();
	for (int i = 1; i < vac; ++i)
	{
		float angle = ((10 - i) / 9.f * 2.f - 0.5f) * Utils::PI;
		mask[i].position = { radius * cosf(angle),radius * sinf(angle) };
		mask[i].position += iconsize * 0.5f;
		mask[i].color = sf::Color({ 90,90,90,0 });
	}
	texture.create(tex.getSize().x, tex.getSize().y);
	timer = 0.f;
	maxTime = 5.f;
}

void BombIcon::LateUpdate(float dt)
{
}

void BombIcon::Update(float dt)
{
	sf::Vector2f iconsize = icon.getLocalBounds().getSize();
	float radius = Utils::Magnitude(iconsize * 0.5f);
	int vac = mask.getVertexCount();
	float ratio = Utils::Clamp01(timer / maxTime);

	for (int i = vac - 1; i > 0; --i)
	{
		float angle = ((10 - i) / 9.f * 2.f * (1 - ratio) - 0.5f) * Utils::PI;
		mask[i].position = { radius * cosf(angle),radius * sinf(angle) };
		mask[i].position += iconsize * 0.5f;
	}
	texture.clear();

	iconRenderState.blendMode = sf::BlendMode(sf::BlendMode::One, sf::BlendMode::Zero, sf::BlendMode::Add);
	texture.draw(icon, iconRenderState);
	if (ratio < 1.f)
	{
		maskRenderState.blendMode = sf::BlendMode(sf::BlendMode::One, sf::BlendMode::One, sf::BlendMode::ReverseSubtract);
		texture.draw(mask, maskRenderState);
	}
	texture.display();
	drawnicon.setTexture(texture.getTexture(), true);
	drawnicon.setScale({ 2.f ,2.f });
	SetOrigin(originPreset);
}

void BombIcon::FixedUpdate(float dt)
{
}

void BombIcon::Draw(sf::RenderWindow& window)
{
	window.draw(drawnicon);
}

void BombIcon::SetTime(float time, float delay)
{
	timer = time;
	maxTime = delay;
}
