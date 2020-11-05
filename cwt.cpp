#include "cwt.h"

cwt::ColorRgba cwt::getRgba(Color color)
{
	ColorRgba retColor;

	switch (color)
	{
	case Color::BLACK:
		retColor.r = 0;
		retColor.g = 0;
		retColor.b = 0;
		break;
	case Color::BLUE:
		retColor.r = 0;
		retColor.g = 0;
		retColor.b = 255;
		break;
	case Color::CYAN:
		retColor.r = 0;
		retColor.g = 255;
		retColor.b = 255;
		break;
	case Color::DARK_GRAY:
		retColor.r = 102;
		retColor.g = 102;
		retColor.b = 102;
		break;
	case Color::GRAY:
		retColor.r = 153;
		retColor.g = 153;
		retColor.b = 153;
		break;
	case Color::GREEN:
		retColor.r = 0;
		retColor.g = 255;
		retColor.b = 0;
		break;
	case Color::LIGHT_GRAY:
		retColor.r = 204;
		retColor.g = 204;
		retColor.b = 204;
		break;
	case Color::MAGENTA:
		retColor.r = 255;
		retColor.g = 0;
		retColor.b = 255;
		break;
	case Color::ORANGE:
		retColor.r = 255;
		retColor.g = 102;
		retColor.b = 0;
		break;
	case Color::PINK:
		retColor.r = 255;
		retColor.g = 192;
		retColor.b = 203;
		break;
	case Color::RED:
		retColor.r = 255;
		retColor.g = 0;
		retColor.b = 0;
		break;
	case Color::WHITE:
		retColor.r = 255;
		retColor.g = 255;
		retColor.b = 255;
		break;
	case Color::YELLOW:
		retColor.r = 255;
		retColor.g = 255;
		retColor.b = 0;
		break;
	case Color::BOOK_BLUE:
		retColor.r = 9;
		retColor.g = 90;
		retColor.b = 196;
		break;
	case Color::BOOK_LIGHT_BLUE:
		retColor.r = 103;
		retColor.g = 198;
		retColor.b = 243;
		break;
	case Color::BOOK_RED:
		retColor.r = 150;
		retColor.g = 35;
		retColor.b = 31;
		break;
	case Color::PRINCETON_ORANGE:
		retColor.r = 245;
		retColor.g = 128;
		retColor.b = 37;
		break;
	case Color::UNDEFINED:
	default:
		assert(!"This RGB combination is not associated with a cwt::Color enum!");
		break;
	}

	return retColor;
}

cwt::Color cwt::getColor(int red, int green, int blue)
{
	{
		for (Color c = Color::FIRST; c != Color::LAST; c = static_cast<Color>(static_cast<int>(c) + 1))
		{
			ColorRgba rgbaColor = getRgba(c);
			if (rgbaColor.r == red && rgbaColor.g == green && rgbaColor.b == blue)
			{
				return c;
			}
		}

		assert(!"RGB Color is not assigned to a cwt::Color enum!");
		return Color::UNDEFINED;
	}
}
