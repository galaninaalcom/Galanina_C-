#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
const float g = 9.81;

// Функция для траектория движения (здесь прописывается вся физика движения шарика). Она нам возвращает номер промежутка, где упадёт шарик
int physics(float x_0, float h_0, float vx0, float vy0,
    int start_number, // Это номер промежутка
    const vector<float>& coordX, const vector<float>& coordY) // вводим массив координат перегородок по Х и их высоту (то есть У). Const означает то, что мы эти данные не сможем менять по ходу программы
 {
    if (vx0 > 0) { // Если скорость положительна
        int Newnumber = start_number + 1; // Прибавляем 1 к номеру промежутка ( то есть летим дальше)
        float xi = coordX[Newnumber]; // coord x
        float ti = (xi - x_0) / vx0; // Время
        float hi = -0.5 * g * ti * ti + vy0 * ti + h_0; // Формула высоты (из школьной физики)

        if (hi <= 0) { // если высота точки в данный момент на уровне земли или ниже, то выводим номер промежутка
            return start_number;
        }
        else if (coordY[Newnumber] >= hi) { // Если произошло столкновение со столбом (отскок)
            float vxi = -vx0; // Скорость меняется на противоположную
            float vyi = -g * ti + vy0;
            return physics(xi, hi, vxi, vyi, Newnumber, coordX, coordY);
        }
        else {
            if (Newnumber >= coordX.size() - 1) { // Если всё нормально, летим дальше
                return Newnumber;
            }
            float vxi = vx0;
            float vyi = -g * ti + vy0;
            return physics(xi, hi, vxi, vyi, Newnumber, coordX, coordY); //Рекурсия
        }
    }

    if (vx0 <= 0) { // Если произошёл отскок:
        int Newnumber = start_number - 1; // Летим назад
        float xi = coordX[Newnumber];
        float ti = (xi - x_0) / vx0;
        float hi = -0.5 * g * ti * ti + vy0 * ti + h_0;
        // По подобию с первой функцией:
        if (hi <= 0) {
            return Newnumber;
        }
        else if (coordY[Newnumber] > hi) {
            float vxi = -vx0;
            float vyi = -g * ti + vy0;
            return physics(xi, hi, vxi, vyi, Newnumber, coordX, coordY);
        }
        else {
            float vxi = vx0;
            float vyi = -g * ti + vy0;
            return physics(xi, hi, vxi, vyi, Newnumber, coordX, coordY);
        }
    }
    return start_number; // В итоге функция возвращает нам номер промежутка
}

// По условию задачи:
int main(int argc, char** argv) {
    if (argc == 2) {
        string line;
        fstream inputFile(argv[1]);
        if (inputFile.is_open()) { //проверка открытия файла
            float h0, VVY, VVX; // Задание переменных в основной программе
            inputFile >> h0;  // считываем начальные данные
            inputFile >> VVX;
            inputFile >> VVY;
            int i = 0;
            float CCoord; // Промежуточная координата
            vector<float> coordX; // координаты перегородок засовываем в массив
            vector<float> coordY;
            coordX.push_back(0);
            coordY.push_back(h0);
            while (inputFile >> CCoord) { // Вытаскиваем координаты
                if (i % 2 == 0) { // Это для икса (то есть первый столбец)
                    coordX.push_back(CCoord);
                }
                else { // это для У (то есть второй)
                    coordY.push_back(CCoord);
                }
                ++i;
            }
            inputFile.close(); // Закрываем файл

            if (coordX.size() <= 1) { // Если столбцов нет, то выводим 0
                cout << 0;
            }
            else {
                int number = physics(0, h0, VVX, VVY, 0, coordX, coordY); // Подсчёт ответа
                cout << number; // Вывод номера промежутка
            }
        }
        else {
            cout << "Unable to open file" << endl; // Если невозможно открыть файл, то ошибка
        }
    }
    else {
        cout << "there are no arguments or there are more of them than we expect" << endl; // Если некорректное кол-во аргументов
    }
    return 0;
}