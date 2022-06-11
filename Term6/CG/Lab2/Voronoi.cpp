#include "Voronoi.hpp"

void Voronoi::processPoint() {
  Point p = points.top();
  points.pop();

  frontInsert(p);
}

void Voronoi::processEvent() {
  Event *e = events.top();
  events.pop();

  if (e->valid) {
    Segment *s = new Segment(e->p, output);

    Arc *a = e->a;
    if (a->prev) {
      a->prev->next = a->next;
      a->prev->s1 = s;
    }
    if (a->next) {
      a->next->prev = a->prev;
      a->next->s0 = s;
    }

    if (a->s0) a->s0->finish(e->p);
    if (a->s1) a->s1->finish(e->p);

    if (a->prev) checkCircleEvent(a->prev, e->x);
    if (a->next) checkCircleEvent(a->next, e->x);
  }
  delete e;
}

void Voronoi::frontInsert(Point p) {
  if (!root) {
    root = new Arc(p);
    return;
  }

  for (Arc *i = root; i; i = i->next) {
    Point z, zz;
    if (intersect(p, i, &z)) {
      if (i->next && !intersect(p, i->next, &zz)) {
        i->next->prev = new Arc(i->p, i, i->next);
        i->next = i->next->prev;
      } else i->next = new Arc(i->p, i);
      i->next->s1 = i->s1;

      i->next->prev = new Arc(p, i, i->next);
      i->next = i->next->prev;

      i = i->next;

      i->prev->s1 = i->s0 = new Segment(z, output);
      i->next->s0 = i->s1 = new Segment(z, output);

      checkCircleEvent(i, p.x);
      checkCircleEvent(i->prev, p.x);
      checkCircleEvent(i->next, p.x);

      return;
    }
  }

  Arc *i;
  for (i = root; i->next; i = i->next);

  i->next = new Arc(p, i);
  Point start;
  start.x = X0;
  start.y = (i->next->p.y + i->p.y) / 2;
  i->s1 = i->next->s0 = new Segment(start, output);
}

void Voronoi::checkCircleEvent(Arc *i, double x0) {
  if (i->e && i->e->x != x0)
    i->e->valid = false;
  i->e = NULL;

  if (!i->prev || !i->next)
    return;

  double x;
  Point o;

  if (circle(i->prev->p, i->p, i->next->p, &x, &o) && x > x0) {
    i->e = new Event(x, o, i);
    events.push(i->e);
  }
}

bool Voronoi::circle(Point a, Point b, Point c, double *x, Point *o) {
  if ((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y) > 0)
    return false;

  double A = b.x - a.x, B = b.y - a.y,
      C = c.x - a.x, D = c.y - a.y,
      E = A * (a.x + b.x) + B * (a.y + b.y),
      F = C * (a.x + c.x) + D * (a.y + c.y),
      G = 2 * (A * (c.y - b.y) - B * (c.x - b.x));

  if (G == 0) return false;

  o->x = (D * E - B * F) / G;
  o->y = (A * F - C * E) / G;

  *x = o->x + sqrt(pow(a.x - o->x, 2) + pow(a.y - o->y, 2));
  return true;
}

bool Voronoi::intersect(Point p, Arc *i, Point *res) {
  if (i->p.x == p.x) return false;

  double a, b;
  if (i->prev)
    a = intersection(i->prev->p, i->p, p.x).y;
  if (i->next)
    b = intersection(i->p, i->next->p, p.x).y;

  if ((!i->prev || a <= p.y) && (!i->next || p.y <= b)) {
    res->y = p.y;

    res->x =
        (i->p.x * i->p.x + (i->p.y - res->y) * (i->p.y - res->y) - p.x * p.x)
        / (2 * i->p.x - 2 * p.x);

    return true;
  }
  return false;
}

Voronoi::Point Voronoi::intersection(Point p0, Point p1, double l) {
  Point res, p = p0;

  if (p0.x == p1.x)
    res.y = (p0.y + p1.y) / 2;
  else if (p1.x == l)
    res.y = p1.y;
  else if (p0.x == l) {
    res.y = p0.y;
    p = p1;
  } else {

    double z0 = 2 * (p0.x - l);
    double z1 = 2 * (p1.x - l);

    double a = 1 / z0 - 1 / z1;
    double b = -2 * (p0.y / z0 - p1.y / z1);
    double c = (p0.y * p0.y + p0.x * p0.x - l * l) / z0
               - (p1.y * p1.y + p1.x * p1.x - l * l) / z1;

    res.y = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
  }

  res.x =
      (p.x * p.x + (p.y - res.y) * (p.y - res.y) - l * l) / (2 * p.x - 2 * l);
  return res;
}

void Voronoi::finishEdges() {
  double l = X1 + (X1 - X0) + (Y1 - Y0);

  for (Arc *i = root; i->next; i = i->next)
    if (i->s1)
      i->s1->finish(intersection(i->p, i->next->p, l * 2));
}

void Voronoi::printOutput() {
  cout << "Bounding box:\n"<< X0 << " " << X1 << " " << Y0 << " " << Y1
  << "\n\nSegments:" << endl;

  vector<Segment *>::iterator i;
  for (i = output.begin(); i != output.end(); i++) {
    Point p0 = (*i)->start;
    Point p1 = (*i)->end;
    cout << p0.x << " " << p0.y << " " << p1.x << " " << p1.y << endl;
  }
}

Voronoi::Voronoi(const vector<Point> &p) {
  for (auto a: p) {
    points.push(a);
  }
}

void Voronoi::run() {
  double dx = (X1 - X0 + 1) / 5.0, dy = (Y1 - Y0 + 1) / 5.0;
  X0 -= dx;
  X1 += dx;
  Y0 -= dy;
  Y1 += dy;

  while (!points.empty())
    if (!events.empty() && events.top()->x <= points.top().x)
      processEvent();
    else
      processPoint();

  while (!events.empty())
    processEvent();

  finishEdges();
}