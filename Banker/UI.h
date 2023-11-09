#pragma once
void menu()
{
	sf::Window window;
	window.create(sf::VideoMode(800, 600), "Banker's Algorithm", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(30);
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
    }
}