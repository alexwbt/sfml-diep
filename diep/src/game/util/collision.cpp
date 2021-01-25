#include "../game.h"

namespace diep
{
    namespace coll
    {
        struct Point
        {
            float x, y;
            Point() : x(0), y(0) {}
            Point(float x, float y) : x(x), y(y) {}
        };

        bool collide(const object::Object& obj1, const object::Object& obj2)
        {
            int shape1 = (int)obj1.shape();
            int shape2 = (int)obj2.shape();
            switch (shape1 | shape2)
            {
            case 0b1: return circle_vs_circle(obj1, obj2);
            case 0b10: return polygon_vs_polygon(obj1, obj2);
            case 0b11: return shape1 == (int)object::Shape::kCircle ? circle_vs_polygon(obj1, obj2) : circle_vs_polygon(obj2, obj1);
            default: return false;
            }
        }

        bool circle_vs_circle(const object::Object& obj1, const object::Object& obj2)
        {
            return pow(obj1.x() - obj2.x(), 2) + pow(obj1.y() - obj2.y(), 2) < pow(obj1.radius() + obj2.radius(), 2);
        }

        bool polygon_vs_polygon(const object::Object& obj1, const object::Object& obj2)
        {
            return false;
        }

        bool circle_vs_polygon(const object::Object& obj1, const object::Object& obj2)
        {
            auto points = new Point[obj2.points()];
            sf::CircleShape polygon(obj2.radius(), obj2.points());
            polygon.setOrigin(obj2.radius(), obj2.radius());
            polygon.setRotation(obj2.rotate());
            for (uint8_t i = 0; i < obj2.points(); i++)
            {
                auto pt = polygon.getTransform().transformPoint(polygon.getPoint(0));
                points[i] = Point(pt.x, pt.y);
            }

            return false;
        }

        bool point_in_polygon(Point point, Point* polygon, uint8_t point_count)
        {

        }
    }
}
