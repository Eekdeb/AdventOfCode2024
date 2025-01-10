#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include "../FileReader.cpp"

using namespace std;

const vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool isValidMove(const vector<vector<int>>& map, const vector<vector<bool>>& visited, int x, int y, int currentValue) {
    int rows = map.size();
    int cols = map[0].size();
    return (x >= 0 && x < rows && y >= 0 && y < cols &&
            map[x][y] == currentValue + 1);            
}

int bfs(const vector<vector<int>>& map, int startX, int startY) {
    int rows = map.size();
    int cols = map[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    queue<pair<int, int>> q;
    int reachableNines = 0;

    q.push({startX, startY});
    visited[startX][startY] = true;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (const auto& [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;

            if (isValidMove(map, visited, nx, ny, map[x][y])) {
                visited[nx][ny] = true;
                q.push({nx, ny});
                if (map[nx][ny] == 9) {
                    reachableNines++;
                }
            }
        }
    }

    return reachableNines;
}

int main() {
    string filename = "input.txt";
    vector<vector<int>> map = convertToVectorVectorInt(filename);

    int total = 0;   
    int rows = map.size();
    int cols = map[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (map[i][j] == 0) {
                total += bfs(map, i, j);
            }
        }
    }

    cout << total << endl;

    return 0;
}
