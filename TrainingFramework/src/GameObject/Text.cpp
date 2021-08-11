#include "Text.h"
#include "GameConfig.h"
#include "Font.h"
#include "Shader.h"
#include "Camera.h"
#include "Application.h"


Text::Text(std::shared_ptr<Shader> shader, std::shared_ptr<Font> font, std::string text, TextColor color, float size, TextAlign align)
	: m_font(font), m_text(text), m_scale(Vector2(size, size)), m_align(align)
{
	m_position = Vector3(-1.0f, 1.0f, 1.0f);
	m_pShader = shader;
	m_color = EnumToVector(color);
	Init();
}

Text::Text(std::shared_ptr<Shader> shader, std::shared_ptr<Font> font, std::string text, Vector4 color, float size, TextAlign align)
	: m_font(font), m_text(text), m_scale(Vector2(size, size)), m_align(align)
{
	m_position = Vector3(-1.0f, 1.0f, 1.0f);
	m_pShader = shader;
	m_color = color;
	Init();
}

Text::Text(std::shared_ptr<Shader> shader, std::shared_ptr<Font> font, std::string text, std::shared_ptr<Texture> texture, float size, TextAlign align)
	: BaseObject(-1, nullptr, shader, texture), m_font(font), m_text(text), m_scale(Vector2(size, size)), m_align(align)
{
	m_position = Vector3(-1.0f, 1.0f, 1.0f);
	Init();
}

Text::~Text()
{
}

void Text::Init()
{
	SetCamera(Application::GetInstance()->GetCamera());
	CalculateWorldMatrix();
}

void Text::Draw()
{
	if (m_pCamera == nullptr) return;
	GLuint iTempShaderVaribleGLID = -1;

	glUseProgram(m_pShader->m_program);
	glBindBuffer(GL_ARRAY_BUFFER, m_font->GetFontVboId());

	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_posL");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 4, GL_FLOAT, GL_FALSE, 0, 0);
	}


	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_color");
	if (iTempShaderVaribleGLID != -1)
		glUniform4fv(iTempShaderVaribleGLID, 1, &m_color.x);

	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_texture");
	if (iTempShaderVaribleGLID != -1)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_font->GetFontTextureId());
		glUniform1i(iTempShaderVaribleGLID, 0);
	}

	// TODO: implementing text alignment

	float sx = 1.0f / Globals::screenWidth * m_scale.x;
	float sy = 1.0f / Globals::screenHeight * m_scale.y;
	float x = m_position.x;
	float y = m_position.y;

	FT_GlyphSlot glyphSlot = m_font->GetGlyphSlot();
	for (const char* p = m_text.c_str(); *p; p++)
	{
		if (FT_Load_Char(m_font->GetFace(), *p, FT_LOAD_RENDER))
		{
			continue;
		}
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_ALPHA,
			glyphSlot->bitmap.width,
			glyphSlot->bitmap.rows,
			0,
			GL_ALPHA,
			GL_UNSIGNED_BYTE,
			glyphSlot->bitmap.buffer
		);
		float x2 = x + glyphSlot->bitmap_left * sx;
		float y2 = -y - glyphSlot->bitmap_top * sy;
		float w = glyphSlot->bitmap.width * sx;
		float h = glyphSlot->bitmap.rows * sy;
		GLfloat box[4][4] = {
			{x2, -y2 , 0, 0},
			{x2 + w, -y2 , 1, 0},
			{x2, -y2 - h, 0, 1},
			{x2 + w, -y2 - h, 1, 1},
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		x += (glyphSlot->advance.x >> 6) * sx;
		y += (glyphSlot->advance.y >> 6) * sy;
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::Update(GLfloat deltatime)
{
}



void Text::SetFont(std::shared_ptr<Font> font)
{
	m_font = font;
}

void Text::SetText(std::string text) {
	m_text = text;
}



Vector4 Text::EnumToVector(TextColor color)
{
	Vector4 vecColor;
	switch (color)
	{
	case TextColor::BLACK:
		vecColor = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
		break;
	case TextColor::WHITE:
		vecColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	case TextColor::RED:
		vecColor = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case TextColor::GREEN:
		vecColor = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	case TextColor::BLUE:
		vecColor = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case TextColor::YELLOW:
		vecColor = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		break;
	case TextColor::PURPLE:
		vecColor = Vector4(0.5f, 0.0f, 0.5f, 1.0f);
		break;
	case TextColor::CYAN:
		vecColor = Vector4(0.0f, 1.0f, 1.0f, 1.0f);
		break;
	default:
		vecColor = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
		break;
	}
	return vecColor;
}

void Text::Set2DPosition(GLfloat x, GLfloat y)
{
	// Convert to top-left origin
	float xx = (2.0f * x) / Globals::screenWidth - 1.0f;
	float yy = 1.0f - (2.0f * y) / Globals::screenHeight;
	m_position = Vector3(xx, yy, 1.0f);
	CalculateWorldMatrix();
}

void Text::Set2DPosition(Vector2 pos)
{
	// Convert to top-left origin
	float xx = (2.0f * pos.x) / Globals::screenWidth - 1.0f;
	float yy = 1.0f - (2.0f * pos.y) / Globals::screenHeight;
	m_position = Vector3(xx, yy, 1.0f);
	CalculateWorldMatrix();
}