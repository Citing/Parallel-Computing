#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>

const int it = 1000;

const std::vector<int> N{8, 9, 10, 11, 12, 13, 14, 15, 16};

class matrix
{
public:
    int n;
    std::vector<std::vector<int>> mat;
    matrix(int n): n(n)
    {
        mat.resize(n);
        for (auto& it: mat)
        {
            it.resize(n);
            for (auto& itt:it)
            {
                itt = 0;
            }
        }
    }
};

class queenT
{
public:
    int i, n, N;
    int result;
    queenT(int i, int n, int N): i(i), n(n), N(N), result(0) {}
};

void test(int n);
void queens(int n, int num_thread);
bool testQueens(int n, int num_thread);
int getQueens(int n, int num_thread);
int DFS(int row, matrix& mat);
void queenThread(std::shared_ptr<queenT> t);

int main()
{
    std::for_each(N.begin(), N.end(), test);
}

void test(int n)
{
    std::cout<<"Number of queens: "<<n<<'\n';
    for (int i = 1; i <= 4; ++i)
    {
        std::cout<<"Number of threads: "<<i<<'\t';
        if (!testQueens(n, i))
        {
            std::cout<<"Wrong result!\n";
            exit(0);
        }
        int N = it;
        std::chrono::duration<double> t_span;
        std::chrono::steady_clock::time_point t_start, t_end;
        t_start = std::chrono::steady_clock::now();
        while (N--)
        {
            std::cerr<<n<<'\t'<<i<<'\t'<<it - N<<'\n';
            queens(n, i);
        }
        t_end = std::chrono::steady_clock::now();
        t_span = std::chrono::duration_cast<std::chrono::duration<double>>(t_end - t_start);
        std::cout<<"Time: "<<t_span.count()<<'\n';
    }
    std::cout<<'\n';
}

void queens(int n, int num_thread)
{
    getQueens(n, num_thread);
}

void queenThread(std::shared_ptr<queenT> t)
{
    for (int i = t->i; i < t->N; i += t->n)
    {
        matrix mat(t->N);
        mat.mat[0][i] = 1;
        int num = DFS(1, mat);
        t->result += num;
    }
}

int getQueens(int n, int num_thread)
{
    std::vector<std::shared_ptr<queenT>> queenTs;
    for (int i = 0; i < num_thread; ++i)
    {
        queenTs.push_back(std::make_shared<queenT>(i, num_thread, n));
    }
    switch (num_thread)
    {
    case 1:
        {
            std::thread t0(queenThread, queenTs[0]);
            t0.join();
            break;
        }
    case 2:
        {
            std::thread t0(queenThread, queenTs[0]);
            std::thread t1(queenThread, queenTs[1]);
            t0.join();
            t1.join();
            break;
        }
    case 3:
        {
            std::thread t0(queenThread, queenTs[0]);
            std::thread t1(queenThread, queenTs[1]);
            std::thread t2(queenThread, queenTs[2]);
            t0.join();
            t1.join();
            t2.join();
            break;
        }
    case 4:
        {
            std::thread t0(queenThread, queenTs[0]);
            std::thread t1(queenThread, queenTs[1]);
            std::thread t2(queenThread, queenTs[2]);
            std::thread t3(queenThread, queenTs[3]);
            t0.join();
            t1.join();
            t2.join();
            t3.join();
            break;
        }
    }
    int count = 0;
    for (const auto& it: queenTs)
    {
        count += it->result;
    }
    return count;
}

bool testQueens(int n, int num_thread)
{
    matrix mat_right(n);
    int right = DFS(0, mat_right);
    int result = getQueens(n, num_thread);
    if (right == result)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int DFS(int row, matrix& mat)
{
    if (row == mat.n)
    {
        return 1;
    }
    int count = 0;
    for (int col = 0; col < mat.n; ++col)
    {
        int flag = 0;
        for (int i = 0; i < row; ++i)
        {
            if (mat.mat[i][col] ||
                (col + std::abs(row - i) < mat.n && mat.mat[i][col + std::abs(row - i)]) ||
                (col - std::abs(row - i) >= 0 && mat.mat[i][col - std::abs(row - i)]))
            {
                flag = 1;
                break;
            }
        }
        if (flag)
        {
            continue;
        }
        mat.mat[row][col] = 1;
        count += DFS(row + 1, mat);
        mat.mat[row][col] = 0;
    }
    return count;
}
