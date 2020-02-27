#include <iostream>
#include <fstream>
#include <map>
#include <unistd.h>
#include <SFML/Graphics.hpp>

using namespace std;

int main(){
    sf::RenderWindow window(sf::VideoMode(600, 600), "Control Flow");
    window.setVerticalSyncEnabled(true);

    sf::CircleShape functions;
    functions.setRadius(20);
    functions.setOrigin(sf::Vector2f(functions.getRadius(), functions.getRadius()));
    functions.setFillColor(sf::Color::Cyan);
    map<int, sf::CircleShape> display_node;

    map<int, int> fun_map;
    int fun_start, fun_end, Y=30;
    ifstream streamNode, streamFlow;
    streamNode.open("flowNode.txt");
    while(!streamNode.eof()){
        streamNode>>fun_start>>fun_end;
        fun_map.insert(pair<int, int>(fun_start, fun_end));
        functions.setPosition(sf::Vector2f(300, Y));
        display_node.insert(pair<int, sf::CircleShape>(fun_start, functions));
        Y+=80;
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
            display_node.at(lower_bound).setFillColor(sf::Color::Red);
            lineItr++;
            sleep(1);
        }
        else{
            display_node.at(lower_bound).setFillColor(sf::Color::Black);
        }

        window.clear(sf::Color::Magenta);
        for(map<int, int>::iterator itr=fun_map.begin(); itr!=fun_map.end(); itr++){
            window.draw(display_node.at(itr->first));
        }
        display_node.at(lower_bound).setFillColor(sf::Color::Cyan);
        window.display();
    }
    return 0;
}