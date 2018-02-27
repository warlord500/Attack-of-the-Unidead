#include "menu.h"
#include "globals.h"
#include <thread>
#include <SOIL.h>

//CLASS VARIABLES
MenuComponent* Panel::hot_comp = NULL;
MenuComponent* Panel::active_comp = NULL;

//MENU COMPONENT

void Panel::key_callback_func(int key, int action) {
	if (active_comp != NULL) {
		if (active_comp->_user_key_callback != NULL)
			active_comp->_user_key_callback(key, action);

		if (active_comp->_general_key_callback != NULL)
			active_comp->_general_key_callback(active_comp, key, action);
	}
}

void Panel::mouse_callback_func(int button, int action, int mousex, int mousey) {
	if (active_comp != NULL) {
		if (active_comp->_user_mouse_callback != NULL)
			active_comp->_user_mouse_callback(button, action, mousex, mousey);

		if (active_comp->_general_mouse_callback != NULL)
			active_comp->_general_mouse_callback(active_comp, button, action, mousex, mousey);
	}
}

void Panel::mouse_pos_callback_func(int mousex, int mousey) {

}

MenuComponent::MenuComponent() {
	x = y = width = height = 0;
	visible = false;
	_user_action_callback = NULL;
	_user_key_callback = NULL;
	_user_mouse_callback = NULL;

	_general_key_callback = NULL;
	_general_mouse_callback = NULL;
}

void MenuComponent::setActionCallback(void(*callback)(void)) {
	_user_action_callback = callback;
}

void MenuComponent::setKeyCallback(void(*callback)(int keycode, int action)) {
	_user_key_callback = callback;
}

void MenuComponent::setMouseCallback(void(*callback)(int button, int action, int mouse_x, int mouse_y)) {
	_user_mouse_callback = callback;
}

//BUTTON

Button::Button() {
	x = y = width = height = 0;
	_cursor_x = 0;
	_color = BLACK;
	_anchor = CENTERED;
}

Button::Button(int x, int y, int width, int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	_cursor_x = 0;
	_color = BLACK;
	_anchor = CENTERED;
}

Button::Button(const Button& other) {
	x = other.x;
	y = other.y;
	width = other.width;
	height = other.height;
	_color = other._color;
	_text = other._text;
	_anchor = other._anchor;
	_cursor_x = other._cursor_x;
	_text_color = other._text_color;
	_font = other._font;
	_text_image = createTextureFromString(_font, _text, _text_color.x, _text_color.y, _text_color.z);
}

void Button::operator=(const Button& other) {
	disposeTexture(_text_image);
	x = other.x;
	y = other.y;
	width = other.width;
	height = other.height;
	_color = other._color;
	_text = other._text;
	_anchor = other._anchor;
	_cursor_x = other._cursor_x;
	_text_color = other._text_color;
	_font = other._font;
	_text_image = createTextureFromString(_font, _text, _text_color.x, _text_color.y, _text_color.z);
}

void Button::setText(std::string text) {
	_text = text;
	_text_image = createTextureFromString(_font, text, _text_color.x, _text_color.y, _text_color.z);
}

void Button::setFont(Font& font) {
	_font = font;
}

void Button::setColor(vec4f color) {
	_color = color;
}

void Button::setAnchor(Anchor anchor) {
	_anchor = anchor;
}

void Button::draw(int xOffset, int yOffset) {
	int xPos = x + xOffset;
	int yPos = y + yOffset;

	if (Panel::hot_comp == this)
		drawRectangle(xPos, yPos, width, height, 170, 128, 95, 255);
	else
		drawRectangle(xPos, yPos, width, height, 230, 206, 171, 255);

	if (Panel::hot_comp == this && Panel::active_comp == this && isButtonDown(MOUSE_BUTTON_LEFT))
		drawRectangle(xPos + 4, yPos + 4, width - 8, height - 8, 150, 108, 75, 255);

	if(_anchor == Anchor::CENTERED)
		drawTexture(_text_image, xPos + (width / 2) - (_text_image.width / 2), yPos + (height / 2) - (_text_image.height / 3.5));
	if (_anchor == Anchor::LEFT_ANCHORED)
		drawTexture(_text_image, xPos + 5, yPos + (height / 2) - (_text_image.height / 3.5));
	if (_anchor == Anchor::RIGHT_ANCHORED)
		drawTexture(_text_image, xPos + (width) - (_text_image.width), yPos + (height / 2) - (_text_image.height / 3.5));

	if (_cursor_left) {
		_cursor_x -= .7;
		if (_cursor_x < 5)
			_cursor_left = false;
	}
	else {
		_cursor_x += .7;
		if (_cursor_x > 15)
			_cursor_left = true;
	}

	if (Panel::hot_comp == this) {
		drawTexture(select_cursor, _cursor_x + xPos - (width / 3), yPos);
	}
}

void Button::update() {
	if (Panel::hot_comp == this && Panel::active_comp == this)
		if (isButtonReleased(MOUSE_BUTTON_LEFT))
			if (_user_action_callback != NULL)
				_user_action_callback();
}

Button::~Button() {
	disposeTexture(_text_image);
}

//TEXT AREA

void TextArea::text_area_key_callback(MenuComponent* comp, int keycode, int action) {
	TextArea* area = (TextArea*)comp;
	if (area->editable) {
		if (action == PRESS || action == REPEAT) {
			if (keycode == KEY_LEFT) {
				area->_caret.x -= area->_font.characters[area->_text[area->_curr_char_index]]->advance >> 6;
				area->_curr_char_index--;
			}
			if (keycode == KEY_RIGHT) {
				area->_caret.x += area->_font.characters[area->_text[area->_curr_char_index]]->advance >> 6;
				area->_curr_char_index++;
			}
			if (!area->empty() && keycode == KEY_BACKSPACE) {
				//area->_caret.x -= area->_font.characters[area->_text[area->_curr_char_index]]->advance >> 6;
				area->remove_at_caret();
			}
			if (keycode == KEY_SPACE) area->insert_at_caret(' ');
			if (keycode >= 65 && keycode <= 90) {
				if (!isKeyDown(KEY_LEFT_SHIFT)) {
					keycode += 32;
				}

				area->insert_at_caret(keycode);
			}
		}
	}
}

void TextArea::text_area_mouse_callback(MenuComponent* comp, int button, int action, int mouse_x, int mouse_y) {
	TextArea* area = (TextArea*)comp;

}

TextArea::TextArea() {
	this->x = this->y = this->width = this->height = 0;
	_caret.x = 0;
	_caret.y = 0;
	_caret.width = 5;
	_caret.height = 15;
	_general_key_callback = text_area_key_callback;
	_general_mouse_callback = text_area_mouse_callback;
	_color = WHITE;
}

TextArea::TextArea(int x, int y, int width, int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	_caret.x = x;
	_caret.y = y;
	_caret.width = 5;
	_caret.height = 15;
	_general_key_callback = text_area_key_callback;
	_general_mouse_callback = text_area_mouse_callback;
	_color = WHITE;
}

void TextArea::draw(int xOffset, int yOffset) {
	int curr_x = x + xOffset;
	int curr_y = y + yOffset;
	int size = 0;
	char curr_char;
	for (int i = 0; i < _text.size(); ++i) {
		if (curr_x - xOffset > width) {
			curr_y += _font.characters['T']->texture.height * 1.5;
			curr_x = x + xOffset;
		}

		curr_char = _text[i];
		if (curr_char == '\n') {
			curr_y += _font.characters['T']->texture.height * 1.5;
			curr_x = x + xOffset;
			continue;
		}
		Character* c = _font.characters[curr_char];
		if (curr_char == ' ') {
			int j = i + 1;
			int text_size = _text.size();
			while (j < text_size && _text[j] != ' ') {
				j++;
				size += (c->advance >> 6);
			}
			size -= (c->advance >> 6);
			if (curr_x - x - xOffset + size > width) {
				//printf("curr_x: %i x: %i xOffset: %i size: %i  width: %i  curr_x - x - xOffset + size: %i\n", curr_x, x, xOffset, size, width, curr_x - x - xOffset + size);
				curr_y += _font.characters['T']->texture.height * 1.5;
				curr_x = x + xOffset;
				size = 0;
				continue;
			}
		}

		int yOffset = (_font.characters['T']->bearing.y - c->bearing.y) + 1;
		if (yOffset < 0) yOffset = 0;
		int xPos = curr_x + c->bearing.x;
		int yPos = curr_y + yOffset;

		drawTexture(c->texture, xPos, yPos, _color.x, _color.y, _color.z, _color.w);
		curr_x += (c->advance >> 6);
	}
	if (editable && Panel::active_comp == this && (int)getElapsedTime() % 2 == 0) {
		drawRectangle(_caret.x + xOffset, _caret.y + yOffset, _caret.width, _caret.height, WHITE);
	}
}

void TextArea::pop_back() {
	_text.pop_back();
}

void TextArea::push_back(char c) {
	_text.push_back(c);
}

void TextArea::insert_at_caret(char c) {
	_caret.x += _font.characters[_text[_curr_char_index]]->advance >> 6;
	_text.insert(_text.begin() + _curr_char_index, c);
	_curr_char_index++;
}

void TextArea::remove_at_caret() {
	_curr_char_index--;
	_caret.x -= _font.characters[_text[_curr_char_index]]->advance >> 6;
	_text.erase(_text.begin() + _curr_char_index);
}

bool TextArea::empty() {
	return _text.empty();
}

void TextArea::setText(std::string text) {
	_text = text;

	//TODO: do this without duplicating the draw code
	int curr_x = x;
	int curr_y = y;
	int size = 0;
	char curr_char;
	for (int i = 0; i < _text.size(); ++i) {
		if (curr_x > width) {
			curr_y += _font.characters['T']->texture.height * 1.5;
			curr_x = x;
		}

		curr_char = _text[i];
		if (curr_char == '\n') {
			curr_y += _font.characters['T']->texture.height * 1.5;
			curr_x = x;
			continue;
		}
		Character* c = _font.characters[curr_char];
		if (curr_char == ' ') {
			int j = i + 1;
			int text_size = _text.size();
			while (j < text_size && _text[j] != ' ') {
				j++;
				size += (c->advance >> 6);
			}
			size -= (c->advance >> 6);
			if (curr_x + size > width) {
				curr_y += _font.characters['T']->texture.height * 1.5;
				curr_x = x;
				size = 0;
				continue;
			}
		}

		int yOffset = (_font.characters['T']->bearing.y - c->bearing.y) + 1;
		if (yOffset < 0) yOffset = 0;
		int xPos = curr_x + c->bearing.x;
		int yPos = curr_y + yOffset;

		curr_x += (c->advance >> 6);
	}
	_caret.x = curr_x;
	_caret.y = curr_y;
	_curr_char_index = _text.size() - 1;
}

std::string TextArea::getText() {
	return _text;
}

void TextArea::append(std::string text) {
	_text.append(text);
}

void TextArea::setFont(Font & font) {
	_font = font;
	_caret.height = font.characters['T']->size.y;
}

void TextArea::setColor(vec4f color) {
	_color = color;
}

void TextArea::update() {

}

//PANEL

Panel::Panel() {
	_width = 0;
	_height = 0;
	_bg_path = (char*)malloc(18);
	strcpy(_bg_path, "data/art/menu.png");
	init();
}

Panel::Panel(int width, int height) {
	_width = width;
	_height = height;
	_bg_path = (char*)malloc(18);
	strcpy(_bg_path, "data/art/menu.png");
	init();
}

Panel::Panel(char* bg_path, int width, int height) {
	_width = width;
	_height = height;
	_bg_path = (char*)malloc(strlen(bg_path) + 1);
	strcpy(_bg_path, bg_path);
	init();
}

Panel::Panel(const Panel& other) {
	_width = other._width;
	_height = other._height;
	_bg_path = (char*)malloc(strlen(other._bg_path) + 1);
	strcpy(_bg_path, other._bg_path);
	init();
}

void Panel::operator=(const Panel& other) {
	_width = other._width;
	_height = other._height;
	_bg_path = (char*)malloc(strlen(other._bg_path) + 1);
	strcpy(_bg_path, other._bg_path);
	init();
}

void Panel::draw(int xPos, int yPos) {
	drawTexture(bg[0], xPos, yPos);
	drawTexture(bg[2], xPos, yPos + (_height * bg[0].height));
	drawTexture(bg[6], xPos + (_width * bg[0].width), yPos);
	drawTexture(bg[8], xPos + (_width * bg[0].width), yPos + (_height * bg[0].height));
	for (int x = 1; x < _width; ++x) {
		drawTexture(bg[3], (x * bg[0].width) + xPos, yPos);
		drawTexture(bg[5], (x * bg[0].width) + xPos, yPos + (_height * bg[0].height));
	}
	for (int y = 1; y < _height; ++y) {
		drawTexture(bg[1], xPos, (y * bg[0].height) + yPos);
		drawTexture(bg[7], xPos + (_width * bg[0].width), (y * bg[0].height) + yPos);
	}
	for (int x = 1; x < _width; ++x) {
		for (int y = 1; y < _height; ++y) {
			drawTexture(bg[4], (x * bg[0].width) + xPos, (y * bg[0].height) + yPos);
		}
	}

	for (int i = 0; i < components.size(); ++i) {
		MenuComponent* comp = components[i];
		if (comp->visible) {
			int new_comp_x = xPos + getSegmentWidth();
			int new_comp_y = yPos + getSegmentHeight();
			comp->draw(new_comp_x, new_comp_y);
			comp->update();
			double mouse_x;
			double mouse_y;
			getMousePos(&mouse_x, &mouse_y);
			if (mouse_x > comp->x + new_comp_x && mouse_x < comp->x + new_comp_x + comp->width && mouse_y > comp->y + new_comp_y && mouse_y < comp->y + new_comp_y + comp->height) {
				hot_comp = comp;
				if (isButtonPressed(MOUSE_BUTTON_LEFT))
					active_comp = comp;
			}
			else {
				if(hot_comp == comp)
					hot_comp = NULL;
				if (active_comp == comp && isButtonPressed(MOUSE_BUTTON_LEFT))
					active_comp = NULL;
			}
		}
	}
}

void Panel::add(MenuComponent* comp) {
	components.push_back(comp);
}

bool Panel::remove(MenuComponent* comp) {
	for (int i = 0; i < components.size(); ++i) {
		if (components[i] == comp) {
			components.erase(components.begin() + i);
			return true;
		}
	}
	return false;
}

bool Panel::remove(int index) {
	if (index < 0 || index >= components.size()) return false;
	components.erase(components.begin() + index);
	return true;
}

void Panel::removeAll() {
	components.clear();
}

int Panel::getWidth() {
	return _width;
}

int Panel::getHeight() {
	return _height;
}

int Panel::getPixelWidth() {
	return getSegmentWidth() * getWidth();
}

int Panel::getPixelHeight() {
	return getSegmentHeight() * getHeight();
}

int Panel::getSegmentWidth() {
	return bg[0].width;
}

int Panel::getSegmentHeight() {
	return bg[0].height;
}

void Panel::init() {
	int w;
	int h;
	int i = 0;
	unsigned char* image = SOIL_load_image(_bg_path, &w, &h, 0, SOIL_LOAD_RGBA);
	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
			bg[i++] = getSubImage(image, w, x * (w / 3), y * (h / 3), w / 3, h / 3);
	free(image);
}

Panel::~Panel() {
	for (int i = 0; i < 9; ++i) {
		disposeTexture(bg[i]);
	}
	free(_bg_path);
}