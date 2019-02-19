# SC Framework
SimpleControl Framework - фреймворк, содержащий в себе базовые элементы управления пользовательского интерфейса. Фреймворк основан на библиотеке SFML и сделано для С++.

## Установка
Для работы библиотеки необходимо наличие в проекте установленной, вышеупомянутой, библиотеки SFML. Инструкция по установки библиотеки [здесь](https://www.sfml-dev.org/tutorials/2.5/start-vc.php).

## Начало работы

Подключение осуществляется через заголовок файла: `#include "VirtualControls";`. Далее создайте следующую структуру, которая является стандартной для данного фреймворка:

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
2. CaptionButton - кнопка с надписью
3. CheckBox - переключатель с галочкой
4. RadioButton - переключатель между элементами
5. RadioButtonContainer - контейнер для переключателей RadioButton
6. TextBox - поле ввода текста
7. ProgressBar - полоса прогресса

Также присутствуют базовые классы:
* Position - позиция элемента
* Size - рзамер элемента
* IsIn - класс, используемый для определния вхождения точки в размере элемента
* isEnabled - активность элемента
* Open - открытость элемента
* Visible - видимость элемента
* Checked - "включенность" элемента
* ActiveColor - цвета активности элемента
* RenderWindowElement - указатель на окно для элемента
* Caption - надпись элемента
* Background - задний фон или тело элемента
* Click - класс, используемый для определния нажатия на элемент

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
| `bool label.isVisible();` | Возвращает true, если элемент виден. false, если нет. |
| `void setCaption(std::string text)` | Устанавливает текст надписи. Параметры: *text* - текст надписи или массив символов. |
| `void setCaption(std::wstring text)` | Устанавливает текст надписи. Параметры: *text* - текст надписи или массив символов. |
| `void setCaptionCharacterSize(int size)` | Устанавливает размер шрифта надписи. Параметры: *size* - размер в пикселях. |
| `void setCaptionColor(sf::Color color)` | Устанавливает цвет шрифта надписи. Параметры: *color* - цвет надписи. |
| `void setCaptionFont(sf::Font font)` | Устанавливает шрифт надписи. Но стоит обратить внимание, что конструктор по умолчанию требует указать шрифт. Параметры: *font* - указатель на шрифт. |
| `void setCaptionOutlineThickness(int size)` | Устанавливает размер обводки шрифта надписи. Параметры: *size* - размер в пикселях. если указать отрицательное значение, то обводка станет внутреней. |
| `void setCaptionStyle(sf::Uint32 style)` | Устанавливает стиль шрфита надписи. Параметры: *style* - сочетание стилей (стиля). |
| `void setVisibility(bool visibility)` | Установка видимости элемента. Параметры: *visibility* - видимость элемента. |
| `void setPosition(sf::Vector2f position)` | Установка позиции элемента. Параметры: *position* - позиция элемента. |
| `void setPosition(float x, float y)` | Установка позиции элемента. Параметры: *x* - позиция элемента по оси X; *x* - позиция элемента по оси Y. |
| `void setSize(sf::Vector2f size)` | Установка размера элемента. Параметры: *size* - размер элемента; |
| `void setSize(float width, float height)` | Установка размера элемента. Параметры: *width* - ширина элемента; *height* - высота элемента. |
| `void setWindow(sf::RenderWindow window)` | Установка целевого окна элемента. Но стоит обратить внимание, что конструктор по умолчанию требует указать. Параметры: *window* - целевое окно. |

Данный элемент не имеет событийных процедур, а соответственно и событий.

#### CaptionButton

Предназначен для создания кнопки с надписью и привязки процедур к ней.

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
| `void setCaption(wstring text, Vector2f identication)` | Устанавливает текст надписи. Параметры: *text* - текст надписи или массив символов. *identication* - если установлен, то после изменения надписи будет вызван метод `void setSizeByCaption(identication)` |
| `void setCaption(string text, Vector2f identication)` | Устанавливает текст надписи. Параметры: *text* - текст надписи или массив символов. *identication* - если установлен, то после изменения надписи будет вызван метод `void setSizeByCaption(identication)` |
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
| `void setSizeByCaption(Vector2f interval = Vector2f(5, 5))` | Изменяет размер тела кнопки в зависимости от размера надписи. Параметры: *interval* - отличие размера тела кнопки от надписи. |
| `void setBackgroundColors(ActiveColor colors = ActiveColor(Color(225, 225, 225), Color(245, 245, 245), Color(190, 190, 190)))` | Устанавливает цвета тела кнопки. Параметры: *colors* - активные цвета тела кнопки. |
| `void setBorderColors(ActiveColor colors = ActiveColor(Color(225, 225, 225), Color(245, 245, 245), Color(190, 190, 190)))` | Устанавливает цвета рамки кнопки. Параметры: *colors* - активные цвета рамки кнопки. |
| `void setTextColors(ActiveColor colors = ActiveColor(Color(225, 225, 225), Color(245, 245, 245), Color(190, 190, 190)))` | Устанавливает цвета текста кнопки. Параметры: *colors* - активные цвета текста кнопки. |
| `ActiveColor getBackgroundColors()` | Возвращает цвета тела кнопки. |
| `ActiveColor getBorderColors()` | Возвращает цвета рамки кнопки. |
| `ActiveColor getTextColors()` | Возвращает цвета текста кнопки. |
| `int getEvent(sf::Event &event)` | Обрабатывает события для кнопки. Возвращает код события `enum Event`. Параметры: *event* - событийный объект. |
| `void(*onClick)() = NULL` | Указатель на процедуру, которая будет вызвана при нажатии на кнопку.  |
| `void(*onHover)() = NULL` | Указатель на процедуру, которая будет вызвана при наведении на кнопку.  |
| `void(*onHoverOut)() = NULL` | Указатель на процедуру, которая будет вызвана при выводе курсора за границы кнопки.  |

События пренадлежащие CaptionButton (`enum Event`).

| Наименование | Событие |
|:-|:-|
| `CaptionButton::Event::Nothing` | Никакого события не произошло |
| `CaptionButton::Event::Clicked` | Кнопка была нажата |

#### CheckBox
Предназначен для создания переключателя, имеющего два состояния `Checked` и `Unchecked`.

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
| `bool isChecked()` | Возвращает true, если у элемента стоит галочка. false, если нет. |
| `bool label.isVisible();` | Возвращает true, если элемент виден. false, если нет. |
| `void setCaption(wstring text, Vector2f identication)` | Устанавливает текст надписи. Параметры: *text* - текст надписи или массив символов. *identication* - если установлен, то после изменения надписи будет вызван метод `void setSizeByCaption(identication)` |
| `void setCaption(string text, Vector2f identication)` | Устанавливает текст надписи. Параметры: *text* - текст надписи или массив символов. *identication* - если установлен, то после изменения надписи будет вызван метод `void setSizeByCaption(identication)` |
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
| `void setIndentationImg(int indentation)` | Устанавливает отступ между началом галочки и границей поля для нее. Параметры: *indentation* - размер отступа. |
| `void setBackgroundColors(ActiveColor colors = ActiveColor(Color(225, 225, 225), Color(245, 245, 245), Color(190, 190, 190)))` | Устанавливает цвета тела переключателя. Параметры: *colors* - активные цвета тела переключателя. |
| `void setBorderColors(ActiveColor colors = ActiveColor(Color(225, 225, 225), Color(245, 245, 245), Color(190, 190, 190)))` | Устанавливает цвета рамки переключателя. Параметры: *colors* - активные цвета рамки переключателя. |
| `void setTextColors(ActiveColor colors = ActiveColor(Color(225, 225, 225), Color(245, 245, 245), Color(190, 190, 190)))` | Устанавливает цвета текста переключателя. Параметры: *colors* - активные цвета текста переключателя. |
| `void setCheckColors(ActiveColor colors = ActiveColor(Color::Black, Color::Black, Color::Black))` | Устанавливает цвета галочки переключателя. Параметры: *colors* - активные цвета текста переключателя. |
| `void setState(bool checked)` | Устанавливает состояние переключателя. Параметры: *checked* - true соответсвует `Checked`, false - `Unchecked`. |
| `ActiveColor getBackgroundColors()` | Возвращает цвета тела переключателя. |
| `ActiveColor getBorderColors()` | Возвращает цвета рамки переключателя. |
| `ActiveColor getTextColors()` | Возвращает цвета текста переключателя. |
| `ActiveColor getCheckColors()` | Возвращает цвета галочки переключателя. |
| `int getEvent(sf::Event &event)` | Обрабатывает события для переключателя. Возвращает код события `enum Event`. Параметры: *event* - событийный объект. |
| `void(*onChecked)() = NULL` | Указатель на процедуру, которая будет вызвана при переключении элемента в `Checked`. |
| `void(*onChecked)() = NULL` | Указатель на процедуру, которая будет вызвана при переключении элемента в `Unchecked`. |
| `void(*onUnchecked)() = NULL`| Указатель на процедуру, которая будет вызвана при наведении на элемент.|
| `void(*onHoverOut)() = NULL` | Указатель на процедуру, которая будет вызвана при выводе курсора за границы элемента.  |
| `void(*onHover)() = NULL` | Указатель на процедуру, которая будет вызвана при наведении на элемент.  |

События пренадлежащие CheckBox (`enum Event`).

| Наименование | Событие |
|:-|:-|
| `CheckBox::Event::Nothing` | Никакого события не произошло |
| `CheckBox::Event::Checked` | Элемент переключен в состояние `Checked` |
| `CheckBox::Event::Unchecked` | Элемент переключен в состояние `Unchecked` |

#### RadioButton
Элемент схож с CheckBox (предназначен для создания переключателя, имеющего два состояния `Checked` и `Unchecked`), но зависит от других элементов, находящихся в контенере `RadioButtonContainer`. А именно только один переключатель может быть включен в данном контейнере.

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
| `bool isChecked()` | Возвращает true, если у элемента стоит галочка. false, если нет. |
| `bool label.isVisible();` | Возвращает true, если элемент виден. false, если нет. |
| `void setCaption(wstring text, Vector2f identication)` | Устанавливает текст надписи. Параметры: *text* - текст надписи или массив символов. *identication* - если установлен, то после изменения надписи будет вызван метод `void setSizeByCaption(identication)` |
| `void setCaption(string text, Vector2f identication)` | Устанавливает текст надписи. Параметры: *text* - текст надписи или массив символов. *identication* - если установлен, то после изменения надписи будет вызван метод `void setSizeByCaption(identication)` |
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
| `void setIndentationImg(int indentation)` | Устанавливает отступ между началом галочки и границей поля для нее. Параметры: *indentation* - размер отступа. |
| `void setBackgroundColors(ActiveColor colors = ActiveColor(Color(225, 225, 225), Color(245, 245, 245), Color(190, 190, 190)))` | Устанавливает цвета тела переключателя. Параметры: *colors* - активные цвета тела переключателя. |
| `void setBorderColors(ActiveColor colors = ActiveColor(Color(225, 225, 225), Color(245, 245, 245), Color(190, 190, 190)))` | Устанавливает цвета рамки переключателя. Параметры: *colors* - активные цвета рамки переключателя. |
| `void setTextColors(ActiveColor colors = ActiveColor(Color(225, 225, 225), Color(245, 245, 245), Color(190, 190, 190)))` | Устанавливает цвета текста переключателя. Параметры: *colors* - активные цвета текста переключателя. |
| `void setCheckColors(ActiveColor colors = ActiveColor(Color::Black, Color::Black, Color::Black))` | Устанавливает цвета галочки переключателя. Параметры: *colors* - активные цвета текста переключателя. |
| `void setState(bool checked)` | Устанавливает состояние переключателя. Параметры: *checked* - true соответсвует `Checked`, false - `Unchecked`. |
| `ActiveColor getBackgroundColors()` | Возвращает цвета тела переключателя. |
| `ActiveColor getBorderColors()` | Возвращает цвета рамки переключателя. |
| `ActiveColor getTextColors()` | Возвращает цвета текста переключателя. |
| `ActiveColor getCheckColors()` | Возвращает цвета галочки переключателя. |
| `int getEvent(sf::Event &event)` | Обрабатывает события для переключателя. Возвращает код события `enum Event`. Параметры: *event* - событийный объект. |
| `void(*onChecked)() = NULL` | Указатель на процедуру, которая будет вызвана при переключении элемента в `Checked`. |
| `void(*onChecked)() = NULL` | Указатель на процедуру, которая будет вызвана при переключении элемента в `Unchecked`. |
| `void(*onUnchecked)() = NULL`| Указатель на процедуру, которая будет вызвана при наведении на элемент.|
| `void(*onHoverOut)() = NULL` | Указатель на процедуру, которая будет вызвана при выводе курсора за границы элемента.  |
| `void(*onHover)() = NULL` | Указатель на процедуру, которая будет вызвана при наведении на элемент.  |

События пренадлежащие RadioButton (`enum Event`).

| Наименование | Событие |
|:-|:-|
| `RadioButton::Event::Nothing` | Никакого события не произошло |
| `RadioButton::Event::Checked` | Элемент переключен в состояние `Checked` |
| `RadioButton::Event::Unchecked` | Элемент переключен в состояние `Unchecked` |

#### RadioButtonContainer
Указатель на элементы `RadioButton`, которые должны быть связаны между собой. Обеспечевает ограничение по включенным элементам (из всех добавленных только один элемент может находится в состоянии `Checked`, остальные - `Unchecked`).

| Метод | Описание |
|:-|:-|
| `void add(RadioButton &radio_button)` | Метод предназначен для добавления элемента `RadioButton` в контейнер. Параметры: *radio_button* - элемент `RadioButton`. |
| `void events(sf::Event &event)` | Обработка событий контейнера (в отличие от других элементов, не возвращает код события).  Параметры: *event* - событийный объект. |
| `void display()` | Рисование всех добавленных элементов в контейнер. Прорисовка элементов происходит в тех окнах, которые указаны у элементов `RadioButton`. |

#### TextBox
*Comming soon...*

#### ProgressBar
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
