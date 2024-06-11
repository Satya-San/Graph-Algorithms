#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cstdlib>
#include <ctime>

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 20;

enum Cell {
    WALL,
    PATH,
    VISITED,
    START,
    END
};

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

void generateMaze(vector<vector<Cell>>& maze) {
    srand(time(0));
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            maze[i][j] = (rand() % 2) ? WALL : PATH;
        }
    }
    maze[0][0] = START;
    maze[HEIGHT-1][WIDTH-1] = END;
}

bool isValid(int x, int y, vector<vector<Cell>>& maze) {
    return (x >= 0 && x < HEIGHT && y >= 0 && y < WIDTH && maze[x][y] == PATH);
}

bool DFS(vector<vector<Cell>>& maze, int x, int y) {
    if (x == HEIGHT-1 && y == WIDTH-1) return true;

    if (isValid(x, y, maze)) {
        maze[x][y] = VISITED;

        if (DFS(maze, x+1, y)) return true;
        if (DFS(maze, x-1, y)) return true;
        if (DFS(maze, x,
                if (DFS(maze, x, y-1)) return true;

        maze[x][y] = PATH;
    }
    return false;
}

bool BFS(vector<vector<Cell>>& maze) {
    queue<Point> q;
    q.push(Point(0, 0));
    maze[0][0] = VISITED;

    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    while (!q.empty()) {
        Point p = q.front();
        q.pop();

        for (auto& dir : directions) {
            int newX = p.x + dir[0];
            int newY = p.y + dir[1];

            if (newX == HEIGHT-1 && newY == WIDTH-1) return true;

            if (isValid(newX, newY, maze)) {
                q.push(Point(newX, newY));
                maze[newX][newY] = VISITED;
            }
        }
    }
    return false;
}

void printMaze(const vector<vector<Cell>>& maze) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (maze[i][j] == WALL) cout << "# ";
            else if (maze[i][j] == PATH) cout << ". ";
            else if (maze[i][j] == VISITED) cout << "o ";
            else if (maze[i][j] == START) cout << "S ";
            else if (maze[i][j] == END) cout << "E ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<Cell>> maze(HEIGHT, vector<Cell>(WIDTH, WALL));
    generateMaze(maze);

    cout << "Generated Maze:\n";
    printMaze(maze);

    if (DFS(maze, 0, 0)) {
        cout << "\nMaze solved using DFS:\n";
        maze[0][0] = START;
        maze[HEIGHT-1][WIDTH-1] = END;
        printMaze(maze);
    } else {
        cout << "\nNo solution found using DFS!\n";
    }

    generateMaze(maze);
    cout << "\nGenerated Maze:\n";
    printMaze(maze);

    if (BFS(maze)) {
        cout << "\nMaze solved using BFS:\n";
        maze[0][0] = START;
        maze[HEIGHT-1][WIDTH-1] = END;
        printMaze(maze);
    } else {
        cout << "\nNo solution found using BFS!\n";
    }

    return 0;
}

