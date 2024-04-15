#include <iostream>
#include <vector>
#include "solution.h"

using namespace std;

void Solution::dfs(vector<vector<int>> &matrix, int remain, int used, int n, int m, int &best){
    int this_k_unavailable;
    int i, j;
    int x, y;
    if (used >= best)
        return;

    if (remain == 0){
        best = min(best, used);
        return;
    }

    for (i=0; i < n; i++)
        for (j=0; j < m; j++)
            // 找到一个空格子，尝试填入一个正方形
            if (matrix[i][j] == 0){
                for (int k = min(n - i, m - j); k >= 1; k--){
                    this_k_unavailable = 0;
                    x = i;
                    y = j;

                    for (int p = 0; p < k; p++)
                        for (int q = 0; q < k; q++)
                            if (matrix[x + p][y + q])
                                this_k_unavailable = 1;

                    if (this_k_unavailable)
                        continue;

                    for (int p = 0; p < k; p++)
                        for (int q = 0; q < k; q++)
                            matrix[x + p][y + q] = 1;

                    remain -= k * k;
                    used++;
                    dfs(matrix, remain, used, n, m, best) ;
                    used--;
                    remain += k * k;

                    for (int p = 0; p < k; p++)
                        for (int q = 0; q < k; q++)
                            matrix[x + p][y + q] = 0;
                }

                return;
            }
}

int Solution::tilingRectangle(int n, int m) {
    int best=1<<30;

    vector<vector<int>> matrix(n, vector<int> (m));

    dfs(matrix, n * m, 0, n, m, best);

    return best;
}