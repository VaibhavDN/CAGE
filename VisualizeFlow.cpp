#include <iostream>
#include <fstream>
#include <map>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include "LineInserter.cpp"

using namespace std;

int main(){
    sf::RenderWindow window(sf::VideoMode(1200, 768), "Control Flow");
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
    functions.setRadius(8);
    functions.setOrigin(sf::Vector2f(functions.getRadius(), functions.getRadius()));
    //functions.setFillColor(sf::Color(255,0,0,200));
    map<int, sf::CircleShape> display_node;

    ifstream nodeCountStream("NodeCount.txt");
    int node_count;
    nodeCountStream>>node_count;
    nodeCountStream.close();

    map<int, int> fun_map;
    vector<int> depthwise_x, depthwise_y;
    int fun_start, fun_end, X=-220, Y=40, level=0, level_prev=0, bfl_counter = 0, depth = 0, insert_count_y=0, max_depth = 0;
    depthwise_x.emplace_back(X);
    depthwise_y.emplace_back(Y);
    ifstream streamNode, streamFlow;
    streamNode.open("flowNode.txt");

    vector < vector < tuple < int, int, int > > > reorder1, reorder2;
    vector < tuple < int, int, int, string > > entry1, entry2;

    for(int counter=0; counter<node_count; counter++){
        depthwise_y.emplace_back(Y);
        Y+=50;
        depthwise_x.emplace_back(-220);
    }

    while(!streamNode.eof()){
        try{

        streamNode>>fun_start>>fun_end>>level;
        cout<<"\nfun_start: "<<fun_start<<" fun_end: "<<fun_end<<" level: "<<level<<endl;
        //entry1.emplace_back(make_tuple(fun_start, fun_end, level, block_first_line[bfl_counter]));
        //bfl_counter++;

        //! WIP
        
        cout<<"Debug depth: "<<depth<<" X: "<<X<<" Y: "<<Y<<" depthwise_y.size(): "<<depthwise_y.size()<<" level: "<<level<<" level_prev: "<<level_prev<<endl;
        if(depth < 0){
            cout<<"Error: Depth < 0 |VisualizerFlow|"<<endl;
            Y-=50;
            X=80;
            depth = 0;
        }
        else if(level == 0){
            cout<<"level 0"<<endl;
            depth = max_depth;
            depth++;
            Y=depthwise_y[depth];
            X=depthwise_x[depth]+300;
            depthwise_x[depth]=X;
            cout<<"Increasing -> New depth: "<<depth<<endl;
        }
        else if(level > level_prev){
            depth++;
            Y=depthwise_y[depth];
            cout<<"Depth: "<<depth<<endl;
            X=depthwise_x[depth]+300;
            depthwise_x[depth] = X;
        }
        else if(level < level_prev){
            depth-= 1;
            cout<<"Decreasing -> New depth: "<<depth<<endl;
            Y=depthwise_y[depth];
            X=depthwise_x[depth]+300;
            depthwise_x[depth] = X;
        }
        else{
            X=depthwise_x[depth]+300;
            depthwise_x[depth] = X;
        }
        level_prev = level;
        
        if(depth>max_depth){
            max_depth = depth;
        }

        fun_map.insert(pair<int, int>(fun_start, fun_end));
        functions.setPosition(sf::Vector2f(X, Y));
        display_node.insert(pair<int, sf::CircleShape>(fun_start, functions));

        if(block_first_line.size() > 0){
            text.setString(block_first_line.back());
            cout<<block_first_line.back()<<endl;
            text.setFillColor(sf::Color::Black);
            text.setCharacterSize(12);
            text.setPosition(sf::Vector2f(functions.getPosition().x - 20, functions.getPosition().y + 15));
            fun_name.emplace_back(text);
            block_first_line.pop_back();
        }
        
        //! WIP ends here
        }
        catch(exception e){
            cout<<e.what()<<endl;
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
            display_node.at(lower_bound).setFillColor(sf::Color(255, 200, 100));
            lineItr++;
            usleep(800000);
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