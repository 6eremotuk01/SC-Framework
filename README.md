# SC Framework
SimpleControl Framework - фреймворк, содержащий в себе базовые элементы управления приложением. Фреймворк основан на библиотеке SFML, языка С++.

## Установка
Для работы библиотеки необходимо наличие в проекте установленной, вышеупомянутой, библиотеки SFML. Инструкция по установки библиотеки [здесь](https://www.sfml-dev.org/tutorials/2.5/start-vc.php). Подключение осуществляется через заголовок файла:
```c++
#include "VirtualControls";
```
## Пример использования

Ниже представлен простой код счетчика нажатий.

```c++
#include "VirtualWindow.h"
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
