#include "MovingImage.h"

#include <cmath>

MovingImage::MovingImage() : m_texture(), m_sprite(m_texture) {}

void MovingImage::CheckWindowCollision(sf::RenderTarget& target) {
  auto bounds = m_sprite.getGlobalBounds();
  if (bounds.position.x < 0 && _xSpeed < 0.f) {
    _xSpeed *= -1.0f;
  }

  if (bounds.position.y < 0 && _ySpeed < 0.f) {
    _ySpeed *= -1.0f;
  }

  if (bounds.position.x + bounds.size.x > target.getSize().x && _xSpeed > 0) {
    _xSpeed *= -1.0f;
  }

  if (bounds.position.y + bounds.size.y > target.getSize().y && _ySpeed > 0) {
    _ySpeed *= -1.0f;
  }
}

void MovingImage::LoadImage(const std::string& imagePath) {
  if (!m_texture.loadFromFile(imagePath)) {
    std::cout << "Error loading image!" << std::endl;
  }

  m_sprite.setTexture(m_texture, true);
}

void MovingImage::ReverseMove() {
  _xSpeed *= -1.0f;
  _ySpeed *= -1.0f;
}

void MovingImage::SetScale(float scale) {
  m_sprite.setScale({scale, scale});
  m_sprite.scale({0.1f, 0.1f});
}

float* MovingImage::GetColors() { return _color; }

bool& MovingImage::GetShouldDraw() { return _shouldDraw; }

void MovingImage::Draw(sf::RenderTarget& target) {
  if (_shouldDraw && !isPause) target.draw(m_sprite);
}

void MovingImage::SetColor(float r, float g, float b) {
  _color[0] = r;
  _color[1] = g;
  _color[2] = b;
}

void MovingImage::Update(sf::RenderTarget& target) {
  CheckWindowCollision(target);
  m_sprite.setColor(
      sf::Color(_color[0] * 255.f, _color[1] * 255.f, _color[2] * 255.f));
  if (!isStanding && !isPause) {
    m_sprite.setPosition({m_sprite.getPosition().x + _xSpeed,
                          m_sprite.getPosition().y + _ySpeed});
  }
}

void MovingImage::SetPosition(const sf::Vector2f position) {
  m_sprite.setPosition(position);
}

void MovingImage::SetSpeed(float speed, float angle) {
  _xSpeed = speed * cos(angle);
  _ySpeed = speed * sin(angle);
}

void MovingImage::SetSpeed(float speed) {
  if (speed == 0) {
    isStanding = true;
  } else {
    isStanding = false;
    float length = sqrt(_xSpeed * _xSpeed + _ySpeed * _ySpeed);
    _xSpeed *= speed / length;
    _ySpeed *= speed / length;
  }
}
