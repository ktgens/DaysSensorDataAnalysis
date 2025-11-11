#include <iostream>
using namespace std;

void validateInput(float &outValue, int lowerBound, int upperBound) {
    while (true) {
        cin >> outValue;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка, введите число" << endl;
            continue;
        }

        if (outValue < lowerBound || outValue > upperBound) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка, введите число от " << lowerBound << " до "
                 << upperBound << endl;
            continue;
        }

        break;
    }
}

float dayAverage(float *row, int h) {
    float sm = 0;
    for (int i = 0; i < h; i++) {
        sm += *(row + i);
    }
    return sm / h;
}

float overallAverage(float **p, int d, int h) {
    float sm = 0;
    for (int i = 0; i < d; i++) {
        sm += dayAverage(*(p + i), h);
    }
    return sm / d;
}

void showHotDays(float **p, int d, int h) {
    bool fl = false;
    float avg = overallAverage(p, d, h);
    for (int i = 0; i < d; i++) {
        float dayAvg = dayAverage(*(p + i), h);
        if (dayAvg > avg) {
            fl = true;
            cout << "День " << i + 1 << " (среднее = " << dayAvg << ")";
        }
    }
    if (!fl) {
        cout << "отсутствуют" << endl;
    }
}

int main() {
    cout << "===Анализ сенсора===" << endl;
    float d;
    float h;
    cout << "Введите количество дней (до 30): ";
    validateInput(d, 1, 30);
    cout << "Введите количество измерений в дне (до 24): ";
    validateInput(h, 1, 24);

    float **data = new float *[d];
    for (int i = 0; i < d; i++) {
        *(data + i) = new float[h];
    }

    for (int i = 0; i < d; i++) {
        cout << "День " << i + 1 << ": ";
        for (int j = 0; j < h; j++) {
            validateInput(*(*(data + i) + j), -50, 50);
        }
    }

    cout << "Общая средняя температура: " << overallAverage(data, d, h) << endl;
    cout << "Теплые дни: " << endl;
    showHotDays(data, d, h);
}
