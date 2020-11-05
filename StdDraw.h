#pragma once
#include "Render.h"
#include "cwt.h"
#include <thread>
#include <stdexcept>
#include <string>
#include <vector>

// Constants
constexpr int DEFAULT_SIZE = 512;
constexpr double DEFAULT_PEN_RADIUS = 0.002;
constexpr double BORDER = 0.00;
constexpr double DEFAULT_XMIN = 0.0;
constexpr double DEFAULT_XMAX = 1.0;
constexpr double DEFAULT_YMIN = 0.0;
constexpr double DEFAULT_YMAX = 1.0;
const cwt::Color DEFAULT_PEN_COLOR = cwt::Color::BLACK;
// default font
const cwt::Font DEFAULT_FONT = cwt::Font(L"SansSerif", cwt::Font::Style::FontStyleRegular, 16);

class StdDraw final
{
public:
	static StdDraw& getInstance()
	{
		static StdDraw instance;
		return instance;
	}
	
	StdDraw(const StdDraw&) = delete;
	void operator=(const StdDraw&) = delete;

	~StdDraw();

	/**
	 * Sets the canvas (drawing area) to be 512-by-512 pixels.
	 * This also erases the current drawing and resets the coordinate system,
	 * pen radius, pen color, and font back to their default values.
	 * Ordinarily, this method is called once, at the very beginning
	 * of a program.
	 */
	void setCanvasSize();

	/**
	 * Sets the canvas (drawing area) to be width-by-height pixels.
	 * This also erases the current drawing and resets the coordinate system,
	 * pen radius, pen color, and font back to their default values.
	 * Ordinarily, this method is called once, at the very beginning
	 * of a program.
	 *
	 * @param  canvasWidth the width as a number of pixels
	 * @param  canvasHeight the height as a number of pixels
	 * @throws std::invalid_argument unless both canvasWidth and canvasHeight 
	 * are positive
	 */
	void setCanvasSize(int canvasWidth, int canvasHeight);

	/**
	* Returns the current pen radius.
	*
	* @return the current value of the pen radius
	*/
	double getPenRadius();

	/**
	 * Sets the pen size to the default size (0.002).
	 * The pen is circular, so that lines have rounded ends, and when you set the
	 * pen radius and draw a point, you get a circle of the specified radius.
	 * The pen radius is not affected by coordinate scaling.
	 */
	void setPenRadius();

	/**
	 * Sets the radius of the pen to the specified size.
	 * The pen is circular, so that lines have rounded ends, and when you set the
	 * pen radius and draw a point, you get a circle of the specified radius.
	 * The pen radius is not affected by coordinate scaling.
	 *
	 * @param  radius the radius of the pen
	 * @throws std::invalid_argument if radius is negative, NaN, or infinite
	 */
	void setPenRadius(double radius);

	/**
	 * Returns the current pen color.
	 *
	 * @return the current pen color
	 */
	cwt::Color getPenColor();

	/**
	 * Sets the pen color to the default color (black).
	 */
	void setPenColor();

	/**
	 * Sets the pen color to the specified color.
	 * <p>
	 * The predefined pen color names are BLACK, BLUE, CYAN, DARK_GRAY, GRAY, 
	 * GREEN, LIGHT_GRAY, MAGENTA, ORANGE, PINK, RED, WHITE, and YELLOW.
	 *
	 * @param color the color to make the pen
	 * @throws std::invalid_argument if color is null
	 */
	void setPenColor(cwt::Color color);

	/**
	 * Sets the pen color to the specified RGB color.
	 *
	 * @param  red the amount of red (between 0 and 255)
	 * @param  green the amount of green (between 0 and 255)
	 * @param  blue the amount of blue (between 0 and 255)
	 * @throws std::invalid_argument if red, green, or blue is outside its 
	 * prescribed range
	 */
	void setPenColor(int red, int green, int blue);

	/**
	 * Returns the current font.
	 *
	 * @return the current font
	 */
	cwt::Font getFont();

	/**
	 * Sets the font to the default font (sans serif, 16 point).
	 */
	void setFont();

	/**
	 * Sets the font to the specified value.
	 *
	 * @param font the font
	 */
	void setFont(cwt::Font font);

	/***************************************************************************
	*  Drawing geometric shapes.
	***************************************************************************/

	/**
	 * Draws a line segment between (x0, y0) and (x1, y1).
	 *
	 * @param  x0 the x-coordinate of one endpoint
	 * @param  y0 the y-coordinate of one endpoint
	 * @param  x1 the x-coordinate of the other endpoint
	 * @param  y1 the y-coordinate of the other endpoint
	 * @throws std::invalid_argument if any coordinate is either NaN or infinite
	 */
	void line(double x0, double y0, double x1, double y1);

	/**
	 * Draws a circle of the specified radius, centered at (x, y).
	 *
	 * @param  x the x-coordinate of the center of the circle
	 * @param  y the y-coordinate of the center of the circle
	 * @param  radius the radius of the circle
	 * @throws std::invalid_argument if radius is negative
	 * @throws std::invalid_argument if any argument is either NaN or infinite
	 */
	void circle(double x, double y, double radius);

	/**
	 * Draws a filled circle of the specified radius, centered at (x, y).
	 *
	 * @param  x the x-coordinate of the center of the circle
	 * @param  y the y-coordinate of the center of the circle
	 * @param  radius the radius of the circle
	 * @throws std::invalid_argument if radius is negative
	 * @throws std::invalid_argument if any argument is either NaN or infinite
	 */
	void filledCircle(double x, double y, double radius);

	/**
	* Draws a circular arc of the specified radius,
	* centered at (x, y), from angle1 to angle2 (in degrees).
	*
	* @param  x the x-coordinate of the center of the circle
	* @param  y the y-coordinate of the center of the circle
	* @param  radius the radius of the circle
	* @param  angle1 the starting angle. 0 would mean an arc beginning at 3 o'clock.
	* @param  angle2 the angle at the end of the arc. For example, if
	*         you want a 90 degree arc, then angle2 should be angle1 + 90.
	* @throws std::invalid_argument if {@code radius} is negative
	* @throws std::invalid_argument if any argument is either NaN or infinite
	*/
	void arc(double x, double y, double radius, double angle1, double angle2);

	/**
	 * Draws a square of the specified size, centered at (x, y).
	 *
	 * @param  x the x-coordinate of the center of the square
	 * @param  y the y-coordinate of the center of the square
	 * @param  halfLength one half the length of any side of the square
	 * @throws std::invalid_argument if halfLength is negative
	 * @throws std::invalid_argument if any argument is either NaN or infinite
	 */
	void square(double x, double y, double halfLength);

	/**
	* Draws a filled square of the specified size, centered at (x, y).
	*
	* @param  x the x-coordinate of the center of the square
	* @param  y the y-coordinate of the center of the square
	* @param  halfLength one half the length of any side of the square
	* @throws std::invalid_argument if halfLength is negative
	* @throws std::invalid_argument if any argument is either NaN or infinite
	*/
	void filledSquare(double x, double y, double halfLength);

	/**
	 * Draws a polygon with the vertices
	 * (x0, y0),
	 * (x1, y1), ...,
	 * (xn–1, yn–1).
	 *
	 * @param  x a vector of all the x-coordinates of the polygon
	 * @param  y a vector of all the y-coordinates of the polygon
	 * @throws std::invalid_argument unless {@code x[]} and {@code y[]}
	 *         are of the same length
	 * @throws std::invalid_argument if any coordinate is either NaN or infinite
	 */
	void polygon(std::vector<double> x, std::vector<double> y);

	/**
	 * Draws a filled polygon with the vertices
	 * (x0, y0),
	 * (x1, y1), ...,
	 * (xn–1, yn–1).
	 *
	 * @param  x a vector of all the x-coordinates of the polygon
	 * @param  y a vector of all the y-coordinates of the polygon
	 * @throws std::invalid_argument unless {@code x[]} and {@code y[]}
	 *         are of the same length
	 * @throws std::invalid_argument if any coordinate is either NaN or infinite
	 */
	void filledPolygon(std::vector<double> x, std::vector<double> y);

	/***************************************************************************
	*  Drawing text.
	***************************************************************************/

	/**
	 * Writes the given text string in the current font, centered at (x, y).
	 *
	 * @param  x the center x-coordinate of the text
	 * @param  y the center y-coordinate of the text
	 * @param  text the text to write
	 * @throws std::invalid_argument if {@code x} or {@code y} is either NaN or infinite
	 */
	void text(double x, double y, std::wstring text);

	/**
	 * Test client.
	 *
	 * @param argc number of arguments passed to the program
	 * @param argv the command-line arguments
	 */
	static void test(int argc, char* argv[]);

private:
	StdDraw() = default;

	Render render{ 
		cwt::Pen{ cwt::ColorRgba{cwt::getRgba(cwt::Color::BLACK)}, DEFAULT_PEN_RADIUS },
		DEFAULT_SIZE,		// Width
		DEFAULT_SIZE,		// Height
		L"Standard Draw"	// Caption
	};
	std::thread tRender;
	bool hasRenderInit = false;
	
	// Canvas size
	int width = DEFAULT_SIZE;
	int height = DEFAULT_SIZE;

	// boundary of drawing canvas
	double xmin = DEFAULT_XMIN;
	double ymin = DEFAULT_YMIN;
	double xmax = DEFAULT_XMAX;
	double ymax = DEFAULT_YMAX;

	// Init
	void init();

	// Draw
	void draw();

	// throw an std::invalid_argument if x is NaN or infinite
	void validate(double x, const std::string& name);

	// throw an std::invalid_argument if s is null
	void validateNonnegative(double x, const std::string& name);

	// throw an std::invalid_argument if s is null
	template <class Object>
	void validateNotNull(Object x, std::string name) 
	{
		if (x == nullptr)
		{
			throw std::invalid_argument(name + " is null");
		}
	}

	// helper functions that scale from user coordinates to screen coordinates and back
	double  scaleX(double x) { return width * (x - xmin) / (xmax - xmin); }
	double  scaleY(double y) { return height * (ymax - y) / (ymax - ymin); }
	double factorX(double w) { return w * width / abs(xmax - xmin); }
	double factorY(double h) { return h * height / abs(ymax - ymin); }
	double   userX(double x) { return xmin + x * (xmax - xmin) / width; }
	double   userY(double y) { return ymax - y * (ymax - ymin) / height; }

	/**
	* Draws one pixel at (x, y).
	* This method is private because pixels depend on the display.
	* To achieve the same effect, set the pen radius to 0 and call point().
	*
	* @param  x the x-coordinate of the pixel
	* @param  y the y-coordinate of the pixel
	* @throws std::invalid_argument if x or y is either NaN or infinite
	*/
	void pixel(double x, double y);
};