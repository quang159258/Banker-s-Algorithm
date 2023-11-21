#pragma once
#define MAX_OBJECTS 5
#define MAX_PROPERTIES 4
#define MAX_THREAD 8 
#define v std::vector
struct Process
{
	int x;
	int y;
	int id;
    sf::RectangleShape Shape;
    sf::Text text;
    void Set(int X, int Y, int ID)
    {
        x = X;
        y = Y;
        id = ID;
    }
	void SetInfor(sf::RenderWindow *window,sf::Color color)
	{
        Shape.setSize(sf::Vector2f(50.f, 50.f));
        Shape.setFillColor(sf::Color(color));
        Shape.setPosition(sf::Vector2f(x, y));
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
            return;
        }
        text.setFont(font);
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(24);
        text.setString(to_string(id));
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(Shape.getPosition().x + Shape.getSize().x / 2.0f,
            Shape.getPosition().y + Shape.getSize().y / 2.0f);
        window->draw(Shape);
        window->draw(text);
	}
};
void DrawProcess(sf::RenderWindow *window, int x, int y, v<bool>Finish,v<Process>&P)
{
    for (int i = 0; i < Finish.size(); i++)
    {
        if (!Finish[i])
        {
            P[i].Set(x, y, i);
            P[i].SetInfor(window,sf::Color::Green);
            y += 70;
        }
    }
}
float Cal_Y(int x, const sf::CircleShape& A, const sf::RectangleShape& B)
{
    return (-(A.getPosition().y - B.getPosition().y) * 1.00 * (x - A.getPosition().x) / (B.getPosition().x - A.getPosition().x)) + A.getPosition().y;
}
struct Rq
{
    int x;
    int y;
    int id;
    sf::CircleShape Shape;
    sf::Text text;
    void Set(int X, int Y, int ID)
    {
        x = X;
        y = Y;
        id = ID;
    }
    void SetInfor(sf::RenderWindow* window, sf::Color color)
    {
        Shape.setRadius(25.f);
        Shape.setFillColor(sf::Color(color));
        Shape.setPosition(sf::Vector2f(x, y));
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
            return;
        }
        text.setFont(font);
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(24);
        text.setString(to_string(id));
        text.setPosition(Shape.getPosition().x + (Shape.getRadius() * 2 - text.getGlobalBounds().width) / 2,
            Shape.getPosition().y + (Shape.getRadius() * 2 - text.getGlobalBounds().height) / 2);
        window->draw(Shape);
        window->draw(text);
    }
    void move(sf::RenderWindow& window, sf::Color color,Process P,int speed)
    {
        SetInfor(&window,color);
        while (x <= P.x)
        {
            SetInfor(&window, color);
            window.display();
            x += speed;
            y = Cal_Y(x, Shape, P.Shape);
        }
    }
};
void DrawRequest(sf::RenderWindow* window, int x, int y, v <int>id, v<Rq>& R)
{
    R.clear();
    R.resize(id.size());
    for (int i = 0; i < id.size(); i++)
    {
        R[i].Set(x, y, id[i]);
        R[i].SetInfor(window, sf::Color::Green);
        y += 70;

    }
}
void DrawPaR(sf::RenderWindow& window, v<Process>&P, v<Rq>&R, v<int>id, v<bool>Finish,sf::RectangleShape Background)
{
    int x = window.getSize().x * 80 / 100, y = window.getSize().y * 30 / 100;
    window.draw(Background);
    DrawRequest(&window, x - 700, y, id, R);
    DrawProcess(&window, x, y, Finish, P);
}