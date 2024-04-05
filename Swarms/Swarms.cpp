#include "Swarms.hpp"

Swarmer::Swarmer() : gridder(this) {
  iconOut.setCol(Colour(68, 68, 68));
  iconBack.setCol(Colour(100, 235, 255));
  dir = Vec2f_randNorm();
}

void Swarmer::setPos(Vec2f p) {
  pos = p;
  iconBack.setPos(p, dir);
  iconOut.setPos(p, dir);
  gridder.setPos(p);
}

void Swarmer::update() {
  Vec2f goal;
  Vec2f align, cohere, separate;

  int num = 0;
  Swarmer *n;
  gridder.resetLocals();
  while (gridder.pollLocals((void **)&n)) {
    if (n == this)
      continue;
    const Vec2f npos = n->pos;
    const Vec2f ndir = n->dir;
    const Vec2f nvec = npos - pos;

    const float d2 = nvec.len2();
    if (d2 > 6 * 6)
      continue;

    // vision
    if (fabs(dir.thetaTo(nvec)) > 0.8 * M_PI)
      continue;

    // 1.) alignment
    align += ndir;

    // 2.) coherence
    cohere += nvec;

    // 3.) seperation
    float invd2 = 1.0 / d2;
    if (!isnanf(invd2)) {
      CLAMP(invd2, 0, 100);
      separate += nvec * invd2;
    }

    num++;
  }

  if (num > 0) {
    cohere /= num; // avergage position
    align /= num;  // average  direction

    goal += align * alignment;
    goal += cohere * cohesion;
    goal -= separate * separation;
  }

  goal += wall;

  dir = dir + goal * 0.2;
  dir.normalise();
  vel = dir * speed;
}

Swarmer *Swarms::newSwarmer() {
  Swarmer *s = new Swarmer;
  s->iconBack.setIcon(shipBack);
  s->iconOut.setIcon(shipOut);
  s->gridder.setGrid(grid);
  s->setPos(Vec2f_rand(grid.rect()));
  swarmers.add(s);
  return s;
}

Swarms::Swarms() : grid(Rectf(300, 200), 6) {
  shipOut.loadFile("Soup/Resources/Ship_Outline.png");
  shipBack.loadFile("Soup/Resources/Ship_Background.png");
}

Vec2f Swarms::wall(Vec2f pos) {
  const Rectf rec = grid.rect();
  const float distL = pos.x - rec.x;
  const float distR = rec.xopp() - pos.x;
  const float distT = pos.y - rec.y;
  const float distB = rec.yopp() - pos.y;

  const float amp = 0.05;
  const float peak = 40;
  const float max = 20;
  const float min = 0;

  float left = amp * (peak - distL);
  float right = amp * (peak - distR);
  float top = amp * (peak - distT);
  float bottom = amp * (peak - distB);

  CLAMP(left, min, max);
  CLAMP(right, min, max);
  CLAMP(top, min, max);
  CLAMP(bottom, min, max);

  return Vec2f(left - right, top - bottom);
}

void Swarms::update() {
  for (int i = 0; i < swarmers.count; i++) {
    Swarmer *s = swarmers[i];

    s->wall = wall(s->pos);
    s->alignment = alignment;
    s->cohesion = cohesion;
    s->separation = separation;
    s->speed = speed;
    s->update();
    Vec2f pos = s->pos + s->vel;
    pos.clamp(grid.rect());
    s->setPos(pos);
  }
}

void Swarms::draw(sf::RenderTarget &target) {
  shipBack.draw(target);
  shipOut.draw(target);
}
