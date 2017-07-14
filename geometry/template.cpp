class Point { // 点
public:
    double x, y;
    Point(double x = 0, double y = 0):x(x), y(y){}
    Point operator + (Point p) const { return Point(x + p.x, y + p.y); }
    Point operator - (Point p) const { return Point(x - p.x, y - p.y); }
    Point operator * (double a) const { return Point(a * x, a * y); }
    Point operator / (double a) const { return Point(x / a, y / a); }
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
// (x, y, z) の点を光源(xy座標での角度がtheta度, xy平面からz方向への角度がphi度の時の)からてらした時の影のxy座標
Point Shadow(double x, double y, double z, double theta, double phi) {
    theta = PI * theta / 180.0, phi = PI * phi / 180.0;
    return Point(x - z / tan(phi) * cos(theta), y - z / tan(phi) * sin(theta));
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

// *** 多角形 ***
// IN := 2, ON := 1, OUT := 0
vector<Segment> getPolygonSegument(const Polygon& p) { //多角形の点から多角形の辺を求める
    vector<Segment> ret;
    rep(i, p.size() - 1) ret.push_back(Segment(p[i], p[i + 1]));
    ret.push_back(Segment(p[p.size() - 1], p[0]));
    return ret;
}
int contains(const Polygon& g, const Point& p){ // 多角形gの中に点pが含まれているか
    int n = g.size(); bool x = false;
    for (int i = 0; i < n; ++i) {
        Point a = g[i] - p, b = g[(i + 1) % n] - p;
        if ( abs(cross(a, b)) < EPS && dot(a, b) < EPS ) return 1;
        if (a.y > b.y) swap(a, b);
        if (a.y < EPS && EPS < b.y && cross(a, b) > EPS ) x = !x;
    }
    return (x ? 2 : 0);
}
Polygon andrewScan(Polygon s) { // 凸包(最も左にある頂点から)
    Polygon u, l;
    if (s.size() < 3) return s;
    sort(s.begin(), s.end()); // x, yを基準に昇順ソート
    // xが小さいものから2つ u に追加
    u.push_back(s[0]), u.push_back(s[1]);
    // x が大きいものから2つ1に追加
    l.push_back(s[s.size() - 1]), l.push_back(s[s.size() - 2]);
    // 凸包の上部を生成
    for (int i = 2; i < s.size(); i++) {
        for (int n = u.size(); n >= 2 && ccw(u[n - 2], u[n - 1], s[i]) != CLOCKWISE; n--){
            u.pop_back();
        }
        u.push_back(s[i]);
    }
    // 凸包の下部を生成
    for (int i = s.size() - 3; i >= 0; i--) {
        for (int n = l.size(); n >= 2 && ccw(l[n - 2], l[n - 1], s[i]) != CLOCKWISE; n--){
            l.pop_back();
        }
        l.push_back(s[i]);
    }
    // 時計回りになるように凸包の点の列を生成
    reverse(l.begin(), l.end());
    for (int i = u.size() - 2; i >= 1; i--) l.push_back(u[i]);
    return l;
}


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
double getDistanceSS(const Segment& s1, const Segment& s2) { // 線分s1と線分s2の交点
    if( intersect(s1, s2) ) return 0.0; //交わっているとき
    return min(min(getDistanceSP(s1, s2.p1), getDistanceSP(s1, s2.p2)),
               min(getDistanceSP(s2, s1.p1), getDistanceSP(s2, s1.p2)));
}
double getDistancePolP(const Polygon& pol, const Point& p) { // 多角形polと点pの距離
    if(contains(pol, p) != 0) return 0.0; // 点が多角形の内部に含まれている
    double ret = 1e9;
    for(Segment& u : getPolygonSegument(pol)) ret = min(ret, getDistanceSP(u, p));
    return ret;
}
double getDistancePolPol(const Polygon& p1, const Polygon& p2) { // 多角形p1とp2の距離
    for(const Point& p : p1) if(contains(p2, p) != 0) return 0.0; // p1の点が多角形p2の中に含まれている
    for(const Point& p : p2) if(contains(p1, p) != 0) return 0.0; // p2の点が多角形p1の中に含まれている
    double ret = 1e9;
    for(const Segment& u : getPolygonSegument(p1))for(const Segment& v : getPolygonSegument(p2)) {
        ret = min(ret, getDistanceSS(u, v));
    }
    return ret;
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


class Circle {
public:
	Point c;
	double r;
	Circle(Point c = Point(), double r = 0.0):c(c), r(r) {}
}
double arg(Vector p) { return atan2(p.y, p.x); }
Vector polar(double a, double b) { return Point(cos(r) * a, sin(r) * a); }
pair<Point, Point> getCrossPoints(Circle c1, Circle c2) {
	assert(intersect(c1, c2));
	double b = abs(c1.c - c2.c);
	double a = acos(c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d);
	double t = arg(c2.c - c1.c);
	return make_pair(c1.c + polar(c1.r, t + a), c1.c + polar(c1.r, t - a));
}

/*
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2009
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1157&lang=jp
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2402
*/