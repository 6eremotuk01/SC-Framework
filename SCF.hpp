#pragma once

#include <iostream>
#include <list>

#include <SFML\Graphics.hpp>

using namespace sf;
using namespace std;

/*
	Basic classes

	By using this classes you can make your own GUI element.
	Documentation API: https://github.com/6eremotuk01/SC-Framework/blob/master/README.md
*/

#pragma region Basic classes

class PositionSize
{
protected:
	Vector2f position,
		size;

	virtual void position_update() = 0;

	virtual void size_update() = 0;


public:
	virtual void setPosition(Vector2f position)
	{
		this->position = position;

		position_update();
	}

	void setPosition(float position_x, float position_y)
	{
		setPosition(Vector2f(position_x, position_y));
	}

	virtual Vector2f getPosition()
	{
		return this->position;
	}


	virtual void setSize(Vector2f size)
	{
		this->size = size;

		size_update();
	}

	virtual void setSize(float size_x, float size_y)
	{
		setSize(Vector2f(size_x, size_y));
	}

	virtual Vector2f getSize()
	{
		return this->size;
	}
};

class IsIn : public PositionSize
{
public:
	virtual bool isIn(Vector2f current_position)
	{
		if (position.x <= current_position.x &&
			position.y <= current_position.y &&
			position.x + size.x >= current_position.x &&
			position.y + size.y >= current_position.y) return true;

		return false;
	}

	virtual bool isIn(Vector2i current_position)
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

	void enable()
	{
		is_enabled = true;
	}

	void unable()
	{
		is_enabled = false;
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

	void visible()
	{
		is_visible = true;
	}

	void invisible()
	{
		is_visible = false;
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

	void checked()
	{
		this->is_checked = true;
	}

	void unchecked()
	{
		this->is_checked = false;
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
};

class RenderWindowElement
{
protected:
	RenderWindow* window = NULL;

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

	virtual void caption_update() = 0;

public:

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

	const Font *getFont()
	{
		return caption.getFont();
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

	unsigned int getCaptionCharacterSize()
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


	void setCaptionOutlineColor(Color color)
	{
		caption.setOutlineColor(color);
		caption.getOutlineColor();
	}

	Color getCaptionOutlineColor()
	{
		return caption.getOutlineColor();
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

class Textured
{

};

#pragma endregion


/*
	Basics elements

	You can create GUI by using basic elements. For example you can create 
	simple button by using CaptionButton element.

	Documentation API: https://github.com/6eremotuk01/SC-Framework/blob/master/README.md#%D0%9E%D0%BF%D0%B8%D1%81%D0%B0%D0%BD%D0%B8%D0%B5-%D0%BC%D0%B5%D1%82%D0%BE%D0%B4%D0%BE%D0%B2-%D0%B8-%D0%BA%D0%BE%D0%BC%D0%BF%D0%BE%D0%BD%D0%B5%D0%BD%D1%82%D0%BE%D0%B2
*/

#pragma region Basic elements

class Label : 
	public Enable, 
	public Visible, 
	public Caption, 
	public PositionSize,
	public RenderWindowElement
{
protected:
	bool click_in = false;

	void caption_update()
	{
		size =  Vector2f(caption.getLocalBounds().width + caption.getLocalBounds().left, caption.getLocalBounds().height + caption.getLocalBounds().top);
	}

	void position_update()
	{
		caption.setPosition(position);
	}
	
	void size_update()
	{

	}

public:

	Label(RenderWindow &window, Font &font)
	{
		setCaptionFont(font);
		this->window = &window;

		position = Vector2f(0, 0);

		caption.setFillColor(Color::Black);

		setPosition(position);
		setCaptionCharacterSize(15);
	}

	void display()
	{
		if (!is_visible)
			return;

		window->draw(caption);
	}

	friend class VirtualWindow;
};

class CaptionButton : 
	public Enable, 
	public Click, 
	public Visible, 
	public Caption, 
	public Background,
	public RenderWindowElement
{
protected:
	ActiveColor background_color,
		text_color,
		border_color;

	void Brush(Color bg_color, Color txt_color, Color brd_color)
	{
		background.setFillColor(bg_color);
		caption.setFillColor(txt_color);
		background.setOutlineColor(brd_color);
	}

	virtual void caption_update()
	{
		float size_x = 0, size_y = 0;

		if (window)
		{
			window->draw(caption);
			size_x = caption.getLocalBounds().width + caption.getLocalBounds().left;
			size_y = caption.getLocalBounds().height + caption.getLocalBounds().top;
			caption.setOrigin(-int(size.x / 2 - size_x / 2), -int(size.y / 2 - size_y / 2));
		}
		else
			caption.setOrigin(0, 0);
	}

	virtual void background_update()
	{
	
	}

	virtual void size_update()
	{
		background.setSize(size);

		caption_update();
		background_update();
	}

	virtual void position_update()
	{
		caption.setPosition(position);
		background.setPosition(position);

		caption_update();
		background_update();
	}

public:

	CaptionButton(RenderWindow &window, Font &font)
	{
		this->window = &window;
		setCaptionFont(font);

		size = Vector2f(75, 35);
		position = Vector2f(0, 0);

		setBasicColors();
		setHoveredColors();
		setClickedColors();
		setBorderSize(-2);

		setSize(size);
		setPosition(position);
		setCaptionCharacterSize(15);
	}
	

	void setCaption(wstring text, Vector2f interval)
	{
		caption.setString(text);
		setSizeByCaption(interval);
	}

	void setCaption(string text, Vector2f interval)
	{
		caption.setString(text);
		setSizeByCaption(interval);
	}


	void setCaption(wstring text)
	{
		caption.setString(text);
	}

	void setCaption(string text)
	{
		caption.setString(text);
	}


	void setSizeByCaption(Vector2f interval = Vector2f(5, 5))
	{
		setSize((caption.getLocalBounds().width - caption.getLocalBounds().left) + interval.x * 2,
			(caption.getLocalBounds().height + caption.getLocalBounds().top) + interval.y * 2);
		caption_update();
	}


	void setBasicColors(Color bg_color = Color(225, 225, 225), Color txt_color = Color::Black, Color brd_color = Color(225, 225, 225))
	{
		background_color.basic = bg_color;
		text_color.basic = txt_color;
		border_color.basic = brd_color;

		Brush(background_color.basic, text_color.basic, border_color.basic);
	}

	void setHoveredColors(Color bg_color = Color(245, 245, 245), Color txt_color = Color::Black, Color brd_color = Color(245, 245, 245))
	{
		background_color.hovered = bg_color;
		text_color.hovered = txt_color;
		border_color.hovered = brd_color;
	}

	void setClickedColors(Color bg_color = Color(190, 190, 190), Color txt_color = Color::Black, Color brd_color = Color(190, 190, 190))
	{
		background_color.clicked = bg_color;
		text_color.clicked = txt_color;
		border_color.clicked = brd_color;
	}


	ActiveColor getBackgroundColors()
	{
		return background_color;
	}

	ActiveColor getTextColors()
	{
		return background_color;
	}

	ActiveColor getBorderColors()
	{
		return background_color;
	}


	void display()
	{
		if (!is_visible)
			return;

		window->draw(background);
		window->draw(caption);
	}


	int getEvent(sf::Event &event)
	{
		if (!is_enabled) 
			return Event::Nothing;
		
		Vector2f mouse = window->mapPixelToCoords(Mouse::getPosition(*window));

		if (isIn(mouse))
		{
			Brush(background_color.hovered, text_color.hovered, border_color.hovered);
			if (onHover) onHover();
		}
		else
		{
			Brush(background_color.basic, text_color.basic, border_color.basic);
			if (onHoverOut) onHoverOut();
		}

		if (ClickedOn(event, mouse))
		{
			if (onClick) onClick();
			return Event::Clicked;
		}
		
		if (click_in)
			Brush(background_color.clicked, text_color.clicked, border_color.clicked);

		return Event::Nothing;
	}

	enum Event
	{
		Nothing = 0,
		Hovered,
		Clicked
	};

	void(*onClick)() = NULL;
	void(*onHover)() = NULL;
	void(*onHoverOut)() = NULL;
};

class CheckBox : 
	public Enable, 
	public Click, 
	public Visible, 
	public Caption, 
	public Background,
	public RenderWindowElement,
	public Checked
{
protected:
	VertexArray check;
	ActiveColor text_color,
		background_color,
		check_color,
		border_color;

	int indentation = 2;

	void Brush(Color bg_color, Color txt_color, Color brd_color, Color check_color)
	{
		for (int i = 0; i < 8; i++)
			check[i].color = check_color;
		background.setFillColor(bg_color);
		caption.setFillColor(txt_color);
		background.setOutlineColor(brd_color);
	}

	void caption_update()
	{
		if (window)
		{
			float size_y = caption.getLocalBounds().height - caption.getLocalBounds().top;
			caption.setOrigin(-int(size.x + 5), int((size.y - size_y) / 2));
		}
		else
			caption.setOrigin(-(size.x + 5), 0);
	}

	void background_update()
	{

	}

	void position_update()
	{
		check[0].position = Vector2f(position.x + indentation, position.y + size.y / 2);
		check[1].position = Vector2f(position.x + indentation + 3, position.y + size.y / 2);
		check[2].position = Vector2f(position.x + size.x / 2 + 1, position.y + size.y - indentation);
		check[3].position = Vector2f(position.x + size.x / 2 - 2, position.y + size.y - indentation);

		check[4].position = Vector2f(position.x + size.x / 2 - 2, position.y + size.y - indentation);
		check[5].position = Vector2f(position.x + size.x / 2 + 1, position.y + size.y - indentation);
		check[6].position = Vector2f(position.x + size.x - indentation, position.y + indentation);
		check[7].position = Vector2f(position.x + size.x - indentation - 3, position.y + indentation);

		caption.setPosition(position);
		background.setPosition(position);

		background_update();
		caption_update();
	}

	void size_update()
	{
		background.setSize(size);

		background_update();
		caption_update();
	}

	bool isIn(Vector2f current_position)
	{
		if (position.x <= current_position.x &&
			position.y <= current_position.y &&
			position.x + size.x + caption.getLocalBounds().width + 5 >= current_position.x &&
			position.y + size.y >= current_position.y) return true;

		return false;
	}

	bool isIn(Vector2i current_position)
	{
		return isIn(Vector2f(current_position));
	}

public:

	CheckBox(RenderWindow &window, Font &font)
	{
		setCaptionFont(font);
		this->window = &window;
		is_checked = false;

		check = VertexArray(sf::Quads, 8);
		size = Vector2f(15, 15);
		position = Vector2f(0, 0);

		setBasicColors();
		setHoveredColors();
		setClickedColors();

		background.setOutlineThickness(-1);
		setCaptionCharacterSize(15);

		setSize(size);
		setPosition(position);
	}


	void setCaptionCharacterSize(int size = 0)
	{
		if (size == 0)
			caption.setCharacterSize(this->size.y - 2);
		else
			caption.setCharacterSize(size);
		caption_update();
	}


	Vector2f getSize()
	{
		return Vector2f(size.x + caption.getLocalBounds().width + 5, size.y);
	}


	void setBasicColors(Color bg_color = Color(225, 225, 225), Color txt_color = Color::Black, Color brd_color = Color::Black, Color ck_color = Color::Black)
	{
		background_color.basic = bg_color;
		text_color.basic = txt_color;
		border_color.basic = brd_color;
		check_color.basic = ck_color;

		Brush(background_color.basic, text_color.basic, border_color.basic, check_color.basic);
	}

	void setHoveredColors(Color bg_color = Color(245, 245, 245), Color txt_color = Color::Black, Color brd_color = Color::Black, Color ck_color = Color::Black)
	{
		background_color.hovered = bg_color;
		text_color.hovered = txt_color;
		border_color.hovered = brd_color;
		check_color.hovered = ck_color;
	}

	void setClickedColors(Color bg_color = Color(190, 190, 190), Color txt_color = Color::Black, Color brd_color = Color::Black, Color ck_color = Color::Black)
	{
		background_color.clicked = bg_color;
		text_color.clicked = txt_color;
		border_color.clicked = brd_color;
		check_color.clicked = ck_color;
	}


	void setIndentationImg(int indentation)
	{
		this->indentation = indentation;
	}


	void display()
	{
		if (!is_visible)
			return;

		window->draw(background);
		if (is_checked) window->draw(check);
		window->draw(caption);
	}


	int getEvent(sf::Event &event)
	{
		if (!is_enabled) return Event::Nothing;

		Vector2f mouse = window->mapPixelToCoords(Mouse::getPosition(*window));

		if (isIn(Mouse::getPosition(*window)))
		{
			if (onHover) onHover();
			Brush(background_color.hovered, text_color.hovered, border_color.hovered, check_color.hovered);
		}
		else
		{
			if (onHoverOut) onHoverOut();
			Brush(background_color.basic, text_color.basic, border_color.basic, check_color.basic);
		}

		if (ClickedOn(event, mouse))
		{
			is_checked = !is_checked;
			if (is_checked)
			{
				return Event::Checked;
				if (onChecked) onChecked();
			}
			else 
			{
				return Event::Unchecked;
				if (onUnchecked) onUnchecked();
			}
		}

		if (click_in)
			Brush(background_color.clicked, text_color.clicked, border_color.clicked, check_color.clicked);

		return Event::Nothing;
	}

	enum Event
	{
		Nothing = 0,
		Checked,
		Unchecked
	};

	void(*onChecked)()	= NULL;
	void(*onUnchecked)() = NULL;
	void(*onHover)() = NULL;
	void(*onHoverOut)() = NULL;
};

class RadioButton : 
	public Enable, 
	public Click, 
	public Visible, 
	public Caption, 
	public Checked,
	public RenderWindowElement
{
protected:
	CircleShape background, 
		check;

	ActiveColor text_color,
		background_color,
		check_color,
		border_color;

	int indentation = 2;

	void Brush(Color bg_color, Color txt_color, Color brd_color, Color check_color)
	{
		check.setFillColor(check_color);
		background.setFillColor(bg_color);
		caption.setFillColor(txt_color);
		background.setOutlineColor(brd_color);
	}

	void caption_update()
	{
		if (window)
		{
			float size_y = caption.getLocalBounds().height - caption.getLocalBounds().top;
			caption.setOrigin(-int(size.x + 5), int((size.y - size_y) / 2));
		}
		else
			caption.setOrigin(-(size.x + 5), 0);
	}

	void position_update()
	{
		check.setPosition(position);
		background.setPosition(position);
		caption.setPosition(position);

		caption_update();
	}

	void size_update()
	{
		background.setRadius(size.x / 2);
		check.setRadius(size.x / 2 - indentation * 2);
		check.setOrigin(-(indentation * 2), -(indentation * 2));

		caption_update();
	}

	bool isIn(Vector2f current_position)
	{
		if (position.x <= current_position.x &&
			position.y <= current_position.y &&
			position.x + size.x + caption.getLocalBounds().width + 5 >= current_position.x &&
			position.y + size.y >= current_position.y) return true;

		return false;
	}

	bool isIn(Vector2i current_position)
	{
		return isIn(Vector2f(current_position));
	}

public:
	RadioButton(RenderWindow &window, Font &font)
	{
		setCaptionFont(font);
		this->window = &window;
		is_checked = false;

		size = Vector2f(15, 15);
		position = Vector2f(0, 0);

		setBasicColors();
		setHoveredColors();
		setClickedColors();

		background.setOutlineThickness(-1);
		setCaptionCharacterSize(15);

		setSize(size);
		setPosition(position);
	}


	void setCaptionCharacterSize(float size = 0)
	{
		if (size == 0)
			caption.setCharacterSize(this->size.y - 2);
		else
			caption.setCharacterSize(size);
		setSize(this->size);
	}


	Vector2f getSize()
	{
		return Vector2f(size.x + caption.getLocalBounds().width + 5, size.y);
	}


	void setBasicColors(Color bg_color = Color(225, 225, 225), Color txt_color = Color::Black, Color brd_color = Color::Black, Color ck_color = Color::Black)
	{
		background_color.basic = bg_color;
		text_color.basic = txt_color;
		border_color.basic = brd_color;
		check_color.basic = ck_color;

		Brush(background_color.basic, text_color.basic, border_color.basic, check_color.basic);
	}

	void setHoveredColors(Color bg_color = Color(245, 245, 245), Color txt_color = Color::Black, Color brd_color = Color::Black, Color ck_color = Color::Black)
	{
		background_color.hovered = bg_color;
		text_color.hovered = txt_color;
		border_color.hovered = brd_color;
		check_color.hovered = ck_color;
	}

	void setClickedColors(Color bg_color = Color(190, 190, 190), Color txt_color = Color::Black, Color brd_color = Color::Black, Color ck_color = Color::Black)
	{
		background_color.clicked = bg_color;
		text_color.clicked = txt_color;
		border_color.clicked = brd_color;
		check_color.clicked = ck_color;
	}


	void setBorderSize(float size)
	{
		background.setOutlineThickness(size);
	}


	void setIndentationImg(int indentation)
	{
		this->indentation = indentation;
	}

	void display()
	{
		if (!is_visible)
			return;

		window->draw(background);
		if (is_checked) window->draw(check);
		window->draw(caption);
	}


	int getEvent(sf::Event &event)
	{
		if (!is_enabled) return Event::Nothing;

		Vector2f mouse = window->mapPixelToCoords(Mouse::getPosition(*window));

		if (isIn(Mouse::getPosition(*window)))
		{
			if (onHover) onHover();
			Brush(background_color.hovered, text_color.hovered, border_color.hovered, check_color.hovered);
		}
		else
		{
			if (onHoverOut) onHoverOut();
			Brush(background_color.basic, text_color.basic, border_color.basic, check_color.basic);
		}

		if (ClickedOn(event, mouse))
		{
			if (!is_checked)
			{
				if (onChecked) onChecked();

				is_checked = true;
				return Event::Checked;
			}
			else
			{
				if (onUnchecked) onUnchecked();
				return Event::Unchecked;
			}
		}

		if (click_in)
			Brush(background_color.clicked, text_color.clicked, border_color.clicked, check_color.clicked);

		return Event::Nothing;
	}
	
	enum Event
	{
		Nothing = 0,
		Checked,
		Unchecked
	};

	void(*onChecked)() = NULL;
	void(*onUnchecked)() = NULL;
	void(*onHover)() = NULL;
	void(*onHoverOut)() = NULL;
}; 

class RadioButtonContainer
{
protected:
	list <RadioButton*> radio_buttons;

public:
	void add(RadioButton &radio_button)
	{
		radio_buttons.push_back(&radio_button);
	}

	void events(sf::Event &event)
	{
		for (auto radio_button : radio_buttons)
		{
			if (radio_button->getEvent(event) == RadioButton::Event::Checked)
			{
				for (auto rb : radio_buttons)
					rb->is_checked = false;
				radio_button->is_checked = true;
				break;
			}
		}
	}

	void display() 
	{
		for (auto radio_button : radio_buttons)
			radio_button->display();
	}
};

class TextBox : 
	public Enable, 
	public Click, 
	public Visible, 
	public Background,
	public RenderWindowElement
{
protected:
	RenderTexture wordspace_render;
	Text text;
	Sprite wordspace;
	Clock clock;
	RectangleShape text_cursor;
	wstring result_text = L"";
	FloatRect cursor_identication;

	bool is_typing = false, for_break = false;
	double frames = 0;
	int char_pos = 0, identication;

	ActiveColor background_color,
		text_color,
		border_color;

	int boder_size = 2;

	void background_update()
	{
		wstring buf = text.getString().toWideString();
		text.setString("Hello, World!");
		window->draw(text);

		int size_y = text.getLocalBounds().height + text.getLocalBounds().top;

		text.setOrigin(-int(size.y / 2 - size_y / 2), -int(size.y / 2 - size_y / 2));
		text_cursor.setOrigin(-(size.y / 2 - size_y / 2), -(size.y / 2 - text_cursor.getSize().y / 2));

		text.setString(buf);
	}

	void Brush(Color bg_color, Color txt_color, Color brd_color)
	{
		background.setFillColor(bg_color);
		text.setFillColor(txt_color);
		background.setOutlineColor(brd_color);
	}

	void update()
	{
		float time = 0;

		if (is_typing)
		{
			time = clock.getElapsedTime().asSeconds();
			clock.restart();

			if ((int)frames < 2)
				frames += time * 2;
			else
				frames = 0;
		}
		else
			frames = 1;
	}

	FloatRect getTextBounds(wstring line)
	{
		Text text_ = text;

		text_.setString(line);
		window->draw(text_);

		return text_.getLocalBounds();
	}

	FloatRect getTextBounds(string line)
	{
		Text text_ = text;
		text_.setString(line);
		window->draw(text_);

		return text_.getLocalBounds();
	}

	void size_update()
	{
		wordspace_render.create((int)size.x, (int)size.y, true);
		wordspace.setTexture(wordspace_render.getTexture(), true);
		background.setSize(size);
		
		background_update();
	}

	void position_update()
	{
		wordspace.setPosition(position);
		background.setPosition(position);

		background_update();
	}

public:

	TextBox(RenderWindow &window, Font &font)
	{
		this->window = &window;
		setFont(font);

		size = Vector2f(75, 25);
		position = Vector2f(0, 0);

		setBasicColors();
		setHoveredColors();
		setClickedColors();
		setBorderSize(-1);

		setSize(size);
		setPosition(position);
		text.setCharacterSize(15);
		text.setPosition(0, 0);

		text_cursor.setSize(Vector2f(2, 15*1.2));
		text_cursor.setFillColor(Color::Black);

		wordspace.setTexture(wordspace_render.getTexture(), true);
	}


	void setSizeByCaption(Vector2f interval = Vector2f(5, 5))
	{
		wstring buf = text.getString().toWideString();
		text.setString("Hello, World!");
		window->draw(text);

		setSize((text.getLocalBounds().width - text.getLocalBounds().left) + interval.x * 2,
			(text.getLocalBounds().height + text.getLocalBounds().top) + interval.y * 2);

		text.setString(buf);
	}


	void setBasicColors(Color bg_color = Color(255, 255, 255), Color txt_color = Color::Black, Color brd_color = Color::Black)
	{
		background_color.basic = bg_color;
		text_color.basic = txt_color;
		border_color.basic = brd_color;

		Brush(background_color.basic, text_color.basic, border_color.basic);
	}
																														
	void setHoveredColors(Color bg_color = Color(245, 245, 245), Color txt_color = Color::Black, Color brd_color = Color::Black)
	{
		background_color.hovered = bg_color;
		text_color.hovered = txt_color;
		border_color.hovered = brd_color;
	}
																														
	void setClickedColors(Color bg_color = Color(225, 225, 225), Color txt_color = Color::Black, Color brd_color = Color::Black)
	{
		background_color.clicked = bg_color;
		text_color.clicked = txt_color;
		border_color.clicked = brd_color;
	}
	

	void setFont(Font &font)
	{
		text.setFont(font);

		background_update();
	}


	void setTextCharacterSize(unsigned int size)
	{
		text.setCharacterSize(size);
		text_cursor.setSize(Vector2f(2, size * 1.2));

		background_update();
	}

	unsigned int getTextCharacterSize()
	{
		return text.getCharacterSize();
	}


	void setText(string text, Vector2f interval)
	{
		this->text.setString(text);
		this->result_text = wstring(text.begin(), text.end());

		setSizeByCaption(interval);

		background_update();
	}

	void setText(wstring text, Vector2f interval)
	{
		this->text.setString(text);
		this->result_text = text;

		setSizeByCaption(interval);

		background_update();
	}

	void setText(string text)
	{
		this->text.setString(text);
		this->result_text = wstring(text.begin(), text.end());

		background_update();
	}

	void setText(wstring text)
	{
		this->text.setString(text);
		this->result_text = text;

		background_update();
	}


	String getText()
	{
		return text.getString();
	}

	void display()
	{		
		if (!is_visible)
			return;
		
		update();

		wordspace_render.clear(Color::Transparent);
		wordspace_render.draw(text);
		if ((int)frames % 2 != 0 && is_typing) 
			wordspace_render.draw(text_cursor);
		wordspace_render.display();

		window->draw(background);
		window->draw(wordspace);
	}


	int getEvent(sf::Event &event)
	{
		Vector2f mouse = window->mapPixelToCoords(Mouse::getPosition(*window));

		if (isIn(Mouse::getPosition(*window))) 
		{
			if (onHover) onHover();
			Brush(background_color.hovered, text_color.hovered, border_color.hovered);
			return Event::Hovered;
		}
		else 
		{
			if (onHoverOut) onHoverOut();
			Brush(background_color.basic, text_color.basic, border_color.basic);
		}

		if (ClickedOn(event, mouse))
		{
			if (onClick) onClick();

			is_typing = true;
			frames = 1;

			return Event::Clicked;
		}

		if (ClickedOut(event, mouse))
		{
			is_typing = false;

			identication = 0;
			char_pos = 0;

			text_cursor.setPosition(text.getPosition().x + cursor_identication.width + cursor_identication.left, text.getPosition().y);
			text.setPosition(identication, text.getPosition().y);

			return Event::Clicked_out;
		}
			
		if (is_typing)
		{
			if (event.type == sf::Event::KeyPressed && event.key.code == Keyboard::BackSpace)
			{
				if (char_pos != 0)
				{
					result_text = result_text.substr(0, char_pos - 1) + result_text.substr(char_pos, result_text.length());
					--char_pos;
				}
				frames = 1;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == Keyboard::Delete)
			{
				if (result_text.length() != 0 && char_pos < result_text.length())
					result_text = result_text.substr(0, char_pos) + result_text.substr(char_pos + 1, result_text.length());
				frames = 1;
			}

			if (event.type == sf::Event::TextEntered)
			{
				switch (int(event.text.unicode))
				{
				case 8:
					break;
				case 127:
					break;
				case 13:
					break;
				default:
					result_text = result_text.substr(0, char_pos) + event.text.unicode + result_text.substr(char_pos, result_text.length());
					++char_pos;
					break;
				}
				frames = 1;

				if (onTextChanged) 
					onTextChanged();
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == Keyboard::Left)
			{
				if (char_pos - 1 >= 0) --char_pos;
				frames = 1;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == Keyboard::Right)
			{
				if (char_pos < result_text.length()) ++char_pos;
				frames = 1;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == Keyboard::Home)
			{
				char_pos = 0;
				frames = 1;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == Keyboard::End)
			{
				char_pos = result_text.length();
				frames = 1;
			}

			cursor_identication = getTextBounds(result_text.substr(0, char_pos));
			text_cursor.setPosition(text.getPosition().x + cursor_identication.width + cursor_identication.left, text.getPosition().y);
			text.setPosition(identication, text.getPosition().y);

			if (text_cursor.getPosition().x + 10 > size.x)
				identication -= text_cursor.getPosition().x - size.x + 10;
			else
				if (text_cursor.getPosition().x - 10 < 0)
					identication += 0 - text_cursor.getPosition().x + 10;

			if (identication > 0) 
				identication = 0;
			
			cursor_identication = getTextBounds(result_text.substr(0, char_pos));
			text_cursor.setPosition(text.getPosition().x + cursor_identication.width + cursor_identication.left, text.getPosition().y);
			text.setPosition(identication, text.getPosition().y);

			text.setString(result_text);

			if (event.type == sf::Event::KeyReleased && event.key.code == Keyboard::Return)
			{
				if (onReturned) onReturned();
				return Event::Returned;
			}
		}

		if (click_in)
			Brush(background_color.clicked, text_color.clicked, border_color.clicked);

		return Event::Nothing;
	}

	enum Event
	{
		Nothing = 0,
		Hovered,
		Clicked,
		Clicked_out,
		Returned
	};

	void(*onClick)() = NULL;
	void(*onHover)() = NULL;
	void(*onHoverOut)() = NULL;
	void(*onReturned)() = NULL;
	void(*onTextChanged)() = NULL;
};

class ProgressBar:
	public Enable,
	public PositionSize,
	public Visible,
	public Background,
	public RenderWindowElement
{
protected:
	RectangleShape progressed;
	int value = 0;
	float one_progress_step = 0;

	Color background_color,
		border_color,
		progressed_color;

	void Brush(Color bg_color, Color prg_color, Color brd_color)
	{
		background.setFillColor(bg_color);
		progressed.setFillColor(prg_color);
		background.setOutlineColor(brd_color);
	}

	void background_update() 
	{
	}

	void update()
	{
		progressed.setSize(Vector2f(one_progress_step * value, size.y));
	}

	void position_update()
	{
		background.setPosition(position);
		progressed.setPosition(position);

		background_update();
	}

	void size_update()
	{
		background.setSize(size);
		one_progress_step = size.x / 100;

		background_update();
	}

public:

	ProgressBar(RenderWindow &window)
	{
		this->window = &window;

		setSize(100, 20);
		setPosition(0, 0);

		setBasicColors();
	}
	

	void setBasicColors(Color bg_color = Color(225, 225, 225), Color prg_color = Color::Green, Color brd_color = Color::Black)
	{
		Brush(bg_color, prg_color, brd_color);
	}


	void setValue(int value_)
	{
		value = value_;

		if (value > 100) value = 100;
		if (value < 0) value = 0;

		update();
	}

	int getValue()
	{
		return this->value;
	}


	virtual void display()
	{
		if (!is_visible)
			return;

		window->draw(background);
		window->draw(progressed);
	}
};

#pragma endregion


/*
	Textured elements

	Also you can create basic GUI elements with your own design by using 
	textured elements.

	Documentation API: https://github.com/6eremotuk01/SC-Framework/blob/master/README.md#%D0%9E%D0%BF%D0%B8%D1%81%D0%B0%D0%BD%D0%B8%D0%B5-%D0%BC%D0%B5%D1%82%D0%BE%D0%B4%D0%BE%D0%B2-%D0%B8-%D0%BA%D0%BE%D0%BC%D0%BF%D0%BE%D0%BD%D0%B5%D0%BD%D1%82%D0%BE%D0%B2
*/

#pragma region Textured elements

class ElementTextures 
{
protected:
	vector<sf::Texture> textures;
	string texture_path;

public:
	ElementTextures(string texture_path)
	{
		textures = vector<sf::Texture>(9);
		this->texture_path = texture_path;
	}

	void setRects(vector<IntRect> corners, vector<IntRect> frames, IntRect background)
	{
		textures[0].loadFromFile(texture_path, corners[0]);
		textures[1].loadFromFile(texture_path, corners[1]);
		textures[2].loadFromFile(texture_path, corners[2]);
		textures[3].loadFromFile(texture_path, corners[3]);

		textures[4].loadFromFile(texture_path, frames[0]);
		textures[5].loadFromFile(texture_path, frames[1]);
		textures[6].loadFromFile(texture_path, frames[2]);
		textures[7].loadFromFile(texture_path, frames[3]);

		textures[8].loadFromFile(texture_path, background);
	}

	void setRepeated(bool rep = true)
	{
		for (auto elem : textures)
			elem.setRepeated(rep);
	}

	Texture &operator[] (int index)
	{
		return textures[index];
	}

	friend class Textured;
};

class TextureCaptionButton : 
	public CaptionButton, 
	public Textured
{
protected:
	Sprite corner_lt_basic, corner_rt_basic, corner_rb_basic, corner_lb_basic,
		frame_l_basic, frame_t_basic, frame_r_basic, frame_b_basic,
		background_basic;

	Sprite corner_lt_hover, corner_rt_hover, corner_rb_hover, corner_lb_hover,
		frame_l_hover, frame_t_hover, frame_r_hover, frame_b_hover,
		background_hover;

	Sprite corner_lt_click, corner_rt_click, corner_rb_click, corner_lb_click,
		frame_l_click, frame_t_click, frame_r_click, frame_b_click,
		background_click;

	void size_update()
	{
		IntRect corner_size = corner_lt_basic.getTextureRect();

		corner_lt_basic.setTextureRect(IntRect(0, 0, corner_size.width, corner_size.height));
		corner_rt_basic.setTextureRect(IntRect(0, 0, corner_size.width, corner_size.height));
		corner_rb_basic.setTextureRect(IntRect(0, 0, corner_size.width, corner_size.height));
		corner_lb_basic.setTextureRect(IntRect(0, 0, corner_size.width, corner_size.height));
		frame_l_basic.setTextureRect(IntRect(0, 0, corner_size.width, size.y - corner_size.height * 2));
		frame_r_basic.setTextureRect(IntRect(0, 0, corner_size.width, size.y - corner_size.height * 2));
		frame_t_basic.setTextureRect(IntRect(0, 0, size.x - corner_size.width * 2, corner_size.height));
		frame_b_basic.setTextureRect(IntRect(0, 0, size.x - corner_size.width * 2, corner_size.height));
		background_basic.setTextureRect(IntRect(0, 0,size.x - corner_size.width * 2, size.y - corner_size.height * 2));

		corner_lt_hover.setTextureRect(corner_lt_basic.getTextureRect());
		corner_rt_hover.setTextureRect(corner_rt_basic.getTextureRect());
		corner_rb_hover.setTextureRect(corner_rb_basic.getTextureRect());
		corner_lb_hover.setTextureRect(corner_lb_basic.getTextureRect());
		frame_l_hover.setTextureRect(frame_l_basic.getTextureRect());
		frame_r_hover.setTextureRect(frame_r_basic.getTextureRect());
		frame_t_hover.setTextureRect(frame_t_basic.getTextureRect());
		frame_b_hover.setTextureRect(frame_b_basic.getTextureRect());
		background_hover.setTextureRect(background_basic.getTextureRect());

		corner_lt_click.setTextureRect(corner_lt_basic.getTextureRect());
		corner_rt_click.setTextureRect(corner_rt_basic.getTextureRect());
		corner_rb_click.setTextureRect(corner_rb_basic.getTextureRect());
		corner_lb_click.setTextureRect(corner_lb_basic.getTextureRect());
		frame_l_click.setTextureRect(frame_l_basic.getTextureRect());
		frame_r_click.setTextureRect(frame_r_basic.getTextureRect());
		frame_t_click.setTextureRect(frame_t_basic.getTextureRect());
		frame_b_click.setTextureRect(frame_b_basic.getTextureRect());
		background_click.setTextureRect(background_basic.getTextureRect());

		corner_lt_basic.setOrigin(0, 0);
		corner_rt_basic.setOrigin(-corner_size.width - frame_t_basic.getTextureRect().width, 0);
		corner_rb_basic.setOrigin(-corner_size.width - frame_t_basic.getTextureRect().width, -corner_size.width - frame_r_basic.getTextureRect().height);
		corner_lb_basic.setOrigin(0, -corner_size.width - frame_r_basic.getTextureRect().height);
		frame_t_basic.setOrigin(-corner_size.width, 0);
		frame_r_basic.setOrigin(corner_size.width - size.x, -corner_size.height);
		frame_b_basic.setOrigin(-corner_size.width, corner_size.height - size.y);
		frame_l_basic.setOrigin(0, -corner_size.height);
		background_basic.setOrigin(-corner_size.width, -corner_size.height);

		corner_lt_hover.setOrigin(corner_lt_basic.getOrigin());
		corner_rt_hover.setOrigin(corner_rt_basic.getOrigin());
		corner_rb_hover.setOrigin(corner_rb_basic.getOrigin());
		corner_lb_hover.setOrigin(corner_lb_basic.getOrigin());
		frame_l_hover.setOrigin(frame_l_basic.getOrigin());
		frame_r_hover.setOrigin(frame_r_basic.getOrigin());
		frame_t_hover.setOrigin(frame_t_basic.getOrigin());
		frame_b_hover.setOrigin(frame_b_basic.getOrigin());
		background_hover.setOrigin(background_basic.getOrigin());

		corner_lt_click.setOrigin(corner_lt_basic.getOrigin());
		corner_rt_click.setOrigin(corner_rt_basic.getOrigin());
		corner_rb_click.setOrigin(corner_rb_basic.getOrigin());
		corner_lb_click.setOrigin(corner_lb_basic.getOrigin());
		frame_l_click.setOrigin(frame_l_basic.getOrigin());
		frame_r_click.setOrigin(frame_r_basic.getOrigin());
		frame_t_click.setOrigin(frame_t_basic.getOrigin());
		frame_b_click.setOrigin(frame_b_basic.getOrigin());
		background_click.setOrigin(background_basic.getOrigin());

		caption_update();
	}

	void position_update()
	{
		corner_lt_basic.setPosition(position);
		corner_rt_basic.setPosition(position);
		corner_rb_basic.setPosition(position);
		corner_lb_basic.setPosition(position);
		frame_l_basic.setPosition(position);
		frame_t_basic.setPosition(position);
		frame_r_basic.setPosition(position);
		frame_b_basic.setPosition(position);
		background_basic.setPosition(position);

		corner_lt_click.setPosition(position);
		corner_rt_click.setPosition(position);
		corner_rb_click.setPosition(position);
		corner_lb_click.setPosition(position);
		frame_l_click.setPosition(position);
		frame_t_click.setPosition(position);
		frame_r_click.setPosition(position);
		frame_b_click.setPosition(position);
		background_click.setPosition(position);

		corner_lt_hover.setPosition(position);
		corner_rt_hover.setPosition(position);
		corner_rb_hover.setPosition(position);
		corner_lb_hover.setPosition(position);
		frame_l_hover.setPosition(position);
		frame_t_hover.setPosition(position);
		frame_r_hover.setPosition(position);
		frame_b_hover.setPosition(position);
		background_hover.setPosition(position);

		caption.setPosition(position);
	}

public:
	
	TextureCaptionButton(RenderWindow &window, Font &font) : CaptionButton(window, font)
	{
	}


	void setBasicTexture(ElementTextures &texture)
	{
		corner_lt_basic.setTexture(texture[0]);
		corner_rt_basic.setTexture(texture[1]);
		corner_rb_basic.setTexture(texture[2]);
		corner_lb_basic.setTexture(texture[3]);

		frame_l_basic.setTexture(texture[4]);
		frame_t_basic.setTexture(texture[5]);
		frame_r_basic.setTexture(texture[6]);
		frame_b_basic.setTexture(texture[7]);

		background_basic.setTexture(texture[8]);
	}

	void setBasicTexture(vector<Texture> &texture)
	{
		corner_lt_basic.setTexture(texture[0]);
		corner_rt_basic.setTexture(texture[1]);
		corner_rb_basic.setTexture(texture[2]);
		corner_lb_basic.setTexture(texture[3]);

		frame_l_basic.setTexture(texture[4]);
		frame_t_basic.setTexture(texture[5]);
		frame_r_basic.setTexture(texture[6]);
		frame_b_basic.setTexture(texture[7]);

		background_basic.setTexture(texture[8]);
	}

	void setHoverTexture(ElementTextures &texture)
	{
		corner_lt_hover.setTexture(texture[0]);
		corner_rt_hover.setTexture(texture[1]);
		corner_rb_hover.setTexture(texture[2]);
		corner_lb_hover.setTexture(texture[3]);

		frame_l_hover.setTexture(texture[4]);
		frame_t_hover.setTexture(texture[5]);
		frame_r_hover.setTexture(texture[6]);
		frame_b_hover.setTexture(texture[7]);

		background_hover.setTexture(texture[8]);
	}

	void setHoverTexture(vector<Texture> &texture)
	{
		corner_lt_hover.setTexture(texture[0]);
		corner_rt_hover.setTexture(texture[1]);
		corner_rb_hover.setTexture(texture[2]);
		corner_lb_hover.setTexture(texture[3]);

		frame_l_hover.setTexture(texture[4]);
		frame_t_hover.setTexture(texture[5]);
		frame_r_hover.setTexture(texture[6]);
		frame_b_hover.setTexture(texture[7]);

		background_hover.setTexture(texture[8]);
	}

	void setClickTexture(ElementTextures &texture)
	{
		corner_lt_click.setTexture(texture[0]);
		corner_rt_click.setTexture(texture[1]);
		corner_rb_click.setTexture(texture[2]);
		corner_lb_click.setTexture(texture[3]);

		frame_l_click.setTexture(texture[4]);
		frame_t_click.setTexture(texture[5]);
		frame_r_click.setTexture(texture[6]);
		frame_b_click.setTexture(texture[7]);

		background_click.setTexture(texture[8]);
	}

	void setClickTexture(vector<Texture> &texture)
	{
		corner_lt_click.setTexture(texture[0]);
		corner_rt_click.setTexture(texture[1]);
		corner_rb_click.setTexture(texture[2]);
		corner_lb_click.setTexture(texture[3]);

		frame_l_click.setTexture(texture[4]);
		frame_t_click.setTexture(texture[5]);
		frame_r_click.setTexture(texture[6]);
		frame_b_click.setTexture(texture[7]);

		background_click.setTexture(texture[8]);
	}


	void display()
	{
		if (!is_visible)
			return;

		Vector2f mouse = window->mapPixelToCoords(Mouse::getPosition(*window));
		if (click_in)
		{
			window->draw(background_click);
			window->draw(frame_l_click);
			window->draw(frame_t_click);
			window->draw(frame_r_click);
			window->draw(frame_b_click);
			window->draw(corner_lt_click);
			window->draw(corner_rt_click);
			window->draw(corner_rb_click);
			window->draw(corner_lb_click);
		}
		else if (isIn(mouse))
		{
			window->draw(background_hover);
			window->draw(frame_l_hover);
			window->draw(frame_t_hover);
			window->draw(frame_r_hover);
			window->draw(frame_b_hover);
			window->draw(corner_lt_hover);
			window->draw(corner_rt_hover);
			window->draw(corner_rb_hover);
			window->draw(corner_lb_hover);
		}
		else
		{
			window->draw(background_basic);
			window->draw(frame_l_basic);
			window->draw(frame_t_basic);
			window->draw(frame_r_basic);
			window->draw(frame_b_basic);
			window->draw(corner_lt_basic);
			window->draw(corner_rt_basic);
			window->draw(corner_rb_basic);
			window->draw(corner_lb_basic);
		}

		window->draw(caption);
	}
};

#pragma endregion


/*
	Positions functions
	
	If you want to fast positioning your elements you can use this 
	functions.

	Documentation API: https://github.com/6eremotuk01/SC-Framework/blob/master/README.md#%D0%9E%D0%BF%D0%B8%D1%81%D0%B0%D0%BD%D0%B8%D0%B5-%D0%BC%D0%B5%D1%82%D0%BE%D0%B4%D0%BE%D0%B2-%D0%B8-%D0%BA%D0%BE%D0%BC%D0%BF%D0%BE%D0%BD%D0%B5%D0%BD%D1%82%D0%BE%D0%B2
*/

#pragma region Position function

void horizontalStack(PositionSize &element_1, PositionSize &element_2, float interval = 5.0, bool get_Y = false)
{
	if (!get_Y)
		element_2.setPosition(element_1.getPosition().x + element_1.getSize().x + interval, element_2.getPosition().y);
	else
		element_2.setPosition(element_1.getPosition().x + element_1.getSize().x + interval, element_1.getPosition().y);
}

void verticalStack(PositionSize &element_1, PositionSize &element_2, float interval = 5.0, bool get_X = false)
{
	if (!get_X)
		element_2.setPosition(element_2.getPosition().x, element_1.getPosition().y + element_1.getSize().y + interval);
	else
		element_2.setPosition(element_1.getPosition().x, element_1.getPosition().y + element_1.getSize().y + interval);
}

void horizontalCenter(PositionSize &element_1, PositionSize &element_2)
{
	element_2.setPosition(element_1.getPosition().x + (element_1.getSize().x - element_2.getSize().x) / 2, element_2.getPosition().y);
}

void verticalCenter(PositionSize &element_1, PositionSize &element_2)
{
	element_2.setPosition(element_2.getPosition().x, element_1.getPosition().y + (element_1.getSize().y - element_2.getSize().y) / 2);
}

#pragma endregion