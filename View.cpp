#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	int x,y=0,flag=0;
	sf::RenderWindow window(sf::VideoMode(800,600),"View");
	window.setVerticalSyncEnabled(true);
	sf::Color color=sf::Color(153, 204, 255,50);
	sf::Font font;
	font.loadFromFile("FiraSans-Book.otf");
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold);
	sf::String string;
	
	sf::View view;
	view.setViewport(sf::FloatRect(0,0,1.0f,1.0f));
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::TextEntered:
					if(event.text.unicode>=32 && event.text.unicode <=126)
					{
						string+=(char)event.text.unicode;
					}
					else if(event.text.unicode==8)
					{
						string.erase(string.getSize()-1,string.getSize());
					}
					flag++;
					if(flag>40)
					{
						string+="\n";
						flag=0;
					}
					text.setString(string);
					break;
				case sf::Event::MouseWheelScrolled:
					int i=event.mouseWheel.y;
					int j=event.mouseWheelScroll.delta;
					std::cout<<i<<" "<<j<<std::endl;
					if(event.mouseWheelScroll.delta<0)
					{
						x=0;y+=10;
						std::cout<<y<<std::endl;
						view.reset(sf::FloatRect(x,y,800,600));
					}
					if(event.mouseWheelScroll.delta>0)
					{
							x=0;y=0;
							view.reset(sf::FloatRect(x,y,800,600));
					}
					window.setView(view);
					break;
			}
		}
		window.draw(text);
		window.display();
		window.clear(color);
	}
	return(0);
}
