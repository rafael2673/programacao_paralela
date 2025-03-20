#include <iostream>
#include <vector>

using namespace std;

// Função para multiplicar matriz por vetor
vector<int> multiplyMatrixVector(const vector<vector<int>>& matrix, const vector<int>& vec) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<int> result(rows, 0);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i] += matrix[i][j] * vec[j];
        }
    }
    return result;
}

int main() {
    int rows, cols;
    cout << "Digite o número de linhas da matriz: ";
    cin >> rows;
    cout << "Digite o número de colunas da matriz (igual ao tamanho do vetor): ";
    cin >> cols;

    vector<vector<int>> matrix(rows, vector<int>(cols));
    vector<int> vec(cols);

    cout << "Digite os elementos da matriz: \n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> matrix[i][j];
        }
    }

    cout << "Digite os elementos do vetor: \n";
    for (int i = 0; i < cols; i++) {
        cin >> vec[i];
    }

    vector<int> result = multiplyMatrixVector(matrix, vec);

    cout << "Resultado da multiplicação: \n";
    for (int i = 0; i < rows; i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}
