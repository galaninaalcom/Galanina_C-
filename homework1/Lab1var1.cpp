#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

//Первый вариант

float vectorLength(float x, float y) { // Функция, считающая длину вектора
    return std::sqrt(x * x + y * y);
};

int main(int argc, char** argv) {
    fstream inputFile("in.txt"); // Вытаскиваем файл
    if (inputFile.is_open()) { //проверка открытия файла
        float xn, yx; // Задаём переменные х и у

        inputFile >> xn; //Приём координат
        inputFile >> yx;

        float ccoord; // временная координата
        vector<float> coordX; // координаты точек
        vector<float> coordY;
        // Пока в файле есть данные, выполнять:
        while (inputFile >> ccoord) {
            coordX.push_back(ccoord); // Вставка в массив данных о координатах
            inputFile >> ccoord;
            coordY.push_back(ccoord);
        }
        inputFile.close(); // Закрытие файла

    //Задание переменных левого минимального угла, правого и их подсчёт
        int left = -1, right = -1; // Индикатор того, есть ли слева/справа вообще точке (понадобится в подсчёте)
        float LeftMinCos = 1, RightMinCos = 1; // Начальное задание минимального косинуса и синуса
        float len_v = sqrt(xn * xn + yx * yx); // Длина вектора
        float cos_a = xn / len_v; // Косинус альфа через отношение прилежащего к гипотенузе
        float sin_a = yx / len_v; // Синус альфа через отношение прилежащего к гипотенузе

            //Цикл, считающий по каждой координате:
        for (int i = 0; i < coordX.size(); ++i) {
            float new_x = cos_a * coordX[i] + sin_a * coordY[i]; //координаты после поворота
            float new_y = -sin_a * coordX[i] + cos_a * coordY[i]; //координаты после поворота

            float prod_dot = new_x * 1 + new_y * 0; //перемножаем координаты (то есть скалярное произведение)
            float len_p = sqrt(new_x * new_x + new_y * new_y); //находим длину второго вектора
            float cos = prod_dot / 1 / len_p; // здесь находим косинус между векторами

            if (new_y > 0) { //слева
                if (cos <= LeftMinCos) {
                    LeftMinCos = cos; // Если наш косинус в данный момент меньше, чем минимальный найденный косинус, то ему присваиваем новое значение данного косинуса
                    left = i; // Присваивается индикатору то, что слева существуют точки
                }
            }

            if (new_y <= 0) { // справа аналогично
                if (cos <= RightMinCos) {
                    RightMinCos = cos;
                    right = i;
                }
            }
        }
        if (left != -1) { // Если точки слева есть, то находим самые левые точки
            cout << "Leftmost: " << coordX[left] << " " << coordY[left] << endl;
        }
        else { // Если слева точек нет, то просто выводим точку начала координат
            cout << "Leftmost: " << 0 << " " << 0 << endl;
        }
        if (right != -1) {
            cout << "Rightmost: " << coordX[right] << " " << coordY[right] << endl;
        }
        else {
            cout << "Rightmost: " << 0 << " " << 0 << endl;
        }
    }
    else { // Если файл не открылся, то выводим ошибку
        cout << "Unknown file" << endl;
    }
    return 0; // Типа заканчиваем прогу
}