#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

const int N = 20;
string tourist_towns[5] = {"Москва", "Санкт-Петербург", "Екатеринбург", "Пермь", "Ярославль"};

struct time_s {
    int h, m, s;
};

struct route {
    string name;              // название маршрута
    string start;             // пункт отправления
    string end;               // пункт прибытия
    time_s departure_time;    // время отправления
    time_s arrival_time;      // время прибытия
    int carriages;            // количество вагонов
    string type;              // тип электропоезда
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
        if (name == tourist_towns[i]) {
            return true;
        }
    }
    return false;
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

route* bubbleSort(route shedule[], bool(*cmp)(route, route)) {
    for (int i = 0; i < N - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < N - i - 1; ++j) {
            if (cmp(shedule[j + 1], shedule[j])) {
                swap(shedule[j + 1], shedule[j]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
    return shedule;
}

void print_route(const route& r) {
    cout << r.name << " | "
         << r.start << " -> " << r.end << " | "
         << r.departure_time.h << ":" << r.departure_time.m << ":" << r.departure_time.s << " | "
         << r.arrival_time.h << ":" << r.arrival_time.m << ":" << r.arrival_time.s << " | "
         << r.carriages << " | " << r.type << '\n';
}

void print_shedule(route shedule[], int n = N) {
    for (int i = 0; i < n; ++i)
        print_route(shedule[i]);
}

void print_filtered_routes(route shedule[], int n, bool(*filter)(route)) {
    for (int i = 0; i < n; ++i)
        if (filter(shedule[i]))
            print_route(shedule[i]);
}

bool filter_tourist(route r) {
    return found_town(r.end);
}

bool filter_passanger(route r) {
    return r.type == "Пассажирский";
}

void read_carriages_from_text_file(route shedule[], int n, string filename) { // 1 задание из 10 практики
    ifstream fin(filename);
    if (!fin) {
        cout << "Не удалось открыть текстовый файл " << filename << '\n';
        return;
    }
    int route_number, new_carriages;
    while (fin >> route_number >> new_carriages)
        if (route_number >= 1 && route_number <= n)
            shedule[route_number - 1].carriages = new_carriages;
    fin.close();
}

void write_string_binary(ofstream& fout, string str) {
    int len = str.size();
    fout.write((char*)&len, sizeof(len));
    fout.write(str.c_str(), len);
}

void read_string_binary(ifstream& fin, string& str) {
    int len;
    fin.read((char*)&len, sizeof(len));
    char* buffer = new char[len + 1];
    fin.read(buffer, len);
    buffer[len] = '\0';
    str = buffer;
    delete[] buffer;
}

void write_route_binary(ofstream& fout, route& r) {
    write_string_binary(fout, r.name);
    write_string_binary(fout, r.start);
    write_string_binary(fout, r.end);
    fout.write((char*)&r.departure_time, sizeof(r.departure_time));
    fout.write((char*)&r.arrival_time, sizeof(r.arrival_time));
    fout.write((char*)&r.carriages, sizeof(r.carriages));
    write_string_binary(fout, r.type);
}

void read_route_binary(ifstream& fin, route& r) {
    read_string_binary(fin, r.name);
    read_string_binary(fin, r.start);
    read_string_binary(fin, r.end);
    fin.read((char*)&r.departure_time, sizeof(r.departure_time));
    fin.read((char*)&r.arrival_time, sizeof(r.arrival_time));
    fin.read((char*)&r.carriages, sizeof(r.carriages));
    read_string_binary(fin, r.type);
}

void save_shedule_to_binary(route shedule[], int n, const string& filename) {
    ofstream fout(filename, ios::binary);
    if (!fout) {
        cout << "Не удалось открыть бинарный файл " << filename << " для записи\n";
        return;
    }
    fout.write((char*)&n, sizeof(n));
    for (int i = 0; i < n; ++i)
        write_route_binary(fout, shedule[i]);
    fout.close();
}

route* load_shedule_from_binary(int& n, const string& filename) {
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cout << "Не удалось открыть бинарный файл " << filename << " для чтения\n";
        n = 0;
        return nullptr;
    }
    fin.read((char*)&n, sizeof(n));
    route* shedule = new route[n];
    for (int i = 0; i < n; ++i)
        read_route_binary(fin, shedule[i]);
    fin.close();
    return shedule;
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    route* shedule = init();
    cout << "-------------------- Исходное расписание --------------------\n";
    print_shedule(shedule);
    cout << "\n-------------------- Маршруты в туристические города --------------------\n";
    print_filtered_routes(shedule, N, filter_tourist);
    cout << "\n-------------------- Сортировка по пункту отправления --------------------\n";
    shedule = bubbleSort(shedule, cmp_start);
    print_shedule(shedule);
    cout << "\n-------------------- 3 самых коротких пассажирских поезда --------------------\n";
    shedule = bubbleSort(shedule, cmp_size_and_passanger);
    print_shedule(shedule, 3);
    cout << "\n-------------------- Чтение числового поля из текстового файла --------------------\n";
    read_carriages_from_text_file(shedule, N, "routes.txt");
    print_shedule(shedule);
    cout << "\n-------------------- Запись в бинарный файл --------------------\n";
    save_shedule_to_binary(shedule, N, "routes_out.txt");
    cout << "Данные записаны в файл routes.dat\n";
    cout << "\n-------------------- Чтение из бинарного файла --------------------\n";
    int n = 0;
    route* loaded = load_shedule_from_binary(n, "routes_out.txt");
    if (loaded != nullptr)
        print_shedule(loaded, n);
}
