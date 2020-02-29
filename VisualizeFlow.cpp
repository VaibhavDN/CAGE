#include <iostream>
#include <fstream>
#include <map>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include "LineInserter.cpp"

using namespace std;

int main(){
    sf::RenderWindow window(sf::VideoMode(1200, 600), "Control Flow");
    window.setVerticalSyncEnabled(true);

    LineInserter lineInserter;
    lineInserter.mainLineInserter();
    //exit(0);
    vector<string> block_first_line = lineInserter.getFunFirstLine();
    reverse(block_first_line.begin(), block_first_line.end());
    vector<sf::Text> fun_name;
    sf::Text text;
    sf::Font font;
    font.loadFromFile("FiraSans-Book.otf");
    text.setFont(font);

    sf::Texture texture;
    texture.loadFromFile("pearl.jpg");
    texture.setSmooth(true);
    sf::CircleShape functions;
    functions.setTextureRect(sf::IntRect(130,130,730,730));
    functions.setTexture(&texture);
    functions.setRadius(20);
    functions.setOrigin(sf::Vector2f(functions.getRadius(), functions.getRadius()));
    //functions.setFillColor(sf::Color(255,0,0,200));
    map<int, sf::CircleShape> display_node;

    map<int, int> fun_map;
    vector<int> depthwise_x, depthwise_y;
    int fun_start, fun_end, X=0, Y=-50, level=0, level_prev=0, depth=0;
    depthwise_x.emplace_back(X);
    depthwise_y.emplace_back(Y);
    ifstream streamNode, streamFlow;
    streamNode.open("flowNode.txt");
    while(!streamNode.eof()){
        streamNode>>fun_start>>fun_end>>level;
        if(level == 0){
            Y=depthwise_y.back();
            Y+=80;
            depthwise_y.emplace_back(Y);
            depth++;
            X=80;
            depthwise_x.emplace_back(X);
        }
        else if(level > level_prev){
            Y=depthwise_y[depth];
            Y+=80;
            depthwise_y.emplace_back(Y);
            depth++;
            X=80;
            depthwise_x.emplace_back(X);
        }
        else if(level < level_prev){
            depth--;
            Y=depthwise_y[depth];
            X=depthwise_x[depth]+300;
            depthwise_x[depth] = X;
        }
        else{
            X=depthwise_x[depth]+300;
            depthwise_x[depth] = X;
        }
        level_prev = level;
        fun_map.insert(pair<int, int>(fun_start, fun_end));
        functions.setPosition(sf::Vector2f(X, Y));
        display_node.insert(pair<int, sf::CircleShape>(fun_start, functions));

        if(block_first_line.size() > 0){
            text.setString(block_first_line.back());
            cout<<block_first_line.back()<<endl;
            text.setFillColor(sf::Color::Black);
            text.setCharacterSize(12);
            text.setPosition(sf::Vector2f(functions.getPosition().x - 20, functions.getPosition().y + 30));
            fun_name.emplace_back(text);
            block_first_line.pop_back();
        }
        
    }
    streamNode.close();

    vector<int> flow;
    int lineNo;
    streamFlow.open("flowOutput.txt");
    while(!streamFlow.eof()){
        streamFlow>>lineNo;
        flow.emplace_back(lineNo);
    }
    streamFlow.close();

    int lineItr=0;
    while(window.isOpen()){
        sf::Event event;

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        int lower_bound;
        if(lineItr<flow.size()){
            map<int, int>::iterator itr = fun_map.lower_bound(flow.at(lineItr));
            if(itr != fun_map.begin()){
                itr--;
            }
            lower_bound = itr->first;
            cout<<"lineNo: "<<flow.at(lineItr)<<" lower_bound: "<<lower_bound<<endl;
            display_node.at(lower_bound).setFillColor(sf::Color(255, 217, 179));
            lineItr++;
            sleep(1);
        }
        else{
            display_node.at(lower_bound).setFillColor(sf::Color::Red);
        }

        window.clear(sf::Color::White);
        int counter = 0;
        for(map<int, int>::iterator itr=fun_map.begin(); itr!=fun_map.end(); itr++){
            window.draw(display_node.at(itr->first));
            window.draw(fun_name.at(counter));
            counter++;
        }
        display_node.at(lower_bound).setFillColor(sf::Color::White);
        window.display();
    }
    return 0;
}