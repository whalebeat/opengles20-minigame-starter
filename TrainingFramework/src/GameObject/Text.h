#pragma once
#include "BaseObject.h"

enum class TextColor {
	WHITE = 0,
	RED,
	GREEN,
	BLUE,
	YELLOW,
	PURPLE,
	CYAN,
	BLACK
};

enum class TextAlign {
	LEFT = 0,
	RIGHT,
	CENTER
};

class Font;

class Text : public BaseObject
{
public:
	Text(std::shared_ptr<Shader> shader, std::shared_ptr<Font> font, std::string text, TextColor color, float size, TextAlign align = TextAlign::LEFT);
	Text(std::shared_ptr<Shader> shader, std::shared_ptr<Font> font, std::string text, Vector4 color, float size, TextAlign align = TextAlign::LEFT);
	Text(std::shared_ptr<Shader> shader, std::shared_ptr<Font> font, std::string text, std::shared_ptr<Texture> texture, float size, TextAlign align = TextAlign::LEFT);
	~Text();

	void		Init() override;
	void		Draw() final;
	void		Update(GLfloat deltatime) override;
	void		SetFont(std::shared_ptr<Font> font);
	void		SetText(std::string text);

	void		Set2DPosition(GLfloat x, GLfloat y);
	void		Set2DPosition(Vector2 pos);

private:
	std::string				m_text;
	std::shared_ptr<Font>	m_font;

	GLint		m_iHeight;
	GLint		m_iWidth;
	Vector2		m_scale;
	TextAlign	m_align;
	Vector4		EnumToVector(TextColor color);
};
