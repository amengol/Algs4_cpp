#include "Render.h"
#include "Render_Impl.h"

Render::Render(const cwt::Pen& pen, int width, int height, const wchar_t* caption)
    : pRender_impl(new Render_Impl(pen, width, height, caption)) {}

Render::~Render()
{
    delete pRender_impl;
    pRender_impl = nullptr;
}

const cwt::Pen& Render::viewPen() const
{
    return pRender_impl->viewPen();
}

cwt::Pen& Render::getPen()
{
    return pRender_impl->getPen();
}

const cwt::Font& Render::viewFont() const
{
    return pRender_impl->viewFont();
}

cwt::Font& Render::getFont()
{
    return pRender_impl->getFont();
}

bool Render::isWindowOpen()
{
    return pRender_impl->isWindowOpen();
}

void Render::drawLine(double x1, double y1, double x2, double y2)
{
    pRender_impl->drawLine(x1, y1, x2, y2);
}

void Render::drawElipse(double x, double y, double width, double height)
{
    pRender_impl->drawElipse(x, y, width, height);
}

void Render::fillElipse(double x, double y, double width, double height)
{
    pRender_impl->fillElipse(x, y, width, height);
}

void Render::drawArc(double x, double y, double width, double height, double start, double sweep)
{
    pRender_impl->drawArc(x, y, width, height, start, sweep);
}

void Render::drawRectangle(double x, double y, double width, double height)
{
    pRender_impl->drawRectangle(x, y, width, height);
}

void Render::fillRectangle(double x, double y, double width, double height)
{
    pRender_impl->fillRectangle(x, y, width, height);
}

void Render::drawPolygon(const std::vector<double>& x, const std::vector<double>& y)
{
    pRender_impl->drawPolygon(x, y);
}

void Render::fillPolygon(const std::vector<double>& x, const std::vector<double>& y)
{
    pRender_impl->fillPolygon(x, y);
}

void Render::drawString(const wchar_t* text, double x, double y)
{
    pRender_impl->drawString(text, x, y);
}

void Render::show()
{
    pRender_impl->show();
}

void Render::setCanvasSize(int canvasWidth, int canvasHeight)
{
    pRender_impl->setCanvasSize(canvasWidth, canvasHeight);
}

void Render::GetTextExtent(const wchar_t* text, int len, int& w, int& h)
{
    pRender_impl->GetTextExtent(text, len, w, h);
}
