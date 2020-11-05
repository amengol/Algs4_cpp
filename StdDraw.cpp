#include "StdDraw.h"
#include <cmath>
#include <vector>

void renderThreadFunc(Render& render)
{
	render.show();
}

StdDraw::~StdDraw()
{
	tRender.join();
}

void StdDraw::setCanvasSize()
{
	setCanvasSize(DEFAULT_SIZE, DEFAULT_SIZE);
}

void StdDraw::setCanvasSize(int canvasWidth, int canvasHeight)
{
	if (canvasWidth <= 0) throw new std::invalid_argument("width must be positive");
	if (canvasHeight <= 0) throw new std::invalid_argument("height must be positive");
	width = canvasWidth;
	height = canvasHeight;
	render.setCanvasSize(canvasWidth, canvasHeight);
}

double StdDraw::getPenRadius()
{
	return render.viewPen().radius;
}

void StdDraw::setPenRadius()
{
	setPenRadius(DEFAULT_PEN_RADIUS);
}

void StdDraw::setPenRadius(double radius)
{
	validate(radius, "pen radius");
	validateNonnegative(radius, "pen radius");

	render.getPen().radius = radius;
}

cwt::Color StdDraw::getPenColor()
{
	return cwt::getColor(render.viewPen().color.r, render.viewPen().color.g, render.viewPen().color.b);
}

void StdDraw::setPenColor()
{
	setPenColor(DEFAULT_PEN_COLOR);
}

void StdDraw::init()
{
	tRender = std::thread(renderThreadFunc, std::ref(render));
}

void StdDraw::draw()
{
	if (!hasRenderInit)
	{
		init();
		hasRenderInit = true;
	}
}

void StdDraw::setPenColor(cwt::Color color)
{
	render.getPen().color = cwt::getRgba(color);
}

void StdDraw::setPenColor(int red, int green, int blue)
{
	if (red < 0 || red >= 256)
	{
		throw new std::invalid_argument("red must be between 0 and 255");
	}
	if (green < 0 || green >= 256)
	{
		throw new std::invalid_argument("green must be between 0 and 255");
	}
	if (blue < 0 || blue >= 256)
	{
		throw new std::invalid_argument("blue must be between 0 and 255");
	}
	render.getPen().color.r = red;
	render.getPen().color.g = green;
	render.getPen().color.b = blue;
}

cwt::Font StdDraw::getFont()
{
	return render.viewFont();
}

void StdDraw::setFont()
{
	setFont(DEFAULT_FONT);
}

void StdDraw::setFont(cwt::Font font)
{
	render.getFont() = font;
}

void StdDraw::line(double x0, double y0, double x1, double y1)
{
	validate(x0, "x0");
	validate(y0, "y0");
	validate(x1, "x1");
	validate(y1, "y1");
	render.drawLine(x0, y0, x1, y1);

	draw();
}

void StdDraw::circle(double x, double y, double radius)
{
	validate(x, "x");
	validate(y, "y");
	validate(radius, "radius");
	validateNonnegative(radius, "radius");

	double xs = scaleX(x);
	double ys = scaleY(y);
	double ws = factorX(2 * radius);
	double hs = factorY(2 * radius);
	if (ws <= 1 && hs <= 1)
	{
		pixel(x, y);
	}
	else
	{
		render.drawElipse(xs - ws / 2, ys - hs / 2, ws, hs);
	}
	draw();
}

void StdDraw::filledCircle(double x, double y, double radius)
{
	validate(x, "x");
	validate(y, "y");
	validate(radius, "radius");
	validateNonnegative(radius, "radius");

	double xs = scaleX(x);
	double ys = scaleY(y);
	double ws = factorX(2 * radius);
	double hs = factorY(2 * radius);
	if (ws <= 1 && hs <= 1)
	{
		pixel(x, y);
	}
	else
	{
		render.fillElipse(xs - ws / 2, ys - hs / 2, ws, hs);
	}
	draw();
}

void StdDraw::arc(double x, double y, double radius, double angle1, double angle2)
{
	validate(x, "x");
	validate(y, "y");
	validate(radius, "arc radius");
	validate(angle1, "angle1");
	validate(angle2, "angle2");
	validateNonnegative(radius, "arc radius");

	while (angle2 < angle1)
	{
		angle2 += 360;
	}
	double xs = scaleX(x);
	double ys = scaleY(y);
	double ws = factorX(2 * radius);
	double hs = factorY(2 * radius);
	if (ws <= 1 && hs <= 1)
	{
		pixel(x, y);
	}
	else
	{
		render.drawArc(xs - ws / 2, ys - hs / 2, ws, hs, angle1, angle2 - angle1);
	}
	draw();
}

void StdDraw::square(double x, double y, double halfLength)
{
	validate(x, "x");
	validate(y, "y");
	validate(halfLength, "halfLength");
	validateNonnegative(halfLength, "half length");

	double xs = scaleX(x);
	double ys = scaleY(y);
	double ws = factorX(2 * halfLength);
	double hs = factorY(2 * halfLength);
	if (ws <= 1 && hs <= 1)
	{
		pixel(x, y);
	}
	else
	{
		render.drawRectangle(xs - ws / 2, ys - hs / 2, ws, hs);
	}

	draw();
}

void StdDraw::filledSquare(double x, double y, double halfLength)
{
	validate(x, "x");
	validate(y, "y");
	validate(halfLength, "halfLength");
	validateNonnegative(halfLength, "half length");

	double xs = scaleX(x);
	double ys = scaleY(y);
	double ws = factorX(2 * halfLength);
	double hs = factorY(2 * halfLength);
	if (ws <= 1 && hs <= 1)
	{
		pixel(x, y);
	}
	else
	{
		render.fillRectangle(xs - ws / 2, ys - hs / 2, ws, hs);
	}

	draw();
}

void StdDraw::polygon(std::vector<double> x, std::vector<double> y)
{
	if (x.empty())
	{
		return;
	}

	size_t sizeOfArrayX = x.size();
	size_t sizeOfArrayY = y.size();
	for (size_t i = 0; i < sizeOfArrayX; i++)
	{
		validate(x[i], "x[" + std::to_string(i) + "]");
	}
	for (size_t i = 0; i < sizeOfArrayY; i++)
	{
		validate(y[i], "y[" + std::to_string(i) + "]");
	}

	if (sizeOfArrayX != sizeOfArrayY)
	{
		throw std::invalid_argument("arrays must be of the same length");
	}

	// Scale x and y
	for (size_t i = 0; i < sizeOfArrayX; i++)
	{
		x[i] = scaleX(x[i]);
		y[i] = scaleY(y[i]);
	}

	render.drawPolygon(x, y);
	draw();
}

void StdDraw::filledPolygon(std::vector<double> x, std::vector<double> y)
{
	if (x.empty())
	{
		return;
	}

	size_t sizeOfArrayX = x.size();
	size_t sizeOfArrayY = y.size();
	for (size_t i = 0; i < sizeOfArrayX; i++)
	{
		validate(x[i], "x[" + std::to_string(i) + "]");
	}
	for (size_t i = 0; i < sizeOfArrayY; i++)
	{
		validate(y[i], "y[" + std::to_string(i) + "]");
	}

	if (sizeOfArrayX != sizeOfArrayY)
	{
		throw std::invalid_argument("arrays must be of the same length");
	}
	
	// Scale x and y
	for (size_t i = 0; i < sizeOfArrayX; i++)
	{
		x[i] = scaleX(x[i]);
		y[i] = scaleY(y[i]);
	}

	render.fillPolygon(x, y);
	draw();
}

void StdDraw::text(double x, double y, std::wstring text)
{
	validate(x, "x");
	validate(y, "y");

	double xs = scaleX(x);
	double ys = scaleY(y);
	int ws = 0;
	int hs = 0;
	render.GetTextExtent(text.c_str(), (int)text.size(), ws, hs);
	render.drawString(text.c_str(), (double)(xs - ws / 2.0), (double)(ys - hs));
	draw();
}

void StdDraw::test(int argc, char* argv[])
{
	StdDraw& stdDraw = StdDraw::getInstance();

	stdDraw.square(0.2, 0.8, 0.1);
	stdDraw.filledSquare(0.8, 0.8, 0.2);
	stdDraw.circle(0.8, 0.2, 0.2);
	//
	stdDraw.setPenColor(cwt::Color::BOOK_RED);
	stdDraw.setPenRadius(0.02);
	stdDraw.arc(0.8, 0.2, 0.1, 200, 45);

	// draw a blue diamond
	stdDraw.setPenRadius();
	stdDraw.setPenColor(cwt::Color::BOOK_BLUE);
	std::vector<double> x = { 0.1, 0.2, 0.3, 0.2 };
	std::vector<double> y = { 0.2, 0.3, 0.2, 0.1 };
	stdDraw.filledPolygon(x, y);

	// text
	stdDraw.setPenColor(cwt::Color::BLACK);
	stdDraw.text(0.2, 0.5, L"black text");
	stdDraw.setPenColor(cwt::Color::WHITE);
	stdDraw.text(0.8, 0.8, L"white text");
}

void StdDraw::validate(double x, const std::string& name)
{
	if (std::isnan(x))
	{
		throw std::invalid_argument(name + " is NaN");
	}
	if (!std::isfinite(x))
	{
		throw std::invalid_argument(name + " is infinite");
	}
}

void StdDraw::validateNonnegative(double x, const std::string& name)
{
	if (x < 0.0)
	{
		throw std::invalid_argument(name + " negative");
	}
}

void StdDraw::pixel(double x, double y)
{
	validate(x, "x");
	validate(y, "y");
	render.fillRectangle((int)std::round(scaleX(x)), (int)std::round(scaleY(y)), 1, 1);

	draw();
}
