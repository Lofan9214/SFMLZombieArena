#pragma once

class TileMap : public GameObject
{
protected:
	sf::VertexArray va;
	std::string spriteSheetId = "graphics/background_sheet.png";

	sf::Texture* texture;

	sf::Transform transform;

	sf::Vector2i cellCount;
	sf::Vector2f cellSize;
	sf::Vector2f tileSize;

public:
	TileMap(const std::string& name = "");
	~TileMap() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Set(const sf::Vector2i& count, const sf::Vector2f& size, const sf::Vector2f& tilesize);
	void UpdateTransform();
};
