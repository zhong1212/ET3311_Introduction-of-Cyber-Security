#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Hàm chuẩn hóa chuỗi: in hoa, loại bỏ khoảng trắng và số, gộp J thành I
string formatString(string s) {
    string res = "";
    for (char c : s) {
        if (isalpha(c)) {
            c = toupper(c);
            if (c == 'J') c = 'I';
            res += c;
        }
    }
    return res;
}

// Xây dựng ma trận 5x5 từ từ khóa
void buildMatrix(string key, char matrix[5][5]) {
    bool used[26] = {false};
    used['J' - 'A'] = true; // Bỏ qua J
    string uniqueKey = "";
    
    for (char c : key) {
        if (!used[c - 'A']) {
            uniqueKey += c;
            used[c - 'A'] = true;
        }
    }
    
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!used[c - 'A']) {
            uniqueKey += c;
        }
    }
    
    int k = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = uniqueKey[k++];
        }
    }
}

// Tìm vị trí của ký tự trong ma trận
void findPosition(char matrix[5][5], char c, int &row, int &col) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == c) {
                row = i;
                col = j;
                return;
            }
        }
    }
}

// Hàm mã hóa Playfair
string encryptPlayfair(string pt, string key) {
    pt = formatString(pt);
    key = formatString(key);
    
    char matrix[5][5];
    buildMatrix(key, matrix);
    
    // Xử lý cặp ký tự (thêm X nếu trùng)
    string preparedPt = "";
    for (size_t i = 0; i < pt.length(); i++) {
        preparedPt += pt[i];
        if (i + 1 < pt.length() && pt[i] == pt[i+1]) {
            preparedPt += 'X';
        } else if (i + 1 < pt.length()) {
            preparedPt += pt[++i];
        }
    }
    if (preparedPt.length() % 2 != 0) preparedPt += 'X'; // Lẻ thì thêm X ở cuối
    
    string ciphertext = "";
    for (size_t i = 0; i < preparedPt.length(); i += 2) {
        int r1, c1, r2, c2;
        findPosition(matrix, preparedPt[i], r1, c1);
        findPosition(matrix, preparedPt[i+1], r2, c2);
        
        if (r1 == r2) { // Cùng hàng
            ciphertext += matrix[r1][(c1 + 1) % 5];
            ciphertext += matrix[r2][(c2 + 1) % 5];
        } else if (c1 == c2) { // Cùng cột
            ciphertext += matrix[(r1 + 1) % 5][c1];
            ciphertext += matrix[(r2 + 1) % 5][c2];
        } else { // Khác hàng, khác cột
            ciphertext += matrix[r1][c2];
            ciphertext += matrix[r2][c1];
        }
    }
    return ciphertext;
}

int main() {
    // Thông tin từ slide
    string plaintext = "Mon ly thuyet mat ma ky mua thu";
    string keyword1 = "nhungiotdhbkhn";
    string keyword2 = "dtvtdhbkhn";
    
    cout << "Plaintext: " << plaintext << endl;
    cout << "Keyword 1: " << keyword1 << endl;
    cout << "Ciphertext 1: " << encryptPlayfair(plaintext, keyword1) << endl;
    cout << "Keyword 1: " << keyword2 << endl;
    cout << "Ciphertext 2: " << encryptPlayfair(plaintext, keyword2) << endl;
    
    return 0;
}