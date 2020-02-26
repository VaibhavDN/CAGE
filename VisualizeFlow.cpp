#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

using namespace std;

int main(){
    sf::RenderWindow window(sf::VideoMode(600, 600), "Control Flow");
    window.setVerticalSyncEnabled(true);

    string fun_start, fun_end;
    ifstream streamNode, streamFlow;
    streamNode.open("flowNode.txt");
    while(!streamNode.eof()){
        streamNode>>fun_start>>fun_end;
    }
    streamNode.close();

    while(window.isOpen()){
        sf::Event event;

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.clear(sf::Color::Magenta);
        window.display();
        
    }
    return 0;
}