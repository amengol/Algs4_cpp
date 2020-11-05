#pragma once
#include <string>
#include <algorithm>
#include <cassert>

namespace cwt
{
	enum class Color
	{
		FIRST,
		UNDEFINED = FIRST,
		BLACK,
		BLUE,
		CYAN,
		DARK_GRAY,
		GRAY,
		GREEN,
		LIGHT_GRAY,
		MAGENTA,
		ORANGE,
		PINK,
		RED,
		WHITE,
		YELLOW,
		BOOK_BLUE,
		BOOK_LIGHT_BLUE,
		BOOK_RED,
		PRINCETON_ORANGE,
		DEFAULT_PEN_COLOR = BLACK,
		DEFAULT_CLEAR_COLOR = WHITE,
		LAST
	};

	struct ColorRgba
	{
		int r = 0;
		int g = 0;
		int b = 0;
		int a = 255;	
	};	

	ColorRgba getRgba(Color color);
	
	Color getColor(int red, int green, int blue);

	struct Pen
	{
		ColorRgba color;
		double radius;
	};

	class Font
	{
	public:
		enum class Style
		{
			FontStyleRegular,
			FontStyleBold,
			FontStyleItalic,
			FontStyleBoldItalic,
			FontStyleUnderline,
			FontStyleStrikeout
		};

		Font() = default;
		Font(const std::wstring fontName, const Style fontStyle, size_t fontSize)
		{
			name = fontName;
			style = fontStyle;
			size = fontSize;
		}

		Style viewFontSyle() const
		{
			return this->style;
		}

		const std::wstring& viewFontName() const
		{
			return this->name;
		}

		size_t viewFontSize() const
		{
			return this->size;
		}
	private:
		std::wstring name = L"SansSerif";
		Style style = Style::FontStyleRegular;
		size_t size = 16;
	};
}