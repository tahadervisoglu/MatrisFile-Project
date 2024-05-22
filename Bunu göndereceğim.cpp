#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

void menuac() {
    cout << "1 - Generate new matrices" << endl;
    cout << "2 - Read matrices from an existing file" << endl;
}
bool dosyaBosMu(const string& dosyaAdi) {
    ifstream dosya(dosyaAdi);
    return dosya.peek() == ifstream::traits_type::eof();
}

void konvolusyon(int** input, int inputRow, int inputCol, int** core, int coreRow, int coreCol, float** sonmatris) {
    int sonmatrisboyut = inputRow - coreRow + 1;
    int bolu = coreRow * coreCol;

    for (int i = 0; i < inputRow - coreRow + 1; ++i) {
        for (int j = 0; j < inputCol - coreCol + 1; ++j) {
            sonmatris[i][j] = 0.0;
            for (int m = 0; m < coreRow; ++m) {
                for (int n = 0; n < coreCol; ++n) {
                    sonmatris[i][j] += static_cast<float>(input[i + m][j + n]) * core[coreRow - m - 1][coreCol - n - 1];
                }
            }
            sonmatris[i][j] = floor(static_cast<float>(sonmatris[i][j]) / bolu);
        }
    }
}


void dosyaoku(int& inputRow, int& inputCol, int**& inputMatrix, int& coreRow, int& coreCol, int**& coreMatrix) {
    string dosyaAdi = "data.txt";

    if (dosyaBosMu(dosyaAdi)) {
        cout << "Dosya bos. Lutfen matrisleri olusturun." << endl;
        return;
    }
    ifstream dosyaOku("data.txt");
    dosyaOku >> inputRow >> inputCol;

    inputMatrix = new int* [inputRow];
    for (int i = 0; i < inputRow; ++i) {
        inputMatrix[i] = new int[inputCol];
    }

    for (int i = 0; i < inputRow; ++i) {
        for (int j = 0; j < inputCol; ++j) {
            dosyaOku >> inputMatrix[i][j];
        }
    }

    cout << "Read INPUT MATRIX" << endl;
    for (int i = 0; i < inputRow; ++i) {
        for (int j = 0; j < inputCol; ++j) {
            cout << inputMatrix[i][j] << " ";
        }
        cout << endl;
    }

    dosyaOku >> coreRow >> coreCol;

    coreMatrix = new int* [coreRow];
    for (int i = 0; i < coreRow; ++i) {
        coreMatrix[i] = new int[coreCol];
    }

    for (int i = 0; i < coreRow; ++i) {
        for (int j = 0; j < coreCol; ++j) {
            dosyaOku >> coreMatrix[i][j];
        }
    }

    cout << "Read CORE MATRIX" << endl;
    for (int i = 0; i < coreRow; ++i) {
        for (int j = 0; j < coreCol; ++j) {
            cout << coreMatrix[i][j] << " ";
        }
        cout << endl;
    }

    dosyaOku.close();

    // Üçüncü matris için yer ayır
    float** sonMatris = new float* [inputRow - coreRow + 1];
    for (int i = 0; i < inputRow - coreRow + 1; ++i) {
        sonMatris[i] = new float[inputCol - coreCol + 1];
    }

    // Konvolüsyon işlemini yap ve ekrana yazdır
    konvolusyon(inputMatrix, inputRow, inputCol, coreMatrix, coreRow, coreCol, sonMatris);

    cout << "Resulting MATRIX" << endl;
    for (int i = 0; i < inputRow - coreRow + 1; ++i) {
        for (int j = 0; j < inputCol - coreCol + 1; ++j) {
            cout << sonMatris[i][j] << " ";
        }
        cout << endl;
    }

    // Belleği temizle
    for (int i = 0; i < inputRow - coreRow + 1; ++i) {
        delete[] sonMatris[i];
    }
    delete[] sonMatris;
}


void dosyayaz(int inputRow, int inputCol, int** inputMatrix, int coreRow, int coreCol, int** coreMatrix) {
    ofstream dosyaYaz("data.txt");
    dosyaYaz << inputRow << " " << inputCol << endl;

    for (int i = 0; i < inputRow; ++i) {
        for (int j = 0; j < inputCol; ++j) {
            dosyaYaz << inputMatrix[i][j] << " ";
        }
        dosyaYaz << endl;
    }

    dosyaYaz << coreRow << " " << coreCol << endl;

    for (int i = 0; i < coreRow; ++i) {
        for (int j = 0; j < coreCol; ++j) {
            dosyaYaz << coreMatrix[i][j] << " ";
        }
        dosyaYaz << endl;
    }

    dosyaYaz.close();
}



int main() {
    srand(time(NULL));

    for (;;) {            //sonsuz döngü oluşturuyoruz.
        menuac();
        int secim;
        cin >> secim;

        if (secim == 2) {
           
                cout << "File is not empty. Reading matrices from the file." << endl;

                int inputRow, inputCol, coreRow, coreCol;
                int** inputMatrix;
                int** coreMatrix;

                dosyaoku(inputRow, inputCol, inputMatrix, coreRow, coreCol, coreMatrix);

                // Matrisleri serbest bırak
                for (int i = 0; i < inputRow; ++i) {
                    delete[] inputMatrix[i];
                }
                delete[] inputMatrix;

                for (int i = 0; i < coreRow; ++i) {
                    delete[] coreMatrix[i];
                }
                delete[] coreMatrix;
            
        }


        if (secim == 1) {
            int inputRow, inputCol, i, j;

            inputCol = rand() % 15 + 6;
            inputRow = inputCol;

            int** inputMatrix = new int* [inputRow];
            for (i = 0; i < inputRow; ++i) {
                inputMatrix[i] = new int[inputCol];
            }

            for (i = 0; i < inputRow; ++i) {
                for (j = 0; j < inputCol; ++j) {
                    inputMatrix[i][j] = rand() % 10 + 10;
                }
            }

            int coreRow, coreCol;

            coreCol = rand() % 3 + 2;
            coreRow = coreCol;

            int** coreMatrix = new int* [coreRow];
            for (i = 0; i < coreRow; ++i) {
                coreMatrix[i] = new int[coreCol];
            }
            for (i = 0; i < coreRow; ++i) {
                for (j = 0; j < coreCol; ++j) {
                    coreMatrix[i][j] = rand() % 10 + 1;
                }
            }
            float** sonmatris;
            int sRow = inputRow - coreRow + 1;
            int sCol = inputCol - coreCol + 1;
            sonmatris = new float* [sRow];
            for (i = 0; i < sRow; ++i) {
                sonmatris[i] = new float[sCol];
            }
            konvolusyon(inputMatrix, inputRow, inputCol, coreMatrix, coreRow, coreCol, sonmatris);

            int** intsonmatris = new int* [sRow];
            for (i = 0; i < sRow; ++i) {
                intsonmatris[i] = new int[sCol];
                for (j = 0; j < sCol; ++j) {
                    intsonmatris[i][j] = static_cast<int>(sonmatris[i][j]);
                }
            }
            cout << "islem basarili" << endl;
            dosyayaz(inputRow, inputCol, inputMatrix, coreRow, coreCol, coreMatrix);
            // Matrisleri serbest bırak
            for (i = 0; i < inputRow; ++i) {
                delete[] inputMatrix[i];
            }
            delete[] inputMatrix;

            for (i = 0; i < coreRow; ++i) {
                delete[] coreMatrix[i];
            }
            delete[] coreMatrix;

            for (i = 0; i < sRow; ++i) {
                delete[] sonmatris[i];
                delete[] intsonmatris[i];
            }
            delete[] sonmatris;
            delete[] intsonmatris;
        }
    }
    return 0;
}
