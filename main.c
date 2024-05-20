#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// функции, написанные в ассемблере
extern double f1 (double x);
extern double f2 (double x);
extern double f3 (double x);
extern double f1_d2 (double x);
extern double f2_d2 (double x);
extern double f3_d2 (double x);


int it_cnt = 0; //число итераций

// функция для вычисления абсциссы точки пересечения по методу деления отрезка пополам 
double root(double(*f)(double), double(*g)(double), double a, double b, double eps){
    double c;
    do{
        it_cnt++;
        c = (a + b) / 2;

        if ((f(a) - g(a)) * (f(c) - g(c)) <= 0){
            b = c;
        }else a = c;
    } while(fabs(b - a) > 2 * eps);

    return (a + b) / 2;
}
// функция для вычисления интеграла по методу трапеций
double integral(double (*f)(double), double (*f_d2)(double), double a, double b, double eps){
    double s = 0;

    double maxValue = f_d2(a) > f_d2(b) ? f_d2(a) : f_d2(b); // 
    
    int n = sqrt((pow((b-a), 3) * maxValue) / (12 * eps)) + 1;

    double h = (b - a) / n;

    while(a < b){
        s += (f(a) + f(a + h)) / 2 * h;
        a += h;
    }

    return s;
}

int main(int param, char *paramstr[]){
    const double eps1 = 0.001;
    const double eps2 = 0.001;

    double t13 = root(f1, f3, 0.1, 5.0, eps1); //значение абсциссы при пересечении f1 и f3
    double t12 = root(f1, f2, 2.1, 5.0, eps1); //значение абсциссы при пересечении f1 и f2
    double t23 = root(f2, f3, 2.1, 5.0, eps1); //значение абсциссы при пересечении f2 и f3

    if (param <= 1){
        printf ("Для справки введите в аргументах командной строки --help\n");
    }else if (strcmp(paramstr[1], "--help") == 0){
        printf("Для запуска программы используйте следующие ключи:\n");
        printf("--root без аргументов выведет абсциссы всех трех точек пересечения\n");
        printf("--square выводит искомую площадь\n");
        printf("--testr f g a b eps\n f и g - числа из диапазона {1, 2, 3} указывают номера функций, a и b - границы поиска абсциссы, не равные 0, eps - точность\n");
        printf("--testin f a b eps\n f - число из диапазона {1, 2, 3} указывает номер функции, a и b - границы расчета интеграла, eps - точность\n");
    }else if(param == 2){
        if (strcmp(paramstr[1], "--root") == 0){
            printf("Абсциссы пересечения функций f1 и f2: %lf\n", t12);
            printf("Абсциссы пересечения функций f1 и f3: %lf\n", t13);
            printf("Абсциссы пересечения функций f2 и f3: %lf\n", t23);
            
            printf("Число итераций: %d\n", it_cnt);
        }else if (strcmp(paramstr[1], "--square") == 0){
            double s1 = integral(f1, f1_d2, t13, t12, eps2); // значение площади под f1
            double s2 = integral(f3, f3_d2,t13, t23, eps2); // значение площади под f3
            double s3 = integral(f2, f2_d2, t23, t12, eps2); // значение площади под f2

            double s = s1 - s2 - s3;
            printf("Площадь заданной фигуры: %lf\n", s);
        }else printf("Некорректный ввод, введите --help для справки\n");
    }else if(param == 7){
        if (strcmp(paramstr[1], "--testr") == 0){
            char *q;

            int func1 = atoi(paramstr[2]);
            int func2 = atoi(paramstr[3]);

            double a = strtod(paramstr[4], &q);
            double b = strtod(paramstr[5], &q);

            double eps = strtod(paramstr[6], &q);

            double t13 = root(f1, f3, a, b, eps); //значение абсциссы при пересечении f1 и f3
            double t12 = root(f1, f2, a, b, eps); //значение абсциссы при пересечении f1 и f2
            double t23 = root(f2, f3, a, b, eps); //значение абсциссы при пересечении f2 и f3

            if ((func1 == 1 && func2 == 2) || (func2 == 1 && func1 == 2)) printf("%f\n",t12);
            else if ((func1 == 1 && func2 == 3) || (func2 == 1 && func1 == 3)) printf("%f\n",t13);
            else if ((func1 == 2 && func2 == 3) || (func2 == 2 && func1 == 3)) printf("%f\n",t23);
            else printf("Некорректный ввод, введите--help для справки\n");
        }else printf("Некорректный ввод, введите --help для справки\n");
    }else if(param == 6){
        if (strcmp(paramstr[1], "--testin") == 0){
            char *q;

            int f = atoi(paramstr[2]);

            double a = strtod(paramstr[3], &q);
            double b = strtod(paramstr[4], &q);

            double eps = strtod(paramstr[5], &q);

            if (f == 1) printf("%f\n", integral(f1, f1_d2, a, b, eps));
            else if (f == 2) printf("%f\n", integral(f2, f2_d2, a, b, eps));
            else if (f == 3) printf("%f\n", integral(f3, f3_d2, a, b, eps));
            else printf("Некорректный ввод, введите --help для справки\n");
        }else printf("Некорректный ввод, введите --help для справки\n");
    }else printf("Некорректный ввод, введите --help для справки\n");

    return 0;
}
