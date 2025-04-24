#include "Text.h"

Text::Text(const Text &other) { Transfer(other); }

Text::Text(Text &&other) { Transfer(other); }

Text::Text(const std::filesystem::path &fontPath, const sf::String text,
           const int fontSize) {
  if (!_font.openFromFile(fontPath)) {
    std::cerr << "Could not load font!\n";
    exit(-1);
  }

  _text = sf::Text(_font, text, fontSize);
}

void Text::SetText(const std::string &text) { _text.setString(text); }

void Text::Draw(sf::RenderTarget &target) {
  if (isPause) {
    target.draw(_text);
  }
}

int Text::GetCharacterSize() const { return _text.getCharacterSize(); }

void Text::SetPosition(const sf::Vector2f position) {
  _text.setPosition(position);
}

Text &Text::operator=(const Text &other) {
  Transfer(other);

  return *this;
}

Text &Text::operator=(Text &&other) {
  Transfer(other);

  return *this;
}

void Text::Transfer(const Text &other) {
  _font = other._font;
  _text = other._text;

  _text.setFont(_font);
}

void Text::Update(sf::RenderTarget &target) {}
