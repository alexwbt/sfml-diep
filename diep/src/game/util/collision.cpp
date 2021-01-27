#include "../game.h"

namespace diep
{
    namespace coll
    {
        bool collide(object::Object& obj1, object::Object& obj2)
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

        bool circle_vs_circle(object::Object& obj1, object::Object& obj2)
        {
            return pow(obj1.x() - obj2.x(), 2) + pow(obj1.y() - obj2.y(), 2) < pow(obj1.radius() + obj2.radius(), 2);
        }

        bool polygon_vs_polygon(object::Object& obj1, object::Object& obj2)
        {
            auto p1 = obj1.GetPoints();
            auto p2 = obj2.GetPoints();
            for (const auto& p : *p1)
                if (point_in_polygon(p.x, p.y, *p2))
                    return true;
            for (const auto& p : *p2)
                if (point_in_polygon(p.x, p.y, *p1))
                    return true;
            return false;
        }

        bool circle_vs_polygon(object::Object& obj1, object::Object& obj2)
        {
            auto points = obj2.GetPoints();
            for (size_t i = 0; i < points->size(); i++)
                if (circle_vs_line(obj1.radius(), obj1.x(), obj1.y(), points->at(i).x, points->at(i).y,
                    points->at((i + 1) % points->size()).x, points->at((i + 1) % points->size()).y))
                    return true;
            return false;
        }

        bool point_in_polygon(float x, float y, const std::vector<Point>& points)
        {
            bool result = false;
            for (size_t i = 0, j = points.size() - 1; i < points.size(); j = i++)
                if ((points[i].y > y) != (points[j].y > y)
                    && (x < (points[j].x - points[i].x) * (y - points[i].y) / (points[j].y - points[i].y) + points[i].x))
                    result = !result;
            return result;
        }

        bool point_in_circle(float radius, float cx, float cy, float x, float y)
        {
            return pow(cx - x, 2) + pow(cy - y, 2) < pow(radius, 2);
        }

        bool circle_vs_line(float radius, float cx, float cy, float x1, float y1, float x2, float y2)
        {
            float rx1 = std::min(x1, x2), ry1 = std::min(y1, y2), rx2 = std::max(x1, x2), ry2 = std::max(y1, y2);
            if (!circle_vs_rect(radius, cx, cy, rx1, ry1, rx2, ry2)) return false;
            float z = (x2 - cx) - (x1 - cx), w = (y2 - cy) - (y1 - cy), k = sqrt(z * z + w * w);
            return pow(radius * k, 2) - pow((x1 - cx) * (y2 - cy) - (x2 - cx) * (y1 - cy), 2) >= 0;
        }

        bool circle_vs_rect(float radius, float cx, float cy, float rx1, float ry1, float rx2, float ry2)
        {
            float px = std::min(rx2, std::max(rx1, cx));
            float py = std::min(ry2, std::max(ry1, cy));
            return point_in_circle(radius, cx, cy, px, py);
        }

        std::shared_ptr<std::vector<Point>> polygon_get_points(float x, float y, float radius, float points, float rotate)
        {
            auto pts = std::make_shared<std::vector<Point>>();
            for (int i = 0; i < points; i++)
            {
                float dir = math::PI * 2 * (float)i / (float)points - (rotate + 180) * math::PI / 180.0f;
                float px = x + sin(dir) * radius;
                float py = y + cos(dir) * radius;
                pts->push_back({ px, py });
            }
            return pts;
        }
    }
}
