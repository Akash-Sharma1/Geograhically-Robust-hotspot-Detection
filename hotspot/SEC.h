#include <algorithm>
#include <cmath>
#include <cstddef>
#include <random>

struct Circle final {
	public: static const Circle INVALID;
	private: static const double MULTIPLICATIVE_EPSILON;
	public:
	    coord c;   // Center
        double r;  // Radius
        int noofpoints;
	public: bool contains(const coord &p) const;
	public: bool contains(const vector<coord> &ps) const;

};


Circle makeSmallestEnclosingCircle(const vector<coord> &coords);
Circle makeDiameter(const coord &a, const coord &b);
Circle makeCircumCircle(const coord &a, const coord &b, const coord &c);

coord coord::subtract(const coord &p) const {
	return coord{x - p.x, y - p.y};
}
double coord::distance(const coord &p) const {
	return hypot(x - p.x, y - p.y);
}
double coord::cross(const coord &p) const {
	return x * p.y - y * p.x;
}

const Circle Circle::INVALID{coord{0, 0}, -1};
const double Circle::MULTIPLICATIVE_EPSILON = 1 + 1e-14;


bool Circle::contains(const coord &p) const {
	return c.distance(p) <= r * MULTIPLICATIVE_EPSILON;
}
bool Circle::contains(const vector<coord> &ps) const {
	for (const coord &p : ps) {
		if (!contains(p))
			return false;
	}
	return true;
}


/*---- Smallest enclosing Circle algorithm ----*/

static Circle makeSmallestEnclosingCircleOnecoord (const vector<coord> &coords, size_t end, const coord &p);
static Circle makeSmallestEnclosingCircleTwocoords(const vector<coord> &coords, size_t end, const coord &p, const coord &q);

static default_random_engine randGen((random_device())());


// Initially: No boundary coords known
Circle makeSmallestEnclosingCircle(const vector<coord> &coords) {
	// Clone list to preserve the caller's data, randomize order
	vector<coord> shuffled = coords;
	shuffle(shuffled.begin(), shuffled.end(), randGen);

	// Progressively add coords to Circle or recompute Circle
	Circle c = Circle::INVALID;
	for (size_t i = 0; i < shuffled.size(); i++) {
		const coord &p = shuffled.at(i);
		if (c.r < 0 || !c.contains(p))
			c = makeSmallestEnclosingCircleOnecoord(shuffled, i + 1, p);
	}
	return c;
}


// One boundary coord known
static Circle makeSmallestEnclosingCircleOnecoord(const vector<coord> &coords, size_t end, const coord &p) {
	Circle c{p, 0};
	for (size_t i = 0; i < end; i++) {
		const coord &q = coords.at(i);
		if (!c.contains(q)) {
			if (c.r == 0)
				c = makeDiameter(p, q);
			else
				c = makeSmallestEnclosingCircleTwocoords(coords, i + 1, p, q);
		}
	}
	return c;
}


// Two boundary coords known
static Circle makeSmallestEnclosingCircleTwocoords(const vector<coord> &coords, size_t end, const coord &p, const coord &q) {
	Circle circ = makeDiameter(p, q);
	Circle left  = Circle::INVALID;
	Circle right = Circle::INVALID;

	// For each coord not in the two-coord Circle
	coord pq = q.subtract(p);
	for (size_t i = 0; i < end; i++) {
		const coord &r = coords.at(i);
		if (circ.contains(r))
			continue;

		// Form a circumCircle and classify it on left or right side
		double cross = pq.cross(r.subtract(p));
		Circle c = makeCircumCircle(p, q, r);
		if (c.r < 0)
			continue;
		else if (cross > 0 && (left.r < 0 || pq.cross(c.c.subtract(p)) > pq.cross(left.c.subtract(p))))
			left = c;
		else if (cross < 0 && (right.r < 0 || pq.cross(c.c.subtract(p)) < pq.cross(right.c.subtract(p))))
			right = c;
	}

	// Select which Circle to return
	if (left.r < 0 && right.r < 0)
		return circ;
	else if (left.r < 0)
		return right;
	else if (right.r < 0)
		return left;
	else
		return left.r <= right.r ? left : right;
}


Circle makeDiameter(const coord &a, const coord &b) {
	coord c{(a.x + b.x) / 2, (a.y + b.y) / 2};
	return Circle{c, max(c.distance(a), c.distance(b))};
}


Circle makeCircumCircle(const coord &a, const coord &b, const coord &c) {
	// Mathematical algorithm from Wikipedia: Circumscribed Circle
	double ox = (min(min(a.x, b.x), c.x) + max(min(a.x, b.x), c.x)) / 2;
	double oy = (min(min(a.y, b.y), c.y) + max(min(a.y, b.y), c.y)) / 2;
	double ax = a.x - ox,  ay = a.y - oy;
	double bx = b.x - ox,  by = b.y - oy;
	double cx = c.x - ox,  cy = c.y - oy;
	double d = (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by)) * 2;
	if (d == 0)
		return Circle::INVALID;
	double x = ((ax*ax + ay*ay) * (by - cy) + (bx*bx + by*by) * (cy - ay) + (cx*cx + cy*cy) * (ay - by)) / d;
	double y = ((ax*ax + ay*ay) * (cx - bx) + (bx*bx + by*by) * (ax - cx) + (cx*cx + cy*cy) * (bx - ax)) / d;
	coord p{ox + x, oy + y};
	double r = max(max(p.distance(a), p.distance(b)), p.distance(c));
	return Circle{p, r};
}

