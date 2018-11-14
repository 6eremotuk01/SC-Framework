#pragma once

#include "Base.h"
#include "VirtualControls.h"

using namespace sf;
using namespace std;

/*
	ToDo:
		- у WirtualWindow создать переменную события (так сказать буффер, который хранит последнее событие в классе)
		- Сделать у WirtualWindow функцию изменения размера окна по растяжению
		* Кнопка свертывания окна
*/


class ExitButton : public Click
{
protected:
	Color hovered_background_color, hovered_cross_color, hovered_border_color,
		background_color, cross_color, border_color,
		clicked_background_color, clicked_cross_color, clicked_border_color;
	Event event;
	VertexArray cross;
	RenderWindow *window;
	RectangleShape background;
	
	int indentation = 3;

	void Brush(Color bg_color, Color color_cross, Color brd_color)
	{
		background.setFillColor(bg_color);
		for (int i = 0; i < 8; i++)
			cross[i].color = color_cross;
		background.setOutlineColor(brd_color);
	}


public:
	ExitButton()
	{
		cross = VertexArray(sf::Quads, 8);

		setPosition(0, 0);
		setBasicColors(Color::Transparent, Color::White, Color::White);
		setHoveredColors(Color::Red, Color::White, Color::White);
		setClickedColors(Color(255, 125, 125), Color::White, Color::White);
		setSize(20, 20);
	}

	ExitButton(RenderWindow &window)
	{
		setWindow(window);

		cross = VertexArray(sf::Quads, 8);

		setPosition(0, 0);
		setBasicColors(Color::Transparent, Color::White, Color::White);
		setHoveredColors(Color::Red, Color::White, Color::White);
		setClickedColors(Color(255, 125, 125), Color::White, Color::White);
		setSize(20, 20);
	}


	void setWindow(RenderWindow &window)
	{
		this->window = &window;
	}


	void setPosition(Vector2f new_position)
	{
		this->position = new_position;

		cross[0].position = Vector2f(position.x + indentation + 3, position.y + indentation);
		cross[1].position = Vector2f(position.x + indentation, position.y + indentation + 3);
		cross[2].position = Vector2f(position.x + size.y - indentation - 3, position.y + size.y - indentation);
		cross[3].position = Vector2f(position.x + size.y - indentation, position.y + size.y - indentation - 3);

		cross[4].position = Vector2f(position.x + size.x - indentation - 3, position.y + indentation);
		cross[5].position = Vector2f(position.x + size.x - indentation, position.y + indentation + 3);
		cross[6].position = Vector2f(position.x + indentation + 3, position.y + size.y - indentation);
		cross[7].position = Vector2f(position.x + indentation, position.y + size.y - indentation - 3);

		background.setPosition(position);
	}

	void setPosition(float new_position_x, float new_position_y)
	{
		setPosition(Vector2f(new_position_x, new_position_y));
	}


	void setSize(Vector2f new_size)
	{
		this->size = new_size;

		background.setSize(size);
		setPosition(this->position);
	}

	void setSize(double new_size_x, double new_size_y)
	{
		setSize(Vector2f(new_size_x, new_size_y));
	}

	void setSize(double new_size)
	{
		setSize(Vector2f(new_size, new_size));
	}


	void setBorderSize(float size)
	{
		background.setOutlineThickness(size);
	}

	float getBorderSize()
	{
		return background.getOutlineThickness();
	}


	void setBasicColors(Color bg_color, Color txt_color, Color brd_color)
	{
		background_color = bg_color;
		cross_color = txt_color;
		border_color = brd_color;

		Brush(background_color, cross_color, border_color);
	}

	void setHoveredColors(Color bg_color, Color txt_color, Color brd_color)
	{
		hovered_background_color = bg_color;
		hovered_cross_color = txt_color;
		hovered_border_color = brd_color;
	}

	void setClickedColors(Color bg_color, Color txt_color, Color brd_color)
	{
		clicked_background_color = bg_color;
		clicked_cross_color = txt_color;
		clicked_border_color = brd_color;
	}


	void setIndentationImg(int indentation)
	{
		this->indentation = indentation;
	}


	virtual bool isIn(Vector2f current_position)
	{
		if (position.x <= current_position.x &&
			position.y <= current_position.y &&
			position.x + size.x >= current_position.x &&
			position.y + size.y >= current_position.y) return true;

		return false;
	}

	bool isIn(Vector2i current_position)
	{
		return isIn(Vector2f(current_position));
	}

	bool isIn()
	{
		if (!window) return false;
		return isIn(window->mapPixelToCoords(Mouse::getPosition(*window)));
	}


	int getEvent(sf::Event event)
	{
		Vector2f mouse = Vector2f(window->mapPixelToCoords(Mouse::getPosition(*window)));

		if (isIn(window->mapPixelToCoords(Mouse::getPosition(*window))))
			Brush(hovered_background_color, hovered_cross_color, hovered_border_color);
		else
			Brush(background_color, cross_color, border_color);

		if (ClickedOn(event, mouse))
			return Event::Clicked;

		if (click_in)
			Brush(clicked_background_color, clicked_cross_color, clicked_border_color);

		return Event::Nothing;
	}

	enum Event
	{
		Nothing = 0,
		Hovered,
		Clicked
	};


	void display()
	{
		if (!window) return;

		window->draw(background);
		window->draw(cross);
	}

	~ExitButton()
	{
		cout << "Object: " << this << " (MaximizeButton) is sucsessfuly deleted" << endl;
	}
};

class MaximizeButton : public Click
{
protected:
	Color hovered_background_color, hovered_rect_color, hovered_border_color,
		background_color, rect_color, border_color,
		clicked_background_color, clicked_rect_color, clicked_border_color;
	Event event;
	VertexArray rect;
	RenderWindow *window;
	RectangleShape background;
	bool minimized = false;

	int indentation = 3;

	void Brush(Color bg_color, Color color_rect, Color brd_color)
	{
		background.setFillColor(bg_color);
		for (int i = 0; i < 16; i++)
			rect[i].color = color_rect;
		background.setOutlineColor(brd_color);
	}


public:
	MaximizeButton()
	{
		rect = VertexArray(sf::Quads, 16);

		setPosition(0, 0);
		setBasicColors(Color::Transparent, Color::White, Color::White);
		setHoveredColors(Color(255, 255, 255, 75), Color::White, Color::White);
		setClickedColors(Color(255, 255, 255, 120), Color::White, Color::White);
		setSize(20, 20);
	}

	MaximizeButton(RenderWindow &window)
	{
		setWindow(window);

		rect = VertexArray(sf::Quads, 16);

		setPosition(0, 0);
		setBasicColors(Color::Transparent, Color::White, Color::White);
		setHoveredColors(Color(255, 255, 255, 75), Color::White, Color::White);
		setClickedColors(Color(255, 255, 255, 120), Color::White, Color::White);
		setSize(20, 20);
	}


	void setWindow(RenderWindow &window)
	{
		this->window = &window;
	}


	void setPosition(Vector2f new_position)
	{
		this->position = new_position;

		if (!minimized)
		{
			rect = VertexArray(sf::Quads, 16);

			// Hat of the lil window
			rect[0].position = Vector2f(position.x + indentation, position.y + indentation);
			rect[1].position = Vector2f(position.x + size.x - indentation, position.y + indentation);
			rect[2].position = Vector2f(position.x + size.x - indentation, position.y + indentation + 3);
			rect[3].position = Vector2f(position.x + indentation, position.y + indentation + 3);

			// Left frame of the lil window
			rect[4].position = Vector2f(position.x + indentation, position.y + indentation);
			rect[5].position = Vector2f(position.x + indentation + 1, position.y + indentation);
			rect[6].position = Vector2f(position.x + indentation + 1, position.y + size.y - indentation);
			rect[7].position = Vector2f(position.x + indentation, position.y + size.y - indentation);

			// Right frame of the lil window
			rect[8].position = Vector2f(position.x + size.x - indentation, position.y + indentation);
			rect[9].position = Vector2f(position.x + size.x - indentation - 1, position.y + indentation);
			rect[10].position = Vector2f(position.x + size.x - indentation - 1, position.y + size.y - indentation);
			rect[11].position = Vector2f(position.x + size.x - indentation, position.y + size.y - indentation);

			// Bottom of the lil window
			rect[12].position = Vector2f(position.x + indentation, position.y + size.y - indentation - 1);
			rect[13].position = Vector2f(position.x + size.x - indentation, position.y + size.y - indentation - 1);
			rect[14].position = Vector2f(position.x + size.x - indentation, position.y + size.y - indentation);
			rect[15].position = Vector2f(position.x + indentation, position.y + size.y - indentation);
		}
		else
		{
			rect = VertexArray(sf::Quads, 32);

			// Hat of the 1st lil window
			rect[0].position = Vector2f(position.x + indentation + 3, position.y + indentation);
			rect[1].position = Vector2f(position.x + size.x - indentation, position.y + indentation);
			rect[2].position = Vector2f(position.x + size.x - indentation, position.y + indentation + 3);
			rect[3].position = Vector2f(position.x + indentation + 3, position.y + indentation + 3);

			// Left frame of the 1st lil window
			rect[4].position = Vector2f(position.x + indentation + 3, position.y + indentation);
			rect[5].position = Vector2f(position.x + indentation + 4, position.y + indentation);
			rect[6].position = Vector2f(position.x + indentation + 4, position.y + indentation + 3);
			rect[7].position = Vector2f(position.x + indentation + 3, position.y + indentation + 3);

			// Bottom frame of the 1st lil window
			rect[8].position = Vector2f(position.x + size.x - indentation - 3, position.y + size.y - indentation - 4);
			rect[9].position = Vector2f(position.x + size.x - indentation, position.y + size.y - indentation - 4);
			rect[10].position = Vector2f(position.x + size.x - indentation, position.y + size.y - indentation - 3);
			rect[11].position = Vector2f(position.x + size.x - indentation - 3, position.y + size.y - indentation - 3);

			// Right frame of the 1st lil window
			rect[12].position = Vector2f(position.x + size.x - indentation - 1, position.y + indentation);
			rect[13].position = Vector2f(position.x + size.x - indentation, position.y + indentation);
			rect[14].position = Vector2f(position.x + size.x - indentation, position.y + size.y - indentation - 3);
			rect[15].position = Vector2f(position.x + size.x - indentation - 1, position.y + size.y - indentation - 3);


			// Hat of the 2nd lil window
			rect[16].position = Vector2f(position.x + indentation, position.y + indentation + 3);
			rect[17].position = Vector2f(position.x + size.x - indentation - 3, position.y + indentation + 3);
			rect[18].position = Vector2f(position.x + size.x - indentation - 3, position.y + indentation + 6);
			rect[19].position = Vector2f(position.x + indentation, position.y + indentation + 6);
			
			// Left frame of the 2nd lil window
			rect[20].position = Vector2f(position.x + indentation, position.y + indentation + 3);
			rect[21].position = Vector2f(position.x + indentation + 1, position.y + indentation + 3);
			rect[22].position = Vector2f(position.x + indentation + 1, position.y + size.y - indentation);
			rect[23].position = Vector2f(position.x + indentation, position.y + size.y - indentation);
				 
			// Bottom frame of the 2nd lil window
			rect[24].position = Vector2f(position.x + indentation, position.y + size.y - indentation - 1);
			rect[25].position = Vector2f(position.x + size.x - indentation - 3, position.y + size.y - indentation - 1);
			rect[26].position = Vector2f(position.x + size.x - indentation - 3, position.y + size.y - indentation);
			rect[27].position = Vector2f(position.x + indentation, position.y + size.y - indentation);
				 
			// Right frame of the 2nd lil window
			rect[28].position = Vector2f(position.x + size.x - indentation - 3, position.y + indentation + 3);
			rect[29].position = Vector2f(position.x + size.x - indentation - 4, position.y + indentation + 3);
			rect[30].position = Vector2f(position.x + size.x - indentation - 4, position.y + size.y - indentation);
			rect[31].position = Vector2f(position.x + size.x - indentation - 3, position.y + size.y - indentation);
		}

		background.setPosition(position);
	}

	void setPosition(float new_position_x, float new_position_y)
	{
		setPosition(Vector2f(new_position_x, new_position_y));
	}


	void setSize(Vector2f new_size)
	{
		this->size = new_size;

		background.setSize(size);
		setPosition(this->position);
	}

	void setSize(double new_size_x, double new_size_y)
	{
		setSize(Vector2f(new_size_x, new_size_y));
	}

	void setSize(double new_size)
	{
		setSize(Vector2f(new_size, new_size));
	}


	void setBorderSize(float size)
	{
		background.setOutlineThickness(size);
	}

	float getBorderSize()
	{
		return background.getOutlineThickness();
	}


	void setBasicColors(Color bg_color, Color txt_color, Color brd_color)
	{
		background_color = bg_color;
		rect_color = txt_color;
		border_color = brd_color;

		Brush(background_color, rect_color, border_color);
	}

	void setHoveredColors(Color bg_color, Color txt_color, Color brd_color)
	{
		hovered_background_color = bg_color;
		hovered_rect_color = txt_color;
		hovered_border_color = brd_color;
	}

	void setClickedColors(Color bg_color, Color txt_color, Color brd_color)
	{
		clicked_background_color = bg_color;
		clicked_rect_color = txt_color;
		clicked_border_color = brd_color;
	}


	void setIndentationImg(int indentation)
	{
		this->indentation = indentation;
	}

	void setState(bool minimized)
	{
		this->minimized = minimized;
	}


	virtual bool isIn(Vector2f current_position)
	{
		if (position.x <= current_position.x &&
			position.y <= current_position.y &&
			position.x + size.x >= current_position.x &&
			position.y + size.y >= current_position.y) return true;

		return false;
	}

	bool isIn(Vector2i current_position)
	{
		return isIn(Vector2f(current_position));
	}

	bool isIn()
	{
		if (!window) return false;
		return isIn(window->mapPixelToCoords(Mouse::getPosition(*window)));
	}


	int getEvent(sf::Event event)
	{
		Vector2f mouse = Vector2f(window->mapPixelToCoords(Mouse::getPosition(*window)));

		if (isIn(mouse))
			Brush(hovered_background_color, hovered_rect_color, hovered_border_color);
		else
			Brush(background_color, rect_color, border_color);

		if (ClickedOn(event, mouse))
			return Event::Clicked;

		if (click_in)
			Brush(clicked_background_color, clicked_rect_color, clicked_border_color);

		return Event::Nothing;
	}

	enum Event
	{
		Nothing = 0,
		Hovered,
		Clicked
	};


	void display()
	{
		if (!window) return;

		window->draw(background);
		window->draw(rect);
	}

	~MaximizeButton()
	{
		cout << "Object: " << this << " (MaximizeButton) is sucsessfuly deleted" << endl;
	}
};


class VirtualWindow : public Size, public Position
{
protected:
	Text caption;

	Vector2f pos_for_move = Vector2f(0, 0),
		position_limit = Vector2f(0, 0),
		wframe_size,
		workspace_position,
		minimized_size,
		minimized_position;

	sf::String full_string,
		short_string;

	Sprite workspace;
	RenderWindow *window;
	RectangleShape border,
		simple_shadow,
		not_active_mask;
	Color border_color,
		workspace_color,
		not_active_mask_color;

	int border_size,
		hat_size;
	bool grubbed = false,
		is_active = true,
		is_open = false,
		maximized = false;

	bool isIn(Vector2f current_position)
	{
		if (position.x <= current_position.x &&
			position.y <= current_position.y &&
			position.x + wframe_size.x >= current_position.x &&
			position.y + wframe_size.y >= current_position.y) return true;

		return false;
	}

	bool isIn(Vector2i current_position)
	{
		return isIn(Vector2f(current_position));
	}

	bool isIn()
	{
		return isIn(window->mapPixelToCoords(Mouse::getPosition(*window)));
	}


	bool isInHat(Vector2f current_position)
	{
		if (current_position.x >= position.x && current_position.x <= position.x + size.x &&
			current_position.y >= position.y && current_position.y <= position.y + hat_size) return true;

		return false;
	}

	bool isInHat(Vector2i current_position)
	{
		return isInHat(Vector2f(current_position));
	}

	bool isInHat()
	{
		return isInHat(window->mapPixelToCoords(Mouse::getPosition(*window)));
	}


	Vector2f positionByWindow(Vector2f current_position)
	{
		return Vector2f(current_position.x - position.x, current_position.y - position.y);
	}

	Vector2f positionByWindow(Vector2i current_position)
	{
		return positionByWindow(Vector2f(current_position));
	}

	Vector2f positionByWindow()
	{
		return positionByWindow(Vector2f(window->mapPixelToCoords(Mouse::getPosition(*window))));
	}

public:
	RenderTexture workspace_render;
	ExitButton exit_button;
	MaximizeButton maximize_button;

	VirtualWindow(RenderWindow &window)
	{
		this->window = &window;
		exit_button.setWindow(window);
		maximize_button.setWindow(window);

		size = Vector2f(150, 100);
		position = Vector2f(0, 0);

		hat_size = 30;
		border_size = 5;

		setColor(Color(0, 155, 255), Color(255, 255, 255, 125));
		workspace_color = Color::White;
		simple_shadow.setFillColor(Color(0, 0, 0, 125));

		setSize(size);
		setCaptionCharacterSize();

		maximize_button.setIndentationImg(4);
		exit_button.setIndentationImg(4);
	}

	VirtualWindow()
	{
		size = Vector2f(150, 100);
		position = Vector2f(0, 0);

		hat_size = 30;
		border_size = 5;

		setColor(Color(0, 155, 255), Color(255, 255, 255, 125));
		workspace_color = Color::White;
		simple_shadow.setFillColor(Color(0, 0, 0, 125));

		setSize(size);
		setCaptionCharacterSize();

		maximize_button.setIndentationImg(4);
		exit_button.setIndentationImg(4);
	}


	VirtualWindow(const VirtualWindow &wind)
	{
		position = wind.position;
		size = wind.size;
		caption = wind.caption;
		pos_for_move = wind.pos_for_move;
		position_limit = wind.position_limit;
		wframe_size = wind.wframe_size;
		workspace_position = wind.workspace_position;
		workspace = wind.workspace;
		exit_button = wind.exit_button;
		window = wind.window;
		border = wind.border;
		simple_shadow = wind.simple_shadow;
		not_active_mask = wind.not_active_mask;
		border_color = wind.border_color;
		workspace_color = wind.workspace_color;
		border_size = wind.border_size;
		hat_size = wind.hat_size;
		grubbed = wind.grubbed;
	}

	void operator= (const VirtualWindow &wind)
	{
		position = wind.position;
		size = wind.size;
		caption = wind.caption;
		pos_for_move = wind.pos_for_move;
		position_limit = wind.position_limit;
		wframe_size = wind.wframe_size;
		workspace_position = wind.workspace_position;
		workspace = wind.workspace;
		exit_button = wind.exit_button;
		window = wind.window;
		border = wind.border;
		simple_shadow = wind.simple_shadow;
		not_active_mask = wind.not_active_mask;
		border_color = wind.border_color;
		workspace_color = wind.workspace_color;
		border_size = wind.border_size;
		hat_size = wind.hat_size;
		grubbed = wind.grubbed;
	}


	void setWindow(RenderWindow &window)
	{
		this->window = &window;
		maximize_button.setWindow(window);
		exit_button.setWindow(window);
	}


	void setPosition(Vector2f new_position)
	{
		this->position = new_position;
		if (!maximized) minimized_position = size;
		this->workspace_position = Vector2f(position.x + border_size, position.y + hat_size);

		border.setPosition(position);
		not_active_mask.setPosition(position);
		simple_shadow.setPosition(position.x + 5, position.y + 5);
		exit_button.setPosition(position.x + border_size + size.x - exit_button.getSize().x, position.y + (hat_size/2 - exit_button.getSize().y/2));
		maximize_button.setPosition(exit_button.getPosition().x - maximize_button.getSize().x, exit_button.getPosition().y);
		caption.setPosition(position.x + border_size, position.y);

		workspace.setPosition(position);
	}

	void setPosition(Vector2i new_position)
	{
		setPosition(Vector2f(new_position));
	}

	void setPosition(double position_x, double position_y)
	{
		setPosition(Vector2f(position_x, position_y));
	}


	void setSize(Vector2f new_size)
	{
		float title_size_x = 0;

		this->size = new_size;
		if (!maximized) minimized_size = size;
		this->wframe_size = Vector2f(size.x + border_size * 2, size.y + hat_size + border_size);

		workspace_render.create(int(size.x), int(size.y));
		workspace.setTexture(workspace_render.getTexture(), true);
		workspace.setOrigin(0 - border_size, 0 - hat_size);

		not_active_mask.setSize(wframe_size);
		exit_button.setSize(hat_size - border_size * 2);
		maximize_button.setSize(exit_button.getSize());
		border.setSize(this->wframe_size);
		simple_shadow.setSize(border.getSize());

		setPosition(position);

		short_string = full_string;
		caption.setString(short_string);
		window->draw(caption);
		title_size_x = caption.getLocalBounds().width + (hat_size / 2 - (caption.getLocalBounds().height + caption.getLocalBounds().top) / 2);
		while (title_size_x > maximize_button.getPosition().x - position.x)
		{
			caption.setString(short_string);
			window->draw(caption);

			title_size_x = caption.getLocalBounds().width + (hat_size / 2 - (caption.getLocalBounds().height + caption.getLocalBounds().top) / 2);

			short_string = short_string.substring(0, short_string.getSize() - 1);
			short_string[short_string.getSize() - 1] = '.';
			short_string[short_string.getSize() - 2] = '.';
			short_string[short_string.getSize() - 3] = '.';
		}
		int or = -(hat_size / 2 - (caption.getLocalBounds().height + caption.getLocalBounds().top) / 2);
		caption.setOrigin(or + border_size, or);

		setPosition(position);
	}

	void setSize(double width, double height)
	{
		setSize(Vector2f(width, height));
	}

	void setSize(Vector2i new_size)
	{
		setSize(Vector2f(new_size));
	}


	void setButtonsSize(Vector2f size)
	{
		exit_button.setSize(size);
		maximize_button.setSize(size);
	}

	void setButtonsSize(float size_x, float size_y)
	{
		setButtonsSize(Vector2f(size_x, size_y));
	}

	void setButtonsSize(float size)
	{
		setButtonsSize(Vector2f(size, size));
	}


	void setCaption(string line)
	{
		full_string = String(line);
		caption.setString(line);
		setPosition(position);
		setSize(size);
	}

	void setCaption(wstring line)
	{
		full_string = String(line);
		caption.setString(line);
		setPosition(position);
		setSize(size);
	}


	void setCaptionStyle(int style)
	{
		caption.setStyle(style);
	}

	void setCaptionCharacterSize(int size = 0)
	{
		if (size == 0)
			caption.setCharacterSize(hat_size / 2);
		else caption.setCharacterSize(size);
		setSize(this->size);
	}

	void setCaptionColor(Color color)
	{
		caption.setFillColor(color);
	}


	void setFont(Font &font)
	{
		caption.setFont(font);
		setPosition(position);
	}


	void setBorderSize(int size)
	{
		border_size = size;
		setSize(this->size);
		setPosition(position);
	}

	void setHatSize(int size)
	{
		hat_size = size;
		setSize(this->size);
		setPosition(position);
	}


	sf::String getCaption()
	{
		return caption.getString();
	}


	void setSmooth(bool smooth)
	{
		workspace_render.setSmooth(smooth);
	}

	
	void setColor(Color color = Color(0, 155, 255), Color isnt_active = Color(255, 255, 255, 125))
	{
		border_color = color;
		not_active_mask_color = isnt_active;

		not_active_mask.setFillColor(isnt_active);
		border.setFillColor(color);
	}

	Color getBorderColor()
	{
		return border_color;
	}

	Color getNoActiveMaskColor()
	{
		return not_active_mask_color;
	}


	void setOutlineThickness(int size)
	{
		border.setOutlineThickness(size);
	}

	void setOutlineColor(Color color)
	{
		border.setOutlineColor(color);
	}


	RenderWindow *getWindow()
	{
		return window;
	}


	bool isOpen()
	{
		return is_open;
	}

	bool isActive()
	{
		return is_active;
	}

	bool isMaximized()
	{
		return maximized;
	}


	int getEvent(sf::Event event)
	{
		Vector2f mouse = window->mapPixelToCoords(Mouse::getPosition(*window));

		// Closed event
		if (exit_button.getEvent(event) == ExitButton::Event::Clicked)
		{
			is_open = false;
			return Event::Closed;
		}

		// Maximized event
		if (maximize_button.getEvent(event) == MaximizeButton::Event::Clicked)
		{
			if (!maximized)
			{
				Maximize();
				return Event::Maximized;
			}
			else
			{
				Minimize();
				return Event::Minimized;
			}
		}

		/*MOVING WINDOW*/
		//Grabbed event
		if (event.type == sf::Event::MouseButtonPressed && event.key.code == Mouse::Left && isInHat(mouse) 
			&& !exit_button.isIn(mouse) && !maximize_button.isIn(mouse))
		{
			grubbed = true;
			Vector2f koef = Vector2f(minimized_size.x / size.x, minimized_size.y / size.y);
			pos_for_move = Vector2f(positionByWindow(mouse).x * koef.x, positionByWindow(mouse).y);
			return Event::Grubbed;
		}

		//Moved event
		if (grubbed && event.type == sf::Event::MouseMoved)
		{
			if (maximized)
			{
				maximized = false;
				maximize_button.setState(false);
				setSize(minimized_size);
			}
			setPosition(mouse - pos_for_move);
			return Event::Moved;
		}

		//Ungrabbed event
		if (grubbed && event.type == sf::Event::MouseButtonReleased && event.key.code == Mouse::Left)
		{
			grubbed = false;
			return Event::Ungrubbed;
		}

		//ClickedIn event
		if (event.type == sf::Event::MouseButtonPressed && event.key.code == Mouse::Left && isIn(mouse))
		{
			is_active = true;
			return Event::ClickedIn;
		}

		if (isIn(mouse))
			return Event::Hovered;

		return Event::Nothing;
	}

	enum Event
	{
		Nothing = 0,
		Closed,
		Grubbed,
		Ungrubbed,
		Moved,
		ClickedIn,
		Maximized,
		Minimized,
		Hovered,
	};


	void clear(Color color = Color::White)
	{
		if (!is_open) return;

		workspace_render.clear(color);
	}


	void draw(const Drawable &drawable, const RenderStates &states = RenderStates::Default)
	{
		if (!is_open) return;

		workspace_render.draw(drawable, states);
	}

	void draw(CaptionButton &button)
	{
		if (!is_open)
		{
			button.window_position = NULL;
			return;
		}

		if (!button.isVisible()) 
			return;

		button.window_position = &workspace_position;

		workspace_render.draw(button.background);
		workspace_render.draw(button.caption);
	}

	void draw(Label &label)
	{
		if (!is_open)
		{
			label.window_position = NULL;
			return;
		}

		if (!label.isVisible()) 
			return;

		label.window_position = &workspace_position;

		workspace_render.draw(label.caption);
	}

	void draw(CheckBox &checkbox)
	{
		if (!is_open)
		{
			checkbox.window_position = NULL;
			return;
		}

		if (!checkbox.isVisible()) 
			return;

		checkbox.window_position = &workspace_position;

		workspace_render.draw(checkbox.background);
		if (checkbox.isChecked()) workspace_render.draw(checkbox.check);
		workspace_render.draw(checkbox.caption);
	}

	void draw(TextBox &textbox)
	{
		if (!is_open)
		{
			textbox.window_position = NULL;
			return;
		}

		if (!textbox.isVisible())
			return;

		textbox.window_position = &workspace_position;

		textbox.update();
		textbox.wordspace_render.clear(Color::Transparent);
		textbox.wordspace_render.draw(textbox.text);
		if ((int)textbox.frames % 2 != 0 && textbox.is_typing)
			textbox.wordspace_render.draw(textbox.text_cursor);
		textbox.wordspace_render.display();
		workspace_render.draw(textbox.background);
		workspace_render.draw(textbox.wordspace);
	}


	void display()
	{
		Vector2f mouse = Vector2f(window->mapPixelToCoords(Mouse::getPosition(*window)));

		if (is_active)
			window->draw(simple_shadow);

		window->draw(border);
		window->draw(caption);
		exit_button.display();
		maximize_button.display();
		workspace_render.display();
		window->draw(workspace);
		
		if (!is_active)
			window->draw(not_active_mask);
	}


	void Minimize()
	{
		maximized = false;
		maximize_button.setState(maximized);
		setPosition(minimized_position);
		setSize(minimized_size);
	}

	void Maximize()
	{
		maximized = true;
		maximize_button.setState(maximized);
		minimized_size = size;
		minimized_position = position;
		setPosition(0, 0);
		setSize(Vector2f(window->mapPixelToCoords(Vector2i(window->getSize())).x - border_size * 2, window->mapPixelToCoords(Vector2i(window->getSize())).y - hat_size - border_size));
	}


	~VirtualWindow()
	{
		cout << "Object \"" << getCaption().toAnsiString() << "\":" << this << " (VirtualWindow) is sucsessfuly deleted" << endl;
	}


	friend class VirtualWindowsWorkspace;
	friend class VWIsIn;
};

class VirtualWindowsWorkspace
{
private:
	list<VirtualWindow*> Windows;
	Vector2f cscade_position;

	bool repeat = false, cascade = true;
	int cascade_number = 0, cascade_step = 25, cascade_max = 5;

public:
	void setCascade(bool cascade)
	{
		this->cascade = cascade;
	}

	void setCascadeParameters(int step, int max_cascade)
	{
		this->cascade_step = step;
		this->cascade_max = max_cascade - 1;
	}

	void setCascadeStartPosition(Vector2f position)
	{
		this->cscade_position = position;
	}

	Vector2f getCascadeStartPosition()
	{
		return cscade_position;
	}


	void closeAll()
	{
		Windows.clear();

		for (auto window : Windows)
		{
			window->is_active = false;
			window->is_open = false;
		}
	}

	void add(VirtualWindow &virtual_window)
	{
		if (cascade && !virtual_window.maximized)
		{
			virtual_window.setPosition(Vector2f(cscade_position.x + cascade_number * cascade_step, cscade_position.y + cascade_number * cascade_step));
			if (cascade_number >= cascade_max) cascade_number = 0;
			else cascade_number++;
		}

		for (auto window : Windows)
			window->is_active = false;

		Windows.push_front(&virtual_window);
		virtual_window.is_active = true;
		virtual_window.is_open = true;
	}


	bool events(Event &event)
	{
		for (list<VirtualWindow*>::iterator it = Windows.begin(); it != Windows.end(); it++)
		{
			switch ((*it)->getEvent(event))
			{
			case VirtualWindow::Event::Closed:
				it = Windows.erase(it);
				if (it != Windows.begin())it--;
				return true;
				break;

			case VirtualWindow::Event::Grubbed:
				Windows.splice(Windows.begin(), Windows, it);
				for (auto window : Windows)
					window->is_active = false;
				(*it)->is_active = true;
				return true;
				break;

			case VirtualWindow::Event::ClickedIn:
				Windows.splice(Windows.begin(), Windows, it);
				for (auto window : Windows)
					window->is_active = false;
				(*it)->is_active = true;
				return true;
				break;
			}
		}

		return false;
	}


	void clearAll(Color color = Color::White)
	{
		for (auto window : Windows)
			window->clear(color);
	}

	void display()
	{
		for (list<VirtualWindow*>::reverse_iterator it = Windows.rbegin(); it != Windows.rend(); it++)
			(*it)->display();
	}

	~VirtualWindowsWorkspace()
	{
		cout << "Object: " << this << " (VirtualWindowsWorkspace) is sucsessfuly deleted" << endl;
	}
};