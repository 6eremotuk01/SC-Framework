#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <list>
#include <Windows.h>

using namespace sf;
using namespace std;


#define Watch(param) cout << #param << " = " << param << endl;

class Position
{
protected:
	Vector2f position, position_limit;

public:
	virtual void setPosition(Vector2f position)
	{
		this->position = position;
	}

	void setPosition(float position_x, float position_y)
	{
		this->position = Vector2f(position_x, position_y);
	}


	virtual Vector2f getPosition()
	{
		return this->position;
	}
};

class Size
{
protected:
	Vector2f size;

public:
	virtual void setSize(Vector2f size)
	{
		this->size = size;
	}

	virtual void setSize(float size_x, float size_y)
	{
		this->size = Vector2f(size_x, size_y);
	}

	virtual Vector2f getSize()
	{
		return this->size;
	}
};

class IsIn : public Position, public Size
{
protected:
	Vector2f* window_position;

public: 
	virtual bool isIn(Vector2f current_position)
	{
		if (window_position)
		{
			if (window_position->x + position.x <= current_position.x &&
				window_position->y + position.y <= current_position.y &&
				window_position->x + position.x + size.x >= current_position.x &&
				window_position->y + position.y + size.y >= current_position.y) return true;
		}
		else
		{
			if (position.x <= current_position.x &&
				position.y <= current_position.y &&
				position.x + size.x >= current_position.x &&
				position.y + size.y >= current_position.y) return true;
		}

		return false;
	}

	bool isIn(Vector2i current_position)
	{
		return isIn(Vector2f(current_position));
	}
};


class Enable
{
protected:
	bool is_enabled = true;

public:
	bool isEnabled()
	{
		return is_enabled;
	}

	void setEnability(bool enablity)
	{
		is_enabled = enablity;
	}
};

class Open
{
protected:
	bool is_open = true;

public:
	bool isOpen()
	{
		return is_open;
	}
};

class Visible
{
protected:
	bool is_visible = true;

public:
	bool isVisible()
	{
		return is_visible;
	}

	void setVisibility(bool visibility)
	{
		is_visible = visibility;
	}
};

class Checked
{
protected:
	bool is_checked = false;

public:
	bool isChecked()
	{
		return is_checked;
	}

	void setState(bool is_checked)
	{
		this->is_checked = is_checked;
	}

	friend class RadioButtonContainer;
};


class ActiveColor 
{
public:
	Color hovered;
	Color clicked;
	Color basic;
	
	ActiveColor()
	{

	}
	
	ActiveColor(Color basic, Color clicked, Color hovered)
	{
		this->hovered = hovered;
		this->clicked = clicked;
		this->basic = basic;
	}

	void setColorsColor(Color basic, Color clicked, Color hovered)
	{
		this->hovered = hovered;
		this->clicked = clicked;
		this->basic = basic;
	}
};

class RenderWindowElement
{
protected:
	RenderWindow* window;

public:
	RenderWindow* getWindow()
	{
		return window;
	}

	void setWindow(RenderWindow &window)
	{
		this->window = &window;
	}
};


class Caption
{
protected:
	Text caption;

public:
	virtual void caption_update() = 0;

	void setCaption(wstring text)
	{
		caption.setString(text);

		caption_update();
	}

	void setCaption(string text)
	{
		caption.setString(text);
		caption_update();
	}

	String getCaption()
	{
		return caption.getString();
	}


	void setCaptionFont(Font &font)
	{
		caption.setFont(font);
		caption_update();
	}

	Font getFont()
	{
		return *caption.getFont();
	}


	void setCaptionStyle(Uint32 style)
	{
		caption.setStyle(style);
		caption_update();
	}


	void setCaptionCharacterSize(unsigned int size)
	{
		caption.setCharacterSize(size);
		caption_update();
	}

	int getCaptionCharacterSize()
	{
		return caption.getCharacterSize();
	}
	

	void setCaptionOutlineThickness(float size)
	{
		caption.setOutlineThickness(size);
		caption_update();
	}

	float getCaptionOutlineThickness()
	{
		return caption.getOutlineThickness();
	}


	void setCaptionColor(Color color)
	{
		caption.setFillColor(color);
	}
};

class Background
{
protected:
	RectangleShape background;

	virtual void background_update() = 0;

public:

	void setBorderSize(float size)
	{
		background.setOutlineThickness(size);
		background_update();
	}

	void setBackgroundColor(Color color)
	{
		background.setFillColor(color);
		background_update();
	}
};

class Click : public IsIn
{
protected:
	bool click_in = false;
	bool click_out = false;

	bool ClickedOn(sf::Event &event, Vector2f position_pointer)
	{
		if (click_in && event.type == sf::Event::MouseButtonReleased && event.key.code == Mouse::Left && isIn(position_pointer))
		{
			click_in = false;
			return true;
		}
		if ((event.type == sf::Event::MouseButtonPressed && event.key.code == Mouse::Left && isIn(position_pointer)) || (click_in && isIn(position_pointer)))
			click_in = true;
		else
			click_in = false;

		return false;
	}

	bool ClickedOn(sf::Event &event, Vector2f position_pointer, bool condition)
	{
		if (click_in && event.type == sf::Event::MouseButtonReleased && event.key.code == Mouse::Left && condition)
		{
			click_in = false;
			return true;
		}
		if ((event.type == sf::Event::MouseButtonPressed && event.key.code == Mouse::Left && condition) || (click_in && condition))
			click_in = true;
		else
			click_in = false;

		return false;
	}

	bool ClickedOut(sf::Event &event, Vector2f position_pointer)
	{
		if (click_out && event.type == sf::Event::MouseButtonReleased && event.key.code == Mouse::Left && !isIn(position_pointer))
		{
			click_out = false;
			return true;
		}
		if ((event.type == sf::Event::MouseButtonPressed && event.key.code == Mouse::Left && !isIn(position_pointer)) || (click_out && !isIn(position_pointer)))
			click_out = true;
		else
			click_out = false;

		return false;
	}
};