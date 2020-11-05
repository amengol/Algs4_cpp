#pragma once
#include <vector>

class Render_Impl;

namespace cwt
{
	struct Pen;
	class Font;
}

class Render final
{
public:
	Render(const cwt::Pen&, int width, int height, const wchar_t* caption);
	Render(const Render&) = delete;
	~Render();

	const cwt::Pen& viewPen() const;
	cwt::Pen& getPen();
	const cwt::Font& viewFont() const;
	cwt::Font& getFont();

	bool isWindowOpen();
	void drawLine(double x1, double y1, double x2, double y2);
	void drawElipse(double x, double y, double width, double height);
	void fillElipse(double x, double y, double width, double height);
	void drawArc(double x, double y, double width, double height, double start, double sweep);
	void drawRectangle(double x, double y, double width, double height);
	void fillRectangle(double x, double y, double width, double height);
	void drawPolygon(const std::vector<double>& x, const std::vector<double>& y);
	void fillPolygon(const std::vector<double>& x, const std::vector<double>& y);
	void drawString(const wchar_t* text, double x, double y);
	void show();
	void setCanvasSize(int canvasWidth, int canvasHeight);
	void GetTextExtent(const wchar_t* text, int len, int& w, int& h);
private:
	Render_Impl* pRender_impl;
};
