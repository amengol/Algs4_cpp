#include "Render_Impl.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
} // WndProc

Render_Impl::~Render_Impl()

{
	delete pGraphics;
	pGraphics = nullptr;

	// EndPaint(hWnd, &ps);
	Gdiplus::GdiplusShutdown(gdiplusToken);
}

bool Render_Impl::isWindowOpen()
{
	return GetMessage(&msg, nullptr, 0, 0);
}

void Render_Impl::drawLine(double x1, double y1, double x2, double y2)
{
	objects2D.emplace_back(std::make_unique<geom::Line>(pen, x1, y1, x2, y2));
}

void Render_Impl::drawElipse(double x, double y, double width, double height)
{
	constexpr double isFill = false;
	objects2D.emplace_back(std::make_unique<geom::Circle>(pen, x, y, width, height, isFill));
}

void Render_Impl::fillElipse(double x, double y, double width, double height)
{
	constexpr double isFill = true;
	objects2D.emplace_back(std::make_unique<geom::Circle>(pen, x, y, width, height, isFill));
}

void Render_Impl::drawArc(double x, double y, double width, double height, double start, double sweep)
{
	objects2D.emplace_back(std::make_unique<geom::Arc>(pen, x, y, width, height, start, sweep));
}

void Render_Impl::drawRectangle(double x, double y, double width, double height)
{
	constexpr double isFill = false;
	objects2D.emplace_back(std::make_unique<geom::Rectangle>(pen, x, y, width, height, isFill));
}

void Render_Impl::fillRectangle(double x, double y, double width, double height)
{
	constexpr double isFill = true;
	objects2D.emplace_back(std::make_unique<geom::Rectangle>(pen, x, y, width, height, isFill));
}

void Render_Impl::drawPolygon(const std::vector<double>& x, const std::vector<double>& y)
{
	constexpr double isFill = false;
	objects2D.emplace_back(std::make_unique<geom::Polygon>(pen, x, y, isFill));
}

void Render_Impl::fillPolygon(const std::vector<double>& x, const std::vector<double>& y)
{
	constexpr double isFill = true;
	objects2D.emplace_back(std::make_unique<geom::Polygon>(pen, x, y, isFill));
}

void Render_Impl::drawString(const wchar_t* text, double x, double y)
{
	objects2D.emplace_back(std::make_unique<geom::Text>(pen, font, text, x, y));
}

void Render_Impl::show()
{
	if (!hasInit)
	{
		init();
	}

	while (isWindowOpen())
	{
		this->preDraw();
		
		for (const std::unique_ptr<geom::Object2D>& obj : objects2D)
		{
			obj->Draw(pGraphics);
		}

		this->posDraw();
	}
}

void Render_Impl::setCanvasSize(int canvasWidth, int canvasHeight)
{
	width = canvasWidth;
	height = canvasHeight;
}

void Render_Impl::GetTextExtent(const wchar_t* text, int len, int& w, int& h)
{
	HDC hdc = GetDC(hWnd);
	SIZE size;
	GetTextExtentPoint32W(hdc, text, len, &size);
	w = size.cx;
	h = size.cy;
}

void Render_Impl::preDraw()
{
	if (!pGraphics)
	{
		pGraphics = new Gdiplus::Graphics(hWnd);
	}
}

void Render_Impl::posDraw()
{
	TranslateMessage(&msg);
	DispatchMessage(&msg);
}

void Render_Impl::init()
{
	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = GetModuleHandle(nullptr);
	wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = windowCaption;
	wndClass.lpszClassName = TEXT("Render");

	RegisterClass(&wndClass);

	hWnd = CreateWindow(
		wndClass.lpszClassName,	// window class name
		wndClass.lpszMenuName,	// window caption
		WS_OVERLAPPEDWINDOW,	// window style
		CW_USEDEFAULT,			// initial x position
		CW_USEDEFAULT,			// initial y position
		width + 17,					// initial x size
		height + 40,					// initial y size
		nullptr,					// parent window handle
		nullptr,					// window menu handle
		wndClass.hInstance,		// program instance handle
		nullptr);					// creation parameters

	INT nCmdShow = SW_SHOWNORMAL;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	hasInit = true;
}
