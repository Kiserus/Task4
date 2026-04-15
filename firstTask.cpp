#include <iostream>
#include <clocale>
#include <windows.h>

using namespace std;

int N = 20;
string tourist_towns[5] = {"Москва", "Санкт-Петербург", "Екатеринбург", "Пермь", "Ярославль"};

struct time {
    int h, m, s;
};

struct route {
    string name; // название маршрута
    string start; // пункт отправления
    string end; // пункт прибытия
    struct time departure_time; // время отправления
    struct time arrival_time; // время прибытия
    int carriages; // количество вагонов
    string type; // тип электропоезда
};

route* init() {
    route* shedule = new route[N];
    shedule[0] = {"Маршрут 1", "Москва", "Тверь", {6, 30, 0}, {8, 15, 0}, 8, "Ласточка"};
    shedule[1] = {"Маршрут 2", "Санкт-Петербург", "Выборг", {7, 10, 0}, {8, 45, 0}, 6, "Экспресс"};
    shedule[2] = {"Маршрут 3", "Казань", "Нижний Новгород", {9, 0, 0}, {13, 20, 0}, 10, "Скорый"};
    shedule[3] = {"Маршрут 4", "Екатеринбург", "Тюмень", {5, 50, 0}, {9, 10, 0}, 12, "Пассажирский"};
    shedule[4] = {"Маршрут 5", "Новосибирск", "Омск", {14, 30, 0}, {20, 0, 0}, 15, "Скорый"};
    shedule[5] = {"Маршрут 6", "Самара", "Саратов", {8, 45, 0}, {12, 15, 0}, 7, "Региональный"};
    shedule[6] = {"Маршрут 7", "Ростов-на-Дону", "Краснодар", {11, 20, 0}, {14, 10, 0}, 9, "Ласточка"};
    shedule[7] = {"Маршрут 8", "Воронеж", "Липецк", {6, 0, 0}, {7, 40, 0}, 5, "Пригородный"};
    shedule[8] = {"Маршрут 9", "Уфа", "Челябинск", {10, 10, 0}, {15, 50, 0}, 11, "Скорый"};
    shedule[9] = {"Маршрут 10", "Пермь", "Екатеринбург", {13, 25, 0}, {17, 10, 0}, 8, "Экспресс"};
    shedule[10] = {"Маршрут 11", "Иркутск", "Улан-Удэ", {7, 15, 0}, {11, 30, 0}, 10, "Пассажирский"};
    shedule[11] = {"Маршрут 12", "Хабаровск", "Владивосток", {5, 40, 0}, {14, 20, 0}, 16, "Скорый"};
    shedule[12] = {"Маршрут 13", "Калуга", "Москва", {6, 50, 0}, {8, 30, 0}, 6, "Ласточка"};
    shedule[13] = {"Маршрут 14", "Тула", "Орёл", {9, 35, 0}, {11, 50, 0}, 7, "Региональный"};
    shedule[14] = {"Маршрут 15", "Ярославль", "Кострома", {12, 10, 0}, {13, 55, 0}, 5, "Пригородный"};
    shedule[15] = {"Маршрут 16", "Белгород", "Курск", {15, 45, 0}, {18, 20, 0}, 6, "Пассажирский"};
    shedule[16] = {"Маршрут 17", "Сочи", "Адлер", {8, 5, 0}, {8, 50, 0}, 4, "Ласточка"};
    shedule[17] = {"Маршрут 18", "Мурманск", "Апатиты", {10, 30, 0}, {13, 10, 0}, 6, "Региональный"};
    shedule[18] = {"Маршрут 19", "Архангельск", "Северодвинск", {7, 55, 0}, {9, 0, 0}, 5, "Пригородный"};
    shedule[19] = {"Маршрут 20", "Кемерово", "Новокузнецк", {16, 20, 0}, {18, 45, 0}, 8, "Экспресс"};
    return shedule;
}

bool found_town(string name) {
    for (int i = 0; i < size(tourist_towns); ++i) {
        if (name == tourist_towns[i])
            return true;
    }
    return false;
}

route* bubbleSort(route* shedule, bool(*cmp) (route, route)) {
    route* local_copy = new route[N];
    copy(shedule, shedule + N, local_copy);
    for (int i = 0; i < N - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < N - i - 1; ++j) {
            if (cmp(local_copy[j + 1], local_copy[j])) {
                swap(local_copy[j + 1], local_copy[j]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    return local_copy;
}

bool cmp_start(route a, route b) {
    return a.start < b.start;
}

bool cmp_size_and_passanger(route a, route b) {
    if (a.type == "Пассажирский" && b.type == "Пассажирский")
        return a.carriages < b.carriages;
    if (a.type == "Пассажирский")
        return true;
    return false;
}

void print_route(route r) {
    cout << r.name << ' ' << r.start << ' ' << r.end
         << " {" << r.departure_time.h << ':' << r.departure_time.m << ':' << r.departure_time.s << "} "
         << r.carriages << ' ' << r.type << '\n';
}

void print_shedule(route shedule[], int n = N) {
    for (int i = 0; i < n; ++i) {
        print_route(shedule[i]);
    }
}

void print_filtered_routes(route shedule[], bool(*filter)(route), int n = N) {
    for (int i = 0; i < n; ++i) {
        if (filter(shedule[i])) {
            print_route(shedule[i]);
        }
    }
}

// Фильтр: маршрут идёт в туристический город
bool filter_tourist(route r) {
    return found_town(r.end);
}

// Фильтр: только пассажирские поезда
bool filter_passanger(route r) {
    return r.type == "Пассажирский";
}

void change_route(route shedule[]) {
    cout << "Введите номер маршрута, который нужно поменять: ";
    int ind;
    cin >> ind;
    cout << "Введите новое имя маршрута: ";
    string name;
    cin.ignore();
    getline(cin, name);
    cout << "Введите пункт отправления поезда: ";
    string start;
    cin >> start;
    cout << "Введите пункт прибытия поезда: ";
    string end;
    cin >> end;
    cout << "Введите время отправления поезда в формате <hh:mm:ss>: ";
    struct time departure_time;
    char bfr;
    cin >> departure_time.h >> bfr >> departure_time.m >> bfr >> departure_time.s;
    cout << "Введите время прибытия поезда в формате <hh:mm:ss>: ";
    struct time arrival_time;
    cin >> arrival_time.h >> bfr >> arrival_time.m >> bfr >> arrival_time.s;
    cout << "Введите кол-во вагонов поезда: ";
    int carriages;
    cin >> carriages;
    cout << "Введите тип поезда: ";
    string type;
    cin >> type;
    for (int i = 0; i < N; ++i) {
        if (shedule[i].name.rfind(to_string(ind)) != string::npos) {
            shedule[i] = route(name, start, end, departure_time, arrival_time, carriages, type);
            return;
        }
    }
    cout << "Такого маршрута нет\n";
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    route *shedule = init();
    cout << "-------------------------------------Распиание-------------------------------------\n";
    print_shedule(shedule);
    route tourist_shedule[N];
    for (int i = 0, cur_ind = 0; i < N; ++i) {
        if (found_town(shedule[i].end))
            tourist_shedule[cur_ind++] = shedule[i];
    }
    cout << "-------------------------------------Маршруты в туристические города-------------------------------------\n";
    print_filtered_routes(shedule, filter_tourist);
    cout << "-------------------------------------Сортировка по пункту отправления-------------------------------------\n";
    route *sorted_shedule = bubbleSort(shedule, cmp_start);
    print_shedule(sorted_shedule);
    cout << "-------------------------------------3 самых коротких пассажирских поездов-------------------------------------\n";
    sorted_shedule = bubbleSort(shedule, cmp_size_and_passanger);
    print_shedule(sorted_shedule, 3);
    cout << "-------------------------------------Изменение маршрута-------------------------------------\n";
    change_route(shedule);
    print_shedule(shedule);
    // 2
    // Маршрут 21
    // Ош
    // Бишкек
    // 12:30:12
    // 17:02:58
    // 7
    // Пассажирский
}
