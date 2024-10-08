#ifndef _RECTANGLE_H
#define _RECTANGLE_H
#include "point.h"
#include <iostream>
#include <string>

enum class Colour { Red, Green, Blue, Orange, Yellow, Black, White };

// A rectangle is defined by a Point that specifies its upper-left corner, a
// Colour, and its dimensions (height and width). The dimensions must be > 0.
struct Rectangle {

	Point point;
	int height, width;
	Colour colour;   

	Rectangle( Point upperLeft, int height, int width, Colour colour );
	void translate( int x = 0, int y = 0 );
	void scale( float heightFactor = 1.0, float widthFactor = 1.0 );
	void change( Colour newColour );
	// Colour colour() const;
	// Point point() const;
	// int width() const;
	// int height() const;
};

// Reads in a Rectangle from the specified input stream. Input format consists
// of: colour x-coordinate y-coordinate height width
std::istream & operator>>( std::istream & in, Rectangle & rectangle );

// Outputs a Rectangle to the specified output stream. Output format is:
// [colour (x,y) heightxwidth]
std::ostream & operator<<( std::ostream & out, const Rectangle & rectangle );

#endif
