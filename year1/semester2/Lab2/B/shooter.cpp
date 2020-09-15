#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <array>

constexpr uint16_t length = 40;
constexpr uint16_t width = 1280;
constexpr uint16_t height = 720;

//Object type
struct Object {
  enum {
    space, med, enemy, trap
  } type;
  int8_t hp = 100;
  int vel = rand()%2 * 2 -1;
};

struct Player {
  uint16_t xp = 0;
  int16_t pos = length/2;
  int8_t dir = 1;
  float hp = 100;
};

class Bullet {
public:
  float pos;
  int vel;
  Bullet(int pos, int vel) : pos(pos), vel(vel) {}
};

void reset(std::array<Object, length> &map,
        std::vector<Bullet> &bullets, Player &pl) {

  map = std::array<Object, length>();

  for (auto &a : map) {
    a.type = Object::space;
  }
  for (int i = 0; i < 3; ++i) {
    map[rand() % length].type = Object::med;
  }
  for (int i = 0; i < 4; ++i) {
    map[rand() % length].type = Object::trap;
  }
  for (int i = 0; i < 2; ++i) {
    map[rand() % length].type = Object::enemy;
  }

  bullets.clear();
  pl.pos = length / 2;
  pl.hp = 100;
}

void kill(std::array<Object, length> &map,
           std::vector<Bullet> &bullets, Player &pl) {
  reset(map, bullets, pl);
  pl.xp = 0;
}

int main() {
  sf::RenderWindow window(sf::VideoMode(width, height), "2D Shooter!");
  sf::Clock timer;

  //Init text labels
  sf::Font font;
  font.loadFromFile("../res/ARCADECLASSIC.TTF");

  sf::Text hptext;
  hptext.setPosition(40, 0);
  hptext.setCharacterSize(120);
  hptext.setFillColor(sf::Color::White);
  hptext.setFont(font);

  sf::Text xptext;
  xptext.setPosition(900, 0);
  xptext.setCharacterSize(120);
  xptext.setFillColor(sf::Color::White);
  xptext.setFont(font);

  sf::Text gameover;
  gameover.setPosition(60, 200);
  gameover.setCharacterSize(240);
  gameover.setFillColor(sf::Color::White);
  gameover.setString("GAME OVER!");
  gameover.setFont(font);

  //Textures load
  sf::Texture tRevolver;
  tRevolver.loadFromFile("../res/revolver.png");

  sf::Texture tEnemy;
  tEnemy.loadFromFile("../res/enemy.png");

  sf::Texture tMed;
  tMed.loadFromFile("../res/med.png");

  sf::Texture tSpikes;
  tSpikes.loadFromFile("../res/spikes.png");

  //Map and player
  std::array<Object, length> map;
  std::vector<Bullet> bullets;
  Player pl;

  reset(map, bullets, pl);


  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::KeyPressed:
          if (event.key.code == sf::Keyboard::Left) {
            --pl.pos;
            pl.dir = -1;
          }
          if (event.key.code == sf::Keyboard::Right) {
            ++pl.pos;
            pl.dir = 1;
          }
          if (event.key.code == sf::Keyboard::Space) {
            bullets.emplace_back(Bullet(pl.pos, pl.dir));
          }
          if (event.key.code == sf::Keyboard::R || pl.hp <= 0) {
            kill(map, bullets, pl);
          }
          break;
        default:
          break;
      }
    }

    //Lables
    hptext.setString(sf::String("HP  " + std::to_string((int)pl.hp)));
    xptext.setString(sf::String("XP  " + std::to_string((int)pl.xp)));

    //Map loop
    if (pl.pos < 0) pl.pos = length - 1;
    else if (pl.pos >= length) pl.pos = 0;

    //Object interactions
    if (map[pl.pos].type == Object::med) {
      pl.hp += 50;
      map[pl.pos].type = Object::space;
    }
    if (map[pl.pos].type == Object::trap) {
      pl.hp -= 1500 * timer.getElapsedTime().asSeconds();
    }
    if (map[pl.pos].type == Object::enemy) {
      pl.hp = 0;
    }

    //Win
    bool k = true;
    for (auto a : map) {
      if (a.type == Object::enemy) k = false;
    }
    if (k) {
      reset(map, bullets, pl);
      ++pl.xp;
    }

    window.clear();

    if (pl.hp <= 0) {
      window.draw(gameover);
    }
    else {

      //Draw boxes
      for (int i = 0; i < length; ++i) {
        sf::RectangleShape shape(sf::Vector2f((float)width/length, (float)width/length));

        shape.setPosition(i * width / length, height/2);

        if (i == pl.pos) {
          shape.setFillColor(sf::Color::White);

          static sf::Clock dmgAnim;
          static bool k = false;
          if (dmgAnim.getElapsedTime().asSeconds() > 0.1) {
            dmgAnim.restart();
            k = !k;
          }
          if (map[pl.pos].type == Object::trap) {
            if (k) shape.setFillColor(sf::Color::White);
            else shape.setFillColor(sf::Color::Red);
          }
        }
        else if (map[i].type == Object::space) shape.setFillColor(sf::Color(30, 30, 30));
        else if (map[i].type == Object::trap) shape.setTexture(&tSpikes);
        else if (map[i].type == Object::med) shape.setTexture(&tMed);
        else if (map[i].type == Object::enemy) shape.setTexture(&tEnemy);

        window.draw(shape);
      }

      //Enemy moving
      static sf::Clock enmove, dirclock;
      if (enmove.getElapsedTime().asSeconds() > 0.2) {
        enmove.restart();

        static int dir = 1;
        if (dirclock.getElapsedTime().asSeconds() > 3) {
          dirclock.restart();
          dir = -dir;
        }
        for (int i = 0; i < length; ++i) {
          if(map[i].type == Object::enemy) {
            auto newp = i + dir * map[i].vel;
            if (newp < 0 || newp >= length) map[i].vel = -map[i].vel;
            newp = i + dir * map[i].vel;

            map[newp] = map[i];
            map[i].type = Object::space;
            if (dir * map[i].vel > 0) ++i;
          }
        }
      }

      //Bullets handling
      for (auto i = bullets.begin(); i != bullets.end();) {
        const int sz = width/length/2;
        sf::RectangleShape bul(sf::Vector2f(sz, sz));
        bul.setPosition(int(i->pos) * width / length + sz/2, height/2 + sz/2);
        bul.setFillColor(sf::Color::White);
        window.draw(bul);

        i->pos += 100 * i->vel * timer.getElapsedTime().asSeconds();
        if (map[i->pos].type == Object::enemy || map[i->pos].type == Object::trap) {
          map[i->pos].hp -= 20;
          if (map[i->pos].hp < 0) map[i->pos].type = Object::space;

          bullets.erase(i);
        }
        else if (i->pos >= length || i->pos < 0) bullets.erase(i);
        else {
          ++i;
        }
      }

      //Draw sprites
      for (int i = 0; i < length; ++i) {
        sf::Sprite sprite;
        sprite.setPosition(i * width / length, height/2);

        if (i == pl.pos)  {
          sprite.setTexture(tRevolver);
          sprite.setScale(1.0/length, 1.0/length);
          sprite.move(-1200.0/length, 100.0/length);
          if (pl.dir > 0) {
            sprite.scale(-1, 1);
            sprite.move(3600.0/length, 0);
          }
        }
        window.draw(sprite);
      }
      window.draw(hptext);
      window.draw(xptext);
    }
    window.display();
    timer.restart();
  }
  return 0;
}