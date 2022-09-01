#include "Terrain.h"
#include "Sprites.h"
#include <QBrush>
#include <QPainter>

Terrain::Terrain(QRect rect) : Inert()
{
	//texture
	QPixmap collage(rect.width(), rect.height());
	QPainter painter(&collage);

	// corners
	painter.drawPixmap(0, 0, Sprites::instance()->get("terrain-L"));
	painter.drawPixmap(rect.width() - 16, 0, Sprites::instance()->get("terrain-R"));
	// center
	for (int x = 16; x <= rect.width() - 32; x += 16)
		painter.drawPixmap(x, 0, Sprites::instance()->get("terrain-C"));

	painter.end();

	// make background color (224, 163, 216) transparent
	collage.setMask(collage.createMaskFromColor(QColor(224, 163, 216)));

	//set starting pixmap, position and Z value
    setPixmap(collage);
	setPos(QPoint(rect.x(), rect.y()));
	setZValue(2);
}
