#pragma once

class SceneGame;

class Blood : public GameObject
{
protected:
	sf::Sprite body;
	sf::String textureId = "graphics/blood.png";
	SceneGame* sceneGame;

	float timer;
	float duration;

public:
	Blood(const std::string& name = "");
	~Blood() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	sf::FloatRect GetLocalBounds() const override { return body.getLocalBounds(); }
	sf::FloatRect GetGlobalBounds() const override { return body.getGlobalBounds(); }

	void Init() override;
	void Release() override;
	void Reset() override;
	void LateUpdate(float dt) override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};
