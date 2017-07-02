class Point { // 点
public:
	double x, y;
	Point(double x = 0, double y = 0):x(x), y(y){}
	Point operator + (Point p) { return Point(x + p.x, y + p.y); }
	Point operator - (Point p) { return Point(x - p.x, y - p.y); }
	Point operator * (double a) { return Point(a * x, a * y); }
	Point operator / (double a) { return Point(x / a, y / a); }
	double abs() const { return sqrt(norm()); }
	double norm() const { return x * x + y * y; }
	// bool operator < (const Point &p) const { return x != p.x ? x < p.x : y < p.y; }
	bool operator < (const Point &p) const { // 誤差を許容して比較
		return x + EPS < p.x || (eq<double>(x, p.x) && y + EPS < p.y);
	}
	bool operator == (const Point &p) const { return (eq<double>(x, p.x) && eq<double>(y, p.y)); }
};
using Vector = Point;
using Polygon = vector<Point>; // 多角形

double dot(const Vector& a, const Vector& b) { return a.x * b.x + a.y * b.y; } // ベクトルaとbの内積
double cross(const Vector& a, const Vector& b) { return a.x * b.y - a.y * b.x; } // ベクトルaとbの外積
double length2(const Point& a) { return a.norm(); } // 通常の長さの2乗
double length(const Point& a) { return a.abs(); } // 通常の長さ
Point rotationalTransfer(Point c, double r, double deg) { // cを中心として半径rの円周上のdeg度の位置座標
	double rad = PI * deg / 180.0; return c + Point(cos(rad), sin(rad)) * r;
}

enum ccw_t {
	COUNTER_CLOCKWISE = 1, // p0->p1 反時計回りの方向にp2
	CLOCKWISE = -1, // p0->p1 時計回りの方向にp2
	ONLINE_BACK = 2, // p2->p0->p1 の順で直線上でp2
	ONLINE_FRONT = -2, // p0->p1->p2 の順で直線上p2
	ON_SEGMENT = 0, // p0->p2->p1 の順で線分p0p1上にp2
};
ccw_t ccw(Point p0, Point p1, Point p2) {
	Vector a = p1 - p0, b = p2 - p0;
	if ( cross(a, b) > EPS  )  return COUNTER_CLOCKWISE;
	if ( cross(a, b) < -EPS )  return CLOCKWISE;
	if ( dot(a, b) < -EPS )    return ONLINE_BACK;
	if ( a.norm() < b.norm() ) return ONLINE_FRONT;
	return ON_SEGMENT;
}

class Segment { //線分
public:
	Point p1, p2;
	Segment(){}
	Segment(Point p1, Point p2):p1(p1), p2(p2){}
};
using Line = Segment;

// *** 線分の交差判定 ***
bool intersect(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
	return ( ccw(p1, p2, p3) * ccw(p1, p2, p4) <= 0 && 
			 ccw(p3, p4, p1) * ccw(p3, p4, p2) <= 0 );
}
bool intersect(const Segment& s1, const Segment& s2) { // 交差していたらtrue
	return intersect(s1.p1, s1.p2, s2.p1, s2.p2);
}
//*** 線分の交点 ***
Point getCrossPoint(Segment s1, Segment s2) { // 線分の交点が存在するから調べた後つかうこと
	Vector base = s2.p2 - s2.p1;
	double d1 = abs(cross(base, s1.p1 - s2.p1)), d2 = abs(cross(base, s1.p2 - s2.p1));
	double t  = d1 / (d1 + d2);
	return s1.p1 + (s1.p2 - s1.p1) * t;
}
// *** 距離 ***
double getDistance(Point& a, Point& b) { // 点aと点bの距離
	return length(a - b);
}
double getDistanceLP(Line& l, Point& p) { // 直線sと点pの距離
	return length(cross(l.p2 - l.p1, p - l.p1) / length(l.p2 - l.p1));
}
double getDistanceSP(Segment s, Point p) { // 線分sと点pの距離
	if( dot(s.p2 - s.p1, p - s.p1) < EPS ) return length(p - s.p1);
	if( dot(s.p1 - s.p2, p - s.p2) < EPS ) return length(p - s.p2);
	return getDistanceLP(s, p);
}
double getDistanceSS(Segment s1, Segment s2) { // 線分s1と線分s2の交点
	if( intersect(s1, s2) ) return 0.0; //交わっているとき
	return min(min(getDistanceSP(s1, s2.p1), getDistanceSP(s1, s2.p2)),
			   min(getDistanceSP(s2, s1.p1), getDistanceSP(s2, s1.p2)));
}

class Rectangle { // 長方形
public:
	// 3 2
	// 0 1 (反時計回りに長方形の頂点をいれること)
	vector<Point> p; // 点を順番にいれること
	Rectangle(vector<Point>&p):p(p) {
		rep(i, 3) reps(j, i + 1, 4) { //適当な順番にいれても大丈夫なように?
			int cnt = 0;
			rep(k, 4) if(k != i && k != j) {
				cnt += ccw(p[i], p[j], p[k]) == COUNTER_CLOCKWISE;
			}
			if(cnt == 2) {
				swap(p[i + 1], p[j]);
				break;
			}
		}
	}
	bool intersect(const Segment& s) { // 線分sと長方形の少なくとも1辺が交差していればtrue
		bool flag = false;
		rep(i, 4) flag |= ::intersect(s, Segment(p[i], p[(i + 1) % 4]));
		return flag;
	}
	bool contain(const Point& pp) { // 点ppが長方形内に含まれれば(辺を含まない)true
		bool flag = true;
		rep(i, 4) flag &= ccw(p[i], p[(i + 1) % 4], pp) == COUNTER_CLOCKWISE;
		return flag;
	}
	bool contain(const Segment& s) { // 線分sが長方形内に含まれれば(辺を含まない)true
		return contain(s.p1) && contain(s.p2);
	}
};
/*
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2009
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1157&lang=jp
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2402
*/