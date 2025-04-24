#ifndef MOVINGIMAGE_H
#define MOVINGIMAGE_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "RenderObject.h"

class MovingImage : public RenderObject {
 public:
  MovingImage();

  void LoadImage(const std::string& imagePath);

  void CheckWindowCollision(sf::RenderTarget& target);

  void ReverseMove();
  float* GetColors();
  bool& GetShouldDraw();
  void SetScale(float scale);
  void SetSpeed(float speed, float angle);
  void SetColor(float r, float g, float b);
  void SetSpeed(float speed);
  void Draw(sf::RenderTarget& target) override;
  void Update(sf::RenderTarget& target) override;
  void SetPosition(const sf::Vector2f position);

 private:
  sf::Texture m_texture;
  sf::Sprite m_sprite;

  // Все дефолтные данные надо будет прочитать из конфигурационного файла
  bool _shouldDraw = true;
  float _color[3] = {1.0f, 1.0f, 0.0f};

  float _xSpeed = 1.0f;
  float _ySpeed = 0.5f;

  bool isStanding = false;

 public:
};

#endif  // MOVINGIMAGE_H
