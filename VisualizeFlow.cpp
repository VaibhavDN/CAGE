#include <iostream>
#include <fstream>
#include <map>
#include <tuple>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include "LineInserter.cpp"

using namespace std;

bool sort_flowNode(tuple<int, int, int, sf::Text, sf::CircleShape> t1, tuple<int, int, int, sf::Text, sf::CircleShape> t2){
    return get<0>(t1) < get<0>(t2);
}

int main(){
    sf::RenderWindow window(sf::VideoMode(1366, 768), "Control Flow");
    window.setVerticalSyncEnabled(true);

    sf::RectangleShape code_side;
    code_side.setFillColor(sf::Color(26, 0, 51));
    code_side.setPosition(sf::Vector2f(window.getSize().x/2, 0));
    code_side.setSize(sf::Vector2f(window.getSize().x/2, window.getSize().y));

    LineInserter lineInserter;
    lineInserter.mainLineInserter();
    //exit(0);
    vector<string> block_first_line = lineInserter.getFunFirstLine();
    reverse(block_first_line.begin(), block_first_line.end());

    map<int, string> user_code_linewise = lineInserter.get_user_code_linewise();

    vector<sf::Text> fun_name;
    sf::Text text;
    sf::Font font;
    font.loadFromFile("FiraSans-Book.otf");
    text.setFont(font);

    int line_spacing=20, text_x=window.getSize().x/2, text_y=0;
    map<int, sf::Text> user_code;
    for(auto itr=user_code_linewise.begin(); itr != user_code_linewise.end(); itr++){
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(14);
        text.setString(itr->second);
        text.setPosition(sf::Vector2f(text_x+(text_x/8), text_y+line_spacing));
        user_code.insert(make_pair(itr->first, text));
        text_y+=line_spacing;
    }

    sf::Texture texture;
    texture.loadFromFile("pearl.jpg");
    texture.setSmooth(true);
    sf::CircleShape functions;
    functions.setTextureRect(sf::IntRect(130,130,730,730));
    functions.setTexture(&texture);
    functions.setRadius(8);
    functions.setOrigin(sf::Vector2f(functions.getRadius(), functions.getRadius()));
    //functions.setFillColor(sf::Color(255,0,0,200));
    map<int, sf::CircleShape> display_node;

    ifstream nodeCountStream("NodeCount.txt");
    int node_count;
    nodeCountStream>>node_count;
    nodeCountStream.close();

    map<int, int> fun_map;
    vector<tuple<int, int, int, sf::Text, sf::CircleShape> >flowNode;      //!New
    vector<int> depthwise_x, depthwise_y;
    int fun_start, fun_end, X=-220, Y=40, level=0, level_prev=0, bfl_counter = 0, depth = 0, insert_count_y=0, max_depth = 0;
    depthwise_x.emplace_back(X);
    depthwise_y.emplace_back(Y);
    ifstream streamNode, streamFlow;
    streamNode.open("flowNode.txt");

    for(int counter=0; counter<node_count; counter++){
        depthwise_y.emplace_back(Y);
        Y+=50;
        depthwise_x.emplace_back(-220);
    }

    while(!streamNode.eof()){
        try{
            streamNode>>fun_start>>fun_end>>level;
            fun_map.insert(make_pair(fun_start, level));
            cout<<"\nfun_start: "<<fun_start<<" fun_end: "<<fun_end<<" level: "<<level<<endl;
            
            cout<<"Debug depth: "<<depth<<" X: "<<X<<" Y: "<<Y<<" depthwise_y.size(): "<<depthwise_y.size()<<" level: "<<level<<" level_prev: "<<level_prev<<endl;
            
            text.setFillColor(sf::Color::Black);
            text.setCharacterSize(12);
            if(block_first_line.size() > 0){
                string str = block_first_line.back()+"\n"+to_string(fun_start)+" : "+to_string(fun_end)+" : "+to_string(level);
                text.setString(str);
                cout<<block_first_line.back()<<endl;
                block_first_line.pop_back();
                flowNode.push_back(make_tuple(level, fun_start, fun_end, text, functions));
            }
            else{
                //!Control should not reach here
                text.setString(to_string(fun_start) + " : " + to_string(fun_end));
            }
            
        }
        catch(exception e){
            cout<<e.what()<<endl;
        }
    }
    streamNode.close();

    sort(flowNode.begin(), flowNode.end(), sort_flowNode);
    
    vector<int> flow;
    int lineNo;
    streamFlow.open("flowOutput.txt");
    while(!streamFlow.eof()){
        streamFlow>>lineNo;
        flow.emplace_back(lineNo);
    }
    streamFlow.close();

    int lineItr=0;
    int lower_bound=0, selected_node=0;
    while(window.isOpen()){
        sf::Event event;

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        
        sf::Color selected_node_color;
        if(lineItr<flow.size()-1){
            int smallest_range = INT16_MAX;
            for(auto itr=flowNode.begin(); itr!=flowNode.end(); itr++){
                if((flow.at(lineItr) >= get<1>(*itr)) && (flow.at(lineItr) <= get<2>(*itr))){
                    if(get<2>(*itr)-get<1>(*itr) < smallest_range){
                        lower_bound = get<1>(*itr);
                        smallest_range = get<2>(*itr)-get<1>(*itr);
                    }
                }
            }
            selected_node_color = sf::Color(255, 200, 100);
            cout<<"lineNo: "<<flow.at(lineItr)<<" lower_bound: "<<lower_bound<<endl;
            lineItr++;
            usleep(800000);
        }
        else{
            selected_node_color = sf::Color::Red;
        }

        window.clear(sf::Color::White);
        window.draw(code_side);

        cout<<"flow.at(lineItr): "<<flow.at(lineItr)<<endl;
        if(user_code.find(flow.at(lineItr)) != user_code.end()){
            user_code.at(flow.at(lineItr)).setFillColor(sf::Color(255, 153, 153));
            for(auto itr=user_code.begin(); itr != user_code.end(); itr++){
                window.draw(itr->second);
            }
            user_code.at(flow.at(lineItr)).setFillColor(sf::Color::White);
        }
        cout<<"Code written on the screen\n";

        int vertical_pos = 70, horizontal_pos = -150, level_prev = 0;
        for(int index=0; index<flowNode.size(); index++){
            level = get<0>(flowNode[index]);
            cout<<"Level acquired\n";
            if(level_prev == level){
                horizontal_pos+=200;
            }
            else{
                level_prev = level;
                horizontal_pos = 50;
                vertical_pos+=70;
            }
            cout<<"Calculated horizontal and vertical pos\n";

            if(get<1>(flowNode[index]) == lower_bound){
                get<4>(flowNode[index]).setFillColor(selected_node_color);
                selected_node = index;
            }

            cout<<"Changed node color\n";

            get<3>(flowNode[index]).setPosition(sf::Vector2f(horizontal_pos-10, vertical_pos+20));
            get<4>(flowNode[index]).setPosition(sf::Vector2f(horizontal_pos, vertical_pos));
            window.draw(get<3>(flowNode[index]));
            window.draw(get<4>(flowNode[index]));

            cout<<"Drawing complete!\n";
            get<4>(flowNode[selected_node]).setFillColor(sf::Color::White);
        }
        window.display();

    }
    return 0;
}