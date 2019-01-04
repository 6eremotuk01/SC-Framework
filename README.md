# SC Framework
SimpleControl Framework - фреймворк, содержащий в себе базовые элементы управления приложением. Фреймворк основан на библиотеке SFML, языка С++.

## Установка
Для работы библиотеки необходимо наличие в проекте установленной, вышеупомянутой, библиотеки SFML. Инструкция по установки библиотеки [здесь](https://www.sfml-dev.org/tutorials/2.5/start-vc.php).

## Начало работы

Подключение осуществляется через заголовок файла: `#include "VirtualControls";`. Далее создайте следующую структуру:

```c++
#include "VirtualControls.h"

using namespace sf;

/*Создание окна*/
RenderWindow window(VideoMode(400, 300), "Testing", Style::Default);

/*Создание объектов*/
Font font;
...
Label label(window, font);

/*Инициализация компонентов*/
void InitializeComponents()
{
	/* Зашрузка шрифта */
   	font.loadFromFile("Consolas.ttf");

	/* Установка свойств для объектов*/
	label.setCaption("Hello, world!");
	...
	Label.setPosition(10, 10);
}

/*Стандартный SFML цикл*/
int main()
{
    InitializeComponents();

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::Magenta);
        label.display(); // Выводит надпись
        window.display();
    }
}
```
Данная структура самая оптимальная для использования фреймвока. Глобализация компонентов необходима для более легкой видимости. К примеру, это пригодится при установки событийных методов или процедур.

## Описание методов и компонентов

Фремворк имеет следующие компоненты:
1. Label - простая надпись
2. CaptionButton - кнопка с надпиьсю
3. CheckBox - переключатель с галочкой
4. RadioButton - переключатель между элементами
5. RadioButtonContainer - контейнер для переключателей RadioButton
6. TextBox - поле ввода текста
7. ProgressBar - полоса прогресса

#### Label
Предназначен для вывода текста.

| Метод | Описание |
|:-|:-|
| `Label(RenderWindow &window, &font)` | Конструктор элемента. Параметры: *window* - окно, в котором будет отображаться элемент; *font* - шрфит надписи. |
| `void display()` | Рисование элемента в целевом окне (для изменения окна используйте `setWindow(sf::RenderWindow window)`, но стоит обратить внимание, что конструктор по умолчанию требует указать целевое окно).|
| `sf::String getCaption()` | Возвращает надпись. |
| `int getCaptionCharacterSize()` | Возвращает размер шрифта. |
| `float getCaptionOutlineThickness()` | Возвращает толщину обводки шрифта. |
| `sf::Font getFont()` | Возвращает указатель на шрифт. Возвращает NULL, если шрифта нет. |
| `sf::Vector2f getPosition()` | Возвращает позицию элемента. |
| `sf::Vector2f getSize()` | Возвращает размер элемента. |
| `sf::RenderWindow getWindow()` | Возвращает указатель на окно. Возвращает NULL, если шрифта нет. |
| `bool isEnabled()` | Возвращает true, если элемент активен. false, если нет. |
| `bool label.isVisible();` | Возвращает true, если элемент виден. false, если нет. |
| `void setCaption(std::string caption)` | Устанавливает текст надписи. Параметры: *caption* - текст надписи или массив символов. |
| `void setCaption(std::wstring caption)` | Устанавливает текст надписи. Параметры: *caption* - текст надписи или массив символов. |
| `void setCaptionCharacterSize(int size)` | Устанавливает размер шрифта надписи. Параметры: *size* - размер в пикселях. |
| `void setCaptionColor(sf::Color color)` | Устанавливает цвет шрифта надписи. Параметры: *color* - цвет надписи. |
| `void setCaptionFont(sf::Font font)` | Устанавливает шрифт надписи. Но стоит обратить внимание, что конструктор по умолчанию требует указать шрифт. Параметры: *font* - указатель на шрифт. |
| `void setCaptionOutlineThickness(int size)` | Устанавливает размер обводки шрифта надписи. Параметры: *size* - размер в пикселях. если указать отрицательное значение, то обводка станет внутреней. |
| `void setCaptionStyle(sf::Uint32 style)` | Устанавливает стиль шрфита надписи. Параметры: *style* - сочетание стилей (стиля). |
| `void setEnability(bool enability)` | Установка активности элемента. Параметры: *enability* - активность элемента. |
| `void setVisibility(bool visibility)` | Установка видимости элемента. Параметры: *visibility* - видимость элемента. |
| `void setPosition(sf::Vector2f position)` | Установка позиции элемента. Параметры: *position* - позиция элемента. |
| `void setPosition(float x, float y)` | Установка позиции элемента. Параметры: *x* - позиция элемента по оси X; *x* - позиция элемента по оси Y. |
| `void setSize(sf::Vector2f size)` | Установка размера элемента. Параметры: *size* - размер элемента; |
| `void setSize(float width, float height)` | Установка размера элемента. Параметры: *width* - ширина элемента; *height* - высота элемента. |
| `void setWindow(sf::RenderWindow window)` | Установка целевого окна элемента. Но стоит обратить внимание, что конструктор по умолчанию требует указать. Параметры: *window* - целевое окно. |

*Comming soon...*

## Пример использования

Ниже представлен простой код счетчика нажатий.

```c++
#include "VirtualControls.h"

using namespace sf;
using namespace std;

RenderWindow window(VideoMode(400, 300), L"Тест", Style::Default, ContextSettings(0, 0, 6));

Font font;
CaptionButton button(window, font); /// Кнопка

/* ПРОЦЕДРУРА ДЛЯ КНОПКИ */
void button_void()
{
	static int clicks = 0;

	++clicks;
	button.setCaption(L"Вы нажали " + to_wstring(clicks) + L" раз.", true); // Изменяет надпись кнопки
}


void InitializeComponents()
{
	/* Зашрузка шрифта */
	font.loadFromFile("Consolas.ttf");

	/* Установка свойств кнопки */
	button.setPosition(10, 15);
	button.setCaptionFont(font);
	button.setCaption(L"Вы нажали 0 раз.", true);
	button.onClick = button_void; // Привязывает процедуру к событию кнопки
}

int main()
{
	InitializeComponents();

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			button.getEvent(event); // Считывает события для кнопки
		}

		window.clear(Color::Magenta);
		button.display(); // Выводит кнопку
		window.display();
	}
}
```
**Вывод**:

![](https://raw.githubusercontent.com/6eremotuk01/SCL-library/master/screenshot.png "Полная версия сайта")
