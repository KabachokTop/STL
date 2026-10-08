#include <iostream>
#include <vector>
#include <clocale>

using namespace std;

struct FindMin {
    int operator()(const vector<int>& v) const {
        if (v.empty()) {
            cout << "Вектор порожній!" << endl;
            return 0;
        }
        int minVal = v[0];
        for (size_t i = 1; i < v.size(); ++i) {
            if (v[i] < minVal) {
                minVal = v[i];
            }
        }
        return minVal;
    }
};

struct FindMax {
    int operator()(const vector<int>& v) const {
        if (v.empty()) {
            cout << "Вектор порожній!" << endl;
            return 0;
        }
        int maxVal = v[0];
        for (size_t i = 1; i < v.size(); ++i) {
            if (v[i] > maxVal) {
                maxVal = v[i];
            }
        }
        return maxVal;
    }
};

struct Descending {
    bool operator()(int a, int b) const {
        return a > b;
    }
};

struct Ascending {
    bool operator()(int a, int b) const {
        return a < b;
    }
};

struct Increase {
    int value;

    explicit Increase(int val) : value(val) {}

    void operator()(int& x) const {
        x += value;
    }
};

struct Decrease {
    int value;

    explicit Decrease(int val) : value(val) {}

    void operator()(int& x) const {
        x -= value;
    }
};

struct EqualTo {
    int value;

    explicit EqualTo(int val) : value(val) {}

    bool operator()(int x) const {
        return x == value;
    }
};

void printVector(const vector<int>& v, const string& msg) {
    cout << msg;
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << endl;
}

template <typename Comparator>
void sortVector(vector<int>& v, Comparator comp) {
    for (size_t i = 0; i < v.size(); ++i) {
        for (size_t j = 0; j < v.size() - 1 - i; ++j) {
            if (comp(v[j + 1], v[j])) {
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

template <typename Functor>
void applyToAll(vector<int>& v, Functor f) {
    for (size_t i = 0; i < v.size(); ++i) {
        f(v[i]);
    }
}

template <typename Predicate>
void removeIf(vector<int>& v, Predicate pred) {
    size_t writeIndex = 0;
    for (size_t i = 0; i < v.size(); ++i) {
        if (!pred(v[i])) {
            v[writeIndex] = v[i];
            ++writeIndex;
        }
    }
    v.resize(writeIndex);
}

int main() {
	setlocale(LC_ALL, "Ukrainian");
    vector<int> data = { 5, 2, 9, 1, 7, 2, 8, 3, 2, 6 };

    printVector(data, "Початковий вектор: ");

    FindMin findMin;
    cout << "Мінімальне значення: " << findMin(data) << endl;

    FindMax findMax;
    cout << "Максимальне значення: " << findMax(data) << endl;

    vector<int> desc = data;
    sortVector(desc, Descending());
    printVector(desc, "Сортування за спаданням: ");

    vector<int> asc = data;
    sortVector(asc, Ascending());
    printVector(asc, "Сортування за зростанням: ");

    vector<int> increased = data;
    applyToAll(increased, Increase(10));
    printVector(increased, "Збільшення на 10: ");

    vector<int> decreased = data;
    applyToAll(decreased, Decrease(3));
    printVector(decreased, "Зменшення на 3: ");

    vector<int> filtered = data;
    removeIf(filtered, EqualTo(2));
    printVector(filtered, "Після видалення всіх 2: ");

    return 0;
}