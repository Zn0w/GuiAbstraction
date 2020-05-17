#include <iostream>

#include <SFML/Graphics.hpp>

#include "zga.h"


int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

	sf::Font font;
	font.loadFromFile("sansation.ttf");

	// init gui
	Gui gui(new AbsoluteContainer());
	
	Label* hello_label = new Label({ 50, 50, 0, 0 });
	hello_label->setText(sf::Text("Hello Label!", font));
	gui.getRoot()->add(hello_label);

	Button* start_button = new Button({ 250, 250, 0, 0 });
	sf::Text button_text("Start", font, 20);
	button_text.setFillColor(sf::Color::Black);
	start_button->setText(button_text);
	start_button->setHandleAction([]() {
		std::cout << "Start Button is clicked!" << std::endl;
	});
	gui.getRoot()->add(start_button);

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		gui.display(&window);

		// end the current frame
		window.display();
	}

	return 0;
}