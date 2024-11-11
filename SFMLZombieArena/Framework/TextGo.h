#pragma once
#include "GameObject.h"
class TextGo : public GameObject
{
protected:
	std::string fontId;
	sf::Text text;

	std::string stringId;

public:

	TextGo(const std::string& fontId = "", const std::string& name = "");
	~TextGo() = default;

	void SetOrigin(Origins preset);
	void SetOrigin(const sf::Vector2f& newOrigin);

	void SetFont(const std::string& fontid);

	void Init() override;
	void Release() override;

	void Reset() override;

	void LateUpdate(float dt) override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void SetRotation(float angle) override;
	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;
	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;

	void SetString(const std::string& str);
	void SetFillColor(sf::Color color);
	void SetCharSize(int size);

	void OnLocalize(Languages lang) override;
};

