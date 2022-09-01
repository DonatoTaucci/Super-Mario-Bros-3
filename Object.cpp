#include "Object.h"
#include "Game.h"
#include "Mario.h"

Object::Object() : QGraphicsPixmapItem(0)
{
    collidable = true;
    collider_visible = false;

    // game mechanics are based on bounding rects only
    // this simplifies (a lot) collision detections, but could
    // be a limit if we have to implement tilted elements
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

    // add to scene
    Game::instance()->getScene()->addItem(this);
}

Direction Object::touchingDirection(Object* item)
{

    // get scene bounding rects
    QRectF curr_rect = mapRectToScene(shape().boundingRect());
    QRectF item_rect = item->mapRectToScene(item->shape().boundingRect());

    // calculate intersection rectangle (IR)
    int xi0 = std::max(curr_rect.x(), item_rect.x());
    int yi0 = std::max(curr_rect.y(), item_rect.y());
    int xi1 = std::min(curr_rect.x() + curr_rect.width(), item_rect.x() + item_rect.width());
    int yi1 = std::min(curr_rect.y() + curr_rect.height(), item_rect.y() + item_rect.height());

    // IR is null along horizontal axis and non-null along vertical
    // --> horizontal touch
    if (xi0 == xi1 && yi1 > yi0)
    {
        // horizontal touch coordinate coincides with left side of current rectangle
        if (xi0 == curr_rect.x())
            return LEFT;
        else
            return RIGHT;
    }
    // IR is null along vertical axis and non-null along horizontal
    // --> vertical touch
    else if (yi0 == yi1 && xi1 > xi0)
    {
        // vertical touch coordinate coincides with top side of current rectangle
        if (yi0 == curr_rect.y())
            return UP;
        else
            return DOWN;
    }

    return UNKNOWN;
}

Direction Object::collisionDirection(Object* item)
{
    QRectF curr_rect = mapRectToScene(shape().boundingRect());
    QRectF item_rect = item->mapRectToScene(item->shape().boundingRect());

    // w/o intersection, we cannot detect collision direction
    if (!curr_rect.intersects(item_rect))
        return UNKNOWN;

    // calculate intersection rectangle (IR)
    QRectF interRect = curr_rect.intersected(item_rect);

    Mario* mario = Game::instance()->getMario();

    // reject corner-corner collisions since we are not able
    // to determine collision direction
    if (interRect.width() <= 1 && interRect.height() <= 1)
        return UNKNOWN;

    // IR is vertical
    // --> collision is horizontal
    if (interRect.width() < interRect.height())
    {
        // left side of IR coincides with left side of current rectangle
        if (interRect.left() == curr_rect.x())
            return LEFT;

        else
            return RIGHT;
    }
    // intersection rectangle is horizontal
    // --> collision is vertical
    else
    {
        // top side of IR coincides with top side of current rectangle
        if (interRect.top() == curr_rect.y())
            return UP;

        else
            return DOWN;
    }
}

void Object::hit(Object* what, Direction fromDir)
{
    static int hit_count = 0;
}

// show / hide collider
void Object::toogleColliderVisible()
{
    if (collidable)
    {
        if (!collider_visible)
        {
            collider_visible = true;
            (new QGraphicsRectItem(shape().boundingRect(), this))->setPen(QPen(QBrush(Qt::red), 1));
        }

        else
        {
            collider_visible = false;
            for (auto& i : childItems())
                delete i;
            childItems().clear();
        }
    }
}