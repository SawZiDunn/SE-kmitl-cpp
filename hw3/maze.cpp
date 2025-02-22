#include <iostream>
#include <vector>
#include <random>
#include <stack>
#include <queue>
#include <algorithm>
#include <iomanip> // For formatting output

using namespace std;

// Maze Elements
const char WALL = '#';
const char PATH = '.';
const char ENTRY = 'E';
const char EXIT = 'X';
const char SOLUTION_PATH = 'o';

class Maze
{
private:
    int width, height;
    vector<vector<char>> grid;
    vector<vector<char>> solutionGrid;
    pair<int, int> entry, exit;
    mt19937 rng;

    bool isValid(int x, int y)
    {
        return x >= 0 && x < height && y >= 0 && y < width;
    }

    vector<pair<int, int>> getNeighbors(int x, int y)
    {
        vector<pair<int, int>> neighbors;
        vector<pair<int, int>> dirs = {{0, 2}, {2, 0}, {0, -2}, {-2, 0}};
        for (auto [dx, dy] : dirs)
        {
            int nx = x + dx, ny = y + dy;
            if (isValid(nx, ny) && grid[nx][ny] == WALL)
            {
                neighbors.push_back({nx, ny});
            }
        }
        shuffle(neighbors.begin(), neighbors.end(), rng);
        return neighbors;
    }

    void generateMaze()
    {
        stack<pair<int, int>> st;
        st.push({1, 1});
        grid[1][1] = PATH;

        while (!st.empty())
        {
            auto [x, y] = st.top();
            auto neighbors = getNeighbors(x, y);

            if (neighbors.empty())
            {
                st.pop();
                continue;
            }

            auto [nx, ny] = neighbors[0];
            grid[nx][ny] = PATH;
            grid[x + (nx - x) / 2][y + (ny - y) / 2] = PATH;
            st.push({nx, ny});
        }

        // Set entry and exit
        entry = {1, 0};
        exit = {height - 2, width - 1};
        grid[entry.first][entry.second] = PATH;
        grid[exit.first][exit.second] = PATH;

        // Copy generated maze to solution grid
        solutionGrid = grid;
    }

    void solveMaze()
    {
        vector<vector<bool>> visited(height, vector<bool>(width, false));
        vector<vector<pair<int, int>>> parent(height, vector<pair<int, int>>(width, {-1, -1}));
        queue<pair<int, int>> q;
        vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        q.push(entry);
        visited[entry.first][entry.second] = true;

        bool found = false;
        while (!q.empty() && !found)
        {
            auto [x, y] = q.front();
            q.pop();

            for (auto [dx, dy] : dirs)
            {
                int nx = x + dx, ny = y + dy;
                if (isValid(nx, ny) && grid[nx][ny] == PATH && !visited[nx][ny])
                {
                    visited[nx][ny] = true;
                    parent[nx][ny] = {x, y};
                    q.push({nx, ny});

                    if (nx == exit.first && ny == exit.second)
                    {
                        found = true;
                        break;
                    }
                }
            }
        }

        // Mark solution path
        pair<int, int> curr = exit;
        while (curr != entry)
        {
            if (curr != exit)
                solutionGrid[curr.first][curr.second] = SOLUTION_PATH;
            curr = parent[curr.first][curr.second];
        }

        // Ensure entry and exit remain distinct
        solutionGrid[entry.first][entry.second] = ENTRY;
        solutionGrid[exit.first][exit.second] = EXIT;
    }

public:
    Maze(int w, int h) : width(w), height(h), rng(random_device{}())
    {
        grid = vector<vector<char>>(height, vector<char>(width, WALL));
        generateMaze();
        solveMaze();
    }

    void displayMaze()
    {
        cout << "Generated Maze:\n";
        for (const auto &row : grid)
        {
            for (char cell : row)
            {
                cout << setw(2) << cell;
            }
            cout << endl;
        }
        cout << endl;
    }

    void displaySolution()
    {
        cout << "Solution Path:\n";
        for (const auto &row : solutionGrid)
        {
            for (char cell : row)
            {
                cout << setw(2) << cell;
            }
            cout << endl;
        }
    }
};

int main()
{
    Maze maze(15, 15);
    maze.displayMaze();     // Show generated maze
    maze.displaySolution(); // Show solution path
    return 0;
}
