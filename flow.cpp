#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <X11/Xlib.h>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class ext
{
    string f_name;
    string fl;
    View v1;
    sf::Font ft, ft2;
    int top = 0;
    int fun_point = 0;
    unordered_map < int, sf::Color> fo = {{0, Color(120,130,140,255)}, {1, Color(120,230,140,255)}, {2, Color(220,130,140,255)}, 
                                                {3, Color(120,130,240,255)}, {4, Color(120,30,140,255)}};

    //RenderWindow *win;
    
    unordered_map < string, string > f_list;
    unordered_map<string, vector < pair<int, string> > > fn_list;
    vector <Text> txt_vec;
    vector <string> fun_name_vec;
public:
    ext(string s1)
    {
        f_name = s1;

    }

    void extract()
    {
        f_list.clear();
        fn_list.clear();
        txt_vec.clear();
        fun_name_vec.clear();
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
                fun_name_vec.push_back(fun);
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

        /*for (auto i = fn_list.begin(); i != fn_list.end(); ++i)
        {
            cout << i->first << endl;
            for(int  k = 0; k < i->second.size(); ++k)
            {
                cout << i->second[k].first << " " << i->second[k].second << endl;
            }
            cout << "\n";
        }*/
    }

    void set_fun_point()
    {
        if(fun_name_vec.size() - 1 > fun_point) ++fun_point;
        else fun_point = 0;
    }

    void flow_vis()
    {
        
        
        ft.loadFromFile("DroidSansMono.ttf");

        for (auto i = fn_list.begin(); i != fn_list.end(); ++i)
        {
            if(i->first == fun_name_vec[fun_name_vec.size() - 1 - fun_point])
            {
                for(int  k = 0; k < i->second.size(); ++k)
                {
                    Text t1;
                    t1.setFont(ft);
                    t1.setString(i->second[k].second);
                    t1.setFillColor(fo[i->second[k].first]);
                    t1.setPosition(10 + i->second[k].first * 15, 30 + k * 50);
                    t1.setCharacterSize(15);
                    txt_vec.push_back(t1);
                }
            }
        }
    }

    void modify_top(int c)
    {
        if(top >= 0) top += c*20;
        if(top < 0) top = 0;
    }

    void f_rend(RenderWindow *win, int rend_mode)
    {
        if(rend_mode == 1)
        {
            help_rend(win);
            return;
        }
        v1.reset(FloatRect(0, top, 500, 500));
        v1.setViewport(FloatRect(0.67f, 0.f, 0.33f, 1.f));
        stack <int> loop_keep;
        loop_keep.push(-2);
        win->setView(v1);

        Text fun_name;
        ft2.loadFromFile("FiraSans-Book.otf");
        fun_name.setFont(ft2);
        fun_name.setString(fun_name_vec[fun_name_vec.size() - 1 - fun_point]);
        fun_name.setCharacterSize(20);
        fun_name.setPosition(10, 0);
        fun_name.setFillColor(Color::Cyan);
        win->draw(fun_name);


        for(int i = 0; i < txt_vec.size(); ++i)
        {

            
            RectangleShape rec;
            FloatRect bounds = txt_vec[i].getGlobalBounds();
            if(i != txt_vec.size() - 1)
            {
                VertexArray conn(Lines, 2);
                FloatRect bounds2 = txt_vec[i + 1].getGlobalBounds();
                conn[0].position = Vector2f(bounds.left, bounds.top + bounds.height);
                conn[1].position = Vector2f(bounds2.left, bounds2.top);
                conn[0].color = Color::Blue;
                conn[1].color = Color::Blue;
                win->draw(conn);
            }

            if(txt_vec[i].getString() == "{")
            {
                //cout << "chala1" << endl;
                int  j = i;
                while((txt_vec[j].getString() != "}" || txt_vec[j].getFillColor() != txt_vec[i].getFillColor()) && j < txt_vec.size() - 1) ++j;

                if(txt_vec[j].getString() == "}" && txt_vec[j].getFillColor() == txt_vec[i].getFillColor() && j != txt_vec.size() - 1)
                {
                    VertexArray conn(Lines, 2);
                    FloatRect bounds3 = txt_vec[i - 1].getGlobalBounds();
                    FloatRect bounds2 = txt_vec[j + 1].getGlobalBounds();
                    conn[0].position = Vector2f(bounds3.left, bounds3.top + bounds3.height);
                    conn[1].position = Vector2f(bounds2.left, bounds2.top);
                    conn[0].color = Color::Green;
                    conn[1].color = Color::Green;
                    win->draw(conn);
                    
                }
                //cout << "chala2" << endl;

                if(txt_vec[j].getString() == "}" && loop_keep.top() == i - 1)
                {
                    //cout << "chala3" << endl;
                    FloatRect bounds4 = txt_vec[j].getGlobalBounds();
                    FloatRect bounds3 = txt_vec[i - 1].getGlobalBounds();
                    VertexArray lop(LineStrip, 4);
                    lop[0].position = Vector2f(bounds4.left + bounds4.width, bounds4.top + bounds4.height);
                    lop[1].position = Vector2f(bounds4.left + 300, bounds4.top + bounds4.height);
                    lop[2].position = Vector2f(bounds4.left + 300, bounds3.top + bounds3.height);
                    lop[3].position = Vector2f(bounds3.left + bounds3.width, bounds3.top + bounds3.height);

                    lop[0].color = Color::Red;
                    lop[1].color = Color::Red;
                    lop[2].color = Color::Red;
                    lop[3].color = Color::Red;
                    loop_keep.pop();

                    win->draw(lop);
                }

            }
            else if(txt_vec[i].getString().substring(0, 3) == "for" || txt_vec[i].getString().substring(0, 5) == "while")
            {
                loop_keep.push(i);
                //cout << "chala" << endl;
            }

            rec.setPosition(Vector2f(bounds.left - 5, bounds.top - 5));
            rec.setSize(Vector2f(bounds.width + 10, bounds.height + 10));
            rec.setFillColor(Color(0,0,0,0));
            rec.setOutlineThickness(1);
            rec.setOutlineColor(txt_vec[i].getFillColor());
            win->draw(rec);
            win->draw(txt_vec[i]);

            
            
        }
        
    }

    void help_rend(RenderWindow *w1)
    {
        vector < sf::Drawable * > d1;
        v1.reset(FloatRect(0, 0, 500, 500));
        v1.setViewport(FloatRect(0.67f, 0.f, 0.33f, 1.f));
        w1->setView(v1);

        ft.loadFromFile("MaldiniBold-OVZO6.ttf");
        Text tx1, tx2, tx3, tx4, tx5, tx6, tx7, tx8, tx9;
        tx1.setFont(ft);
        tx1.setString("CodeFlow");
        tx1.setCharacterSize(60);
        tx1.setFillColor(Color(255, 104, 23, 255));
        tx1.setPosition(20, 20);
        d1.push_back(&tx1);

        ft2.loadFromFile("BloggerSans-Bold.ttf");
        tx2.setFont(ft2);
        tx2.setString("Version 0.5 (beta build)");
        tx2.setCharacterSize(16);
        tx2.setFillColor(Color::Yellow);
        FloatRect tx1b = tx1.getGlobalBounds();
        tx2.setPosition(tx1b.left + tx1b.width, tx1b.top + tx1b.height - 16);
        d1.push_back(&tx2);

        tx3.setFont(ft2);
        tx3.setString(": Help Section :");
        tx3.setPosition(20, 100);
        tx3.setCharacterSize(30);
        tx3.setFillColor(Color(148, 24, 219, 255));
        d1.push_back(&tx3);

        tx4.setFont(ft2);
        tx4.setString("Codeflow reference :-");
        tx4.setPosition(20, 150);
        tx4.setCharacterSize(25);
        tx4.setFillColor(Color(148, 24, 219, 255));
        d1.push_back(&tx4);

        VertexArray rd(Lines, 2);
        rd[0].position = Vector2f(20, 195);
        rd[1].position = Vector2f(50, 195);
        rd[0].color = Color::Red;
        rd[1].color = Color::Red;
        VertexArray gr(Lines, 2);
        gr[0].position = Vector2f(20, 225);
        gr[1].position = Vector2f(50, 225);
        gr[0].color = Color::Green;
        gr[1].color = Color::Green;
        VertexArray bl(Lines, 2);
        bl[0].position = Vector2f(20, 255);
        bl[1].position = Vector2f(50, 255);
        bl[0].color = Color::Blue;
        bl[1].color = Color::Blue;
        d1.push_back(&rd);
        d1.push_back(&gr);
        d1.push_back(&bl);

        tx5.setFont(ft2);
        tx5.setString("Represents a closed loop");
        tx5.setPosition(60, 185);
        tx5.setCharacterSize(20);
        tx5.setFillColor(Color(148, 24, 219, 255));
        d1.push_back(&tx5);

        tx6.setFont(ft2);
        tx6.setString("Represents failure of a conditional statement");
        tx6.setPosition(60, 215);
        tx6.setCharacterSize(20);
        tx6.setFillColor(Color(148, 24, 219, 255));
        d1.push_back(&tx6);

        tx7.setFont(ft2);
        tx7.setString("Represents normal flow in consecutive order");
        tx7.setPosition(60, 245);
        tx7.setCharacterSize(20);
        tx7.setFillColor(Color(148, 24, 219, 255));
        d1.push_back(&tx7);

        tx8.setFont(ft2);
        tx8.setString("Keyboard shortcuts :-");
        tx8.setPosition(20, 275);
        tx8.setCharacterSize(25);
        tx8.setFillColor(Color(148, 24, 219, 255));
        d1.push_back(&tx8);

        tx9.setFont(ft2);
        tx9.setString("alt + s -> Save file\nalt + c -> Compile and run\nalt + h -> Open help section\nalt + d -> Open debugger\nalt + t -> Cycle through different functions\nalt + r -> Restore codeflow window\n");
        tx9.setPosition(20, 310);
        tx9.setCharacterSize(20);
        tx9.setFillColor(Color(148, 24, 219, 255));
        d1.push_back(&tx9);




        for(auto i = 0; i < d1.size(); ++i)
        {
            w1->draw(*d1[i]);
        }

    }

    
};