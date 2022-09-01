#pragma once

#include <QPoint>
#include <QPixmap>
#include <QBitmap>
#include <QColor>
#include <string>

// direction type and related utility functions
enum Direction {UNKNOWN, RIGHT, LEFT, UP, DOWN};

static std::string dir2str(Direction dir)
{
	if(dir == RIGHT)
		return "RIGHT";
	else if(dir == LEFT)
		return "LEFT";
	else if(dir == UP)
		return "UP";
	else if(dir == DOWN)
		return "DOWN";
	else
		return "UNKNOWN";
}

static Direction inverse(Direction dir)
{
    if(dir == RIGHT)
        return LEFT;
    else if(dir == LEFT)
        return RIGHT;
    else if(dir == UP)
        return DOWN;
    else if(dir == DOWN)
        return UP;
    else
        return UNKNOWN;
}

// return true if the given 'str' ends with 'end'
static bool strends (std::string const &str, std::string const &end)
{
	if (str.length() >= end.length()) 
		return (0 == str.compare (str.length() - end.length(), end.length(), end));

	else
		return false;
}

// load texture with transparency using the given color as mask
static QPixmap loadTextureTransparent(const std::string & file, QColor mask_color = Qt::magenta)
{
	QPixmap pixmap(file.c_str());
	pixmap.setMask(pixmap.createMaskFromColor(mask_color));
	return pixmap;
}

// load texture from image file 
// transparent pixel are identified with the given color
// if an image format not supporting transparency is used (e.g. like .bmp)
static QPixmap loadTexture(const std::string file, QColor mask_color = Qt::magenta)
{
	return loadTextureTransparent(file, mask_color);
}
