#include "rectangle.h"

Colour translateColour( char c ) {
	switch( c ) {
		case 'r' : return Colour::Red;
		case 'g' : return Colour::Green;
		case 'b' : return Colour::Blue;
		case 'y' : return Colour::Yellow;
		case 'o' : return Colour::Orange;
		case 'a' : return Colour::Black;
		case 'w' : return Colour::White;
	}
	return Colour::Red;
} // translate

string translateCol(Colour cl) {
    switch ( cl ) {
        case Colour::Red : return "Red";
        case Colour::Green : return "Green";
        case Colour::Blue : return "Blue";
        case Colour::Yellow : return "Yellow";
        case Colour::Orange : return "Orange";
		case Colour::Black : return "Black";
		case Colour::White : return "White";
    }
}

Rectangle :: Rectangle( Point upperLeft, int height, int width, Colour colour ) :
    point (upperLeft), height {height}, width { width }, colour{colour} {}


void Rectangle :: translate( int x = 0, int y = 0 ) {
    point.x  += x;
    point.y += y;
}


void Rectangle :: scale( float heightFactor = 1.0, float widthFactor = 1.0 ) {
    height *= heightFactor;
    width *= widthFactor;
}

void Rectangle :: change( Colour newColour ) {
    colour = newColour;
}


// Reads in a Rectangle from the specified input stream. Input format consists
// of: colour x-coordinate y-coordinate height width
std::istream & operator>>( std::istream & in, Rectangle & rectangle ){

    char c;
    int x, y, height, width;
    in >> c >> x >> y >> height >> width;

    rectangle.colour = translateColour(c);
    rectangle.point = {x, y};
    rectangle.height = height;
    rectangle.width = width;

    return in;
}

// Outputs a Rectangle to the specified output stream. Output format is:
// [colour (x,y) heightxwidth]
std::ostream & operator<<( std::ostream & out, const Rectangle & rectangle ){

    out << "[" << translateCol(rectangle.colour) << " " << rectangle.point;
    out << " " << rectangle.height << "x" << rectangle.width << "]";

    return out;
}

