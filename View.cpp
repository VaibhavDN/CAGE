#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
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
	static vector < pair < sf::Keyboard::Key, sf::Keyboard::Key > > input_buffer;

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
	sf::RectangleShape cur1;
	int transparent = 51;
	int trans_flag = 1;
	size_t cur_pos = 0;
	char trigger_flag = 'y';
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

		total_buffer["cur1"] = &cur1;
		cur1.setFillColor(sf::Color(255,255,255,transparent));
		cur1.setPosition(sf::Vector2f(5,45));
		cur1.setSize(sf::Vector2f(15,25));


	}

	void append_entry(char a)
	{
		str1.insert(str1.begin() + cur_pos, a);
		text1.setString(str1);
		/*if(trigger_flag == 'y' && a == '\n')
		{
			trigger_flag = 'n';
		}*/
		++cur_pos;
	}

	void back_sp()
	{
		if(!str1.empty() && cur_pos > 0)
		{
			str1.erase(str1.begin() + cur_pos - 1);
			text1.setString(str1);
			--cur_pos;
		}	
	}	

	void shift_cursor(char c)
	{
		if(c == 'l' && cur_pos > 0)
		{
			--cur_pos;
		}
		if(c == 'r' && cur_pos < str1.length())
		{
			++cur_pos;
		}
	}

	void set_cursor()
	{
		if(trans_flag == 1)
		{
			transparent -= 2;
			cur1.setFillColor(sf::Color(255,255,255, transparent));
			if(transparent == 0) trans_flag = 0;
		}
		else
		{
			transparent += 2;
			cur1.setFillColor(sf::Color(255,255,255, transparent));
			if(transparent > 100) trans_flag = 1;
		}
		cur1.setPosition(sf::Vector2f(text1.findCharacterPos(cur_pos).x, text1.findCharacterPos(cur_pos).y));
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


	protected:
	void cursor(user_canvas *u1)
	{
		u1->set_cursor();
	}
	void routine_updates(user_canvas *u1)
	{
		cursor(u1);
		//cout<<"chala\n";
	}

	public:
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
					if(e1.key.code == sf::Keyboard::Return)
					{
						u1->append_entry('\n');

					}
					else if(e1.key.code == sf::Keyboard::BackSpace)
					{
						u1->back_sp();
					}
					else if(e1.key.code == sf::Keyboard::Left)
					{
						u1->shift_cursor('l');
					}
					else if(e1.key.code == sf::Keyboard::Right)
					{
						u1->shift_cursor('r');
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

	void draw(user_canvas *u1)
	{
		sf::Clock cl;
		while (w1->isOpen())
			{
				routine_updates(u1);
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
	a1.draw(&u1);
	t1.join();
}
