#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>

struct Circle {
    double x, y, r;
};

bool isInsideCircles(double x, double y, const Circle& c1, const Circle& c2, const Circle& c3) {
    return (pow(x - c1.x, 2) + pow(y - c1.y, 2) <= pow(c1.r, 2)) &&
           (pow(x - c2.x, 2) + pow(y - c2.y, 2) <= pow(c2.r, 2)) &&
           (pow(x - c3.x, 2) + pow(y - c3.y, 2) <= pow(c3.r, 2));
}

int main() {
    // Инициализация генератора случайных чисел
    srand(static_cast<unsigned int>(time(0)));

    Circle c1 = {1.0, 1.0, 1.0};
    Circle c2 = {1.5, 2.0, sqrt(5) / 2.0};
    Circle c3 = {2.0, 1.5, sqrt(5) / 2.0};

    // Границы широкой области
    double x_min_wide = c1.x - c1.r;
    double x_max_wide = c3.x + c3.r;
    double y_min_wide = c1.y - c1.r;
    double y_max_wide = c2.y + c2.r;
    double S_rec_wide = (x_max_wide - x_min_wide) * (y_max_wide - y_min_wide);

    // Границы узкой области
    double x_min_narrow = 1.0;
    double x_max_narrow = 2.0;
    double y_min_narrow = 1.0;
    double y_max_narrow = 2.0;
    double S_rec_narrow = (x_max_narrow - x_min_narrow) * (y_max_narrow - y_min_narrow);

    // Точное значение площади
    double exact_area = 0.25 * M_PI + 1.25 * asin(0.8) - 1.0;

    // Открываем файл для записи данных
    std::ofstream outfile("data.csv");
    outfile << "N,Area_Wide,Error_Wide,Area_Narrow,Error_Narrow\n";

    // Цикл по N от 100 до 100000 с шагом 500
    for (int N = 100; N <= 100000; N += 500) {
        int M_wide = 0;
        int M_narrow = 0;

        // Широкая область
        for (int i = 0; i < N; ++i) {
            double x = x_min_wide + (x_max_wide - x_min_wide) * rand() / RAND_MAX;
            double y = y_min_wide + (y_max_wide - y_min_wide) * rand() / RAND_MAX;

            if (isInsideCircles(x, y, c1, c2, c3)) {
                ++M_wide;
            }
        }

        double approx_area_wide = static_cast<double>(M_wide) / N * S_rec_wide;
        double error_wide = fabs((approx_area_wide - exact_area) / exact_area) * 100.0;

        // Узкая область
        for (int i = 0; i < N; ++i) {
            double x = x_min_narrow + (x_max_narrow - x_min_narrow) * rand() / RAND_MAX;
            double y = y_min_narrow + (y_max_narrow - y_min_narrow) * rand() / RAND_MAX;

            if (isInsideCircles(x, y, c1, c2, c3)) {
                ++M_narrow;
            }
        }

        double approx_area_narrow = static_cast<double>(M_narrow) / N * S_rec_narrow;
        double error_narrow = fabs((approx_area_narrow - exact_area) / exact_area) * 100.0;

        // Записываем результаты в файл
        outfile << N << "," << approx_area_wide << "," << error_wide << "," << approx_area_narrow << "," << error_narrow << "\n";

        // Выводим прогресс
        if (N % 5000 == 0) {
            std::cout << "Обработано N = " << N << std::endl;
        }
    }

    outfile.close();
    std::cout << "Data saved to file: data.csv" << std::endl;

    return 0;
}
