#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <X11/Xlib.h>
#include <algorithm>
#include <unordered_map>
#include <unistd.h>
#include <thread>

using namespace std;


class editorspace
{
	protected:
	static sf::RenderWindow *w1;
	static unordered_map < string, sf::Drawable * > total_buffer;
	static int szx, szy;

	public:
	void push_in_buff(sf::Drawable * g1, string s1)
	{
		total_buffer[s1] = g1;
	}
};

sf::RenderWindow *editorspace::w1;
unordered_map < string, sf::Drawable * > editorspace::total_buffer;
int editorspace::szx = 0;
int editorspace::szy = 0;

class user_canvas : protected editorspace
{
	sf::Font font1;
	sf::Text text1;
	string str1;
	public:
	user_canvas(int szx1, int szy1)
	{
		szx = szx1;
		szy = szy1;
		w1 = new sf::RenderWindow(sf::VideoMode(szx, szy), "CAGE");
		w1->setVerticalSyncEnabled(true);

		font1.loadFromFile("DroidSansMono.ttf");
		text1.setFont(font1);
		text1.setString(str1);

		total_buffer["text1"] = &text1;
		text1.setPosition(sf::Vector2f(5, 45));
		text1.setCharacterSize(18);
		text1.setFillColor(sf::Color(4,191,82,255));
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

class topbar : protected editorspace
{
	sf::RectangleShape topbar1;

	public:
	topbar()
	{
		
		topbar1.setFillColor(sf::Color::Red);
		total_buffer["topbar1"] = &topbar1;
		
		topbar1.setPosition(sf::Vector2f(0,0));
		topbar1.setSize(sf::Vector2f(szx, 20));
	}
};

class toolbar : protected editorspace
{
	sf::RectangleShape toolbar1;

	public:
	toolbar()
	{
		toolbar1.setFillColor(sf::Color::Green);
		total_buffer["toolbar1"] = &toolbar1;

		toolbar1.setPosition(sf::Vector2f(0,20));
		toolbar1.setSize(sf::Vector2f(szx, 20));
	}

};

class aux : protected editorspace
{
	sf::RectangleShape vertscroll;

	public:
	aux()
	{
		vertscroll.setFillColor(sf::Color::Yellow);
		total_buffer["vertscroll"] = &vertscroll;

		vertscroll.setPosition(sf::Vector2f(szx-10, 40));
		vertscroll.setSize(sf::Vector2f(10, szy-60));

	}

	void routine(user_canvas *u1)
	{
		sf::Event e1;
		while(w1->isOpen())
		{
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
		}	
	}

	void draw()
	{
		sf::Clock cl;
		while (w1->isOpen())
			{
				cl.restart();
				w1->clear(sf::Color(112, 89, 89, 255));
				for(auto &it : total_buffer)
				{
					
					w1->draw(*it.second);
				}	
				w1->display();
				usleep(25000 - cl.restart().asMicroseconds());
			}
	}
};



int main(int argc, char* argv[])
{
	XInitThreads();
	user_canvas u1(atoi(argv[1]), atoi(argv[2]));
	topbar to1;
	toolbar tb1;
	aux a1;
	thread t1(&aux::routine, &a1, &u1);
	a1.draw();
	t1.join();
}
