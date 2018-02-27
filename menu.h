#pragma once
#include "ENGINE/bahamut.h"
#include "ENGINE/font.h"

class Panel;

class MenuComponent {
public:
	MenuComponent();
	int x;
	int y;
	int width;
	int height;
	bool visible;
	bool focused;

	void setActionCallback(void(*callback)(void));
	void setKeyCallback(void(*callback)(int keycode, int action));
	void setMouseCallback(void(*callback)(int button, int action, int mouse_x, int mouse_y));
private:
	virtual void update() = 0;
	virtual void draw(int xOffset, int yOffset) = 0;
protected:
	void(*_user_action_callback)(void);
	void(*_user_key_callback)(int keycode, int action);
	void(*_user_mouse_callback)(int button, int action, int mouse_x, int mouse_y);

	//sometimes components will react to inputs on their own (such as TextArea allowing you to edit the text in the area if
	//editable is set to true.)
	void(*_general_key_callback)(MenuComponent* comp, int keycode, int action);
	void(*_general_mouse_callback)(MenuComponent* comp, int button, int action, int mouse_x, int mouse_y);

	friend class Panel;
};

enum Anchor {
	LEFT_ANCHORED,
	CENTERED,
	RIGHT_ANCHORED
};

class Button : public MenuComponent {
public:
	Button();
	Button(int x, int y, int width, int height);
	Button(const Button& other);
	~Button();
	void operator=(const Button& other);

	void setColor(vec4f color);
	void setAnchor(Anchor anchor);
	void setText(std::string text);
	inline std::string getText() {
		return _text;
	}
	void setFont(Font& font);
private:
	float _cursor_x;
	bool _cursor_left;

	vec4f _text_color;
	vec4f _color;
	std::string _text;
	Texture _text_image;
	Anchor _anchor;
	Font _font;
	void draw(int xOffset, int yOffset);
	void update();
};

class TextArea : public MenuComponent {
public:
	TextArea();
	TextArea(int x, int y, int width, int height);

	bool editable;

	void setText(std::string text);
	std::string getText();
	void append(std::string text);
	void pop_back();
	void push_back(char c);
	void insert_at_caret(char c);
	void remove_at_caret();
	bool empty();
	void setFont(Font& font);
	void setColor(vec4f color);
private:
	static void text_area_key_callback(MenuComponent* comp, int keycode, int action);
	static void text_area_mouse_callback(MenuComponent* comp, int button, int action, int mouse_x, int mouse_y);

	Rectangle _caret;
	int _curr_char_index;

	std::string _text;
	Font _font;
	vec4f _color;
	void draw(int xOffset, int yOffset);
	void update();
};

class ScrollPane : public MenuComponent {
public:
	ScrollPane();
	ScrollPane(int x, int y, int width, int height);
private:
	void draw(int xOffset, int yOffset);
	void update();
};

class Label : public MenuComponent {
public:
	Label();
	Label(int x, int y, std::string text);
private:
	std::string _text;
	void draw(int xOffset, int yOffset);
	void update();
};

class DropDown : public MenuComponent {
public:
	DropDown();
	DropDown(int x, int y, int width, int height);
private:
	std::string _text;
	void draw(int xOffset, int yOffset);
	void update();
};

class CheckBox : public MenuComponent {
public:
	CheckBox();
	CheckBox(int x, int y, int width, int height);
private:
	std::string _text;
	void draw(int xOffset, int yOffset);
	void update();
};

class Panel {
public:
	Panel();
	Panel(char* bg_path, int width, int height);
	Panel(int width, int height);
	Panel(const Panel& other);
	void operator=(const Panel& other);
	~Panel();
	void draw(int x, int y);
	void add(MenuComponent* comp);
	bool remove(MenuComponent* comp);
	bool remove(int index);
	void removeAll();

	bool enabled;

	inline void setWidth(int width) {
		if (width < 0) {
			width = 0;
			printf("ERR: PANEL: setWidth: width must be >= 0\n");
		}
		_width = width;
	}
	inline void setHeight(int height) {
		if (height < 0) {
			height = 0;
			printf("ERR: PANEL: setHeight: height must be >= 0\n");
		}
		_height = height;
	}
	int getWidth();
	int getHeight();
	int getPixelWidth();
	int getPixelHeight();
	int getSegmentWidth();
	int getSegmentHeight();

	static void key_callback_func(int key, int action);
	static void mouse_callback_func(int button, int action, int mousex, int mousey);
	static void mouse_pos_callback_func(int mousex, int mousey);
private:
	void init();

	char* _bg_path;
	int _width;
	int _height;
	std::vector<MenuComponent*> components;
	static MenuComponent* hot_comp;
	static MenuComponent* active_comp;
	Texture bg[9];	

	friend class MenuComponent;
	friend class TextArea;
	friend class Button;
};