#pragma once
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
#include <vector>
#include <memory>
#include "cwt.h"

constexpr Gdiplus::REAL STDDRAW_PEN_RADIUS_TO_GDI_PEN_RADIUS = 500.0f;

namespace geom
{
	class Object2D
	{
	public:
		virtual void Draw(Gdiplus::Graphics* pGraphics) const = 0;
		virtual ~Object2D() = default;
	protected:
		Object2D(cwt::Pen _pen) : 
			pen(_pen), 
			gdiPenRadius((Gdiplus::REAL)pen.radius* STDDRAW_PEN_RADIUS_TO_GDI_PEN_RADIUS) 
		{}
		cwt::Pen pen;
		Gdiplus::REAL gdiPenRadius;
	};

	class Line : public Object2D
	{
		double x1;
		double y1;
		double x2;
		double y2;
	public:
		Line(cwt::Pen pen, double x1, double y1, double x2, double y2)
			: Object2D(pen), x1(x1), y1(y1), x2(x2), y2(y2) {}

		void Draw(Gdiplus::Graphics* pGraphics) const override
		{
			Gdiplus::Pen gdiPen(Gdiplus::Color(pen.color.r, pen.color.g, pen.color.b), gdiPenRadius);
			pGraphics->DrawLine(
				&gdiPen, 
				(Gdiplus::REAL)x1, 
				(Gdiplus::REAL)y1, 
				(Gdiplus::REAL)x2, 
				(Gdiplus::REAL)y2);
		}
	};

	class Circle : public Object2D
	{
		double x;
		double y;
		double width;
		double height;
		bool isFill;
	public:
		Circle(cwt::Pen pen, double x, double y, double width, double height, bool isFill)
			: Object2D(pen), x(x), y(y), width(width), height(height), isFill(isFill) {}

		void Draw(Gdiplus::Graphics* pGraphics) const override
		{
			if (isFill)
			{
				Gdiplus::SolidBrush gdiBrush(Gdiplus::Color(pen.color.a, pen.color.r, pen.color.g, pen.color.b));
				pGraphics->FillEllipse(
					&gdiBrush, 
					(Gdiplus::REAL)x, 
					(Gdiplus::REAL)y, 
					(Gdiplus::REAL)width, 
					(Gdiplus::REAL)height);
			}
			else
			{
				Gdiplus::Pen gdiPen(Gdiplus::Color(pen.color.r, pen.color.g, pen.color.b), gdiPenRadius);
				pGraphics->DrawEllipse(
					&gdiPen, 
					(Gdiplus::REAL)x, 
					(Gdiplus::REAL)y, 
					(Gdiplus::REAL)width, 
					(Gdiplus::REAL)height);
			}
		}
	};

	class Arc : public Object2D
	{
		double x;
		double y;
		double width;
		double height;
		double start;
		double sweep;
	public:
		Arc(cwt::Pen pen, double x, double y, double width, double height, double start, double sweep)
			: Object2D(pen), x(x), y(y), width(width), height(height), start(start), sweep(sweep) {}

		void Draw(Gdiplus::Graphics* pGraphics) const override
		{
			Gdiplus::Pen gdiPen(Gdiplus::Color(pen.color.r, pen.color.g, pen.color.b), gdiPenRadius);
			gdiPen.SetStartCap(Gdiplus::LineCap::LineCapRound);
			gdiPen.SetEndCap(Gdiplus::LineCap::LineCapRound);
			pGraphics->DrawArc(
				&gdiPen, 
				(Gdiplus::REAL)x, 
				(Gdiplus::REAL)y, 
				(Gdiplus::REAL)width, 
				(Gdiplus::REAL)height, 
				(Gdiplus::REAL)-start, 
				(Gdiplus::REAL)-sweep);
		}
	};

	class Rectangle : public Object2D
	{
		double x;
		double y;
		double width;
		double height;
		bool isFill;
	public:
		Rectangle(cwt::Pen pen, double x, double y, double width, double height, bool isFill)
			: Object2D(pen), x(x), y(y), width(width), height(height), isFill(isFill) {}

		void Draw(Gdiplus::Graphics* pGraphics) const override
		{
			if (isFill)
			{
				Gdiplus::SolidBrush gdiBrush(Gdiplus::Color(pen.color.a, pen.color.r, pen.color.g, pen.color.b));
				pGraphics->FillRectangle(
					&gdiBrush, 
					(Gdiplus::REAL)x, 
					(Gdiplus::REAL)y, 
					(Gdiplus::REAL)width, 
					(Gdiplus::REAL)height);
			}
			else
			{
				Gdiplus::Pen gdiPen(Gdiplus::Color(pen.color.r, pen.color.g, pen.color.b), gdiPenRadius);
				pGraphics->DrawRectangle(
					&gdiPen, 
					(Gdiplus::REAL)x, 
					(Gdiplus::REAL)y, 
					(Gdiplus::REAL)width, 
					(Gdiplus::REAL)height);
			}
		}
	};

	class Polygon : public Object2D
	{
		bool isFill;
		std::vector<Gdiplus::Point> points;
	public:
		Polygon(cwt::Pen pen, const std::vector<double>& x, const std::vector<double>& y, bool isFill)
			: Object2D(pen), isFill(isFill) 
		{
			if (x.size() != y.size())
			{
				assert(!"Both x and y vectors must be of the same size to create a polygon!");
			}
			for (size_t i = 0; i < x.size(); i++)
			{
				points.emplace_back(Gdiplus::Point((INT)x[i], (INT)y[i]));
			}
		}

		void Draw(Gdiplus::Graphics* pGraphics) const override
		{
			if (isFill)
			{
				Gdiplus::SolidBrush gdiBrush(Gdiplus::Color(pen.color.a, pen.color.r, pen.color.g, pen.color.b));
				pGraphics->FillPolygon(&gdiBrush, points.data(), (INT)points.size());
			}
			else
			{
				Gdiplus::Pen gdiPen(Gdiplus::Color(pen.color.r, pen.color.g, pen.color.b), gdiPenRadius);
				pGraphics->DrawPolygon(&gdiPen, points.data(), (INT)points.size());
			}
		}
	};

	class Text : public Object2D
	{
		cwt::Font font;
		std::wstring text;
		double x;
		double y;

		Gdiplus::FontStyle viewStye(cwt::Font::Style style) const
		{
			switch (style)
			{
			default:
			case cwt::Font::Style::FontStyleRegular:
				return Gdiplus::FontStyleRegular;
				break;
			case cwt::Font::Style::FontStyleBold:
				return Gdiplus::FontStyleBold;
				break;
			case cwt::Font::Style::FontStyleItalic:
				return Gdiplus::FontStyleItalic;
				break;
			case cwt::Font::Style::FontStyleBoldItalic:
				return Gdiplus::FontStyleBoldItalic;
				break;
			case cwt::Font::Style::FontStyleUnderline:
				return Gdiplus::FontStyleUnderline;
				break;
			case cwt::Font::Style::FontStyleStrikeout:
				return Gdiplus::FontStyleStrikeout;
				break;
			}
		}

	public:
		Text(cwt::Pen pen, cwt::Font font, const std::wstring& text, double x, double y)
			: Object2D(pen), font(font), text(text), x(x), y(y) {}

		void Draw(Gdiplus::Graphics* pGraphics) const override
		{
			Gdiplus::Font gdiFont(
				font.viewFontName().c_str(), 
				(Gdiplus::REAL)font.viewFontSize(),
				viewStye(font.viewFontSyle()), 
				Gdiplus::UnitPixel);
			Gdiplus::SolidBrush gdiBrush(Gdiplus::Color(pen.color.a, pen.color.r, pen.color.g, pen.color.b));
			pGraphics->DrawString(
				text.c_str(),
				-1, 
				&gdiFont, 
				Gdiplus::PointF((Gdiplus::REAL)x, (Gdiplus::REAL)y), 
				&gdiBrush);
		}
	};
}

class Render_Impl final
{
public:
	Render_Impl(const cwt::Pen& pen, int width, int height, const wchar_t* caption)
		: 
		hWnd(nullptr),
		msg(),
		wndClass(),
		gdiplusToken(),
		pGraphics(nullptr),
		pen(pen), 
		width(width), 
		height(height), 
		windowCaption(caption) 
	{}
	~Render_Impl();

	const cwt::Pen& viewPen() const { return pen; }
	cwt::Pen& getPen() { return pen; }
	const cwt::Font& viewFont() const { return font; }
	cwt::Font& getFont() { return font; }

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
	void preDraw();
	void posDraw();
	void init();
	
	HWND							hWnd;
	MSG								msg;
	WNDCLASS						wndClass;
	Gdiplus::GdiplusStartupInput	gdiplusStartupInput;
	ULONG_PTR						gdiplusToken;
	Gdiplus::Graphics*				pGraphics;

	// current pen
	cwt::Pen pen;
	// Font
	cwt::Font font;
	// Canvas size
	int width;
	int height;

	const wchar_t* windowCaption;

	std::vector<std::unique_ptr<geom::Object2D>> objects2D;

	bool hasInit = false;
};

