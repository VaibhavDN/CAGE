#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class ext
{
    string f_name;
    string fl;
    RenderWindow *win;
    
    unordered_map < string, string > f_list;
    unordered_map<string, vector < pair<int, string> > > fn_list;
    vector <Text> txt_vec;
public:
    ext(string s1)
    {
        f_name = s1;
    }

    void extract()
    {
        win = new RenderWindow(VideoMode(500, 1000), "Code Flow");
        maker();
    }

    void maker()
    {
        ifstream file(f_name);
        stringstream buff;
        buff << file.rdbuf();
        fl = buff.str();
        int curl_b = 0;
        int  j = 0;
        string fun;
        for(int  i = 0; i < fl.size(); ++i)
        {
            if(fl[i] == '{') ++curl_b;
            if(fl[i] == '}') --curl_b;
            j = i - 10;
            if(curl_b == 0 && fl[i] == '(')
            {
                while(fl[j++] != ' ');
                fun =  fl.substr(j,i-j);
            }
            if(curl_b != 0 && fl[i] != '\t')
            {
                f_list[fun].push_back(fl[i]);
            }
        }
        curl_b = 0;
        for(auto i = f_list.begin(); i != f_list.end(); ++i)
        {
            i->second.erase(0,2);
            string s2 = i->second;
            string bf = "";
            for(int k = 0; k < s2.size(); ++k)
            {
                if(s2[k] == '{') ++curl_b;
                if(s2[k] != '\n')
                {
                    bf.push_back(s2[k]);
                }
                else
                {
                    if(bf[0] == '}')
                    fn_list[i->first].push_back(make_pair(curl_b + 1, bf));
                    else
                    {
                        fn_list[i->first].push_back(make_pair(curl_b, bf));
                    }
                    
                    bf = "";
                }
                if(s2[k] == '}') --curl_b;  
            }
        }

        for (auto i = fn_list.begin(); i != fn_list.end(); ++i)
        {
            cout << i->first << endl;
            for(int  k = 0; k < i->second.size(); ++k)
            {
                cout << i->second[k].first << " " << i->second[k].second << endl;
            }
            cout << "\n";
        }
    }

    void flow_vis()
    {
        unordered_map < int, sf::Color> fo = {{0, Color(120,130,140,255)}, {1, Color(120,230,140,255)}, {2, Color(220,130,140,255)}, 
                                                {3, Color(120,130,240,255)}, {4, Color(120,30,140,255)}};

        Font ft;
        ft.loadFromFile("DroidSansMono.ttf");

        for (auto i = fn_list.begin(); i != fn_list.end(); ++i)
        {
            if(i->first == "main")
            {
                for(int  k = 0; k < i->second.size(); ++k)
                {
                    Text t1;
                    t1.setFont(ft);
                    t1.setString(i->second[k].second);
                    t1.setFillColor(fo[i->second[k].first]);
                    t1.setPosition(10 + i->second[k].first * 10, 10 + k * 30);
                    t1.setCharacterSize(15);
                    txt_vec.push_back(t1);
                }
            }
        }

        Event e1;
        while (win->isOpen())
        {
            while(win->pollEvent(e1))
            {
                if(e1.type == Event::Closed)
                {
                    win->close();
                }
            }
            win->clear(Color::Black);
            for(int i = 0; i < txt_vec.size(); ++i)
            {
                RectangleShape rec;
                sf::FloatRect textBounds = txt_vec[i].getGlobalBounds();
                rec.setPosition(textBounds.left, textBounds.top);

                sf::Vector2f recSize(textBounds.width, textBounds.height);
                rec.setSize(recSize);
                rec.setFillColor(sf::Color(0,0,0,0));
                rec.setOutlineThickness(1);
                rec.setOutlineColor(txt_vec[i].getColor());
                win->draw(rec);
                win->draw(txt_vec[i]);
            }
            win->display();
        }
        
        
    }
};

int main()
{
    ext x1("code.txt");
    x1.extract();
    x1.flow_vis();
}