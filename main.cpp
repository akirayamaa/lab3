#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <limits>
#include <new>

using std::cin;
using std::cout;
using std::endl;

void clearInput()
{
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int readIntRange(const char* prompt, int minV, int maxV)
{
    while (true)
    {
        cout << prompt;
        int x;
        if (!(cin >> x))
        {
            cout << "Ошибка ввода\n";
            clearInput();
            continue;
        }
        clearInput();
        if (x < minV || x > maxV)
        {
            cout << "Выход за диапазон\n";
            continue;
        }
        return x;
    }
}

double readDouble(const char* prompt)
{
    while (true)
    {
        cout << prompt;
        double x;
        if (!(cin >> x))
        {
            cout << "Ошибка ввода\n";
            clearInput();
            continue;
        }
        clearInput();
        return x;
    }
}

void readLineSafe(const char* prompt, char* buf, int maxLen)
{
    while (true)
    {
        cout << prompt;
        cin.getline(buf, maxLen);
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Слишком длинная строка\n";
            continue;
        }
        return;
    }
}

int postMenu()
{
    cout << "\nЗадача завершена.\n";
    cout << "1. Выполнить еще раз\n";
    cout << "2. В главное меню\n";
    return readIntRange("Выберите действие: ", 1, 2);
}

/* ===== ЗАДАНИЕ 1 ===== */

void task1()
{
    const int N = 15;
    int a[N];

    for (int i = 0; i < N; i++)
        a[i] = 2 + rand() % 4;

    int sum = 0;
    for (int i = 0; i < N; i++) sum += a[i];

    double avg = (double)sum / N;

    int bad = 0;
    int excellent = 0;
    for (int i = 0; i < N; i++)
    {
        if (a[i] < 3) bad++;
        if (a[i] == 5) excellent++;
    }

    int freq[6] = {0};
    for (int i = 0; i < N; i++) freq[a[i]]++;

    int mode = 2;
    for (int g = 3; g <= 5; g++)
        if (freq[g] > freq[mode]) mode = g;

    cout << "\nОценки: ";
    for (int i = 0; i < N; i++) cout << a[i] << " ";
    cout << "\nСредний балл: " << avg;
    cout << "\nНеуспевающих: " << bad;
    cout << "\nОтличников: " << excellent;
    cout << "\nМода: " << mode << "\n";
}

/* ===== ЗАДАНИЕ 2 ===== */

struct Operation
{
    double a, b, res;
    char op;
};

bool calcPtr(const double* a, const double* b, char op, double* out)
{
    if (op == '+') *out = *a + *b;
    else if (op == '-') *out = *a - *b;
    else if (op == '*') *out = *a * *b;
    else if (op == '/' && *b != 0) *out = *a / *b;
    else return false;
    return true;
}

void swapPtr(double* x, double* y)
{
    double t = *x; *x = *y; *y = t;
}

void minMaxPtr(const double* x, const double* y, const double* z, double* mn, double* mx)
{
    *mn = *mx = *x;
    if (*y < *mn) *mn = *y;
    if (*z < *mn) *mn = *z;
    if (*y > *mx) *mx = *y;
    if (*z > *mx) *mx = *z;
}

void task2()
{
    const int H = 5;
    Operation hist[H];
    int head = 0, count = 0;

    while (true)
    {
        cout << "\n1) Операция\n2) История\n3) Swap\n4) Min/Max\n0) Выход\n";
        int c = readIntRange("Выбор: ", 0, 4);
        if (c == 0) break;

        if (c == 1)
        {
            double a = readDouble("a: ");
            double b = readDouble("b: ");
            char op;
            cout << "Операция: ";
            cin >> op;
            clearInput();
            double r;
            if (calcPtr(&a, &b, op, &r))
            {
                cout << "Результат: " << r << endl;
                hist[head] = {a, b, r, op};
                head = (head + 1) % H;
                if (count < H) count++;
            }
            else cout << "Ошибка\n";
        }
        else if (c == 2)
        {
            for (int i = 0; i < count; i++)
            {
                int idx = (head + i) % H;
                cout << hist[idx].a << " " << hist[idx].op << " "
                     << hist[idx].b << " = " << hist[idx].res << endl;
            }
        }
        else if (c == 3)
        {
            double x = readDouble("x: ");
            double y = readDouble("y: ");
            swapPtr(&x, &y);
            cout << x << " " << y << endl;
        }
        else if (c == 4)
        {
            double x = readDouble("1: ");
            double y = readDouble("2: ");
            double z = readDouble("3: ");
            double mn, mx;
            minMaxPtr(&x, &y, &z, &mn, &mx);
            cout << "min=" << mn << " max=" << mx << endl;
        }
    }
}

/* ===== ЗАДАНИЕ 3 ===== */

int myLen(const char* s)
{
    int n = 0;
    while (s[n]) n++;
    return n;
}

bool isLetter(char c)
{
    return std::isalpha((unsigned char)c);
}

void normalize(const char* in, char* out, int size)
{
    int j = 0;
    for (int i = 0; in[i]; i++)
        if (isLetter(in[i]) && j < size - 1)
            out[j++] = std::tolower(in[i]);
    out[j] = '\0';
}

bool isPalindrome(const char* s)
{
    char t[256];
    normalize(s, t, 256);
    int n = myLen(t);
    for (int i = 0; i < n / 2; i++)
        if (t[i] != t[n - i - 1]) return false;
    return true;
}

void reverseStr(char* s)
{
    int n = myLen(s);
    for (int i = 0; i < n / 2; i++)
    {
        char t = s[i];
        s[i] = s[n - i - 1];
        s[n - i - 1] = t;
    }
}

bool areAnagrams(const char* a, const char* b)
{
    char x[256], y[256];
    normalize(a, x, 256);
    normalize(b, y, 256);
    int f1[256] = {0}, f2[256] = {0};
    for (int i = 0; x[i]; i++) f1[(unsigned char)x[i]]++;
    for (int i = 0; y[i]; i++) f2[(unsigned char)y[i]]++;
    for (int i = 0; i < 256; i++)
        if (f1[i] != f2[i]) return false;
    return true;
}

void task3()
{
    char s1[256], s2[256];
    readLineSafe("Строка: ", s1, 256);
    cout << (isPalindrome(s1) ? "Палиндром\n" : "Не палиндром\n");
    char r[256];
    for (int i = 0; i <= myLen(s1); i++) r[i] = s1[i];
    reverseStr(r);
    cout << "Реверс: " << r << endl;
    readLineSafe("Первая строка: ", s1, 256);
    readLineSafe("Вторая строка: ", s2, 256);
    cout << (areAnagrams(s1, s2) ? "Анаграммы\n" : "Не анаграммы\n");
}

/* ===== ЗАДАНИЕ 4 ===== */

int** allocMatrix(int r, int c)
{
    int** m = new (std::nothrow) int*[r];
    if (!m) return nullptr;
    for (int i = 0; i < r; i++)
    {
        m[i] = new (std::nothrow) int[c];
        if (!m[i]) return nullptr;
    }
    return m;
}

void freeMatrix(int** m, int r)
{
    for (int i = 0; i < r; i++) delete[] m[i];
    delete[] m;
}

void task4()
{
    int M = readIntRange("M: ", 1, 20);
    int N = readIntRange("N: ", 1, 20);
    int** a = allocMatrix(M, N);
    int** t = allocMatrix(N, M);

    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = rand() % 10;

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }

    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            t[j][i] = a[i][j];

    cout << endl;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            cout << t[i][j] << " ";
        cout << endl;
    }

    freeMatrix(t, N);
    freeMatrix(a, M);
}

/* ===== ЗАДАНИЕ 5 ===== */

struct Book
{
    char* title;
    char* author;
    int year;
};

char* allocStr(const char* s)
{
    int n = myLen(s);
    char* p = new char[n + 1];
    for (int i = 0; i <= n; i++) p[i] = s[i];
    return p;
}

void freeBook(Book& b)
{
    delete[] b.title;
    delete[] b.author;
}

void task5()
{
    Book* books = nullptr;
    int size = 0, cap = 0;

    while (true)
    {
        cout << "\n1) Добавить\n2) Показать\n0) Выход\n";
        int c = readIntRange("Выбор: ", 0, 2);
        if (c == 0) break;

        if (c == 1)
        {
            if (size == cap)
            {
                int ncap = cap == 0 ? 2 : cap * 2;
                Book* nb = new Book[ncap];
                for (int i = 0; i < size; i++) nb[i] = books[i];
                delete[] books;
                books = nb;
                cap = ncap;
            }

            char t[256], a[256];
            readLineSafe("Название: ", t, 256);
            readLineSafe("Автор: ", a, 256);
            int y = readIntRange("Год: ", 0, 2100);

            books[size].title = allocStr(t);
            books[size].author = allocStr(a);
            books[size].year = y;
            size++;
        }
        else if (c == 2)
        {
            for (int i = 0; i < size; i++)
                cout << books[i].title << " - " << books[i].author << " (" << books[i].year << ")\n";
        }
    }

    for (int i = 0; i < size; i++) freeBook(books[i]);
    delete[] books;
}

int main()
{
    setlocale(LC_ALL, "");
    srand(time(nullptr));

    while (true)
    {
        cout << "\n1. Задание 1\n2. Задание 2\n3. Задание 3\n4. Задание 4\n5. Задание 5\n0. Выход\n";
        int c = readIntRange("Выбор: ", 0, 5);
        if (c == 0) break;

        while (true)
        {
            if (c == 1) task1();
            else if (c == 2) task2();
            else if (c == 3) task3();
            else if (c == 4) task4();
            else if (c == 5) task5();

            if (postMenu() == 2) break;
        }
    }
    return 0;
}
