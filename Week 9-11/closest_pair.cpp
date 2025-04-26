#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

using std::vector, std::pair;

class Point {
    public:
    double x;
    double y;

    // needed for containers like std::pair
    Point() = default;
    // needed for emplace back
    Point(double x_val, double y_val) : x(x_val), y(y_val) {};

    void print() const {
        std::cout << x << ", " << y << "\n";
    }

    // short function to read data, beware, not sanity checks
    static vector<Point> readPointsFromFile(const std::string& filename){
        vector<Point> res;
        std::ifstream file(filename);
        double x,y;
        while(file >> x >> y){
            res.emplace_back(x, y);
        }
        return res;
    }
};

// lexicographic order, first compare x then y
bool xComp(const Point& a, const Point& b){
    if (a.x < b.x) return true;
    if (a.x > b.x) return false;
    return a.y < b.y;

}

// lexicographic order, first compare y then x
bool yComp(const Point& a, const Point& b){
    if(a.y < b.y) return true;
    if(a.y > b.y) return false;
    return a.x < b.x; 
}

double distance(const Point& a, const Point& b){
    // can also be more robustly implemented via std::hypot, but do not care about that here
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

double closestInStrip(const vector<Point>& strip, const double dist, pair<Point, Point>& bestPair){
    double minDist = dist;

    // for all vertices check all that are below/above and not too far
    for(size_t i = 0; i < strip.size(); i++){
        // note, that we could even change dist to minDist
        for(size_t j = i + 1; j < strip.size() and std::abs(strip.at(i).y - strip.at(j).y) < dist; j++){
            double localDist = distance(strip.at(i), strip.at(j));
            if(localDist < minDist){
                minDist = localDist;
                bestPair = {strip.at(i), strip.at(j)};
            }
            
        }
    }
    return minDist;
}

// left and right index the field sorted by x coo, PsX are Points Sorted by X, PsY is analogous
double closestDistanceReccurent(const vector<Point>& PsX, const vector<Point>& PsY, size_t left, size_t right,
    pair<Point, Point>& bestPair){
        // bruteforce solution
    if(right - left < 4){
        // initialize search for minimal distance, it will get recomputed in the loop but who cares
        double minDist = distance(PsX.at(left), PsX.at(left+1));
        double dist;
        for(size_t i = left; i < right; i++){
            for(size_t j = i +1; j < right; j++){
                dist = distance(PsX.at(i), PsX.at(j));
                if(dist < minDist){
                    minDist = dist;
                    bestPair = {PsX.at(i), PsX.at(j)};
                }
            }
        }
        return minDist;
    }

    size_t mid = (left + right) / 2;
    Point midPoint = PsX.at(mid);

    // select relevant points in the y-sorted array
    vector<Point> PsYleft, PsYright;
    for(const Point& p : PsY){
        if(p.x < midPoint.x){
            PsYleft.push_back(p);
        } else {
            PsYright.push_back(p);
        }
    }

    double minDistLeft = closestDistanceReccurent(PsX, PsYleft, left, mid, bestPair);
    double minDistRight = closestDistanceReccurent(PsX, PsYright, mid, right, bestPair);
    double minDist = std::min(minDistLeft, minDistRight);

    vector<Point> strip;
    for(const Point& p: PsY){
        if( std::abs(p.x - midPoint.x) < minDist){
            strip.push_back(p);
        }
    }
    double stripDist = closestInStrip(strip, minDist, bestPair);
    return std::min(minDist, stripDist);
}

double closestDistance(vector<Point>& points, pair<Point, Point>& bestPair){
    if(points.size() < 2){
        std::cerr << "Closest distance needs at least two points\n";
        return -1;
    }
    vector<Point> sortedByX = points;
    vector<Point> sortedByY = points;

    std::sort(sortedByX.begin(), sortedByX.end(), xComp);
    std::sort(sortedByY.begin(), sortedByY.end(), yComp);

    return closestDistanceReccurent(sortedByX, sortedByY, 0, points.size(), bestPair);
}

int main(int argc, char* argv[]){
    if(argc < 2){
        std::cerr << "Pls no\n";
        return 1;
    }
    std::string filename(argv[1]);
    std::vector<Point> points = Point::readPointsFromFile(filename);
    
    pair<Point, Point> solution;
    double dist = closestDistance(points, solution);

    std::cout << dist << "\n";
    solution.first.print();
    solution.second.print();
    return 0;
}