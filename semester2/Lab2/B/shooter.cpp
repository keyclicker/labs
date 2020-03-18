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

class Bullet {
public:
  float pos;
  int vel;
  Bullet(int pos, int vel) : pos(pos), vel(vel) {}
};

void reset(std::array<Object, length> &map,
        std::vector<Bullet> &bullets, int16_t &pos, float &hp) {

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
  pos = length / 2;
  hp = 100;
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

  sf::Text gameover;
  gameover.setPosition(60, 200);
  gameover.setCharacterSize(240);
  gameover.setFillColor(sf::Color::White);
  gameover.setString("GAME OVER!");
  gameover.setFont(font);

  //Textures load
  sf::Texture tRevolver;
  tRevolver.loadFromFile("../res/revolver.png");

  //Map and player
  std::array<Object, length> map;
  std::vector<Bullet> bullets;
  int16_t pos;
  int8_t dir = 1;
  float hp;

  reset(map, bullets, pos, hp);


  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::KeyPressed:
          if (event.key.code == sf::Keyboard::Left) {
            --pos;
            dir = -1;
          }
          if (event.key.code == sf::Keyboard::Right) {
            ++pos;
            dir = 1;
          }
          if (event.key.code == sf::Keyboard::Space) {
            bullets.emplace_back(Bullet(pos, dir));
          }
          if (event.key.code == sf::Keyboard::R || hp <= 0) {
            reset(map, bullets, pos, hp);
          }
          break;
        default:
          break;
      }
    }

    hptext.setString(sf::String("HP  " + std::to_string((int)hp)));

    if (pos < 0) pos = length - 1;
    else if (pos >= length) pos = 0;

    if (map[pos].type == Object::med) {
      hp += 50;
      map[pos].type = Object::space;
    }
    if (map[pos].type == Object::trap) {
      hp -= 1000 * timer.getElapsedTime().asSeconds();
    }
    if (map[pos].type == Object::enemy) {
      hp = 0;
    }

    bool k = true;
    for (auto a : map) {
      if (a.type == Object::enemy) k = false;
    }
    if (k) reset(map, bullets, pos, hp);

    window.clear();

    if (hp <= 0) {
      window.draw(gameover);
    }
    else {

      //Draw boxes
      for (int i = 0; i < length; ++i) {
        sf::RectangleShape shape(sf::Vector2f(width/length, width/length));

        shape.setPosition(i * width / length, height/2);

        if (map[i].type == Object::space) shape.setFillColor(sf::Color(30, 30, 30));
        else if (map[i].type == Object::trap) shape.setFillColor(sf::Color(100, 100, 100));
        else if (map[i].type == Object::med) shape.setFillColor(sf::Color::Magenta);
        else if (map[i].type == Object::enemy) shape.setFillColor(sf::Color::Red);

        if (i == pos) shape.setFillColor(sf::Color::White);

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

        if (i == pos)  {
          sprite.setTexture(tRevolver);
          sprite.setScale(1.0/length, 1.0/length);
          sprite.move(-1200.0/length, 100.0/length);
          if (dir > 0) {
            sprite.scale(-1, 1);
            sprite.move(3600.0/length, 0);
          }
        }
        window.draw(sprite);
      }

      window.draw(hptext);
    }
    window.display();
    timer.restart();
  }
  return 0;
}