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

double readDoubleRange(const char* prompt, double minV, double maxV)
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
        if (x < minV || x > maxV)
        {
            cout << "Выход за диапазон\n";
            continue;
        }
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
    cout << "2. Вернуться в главное меню\n";
    return readIntRange("Выберите действие: ", 1, 2);
}

/* ===== ЗАДАНИЕ 1 ===== */

void task1()
{
    const int N = 15;
    int a[N];

    for (int i = 0; i < N; i++)
        a[i] = 2 + rand() % 4; // 2..5

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

    double excellentPct = (double)excellent * 100.0 / N;

    cout << "\nОценки: ";
    for (int i = 0; i < N; i++) cout << a[i] << " ";
    cout << "\n";

    cout << "\nСтатистика:\n";
    cout << "Средний балл: " << avg << "\n";
    cout << "Неуспевающих (<3): " << bad << "\n";
    cout << "Отличников (5): " << excellent << " (" << excellentPct << "%)\n";
    cout << "Мода (самая частая): " << mode << "\n";

    cout << "Частоты:\n";
    cout << "2: " << freq[2] << "\n";
    cout << "3: " << freq[3] << "\n";
    cout << "4: " << freq[4] << "\n";
    cout << "5: " << freq[5] << "\n";
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
    else if (op == '*') *out = (*a) * (*b);
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
            double a = readDoubleRange("a: ", -1e9, 1e9);
            double b = readDoubleRange("b: ", -1e9, 1e9);

            char op;
            cout << "Операция (+ - * /): ";
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
            else
            {
                cout << "Ошибка (неверная операция или деление на 0)\n";
            }
        }
        else if (c == 2)
        {
            if (count == 0)
            {
                cout << "История пуста.\n";
            }
            else
            {
                int start = (count < H) ? 0 : head;
                for (int i = 0; i < count; i++)
                {
                    int idx = (start + i) % H;
                    cout << (i + 1) << ") " << hist[idx].a << " " << hist[idx].op << " "
                         << hist[idx].b << " = " << hist[idx].res << "\n";
                }
            }
        }
        else if (c == 3)
        {
            double x = readDoubleRange("x: ", -1e9, 1e9);
            double y = readDoubleRange("y: ", -1e9, 1e9);
            swapPtr(&x, &y);
            cout << "После swap: " << x << " " << y << endl;
        }
        else if (c == 4)
        {
            double x = readDoubleRange("1: ", -1e9, 1e9);
            double y = readDoubleRange("2: ", -1e9, 1e9);
            double z = readDoubleRange("3: ", -1e9, 1e9);
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

char toLow(char c)
{
    return (char)std::tolower((unsigned char)c);
}

void normalizeForPalindrome(const char* in, char* out, int size)
{
    int j = 0;
    for (int i = 0; in[i]; i++)
    {
        if (isLetter(in[i]))
        {
            if (j < size - 1) out[j++] = toLow(in[i]);
        }
    }
    out[j] = '\0';
}

bool isPalindrome(const char* s)
{
    char t[256];
    normalizeForPalindrome(s, t, 256);
    int n = myLen(t);
    int i = 0, j = n - 1;
    while (i < j)
    {
        if (t[i] != t[j]) return false;
        i++; j--;
    }
    return true;
}

void reverseStrPtr(char* s)
{
    int n = myLen(s);
    char* l = s;
    char* r = s + (n - 1);
    while (l < r)
    {
        char t = *l;
        *l = *r;
        *r = t;
        l++;
        r--;
    }
}

void normalizeForAnagram(const char* in, char* out, int size)
{
    int j = 0;
    for (int i = 0; in[i]; i++)
    {
        if (isLetter(in[i]))
        {
            if (j < size - 1) out[j++] = toLow(in[i]);
        }
    }
    out[j] = '\0';
}

bool areAnagrams(const char* a, const char* b)
{
    char x[256], y[256];
    normalizeForAnagram(a, x, 256);
    normalizeForAnagram(b, y, 256);

    int f1[256] = {0}, f2[256] = {0};
    for (int i = 0; x[i]; i++) f1[(unsigned char)x[i]]++;
    for (int i = 0; y[i]; i++) f2[(unsigned char)y[i]]++;

    for (int i = 0; i < 256; i++)
        if (f1[i] != f2[i]) return false;

    return true;
}

int countWords(const char* s)
{
    int cnt = 0;
    bool inWord = false;
    for (int i = 0; s[i]; i++)
    {
        if (isLetter(s[i]))
        {
            if (!inWord) { cnt++; inWord = true; }
        }
        else
        {
            inWord = false;
        }
    }
    return cnt;
}

void longestWord(const char* s, char* out, int outSize)
{
    int bestLen = 0;
    int bestStart = -1;

    int curLen = 0;
    int curStart = -1;

    for (int i = 0; ; i++)
    {
        char ch = s[i];
        bool letter = (ch != '\0' && isLetter(ch));

        if (letter)
        {
            if (curLen == 0) curStart = i;
            curLen++;
        }
        else
        {
            if (curLen > bestLen)
            {
                bestLen = curLen;
                bestStart = curStart;
            }
            curLen = 0;
        }

        if (ch == '\0') break;
    }

    if (bestLen == 0)
    {
        out[0] = '\0';
        return;
    }

    int k = 0;
    for (int i = 0; i < bestLen && k < outSize - 1; i++)
        out[k++] = s[bestStart + i];
    out[k] = '\0';
}

void cleanNonLetters(const char* in, char* out, int outSize)
{
    int j = 0;
    for (int i = 0; in[i]; i++)
    {
        if (isLetter(in[i]) || in[i] == ' ')
        {
            if (j < outSize - 1) out[j++] = in[i];
        }
    }
    out[j] = '\0';
}

void task3()
{
    char s[256];
    readLineSafe("Строка: ", s, 256);

    cout << (isPalindrome(s) ? "Палиндром\n" : "Не палиндром\n");

    char r[256];
    for (int i = 0; i <= myLen(s); i++) r[i] = s[i];
    reverseStrPtr(r);
    cout << "Реверс: " << r << endl;

    int w = countWords(s);
    cout << "Количество слов: " << w << endl;

    char lw[256];
    longestWord(s, lw, 256);
    if (lw[0]) cout << "Самое длинное слово: " << lw << endl;
    else cout << "Самое длинное слово: (нет)\n";

    char cleaned[256];
    cleanNonLetters(s, cleaned, 256);
    cout << "Очищенная строка: " << cleaned << endl;

    char a[256], b[256];
    readLineSafe("Первая строка (анаграммы): ", a, 256);
    readLineSafe("Вторая строка (анаграммы): ", b, 256);
    cout << (areAnagrams(a, b) ? "Анаграммы\n" : "Не анаграммы\n");
}

/* ===== ЗАДАНИЕ 4 ===== */

int** allocMatrix(int r, int c)
{
    int** m = new (std::nothrow) int*[r];
    if (!m) return nullptr;

    for (int i = 0; i < r; i++) m[i] = nullptr;

    for (int i = 0; i < r; i++)
    {
        m[i] = new (std::nothrow) int[c];
        if (!m[i])
        {
            for (int k = 0; k < r; k++) delete[] m[k];
            delete[] m;
            return nullptr;
        }
    }
    return m;
}

void freeMatrix(int** m, int r)
{
    if (!m) return;
    for (int i = 0; i < r; i++) delete[] m[i];
    delete[] m;
}

void task4()
{
    int M = readIntRange("M (строки): ", 1, 20);
    int N = readIntRange("N (столбцы): ", 1, 20);

    int** a = allocMatrix(M, N);
    if (!a)
    {
        cout << "Ошибка: не удалось выделить память под матрицу\n";
        return;
    }

    int** t = allocMatrix(N, M);
    if (!t)
    {
        cout << "Ошибка: не удалось выделить память под транспонированную матрицу\n";
        freeMatrix(a, M);
        return;
    }

    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = rand() % 10;

    cout << "\nИсходная матрица:\n";
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++) cout << a[i][j] << " ";
        cout << endl;
    }

    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            t[j][i] = a[i][j];

    cout << "\nТранспонированная матрица:\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++) cout << t[i][j] << " ";
        cout << endl;
    }

    cout << "\nСуммы строк исходной матрицы:\n";
    for (int i = 0; i < M; i++)
    {
        int s = 0;
        for (int j = 0; j < N; j++) s += a[i][j];
        cout << "Строка " << i << ": " << s << "\n";
    }

    cout << "\nСуммы столбцов исходной матрицы:\n";
    for (int j = 0; j < N; j++)
    {
        int s = 0;
        for (int i = 0; i < M; i++) s += a[i][j];
        cout << "Столбец " << j << ": " << s << "\n";
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

bool strEq(const char* a, const char* b)
{
    int i = 0;
    while (a[i] && b[i])
    {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}

bool strContains(const char* text, const char* pat)
{
    if (!pat[0]) return true;
    int n = myLen(text);
    int m = myLen(pat);
    if (m > n) return false;

    for (int i = 0; i <= n - m; i++)
    {
        bool ok = true;
        for (int j = 0; j < m; j++)
        {
            if (text[i + j] != pat[j]) { ok = false; break; }
        }
        if (ok) return true;
    }
    return false;
}

char* allocStr(const char* s)
{
    int n = myLen(s);
    char* p = new (std::nothrow) char[n + 1];
    if (!p) return nullptr;
    for (int i = 0; i <= n; i++) p[i] = s[i];
    return p;
}

void freeBook(Book& b)
{
    delete[] b.title;
    delete[] b.author;
    b.title = nullptr;
    b.author = nullptr;
}

bool ensureCapacity(Book*& books, int& cap, int needSize)
{
    if (needSize <= cap) return true;

    int newCap = (cap == 0) ? 2 : cap * 2;
    while (newCap < needSize) newCap *= 2;

    Book* nb = new (std::nothrow) Book[newCap];
    if (!nb) return false;

    for (int i = 0; i < cap; i++)
    {
        nb[i].title = nullptr;
        nb[i].author = nullptr;
        nb[i].year = 0;
    }

    for (int i = 0; i < cap; i++)
    {
        nb[i] = books[i];
    }

    delete[] books;
    books = nb;
    cap = newCap;
    return true;
}

void printBook(const Book& b, int idx)
{
    cout << idx << ") " << b.title << " - " << b.author << " (" << b.year << ")\n";
}

void sortByYear(Book* books, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (books[j].year > books[j + 1].year)
            {
                Book t = books[j];
                books[j] = books[j + 1];
                books[j + 1] = t;
            }
        }
    }
}

void removeAt(Book* books, int& size, int idx)
{
    freeBook(books[idx]);
    for (int i = idx; i < size - 1; i++)
        books[i] = books[i + 1];
    size--;
}

void task5()
{
    Book* books = nullptr;
    int size = 0;
    int cap = 0;

    while (true)
    {
        cout << "\n--- БИБЛИОТЕКА ---\n";
        cout << "1) Добавить книгу\n";
        cout << "2) Поиск по названию\n";
        cout << "3) Поиск по автору\n";
        cout << "4) Показать книги автора (точно)\n";
        cout << "5) Удалить книгу\n";
        cout << "6) Сортировка по году\n";
        cout << "7) Показать все книги\n";
        cout << "0) Выход\n";

        int c = readIntRange("Выбор: ", 0, 7);
        if (c == 0) break;

        if (c == 1)
        {
            if (!ensureCapacity(books, cap, size + 1))
            {
                cout << "Ошибка: не удалось выделить память.\n";
                continue;
            }

            char t[256], a[256];
            readLineSafe("Название: ", t, 256);
            readLineSafe("Автор: ", a, 256);
            int y = readIntRange("Год: ", 0, 2100);

            char* tt = allocStr(t);
            char* aa = allocStr(a);

            if (!tt || !aa)
            {
                delete[] tt;
                delete[] aa;
                cout << "Ошибка: не удалось выделить память под строки.\n";
                continue;
            }

            books[size].title = tt;
            books[size].author = aa;
            books[size].year = y;
            size++;

            cout << "Книга добавлена.\n";
        }
        else if (c == 2)
        {
            if (size == 0) { cout << "Список пуст.\n"; continue; }

            char q[256];
            readLineSafe("Введите часть названия: ", q, 256);

            bool found = false;
            for (int i = 0; i < size; i++)
            {
                if (strContains(books[i].title, q))
                {
                    printBook(books[i], i);
                    found = true;
                }
            }
            if (!found) cout << "Не найдено.\n";
        }
        else if (c == 3)
        {
            if (size == 0) { cout << "Список пуст.\n"; continue; }

            char q[256];
            readLineSafe("Введите часть автора: ", q, 256);

            bool found = false;
            for (int i = 0; i < size; i++)
            {
                if (strContains(books[i].author, q))
                {
                    printBook(books[i], i);
                    found = true;
                }
            }
            if (!found) cout << "Не найдено.\n";
        }
        else if (c == 4)
        {
            if (size == 0) { cout << "Список пуст.\n"; continue; }

            char q[256];
            readLineSafe("Автор (точно как в книге): ", q, 256);

            bool found = false;
            for (int i = 0; i < size; i++)
            {
                if (strEq(books[i].author, q))
                {
                    printBook(books[i], i);
                    found = true;
                }
            }
            if (!found) cout << "Нет книг этого автора.\n";
        }
        else if (c == 5)
        {
            if (size == 0) { cout << "Список пуст.\n"; continue; }

            cout << "Книги:\n";
            for (int i = 0; i < size; i++) printBook(books[i], i);

            int idx = readIntRange("Индекс для удаления: ", 0, size - 1);
            removeAt(books, size, idx);
            cout << "Удалено.\n";
        }
        else if (c == 6)
        {
            if (size == 0) { cout << "Список пуст.\n"; continue; }
            sortByYear(books, size);
            cout << "Отсортировано по году.\n";
        }
        else if (c == 7)
        {
            if (size == 0) { cout << "Список пуст.\n"; continue; }
            for (int i = 0; i < size; i++) printBook(books[i], i);
        }
    }

    for (int i = 0; i < size; i++) freeBook(books[i]);
    delete[] books;
}

/* ===== MAIN ===== */

int main()
{
    setlocale(LC_ALL, "");
    srand((unsigned)time(nullptr));

    while (true)
    {
        cout << "\n=== ЛАБОРАТОРНАЯ РАБОТА 3 ===\n";
        cout << "Задача 1. Анализатор успеваемости группы\n";
        cout << "Задача 2. Умный калькулятор с историей операций\n";
        cout << "Задача 3. Детектор палиндромов и анаграмм\n";
        cout << "Задача 4. Транспонирование матрицы произвольного размера\n";
        cout << "Задача 5. Система управления библиотекой книг\n";
        cout << "0. Выход\n";

        int c = readIntRange("Выберите задачу: ", 0, 5);
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
