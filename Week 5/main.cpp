#include <vector>
#include <iostream>
#include <cmath>
#include <limits>
#include <random>

using std::vector, std::sqrt;

class Point {
    public:
    double x, y;

    Point() : x(0), y(0) {} // Default taken as point (0,0)

    Point(double x_in, double y_in) : x(x_in), y(y_in) {}

    void print() const {
        std::cout << "(" << x << ", " << y << ")\n";
    }

    static double distance(const Point& p1, const Point& p2) {
        return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
    }

    // This is enough to find the closest pair as sqrt is monotonic and increasing
    static double distanceSquared(const Point& p1, const Point& p2) {
        return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
    }

};

std::pair<Point, Point> closestPairBruteforce(const vector<Point>& points) {
    double minDist = std::numeric_limits<double>::max(); // or DOUBLE_MAX
    std::pair<Point, Point> closestPair;

    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            double dist = Point::distanceSquared(points[i], points[j]);
            if (dist < minDist) {
                minDist = dist;
                closestPair = {points[i], points[j]};
            }
        }
    }

    return closestPair;
}

vector<Point> generateRandomPoints(size_t n, double minVal, double maxVal, int seed = 42) {
    vector<Point> points;
    std::mt19937 gen(seed); // seeded by int for simplicity, correct way is seed_seq
    std::uniform_real_distribution<double> dis(minVal, maxVal);

    for (size_t i = 0; i < n; ++i) {
        double x = dis(gen);
        double y = dis(gen);
        points.emplace_back(x, y);
    }

    return points;
}

int main() {
    size_t numPoints = 1e3;
    double minVal = -1.0e3;
    double maxVal = 1.0e3;

    vector<Point> points = generateRandomPoints(numPoints, minVal, maxVal);

    auto closestPair = closestPairBruteforce(points);
    std::cout << "Closest pair:\n";
    closestPair.first.print();
    closestPair.second.print();
    std::cout << "\nDistance: " << Point::distance(closestPair.first, closestPair.second) << std::endl;

    return 0;
}