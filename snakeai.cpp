//This program runs a snakeAI using A* for the algorithm
//The algorithm completes in the findPath function, where the other sub-functions and variables from the struct Node are being fully used.
//The program currently runs in the terminal with different symbols and using the clearConsole function to make it look like an animation.


#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdlib>
using namespace std;
const int SIZE = 10;
vector<char> ca{'.', '*', '#'};
vector<pair<int, int>> snake{{0, 0}};
vector<pair<int, int>> food{};
map<pair<int, int>, char> pos;

struct Node{
    int x; int y; int g; int h; int f;
    Node* parent;

    Node(int x, int y) : x(x), y(y), g(0), h(0), f(0), parent(nullptr) {}
};


int calculateDistance(int startX, int startY, int goalX, int goalY){
    return abs(startX - goalX) + abs(startY - goalY);
}


int calculateCost(Node* currentNode, Node* neighborNode){
    return currentNode->g + 1;
}


vector<pair<int, int>> generateNeighbors(int x, int y){
    const vector<pair<int, int>> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    vector<pair<int, int>> neighbors;
    for(const auto& dir : directions){
        int newX = x + dir.first;
        int newY = y + dir.second;
        if(newX == snake[1].first && newY == snake[1].second){
            continue;
        }
        bool isSnake = false;
        for(const auto& bodyPart : snake){
            if(newX == bodyPart.first && newY == bodyPart.second){
                isSnake = true;
                break;
            }
        }
        if(!isSnake){
            neighbors.emplace_back(newX, newY);
        }
    }
    return neighbors;
}


bool isNodeInList(Node* node, const vector<Node*>& openList, const vector<Node*>& closedList, const vector<pair<int, int>>& snake){
    for(const auto& n : openList){
        if(node->x == n->x && node->y == n->y){
            return true;
        }
    }
    for(const auto& n : closedList){
        if(node->x == n->x && node->y == n->y){
            return true;
        }
    }
    for(const auto& bodyPart : snake){
        if(node->x == bodyPart.first && node->y == bodyPart.second){
            return true;
        }
    }
    return false;
}


vector<pair<int, int>> findPath(int startX, int startY, int goalX, int goalY){
    if(food.empty()){
        return {};
    }
    Node* startNode = new Node(startX, startY);
    Node* goalNode = new Node(goalX, goalY);
    vector<Node*> openList;
    vector<Node*> closedList;

    openList.push_back(startNode);

    while(!openList.empty()){
        Node* currentNode = openList[0];
        int currentIndex = 0;
        for(int i = 1; i < openList.size(); i++){
            if(openList[i]->f < currentNode->f){
                currentNode = openList[i];
                currentIndex = i;
            }
        }
        openList.erase(openList.begin() + currentIndex);
        closedList.push_back(currentNode);
        if(currentNode->x == goalNode->x && currentNode->y == goalNode->y){
            vector<pair<int, int>> path;
            while(currentNode != nullptr){
                path.emplace_back(currentNode->x, currentNode->y);
                currentNode = currentNode->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }
        vector<pair<int, int>> neighbors = generateNeighbors(currentNode->x, currentNode->y);

        for(const auto& neighbor: neighbors){
            int neighborX = neighbor.first;
            int neighborY = neighbor.second;

            Node* neighborNode = new Node(neighborX, neighborY);
            if(isNodeInList(neighborNode, openList, closedList, snake)){
                continue;
            }
            int cost = calculateCost(currentNode, neighborNode);
            bool isInOpenList = isNodeInList(neighborNode, openList, closedList, snake);
            if(!isInOpenList || cost < neighborNode->g){
                neighborNode->g = cost;
                neighborNode->h = calculateDistance(neighborX, neighborY, goalX, goalY);
                neighborNode->f = neighborNode->g + neighborNode->h;
                neighborNode->parent = currentNode;
                if(!isInOpenList){
                    openList.push_back(neighborNode);
                }
            }
        }
    }
    return {};
}
bool isValidMove(int x, int y){
    if(x < 0 || x >= SIZE || y < 0 || y >= SIZE){
        return false;
    }
    auto it = find(snake.begin(), snake.end(), make_pair(x, y));
    return it == snake.end();
}
void base(){
    if(food.empty()){
        int x, y;
        bool collision = false;
        do {
            x = rand() % SIZE;
            y = rand() % SIZE;
            collision = find(snake.begin(), snake.end(), make_pair(x, y)) != snake.end();
        } while (collision);
        food.push_back(make_pair(x, y));
    }
}
void clearConsole(){
    string clear = "\033[2J\033[1;1H";
    cout << clear;
}
void algor(int i, int j) {
    if (!food.empty()) {
        pair<int, int> foodPos = food[0];
        int foodX = foodPos.first;
        int foodY = foodPos.second;
        vector<pair<int, int>> path = findPath(i, j, foodX, foodY);
        if (!path.empty()) {
            pair<int, int> nextPosition = path[1];
            auto collision = find(snake.begin()+1, snake.end(), nextPosition);
            if(collision != snake.end()){
                vector<pair<int, int>> neighbors = generateNeighbors(i, j);
                for(const auto& neighbor : neighbors){
                    if(isValidMove(neighbor.first, neighbor.second)){
                        nextPosition = neighbor;
                        break;
                    }
                }
            }
            snake.insert(snake.begin(), nextPosition);
            if (nextPosition != foodPos) {
                snake.pop_back();
            }
            if (nextPosition == foodPos){
                food.clear();
            }
        }
    }
}
void board(){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            auto snakeid = find(snake.begin(), snake.end(), make_pair(i, j));
            auto foodid = find(food.begin(), food.end(), make_pair(i, j));
            if(snakeid != snake.end()){
                if(snakeid == snake.begin()){
                    pos[{i, j}] = ca[2];
                } else {
                    pos[{i, j}] = ca[2];
                }
            } else if(foodid != food.end()){
                pos[{i, j}] = ca[1];
            } else {
                pos[{i, j}] = ca[0];
            }
            cout << pos[{i, j}] << " ";
        }
        cout << endl;
    }
}

bool isGameOver() {
    int headX = snake[0].first;
    int headY = snake[0].second;
    for(int i = 1; i < snake.size(); i++){
        if(snake[i].first == headX && snake[i].second == headY){
            return true;
        }
    }
    return false;
}


int main(){
    srand(time(NULL));
    bool run = true;
    while(run == true && !isGameOver()){
        base();
        board();
        algor(snake[0].first, snake[0].second);
        this_thread::sleep_for(chrono::milliseconds(200));
        clearConsole();
    }
    run = false;
    cout << "Game Over" << endl;
    return 0;
}
