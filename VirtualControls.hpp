#pragma once

#include "Base.hpp"

using namespace sf;
using namespace std;


class Label : 
	public Enable, 
	public Visible, 
	public Caption, 
	public Click,
	public RenderWindowElement
{
protected:
	bool click_in = false;

	void caption_update()
	{
		size =  Vector2f(caption.getLocalBounds().width + caption.getLocalBounds().left, caption.getLocalBounds().height + caption.getLocalBounds().top);
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


	void setPosition(Vector2f position)
	{
		this->position = position;

		caption.setPosition(position);
	}

	void setPosition(float x, float y)
	{
		setPosition(Vector2f(x, y));
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

	void caption_update()
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

	void background_update() 
	{
	
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
	

	void setSize(Vector2f size)
	{
		this->size = size;
		background.setSize(size);

		caption_update();
	}

	void setSize(float x, float y)
	{
		setSize(Vector2f(x, y));
	}

	
	void setCaption(wstring text, bool size = false)
	{
		caption.setString(text);

		if (size)
			setSizeByCaption();
	}

	void setCaption(string text, bool size = false)
	{
		caption.setString(text);

		if (size)
			setSizeByCaption();
	}


	void setSizeByCaption(Vector2f interval = Vector2f(5, 5))
	{
		setSize((caption.getLocalBounds().width - caption.getLocalBounds().left) + interval.x * 2,
			(caption.getLocalBounds().height + caption.getLocalBounds().top) + interval.y * 2);
		caption_update();
	}


	void setPosition(Vector2f position)
	{
		this->position = position;

		caption.setPosition(position);
		background.setPosition(position);
	}

	void setPosition(float x, float y)
	{
		setPosition(Vector2f(x, y));
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

		if (isIn(Mouse::getPosition(*window)))
			Brush(background_color.hovered, text_color.hovered, border_color.hovered);
		else
			Brush(background_color.basic, text_color.basic, border_color.basic);

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
	public RenderWindowElement
{
protected:
	VertexArray check;
	ActiveColor text_color,
		background_color,
		check_color,
		border_color;

	bool checked = false;
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

public:

	CheckBox(RenderWindow &window, Font &font)
	{
		setCaptionFont(font);
		this->window = &window;
		checked = false;

		check = VertexArray(sf::Quads, 8);
		size = Vector2f(15, 15);
		position = Vector2f(0, 0);

		setBasicColors();
		setHoveredColors();
		setClickedColors();

		background.setOutlineThickness(-1);
		setCharacterSize(15);

		setSize(size);
		setPosition(position);
	}


	void setCharacterSize(int size = 0)
	{
		if (size == 0)
			caption.setCharacterSize(this->size.y - 2);
		else
			caption.setCharacterSize(size);
		caption_update();
	}


	void setPosition(Vector2f position)
	{
		this->position = position;

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
	}

	void setPosition(float position_x, float position_y)
	{
		setPosition(Vector2f(position_x, position_y));
	}


	void setSize(Vector2f size)
	{
		this->position = position;

		background.setSize(size);
	}

	void setSize(float size_x, float size_y)
	{
		setSize(Vector2f(size_x, size_y));
	}


	Vector2f getSize()
	{
		return Vector2f(size.x + caption.getLocalBounds().width + 5, size.y);
	}


	bool isIn(Vector2f current_position)
	{
		if (window_position)
		{
			if (window_position->x + position.x <= current_position.x &&
				window_position->y + position.y <= current_position.y &&
				window_position->x + position.x + size.x + caption.getLocalBounds().width + 5 >= current_position.x &&
				window_position->y + position.y + size.y >= current_position.y) return true;
		}
		else
		{
			if (position.x <= current_position.x &&
				position.y <= current_position.y &&
				position.x + size.x + caption.getLocalBounds().width + 5 >= current_position.x &&
				position.y + size.y >= current_position.y) return true;
		}

		return false;
	}

	bool isIn(Vector2i current_position)
	{
		return isIn(Vector2f(current_position));
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


	bool isChecked()
	{
		return checked;
	}

	void setState(bool checked)
	{
		this->checked = checked;
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
		if (checked) window->draw(check);
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
			checked = !checked;
			if (checked)
			{
				if (onChecked) onChecked();
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
		setCharacterSize(15);

		setSize(size);
		setPosition(position);
	}


	void setCharacterSize(float size = 0)
	{
		if (size == 0)
			caption.setCharacterSize(this->size.y - 2);
		else
			caption.setCharacterSize(size);
		setSize(this->size);
	}


	void setPosition(Vector2f position)
	{
		this->position = position;

		check.setPosition(position);
		background.setPosition(position);
		caption.setPosition(position);
	}

	void setPosition(float position_x, float position_y)
	{
		setPosition(Vector2f(position_x, position_y));
	}


	void setSize(Vector2f size)
	{
		this->size = size;

		background.setRadius(size.x/2);
		check.setRadius(size.x / 2 - indentation * 2);
		check.setOrigin(-(indentation * 2), -(indentation * 2));
	}

	void setSize(float size_x, float size_y)
	{
		setSize(Vector2f(size_x, size_y));
	}


	Vector2f getSize()
	{
		return Vector2f(size.x + caption.getLocalBounds().width + 5, size.y);
	}


	bool isIn(Vector2f current_position)
	{
		if (window_position)
		{
			if (window_position->x + position.x <= current_position.x &&
				window_position->y + position.y <= current_position.y &&
				window_position->x + position.x + size.x + caption.getLocalBounds().width + 5 >= current_position.x &&
				window_position->y + position.y + size.y >= current_position.y) return true;
		}
		else
		{
			if (position.x <= current_position.x &&
				position.y <= current_position.y &&
				position.x + size.x + caption.getLocalBounds().width + 5 >= current_position.x &&
				position.y + size.y >= current_position.y) return true;
		}

		return false;
	}

	bool isIn(Vector2i current_position)
	{
		return isIn(Vector2f(current_position));
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

public:
	TextBox(RenderWindow &window, Font &font)
	{
		setFont(font);
		this->window = &window;
		
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


	void setSize(Vector2f size)
	{
		this->size = size;
		
		wordspace_render.create((int)size.x, (int)size.y, true);
		wordspace.setTexture(wordspace_render.getTexture(), true);

		background.setSize(size);

		background_update();
	}

	void setSize(float size_x, float size_y)
	{
		setSize(Vector2f(size_x, size_y));
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


	void setPosition(Vector2f position)
	{
		this->position = position;

		wordspace.setPosition(position);
		background.setPosition(position);
	}

	void setPosition(float position_x, float position_y)
	{
		setPosition(Vector2f(position_x, position_y));
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

	void setCharacterSize(int size)
	{
		text.setCharacterSize(size);
		text_cursor.setSize(Vector2f(2, size * 1.2));

		background_update();
	}


	void setText(string text, bool size = false)
	{
		this->text.setString(text);
		this->result_text = wstring(text.begin(), text.end());

		if (size)
			setSizeByCaption();

		background_update();
	}

	void setText(wstring text, bool size = false)
	{
		this->text.setString(text);
		this->result_text = text;

		if (size)
			setSizeByCaption();

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
		}
		else 
		{
			if (onHoverOut) onHoverOut();
			Brush(background_color.basic, text_color.basic, border_color.basic);
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

				if (onTextChanged) onTextChanged();
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
		}

		if (click_in)
			Brush(background_color.clicked, text_color.clicked, border_color.clicked);

		return Event::Nothing;
	}

	enum Event
	{
		Nothing = 0,
		Clicked,
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
	public Click,
	public Visible,
	public Background,
	public RenderWindowElement
{
protected:
	RectangleShape progressed;
	int value = 0;
	int one_progress_step = 0;

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
		one_progress_step = size.x / 100;
		progressed.setSize(Vector2f(one_progress_step * value, size.y));
	}

public:

	ProgressBar(RenderWindow &window)
	{
		this->window = &window;

		setSize(100, 20);
		setPosition(0, 0);

		setBasicColors();
	}
	

	void setSize(Vector2f size)
	{
		this->size = size;

		background.setSize(size);
		
		background_update();
	}

	void setSize(float x, float y)
	{
		setSize(Vector2f(x, y));
	}


	void setBasicColors(Color bg_color = Color(225, 225, 225), Color prg_color = Color::Green, Color brd_color = Color::Black)
	{
		Brush(bg_color, prg_color, brd_color);
	}


	void setPosition(Vector2f position)
	{
		this->position = position;
		
		background.setPosition(position);
		progressed.setPosition(position);

		background_update();
	}

	void setPosition(float x, float y)
	{
		setPosition(Vector2f(x, y));
	}


	void setValue(int value)
	{
		if (value > 100) value = 100;
		if (value < 0) value = 0;

		this->value = value;

		background_update();
	}

	int getValue()
	{
		return this->value;
	}


	void display()
	{
		if (!is_visible)
			return;

		window->draw(background);
		window->draw(progressed);
	}

	friend class VirtualWindow;
};