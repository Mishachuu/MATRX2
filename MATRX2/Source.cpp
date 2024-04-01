#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <string>
#include <omp.h> // Подключаем библиотеку OpenMP

using namespace std;

void multiply_matrices(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C)
{
#pragma omp parallel for // Директива OpenMP для параллельного выполнения цикла
    for (int i = 0; i < C.size(); i++) {
        for (int j = 0; j < C[i].size(); j++) {
            C[i][j] = 0;
            for (int k = 0; k < C.size(); k++) {
                C[i][j] += B[i][k] * A[k][j];
            }
        }
    }
}

void read_data(vector<vector<int>>& A, string filename)
{
    ifstream data;
    data.open(filename);

    if (data.is_open()) {
        for (int i = 0; i < A.size(); i++) {
            for (int j = 0; j < A[i].size(); j++) {
                data >> A[i][j];
            }
        }
    }
    data.close();
}

void write_result_matrix(string filename, vector<vector<int>>& C)
{
    ofstream data(filename);

    for (int i = 0; i < C.size(); i++) {
        for (int j = 0; j < C[i].size(); j++) {
            data << C[i][j] << "\n";
        }
    }

    data.close();
}

void resize_matrix(vector<vector<int>>& A, int size)
{
    A.resize(size);
    for (auto& j : A)
        j.resize(size);
}

int main()
{
    srand(time(NULL));

    int size[9]{ 10, 50, 100, 500, 600, 700, 800, 900, 1000 };
    vector<vector<int>> A, B, C;
    string res;

    string res_filename, filename1, filename2;
    string filename[3]{ "C:\\Users\\misha\\source\\repos\\MATRX2\\MATRX2\\python\\data_2\\",
        "C:\\Users\\misha\\source\\repos\\MATRX2\\MATRX2\\python\\data_1\\",
        "C:\\Users\\misha\\source\\repos\\MATRX2\\MATRX2\\python\\result\\" };

    for (int i = 0; i < 9; i++)
    {
        resize_matrix(A, size[i]);
        resize_matrix(B, size[i]);
        resize_matrix(C, size[i]);

        filename1 = filename[0];
        filename2 = filename[1];
        read_data(A, filename1.append(to_string(size[i])).append(".txt"));
        read_data(B, filename2.append(to_string(size[i])).append(".txt"));

        chrono::steady_clock::time_point begin = chrono::steady_clock::now();
        multiply_matrices(A, B, C);
        chrono::steady_clock::time_point end = chrono::steady_clock::now();

        res_filename = filename[2];
        write_result_matrix(res_filename.append(to_string(size[i])).append(".txt"), C);

        res.append("For matrix with size of ").append(to_string(size[i])).append("x").append(to_string(size[i]));
        res.append(" time of multiplication = ").append(to_string(chrono::duration_cast<std::chrono::milliseconds>(end - begin).count())).append(" ms\n\n");
        cout << "Diff(ms) = " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << endl;
    }
    ofstream data("C:\\Users\\misha\\source\\repos\\MATRX2\\MATRX2\\res.txt");
    data << res;
    data.close();

    return 0;
}
