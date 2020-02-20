#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <algorithm>
#include <unordered_map>

using namespace std;

class user_canvas;
class editorspace;
class gui;

class editorspace
{
	protected:
	
	public:
	sf::RenderWindow *w1;
	unordered_map < string, sf::Drawable * > total_buffer;
	editorspace(int szx, int szy)
	{
		w1 = new sf::RenderWindow(sf::VideoMode(szx, szy), "CAGE");
		w1->setVerticalSyncEnabled(true);
	}
	void draw(user_canvas *u1);
};

class user_canvas
{
	editorspace *e1;
	sf::Font font1;
	sf::Text text1;
	string str1;
	public:
	user_canvas(editorspace *e)
	{
		font1.loadFromFile("DroidSansMono.ttf");
		text1.setFont(font1);
		text1.setString(str1);
		e1 = e;
		e1->total_buffer["text1"] = &text1;
		text1.setPosition(sf::Vector2f(5, 45));
		text1.setCharacterSize(20);
		text1.setFillColor(sf::Color(0,0,255,255));
	}

	void append_entry(char a)
	{
		str1 = str1 + a;
		text1.setString(str1);
	}

	void back_sp()
	{
		if(!str1.empty())
		{
			str1.pop_back();
			text1.setString(str1);
		}
		
	}

	
};

class gui
{
	sf::RectangleShape topbar, toolbar, horzscroll, vertscroll, compile;
	editorspace *e1;

	void push_in_buff(editorspace e1, sf::Drawable * g1, string s1)
	{
		e1.total_buffer[s1] = g1;
	}

	public:
	gui(editorspace *e)
	{
		e1 = e;
		int szx = e1->w1->getSize().x;
		int szy = e1->w1->getSize().y;

		topbar.setFillColor(sf::Color::Red);
		e1->total_buffer["topbar"] = &topbar;
		toolbar.setFillColor(sf::Color::Green);
		e1->total_buffer["toolbar"] = &toolbar;
		horzscroll.setFillColor(sf::Color::Blue);
		e1->total_buffer["horzscroll"] = &horzscroll;
		vertscroll.setFillColor(sf::Color::Yellow);
		e1->total_buffer["vertscroll"] = &vertscroll;
		compile.setFillColor(sf::Color::Black);
		e1->total_buffer["compile"] = &compile;

		topbar.setPosition(sf::Vector2f(0,0));
		topbar.setSize(sf::Vector2f(szx, 20));

		toolbar.setPosition(sf::Vector2f(0,20));
		toolbar.setSize(sf::Vector2f(szx, 20));

		vertscroll.setPosition(sf::Vector2f(szx-10, 40));
		vertscroll.setSize(sf::Vector2f(10, szy-60));

		horzscroll.setPosition(sf::Vector2f(0, szy-10));
		horzscroll.setSize(sf::Vector2f(szx-20, 10));

		compile.setPosition(sf::Vector2f(10, toolbar.getPosition().y+toolbar.getSize().y/2-8));
		compile.setSize(sf::Vector2f(50, 16));



		
	}
	void set_stack_tool()
	{

	}
	void set_stack_top()
	{

	}

};

void editorspace::draw(user_canvas *u1)
{
	while (w1->isOpen())
		{
			sf::Event e1;
			
			while (w1->pollEvent(e1))
			{
				if(e1.type == sf::Event::Closed)
				{
					w1->close();
				}
				else if(e1.type == sf::Event::KeyPressed)
				{
					if(e1.key.code == sf::Keyboard::Enter)
					{
						u1->append_entry('\n');
					}
					else if(e1.key.code == sf::Keyboard::BackSpace)
					{
						u1->back_sp();
					}
				}
				else if(e1.type == sf::Event::TextEntered)
				{
					if (e1.text.unicode != 8)
					u1->append_entry((char)e1.text.unicode);
				}
			}

			w1->clear();
			for(auto &it : total_buffer)
			{
				
				w1->draw(*it.second);
			}	
			w1->display();
		}
}

int main(int argc, char* argv[])
{
	editorspace w1(atoi(argv[1]), atoi(argv[2]));
	gui g1(&w1);
	user_canvas u1(&w1);
	w1.draw(&u1);

}
