#include <iostream>
#include <vector>
#include <random>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

class Maze
{
private:
    int width, height;
    vector<vector<char>> grid;
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
            if (isValid(nx, ny) && grid[nx][ny] == '#')
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
        grid[1][1] = '.';

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
            grid[nx][ny] = '.';
            grid[x + (nx - x) / 2][y + (ny - y) / 2] = '.';
            st.push({nx, ny});
        }

        // Set entry and exit
        entry = {1, 0};
        exit = {height - 2, width - 1};
        grid[entry.first][entry.second] = '.';
        grid[exit.first][exit.second] = '.';
    }

    bool solveMaze()
    {
        vector<vector<bool>> visited(height, vector<bool>(width, false));
        vector<vector<pair<int, int>>> parent(height, vector<pair<int, int>>(width));
        queue<pair<int, int>> q;
        vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        q.push(entry);
        visited[entry.first][entry.second] = true;

        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();

            if (x == exit.first && y == exit.second)
            {
                // Mark solution path
                auto curr = exit;
                while (curr != entry)
                {
                    grid[curr.first][curr.second] = 'o';
                    curr = parent[curr.first][curr.second];
                }
                grid[entry.first][entry.second] = 'o';
                return true;
            }

            for (auto [dx, dy] : dirs)
            {
                int nx = x + dx, ny = y + dy;
                if (isValid(nx, ny) && grid[nx][ny] == '.' && !visited[nx][ny])
                {
                    visited[nx][ny] = true;
                    parent[nx][ny] = {x, y};
                    q.push({nx, ny});
                }
            }
        }
        return false;
    }

public:
    Maze(int w, int h) : width(w), height(h), rng(random_device{}())
    {
        grid = vector<vector<char>>(height, vector<char>(width, '#'));
        generateMaze();
        solveMaze();
    }

    void display()
    {
        for (const auto &row : grid)
        {
            for (char cell : row)
            {
                cout << cell;
            }
            cout << endl;
        }
    }
};

int main()
{
    Maze maze(15, 15);
    maze.display();
    return 0;
}