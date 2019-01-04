# SC Framework
SimpleControl Framework - фреймворк, содержащий в себе базовые элементы управления приложением. Фреймворк основан на библиотеке SFML, языка С++.

**Меню**
* [Установка](#установка)
* [Описание файлов](#описание-файлов)
* [Пример использования](#пример-использования)

## Установка
Для работы библиотеки необходимо наличие в проекте установленной, вышеупомянутой, библиотеки SFML. Инструкция по установки библиотеки [здесь](https://www.sfml-dev.org/tutorials/2.5/start-vc.php). Подключение осуществляется через заголовок файла:
```c++
#include "VirtualControls";
```

## Описание файлов

### Base.h
Файл, содержащий в себе базовые классы:
* Позиция и размер:
    * **Position** - информация о позиции (x, y)
    * **Size** - информация о размере (x, y)
    * **IsIn** - содержит в себе методы, определяющие нахождение курсора мыши и объекта
* Состояние элемента:
    * **Enable** - включен елемент или нет
    * **Open** - открыт или закрыт
    * **Visible** - видимость объекта
    * **Checked** - установлен или нет
* Составные части элемента:
    * **Caption** - надписи для объектов
    * **Background** - задний фон для объектов (тело)
    * **Click** - методы для осуществления клика

### VirtualControls.h
Файл, который содержит в себе основные элементы управления:
* **Label** - простая надпись
* **CaptionButton** - простая кнопка с надписью
* **CheckBox** - флажок (переключатель)
* **RadioButton** - переключатели
* **RadioButtonContainer** - контейнер для переключателей. Необходим для переключения между Radio
* **TextBox** - поле для ввода текста

## Пример использования
Данная библиотека имеет свои определнные правила использования и стандарты, но не нарушает основную структуру SFML.

Программа с использованием данной библиотеки имеет следующий код (пример):

```c++
#include "VirtualWindow.h"
#include "VirtualControls.h"

using namespace sf;
using namespace std;

RenderWindow window(VideoMode(400, 300), L"Тест", Style::Default, ContextSettings(0, 0, 6));

Font font;
CaptionButton button(window); /// Кнопка

/* ПРОЦЕДРУРА ДЛЯ КНОПКИ */
void button_void()
{
	static int clicks = 0;

	++clicks;
	button.setCaption(L"Вы нажали " + to_wstring(clicks) + L" раз."); // Изменяет надпись кнопки
	button.setSizeByCaption();
}


void InitializeComponents()
{
	/* Зашрузка шрифта */
	font.loadFromFile("Consolas.ttf");

	/* Установка свойств кнопки */
	button.setPosition(10, 15);
	button.setCaptionFont(font);
	button.setCaption(L"Вы нажали 0 раз.");
	button.setSizeByCaption();
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
