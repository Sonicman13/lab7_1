// lab7_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "conio.h"
#include "locale.h"
#include "math.h"
#include "stdlib.h"
#include <string>
#include "stdio.h"
#include "Windows.h"
#include <iostream>
using namespace std;
#define N 100

class Item {
protected:
    string code;
    string name;
    double price;
    int amount;
public:
    void read();
    Item(string code1, string name1, double price1, int amount1);
    Item();
    virtual void display();
    void setPrice(double price1);
    void setAmount(int amount1);
    string getCode();
    int getAmount();
    bool exists();
    string getName();
    double getPrice();
};

void Item::read() {
    string s;
    s = "-";
    printf("\nВведите название товара\n");
    getline(cin, name);
    printf("Введите код товара\n");
    getline(cin, code);
    do {
        printf("Введите цену\n");
        try {
            getline(cin, s);
            price = stod(s);
        }
        catch (...) {
            price = -1;
        }
        
    } while (price < 0);
    do {
        printf("Введите колличество товара\n");
        try {
            getline(cin, s);
            amount = stoi(s);
        }
        catch (...) {
            amount = -1;
        }
    } while (amount < 0);
}

Item::Item(string code, string name, double price, int amount) {
    this->name = name;
    this->code = code;
    this->price = price;
    this->amount = amount;
}

Item::Item() {
    name = "-";
    code = "-";
    price = 0;
    amount = 0;
}

void Item::display() {
    cout << ("Код: " + code) << endl;
    cout << "Название: " + name << endl;
    printf("Цена: %lf\n", price);
    cout << "Колличество: " + to_string(amount) << endl;
}

void Item::setPrice(double price) {
    this->price = price;
}

void Item::setAmount(int amount) {
    this->amount = amount;
}

string Item::getCode() {
    return code;
}

int Item::getAmount() {
    return amount;
}

string Item::getName() {
    return name;
}

double Item::getPrice() {
    return price;
}

bool Item::exists() {
    if (amount > 0) {
        display();
        return true;
    }
    else {
        return false;
    }
}

class Game : public Item {
private:
    int release[3];
    string platforms[10];
    string publisher;
public:
    Game();
    Game(string code, string name, double price, int amount, int release[], string platforms[], string publisher);
    void read(int d);
    void display();
    void add();
    void operator = (Item b);
};

Game::Game()
{
    release[0] = release[1] = release[2] = -1;
    platforms[0] = "-";
    publisher = "-";
}

Game::Game(string code, string name, double price, int amount, int release[], string platforms[], string publisher) :Item(code, name, price, amount)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        this->release[i] = release[i];
    }
    for (i = 0; i < sizeof(platforms); i++)
    {
        this->platforms[i] = platforms[i];
    }
    this->publisher = publisher;
}

void Game::read(int d)
{
    string s;
    s = "-";
    this->Item::read();
    printf("Введите дату выхода(день, месяц(число), затем год(4 цифры), разделяя их нажатием Enter)\n");
    getline(cin, s);
    release[0] = stoi(s);
    getline(cin, s);
    release[1] = stoi(s);
    getline(cin, s);
    release[2] = stoi(s);
    printf("Введите платформы на которых доступна игра( чтобы закончить вводить платформы введите пустую строку)\n");
    d = -1;
    do
    {
        d++;
        getline(cin, platforms[d]);
    } while (platforms[d] != "");
    printf("Введите издателя\n");
    getline(cin, publisher);
}

void Game::display()
{
    int i;
    this->Item::display();
    cout << "Дата релиза: " + to_string(release[0]);
    cout << "." + to_string(release[1]);
    cout << "." + to_string(release[2]) << endl;
    cout << "Платформы: ";
    for (i = 0; i < 10; i++) {
        cout << platforms[i] + ",";
    }
    cout << "\n";
    cout << "Издатель: " + publisher << endl;
}

void Game::add(){
    int i;
    i = 0;
    while (platforms[i] != "")
    {
        i++;
    }
    printf("Введите платформу на которой доступна игра\n");
    getline(cin, platforms[i]);
}

void Game::operator = (Item b) {
    this->name = b.getName();
    this->code = b.getCode();
    this->price = b.getPrice();
    this->amount = b.getAmount();
    this->release[0] = this->release[1] = this->release[2] = 0;
    this->platforms[0] = "-";
    this->publisher = "-";
}

class Platform : public Item {
private:
    string components[10];
    string plusPlatforms[10];
    string publisher;
public:
    void read(int d);
    Platform(string code, string name, double price, int amount, string components[], string platforms[], string publisher);
    Platform();
    void display();
    void add();
};

Platform::Platform() 
{
    components[0] = "-";
    plusPlatforms[0] = "-";
    publisher = "-";
}

Platform::Platform(string code, string name, double price, int amount, string components[], string platforms[], string publisher) :Item(code, name, price, amount)
{
    int i;
    for (i = 0; i < sizeof(components); i++)
    {
        this->components[i] = components[i];
    }
    for (i = 0; i < sizeof(platforms); i++)
    {
        this->plusPlatforms[i] = platforms[i];
    }
    this->publisher = publisher;
}
void Platform::read(int d)
{
    this->Item::read();
    printf("Введите комплектацию( чтобы закончить вводить комплектацию введите пустую строку)\n");
    d = -1;
    do
    {
        d++;
        getline(cin, components[d]);
    } while (components[d] != "");
    printf("Введите платформы доступные по обратной совместимости( чтобы закончить вводить платформы введите пустую строку)\n");
    d = -1;
    do
    {
        d++;
        getline(cin, plusPlatforms[d]);
    } while (plusPlatforms[d] != "");
    printf("Введите издателя\n");
    getline(cin, publisher);
}

void Platform::display() {
    int i;
    this->Item::display();
    cout << "Комплектация: ";
    for (i = 0; i < 10; i++) {
        cout << components[i] + ",";
    }
    cout << "\n";
    cout << "Платформы доступные по обратной совместимости: ";
    for (i = 0; i < 10; i++) {
        cout << plusPlatforms[i] + ",";
    }
    cout << "\n";
    cout << "Издатель: " + publisher << endl;
}
    
void Platform::add()
{
    int i;
    i = 0;
    while (components[i] != "")
    {
        i++;
    }
    printf("Введите комплектующие\n");
    getline(cin, components[i]);
}


template <class T> class Array
{
private:
    T it[10];
    int size;
public:
    Array()
    {
        size = 0;
    }
    Array(T o[], int size)
    {
        int i;
        this->size = 0;
        for (i = 0; i < size; i++)
        {
            this->it[this->size] = o[i];
            this->size++;
        }
    }
    void display()
    {
        int i;
        for (i = 0; i < size; i++)
        {
            printf("Товар %d\n", i);
            it[i].display();
        }
    }
    void Add(T o)
    {
        it[size] = o;
        size++;
    }
    T* find(string code)
    {
        int i;
        i = 0;
        while (i < size)
        {
            if (it[i].getCode() == code)
            {
                return &it[i];
            }
            i++;
        }
        return nullptr;
    }
    Array<T> sum(Array<T> it2)
    {
        Array<T> it3;
        int i;
        for (i = 0; i < this->size; i++)
        {
            it3.it[it3.size] = this->it[i];
            it3.size++;
        }
        for (i = 0; i < it2.size; i++)
        {
            it3.it[it3.size] = it2.it[i];
            it3.size++;
        }
        return it3;
    }
};

class Store {
private:
    string name;
    string adress;
    Array<Item> item;
    Array<Game> game;
    Array<Platform> platform;
public:
    void read();
    Store(string name, string adress, int numberOfItems, Item item[], int numberOfGames, Game game[], int numberOfPlatforms, Platform platform[]);
    Store();
    void display();
    Store operator ++(int);
    void priceChange(string item1, double price);
    void amountChange(string item1, int amountDifference);
    void displayName();
    friend int storecmp(string name1, Store store);
    string getName() {
        return name;
    }
    Store operator + (Store store);
    void add(string code);
};

void Store::read() {
    char f;
    int i, number;
    Item item1[10];
    Game game1[10];
    Platform platform1[10];
    printf("\nВведите название магазина\n");
    getline(cin, name);
    printf("Введите адрес магазина\n");
    getline(cin, adress);
    number = 0;
    printf("Добавить товар?(1 - да, все остальные символы - нет)\n");
    f = _getche();
    while (f == '1') {
        item1[number].read();
        number++;
        printf("Добавить еще один товар?(1 - да, все остальные символы -нет)\n");
        f = _getche();
        getchar();
    }
    item = Array<Item>(item1, number);
    number = 0;
    printf("Добавить игру?(1 - да, все остальные символы - нет)\n");
    f = _getche();
    while (f == '1') {
        game1[number].read(1);
        number++;
        printf("Добавить еще одну игру?(1 - да, все остальные символы -нет)\n");
        f = _getche();
        getchar();
    }
    game = Array<Game>(game1, number);
    number = 0;
    printf("Добавить консоль?(1 - да, все остальные символы - нет)\n");
    f = _getche();
    while (f == '1') {
        platform1[number].read(1);
        number++;
        printf("Добавить еще одну консоль?(1 - да, все остальные символы -нет)\n");
        f = _getche();
        getchar();
    }
    platform = Array<Platform>(platform1, number);
}

Store::Store(string name, string adress, int numberOfItems, Item item[], int numberOfGames, Game game[], int numberOfPlatforms, Platform platform[]) {
    this->name = name;
    this->adress = adress;
    this->item = Array<Item>(item, numberOfItems);
    this->game = Array<Game>(game, numberOfGames);
    this->platform = Array<Platform>(platform, numberOfPlatforms);
}

Store::Store() {
    this->name = "-";
    this->adress = "-";
}

void Store::display() {
    int i;
    cout << "\nНазвание магазина: " + name << endl;
    cout << "Адрес: " + adress << endl;
    item.display();
    game.display();
    platform.display();
}

Store Store::operator ++ (int){
    Store newStore;
    int n;
    string f;
    newStore.name = this->name;
    newStore.adress = this->adress;
    newStore.item = this->item;
    newStore.game = this->game;
    newStore.platform = this->platform;
    printf("Добавить товар (1), игру (2), консоль (3)?\n");
    getline(cin, f);
    if (f == "1") {
        Item a;
        a.read();
        newStore.item.Add(a);
    }
    if (f == "2") {
        Game a;
        a.read(1);
        newStore.game.Add(a);
    }
    if (f == "3") {
        Platform a;
        a.read(1);
        newStore.platform.Add(a);
    }
    getchar();
    return newStore;
}

void Store::priceChange(string code, double price) {
    Item* item1;
    item1 = nullptr;
    Game* game1;
    game1 = nullptr;
    Platform* platform1;
    platform1 = nullptr;
    item1 = item.find(code);
    if (item1 != nullptr)
    {
        item1->setPrice(price);
    }
    if (item1 == nullptr)
    {
        game1 = game.find(code);
        if (game1 != nullptr)
        {
            game1->setPrice(price);
        }
    }
    if (game1 == nullptr && item1 == nullptr)
    {
        platform1 = platform.find(code);
        if (platform1 != nullptr)
        {
            platform1->setPrice(price);
        }
    }
}

void Store::amountChange(string code, int amountDifference) {
    Item* item1;
    item1 = nullptr;
    Game* game1;
    game1 = nullptr;
    Platform* platform1;
    platform1 = nullptr;
    item1 = item.find(code);
    if (item1 != nullptr)
    {
        item1->setAmount(item1->getAmount() + amountDifference);
    }
    if (item1 == nullptr)
    {
        game1 = game.find(code);
        if (game1 != nullptr)
        {
            game1->setAmount(game1->getAmount() + amountDifference);
        }
    }
    if (game1 == nullptr && item1 == nullptr)
    {
        platform1 = platform.find(code);
        if (platform1 != nullptr)
        {
            platform1->setAmount(platform1->getAmount() + amountDifference);
        }
    }
}

void Store::displayName() {
    printf("\nМагазин:");
    cout << name << endl;
}

int storecmp(string name1, Store store) {
    return name1 == store.getName();
}

Store Store::operator + (Store store) {
    int n, i;
    Store newStore;
    newStore.name = this->name;
    newStore.adress = this->adress;
    newStore.item = this->item.sum(store.item);
    newStore.game = this->game.sum(store.game);
    newStore.platform = this->platform.sum(store.platform);
    return newStore;
}

void Store::add(string code)
{
    Game* game1;
    game1 = nullptr;
    Platform* platform1;
    platform1 = nullptr;
    game1 = game.find(code);
    if (game1 != nullptr)
    {
        game1->add();
    }
    if (game1 == nullptr)
    {
        platform1 = platform.find(code);
        if (platform1 != nullptr)
        {
            platform1->add();
        }
    }
}


int main()
{
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    class Store store1[10], * store2;
    class Item item1[5];
    class Game game1[5];
    class Platform platform1[5];
    int amountDifference, numberOfItems, itemAmount, i, max, n, *g, numberOfGames, numberOfPlatforms, release[3], d;
    double price, itemPrice;
    bool z;
    string s, s1[N], code, name, adress, itemCode, itemName, f, platforms[10], publisher, components[10], plusPlatforms[10], code1, code2;
    printf("Работать с переменной, указателем или указателем на массив?(1 - переменная, 2 - указатель)\n");
    getline(cin, f);

    //Переменная
    g = (int*)malloc(sizeof(int));
    if (f == "1") {
        s = "-";
        s1[0] = "-";
        printf("Использовать или read чтобы ввести данные(1 - read, все остальные символы - init)\n");
        getline(cin, f);
        if (f == "1") {
            store1[0].read();
        }
        else {
            printf("\nВведите название магазина\n");
            getline(cin, name);
            printf("Введите адрес магазина\n");
            getline(cin, adress);
            numberOfItems = 0;;
            printf("Добавить товар?(1-да,0-нет)\n");
            getline(cin, f);
            while (f == "1") {
                printf("\nВведите название товара\n");
                getline(cin, itemName);
                printf("Введите код товара\n");
                getline(cin, itemCode);
                do {
                    printf("Введите цену\n");
                    try {
                        getline(cin, s);
                        itemPrice = stod(s);
                    }
                    catch (...) {
                        itemPrice = -1;
                    }
                } while (itemPrice < 0);
                do {
                    printf("Введите колличество товара\n");
                    try {
                        getline(cin, s);
                        itemAmount = stoi(s);
                    }
                    catch (...) {
                        itemAmount = -1;
                    }
                } while (itemAmount < 0);
                item1[numberOfItems] = Item(itemCode, itemName, itemPrice, itemAmount);
                numberOfItems++;
                printf("Добавить еще один товар?(1 - да, все остальные символы - нет)\n");
                getline(cin, f);
                getchar();
            }
            numberOfGames = 0;;
            printf("Добавить игру?(1-да,0-нет)\n");
            getline(cin, f);
            while (f == "1") {
                printf("\nВведите название товара\n");
                getline(cin, itemName);
                printf("Введите код товара\n");
                getline(cin, itemCode);
                do {
                    printf("Введите цену\n");
                    try {
                        getline(cin, s);
                        itemPrice = stod(s);
                    }
                    catch (...) {
                        itemPrice = -1;
                    }
                } while (itemPrice < 0);
                do {
                    printf("Введите колличество товара\n");
                    try {
                        getline(cin, s);
                        itemAmount = stoi(s);
                    }
                    catch (...) {
                        itemAmount = -1;
                    }
                } while (itemAmount < 0);
                printf("Введите дату выхода(день, месяц(число), затем год(4 цифры), разделяя их нажатием Enter)\n");
                getline(cin, s);
                release[0] = stoi(s);
                getline(cin, s);
                release[1] = stoi(s);
                getline(cin, s);
                release[2] = stoi(s);
                printf("Введите платформы на которых доступна игра( чтобы закончить вводить платформы введите пустую строку)\n");
                d = -1;
                do
                {
                    d++;
                    getline(cin, platforms[d]);
                } while (platforms[d] != "");
                printf("Введите издателя\n");
                getline(cin, publisher);
                game1[numberOfGames] = Game(itemCode, itemName, itemPrice, itemAmount, release, platforms, publisher);
                numberOfGames++;
                printf("Добавить еще одну игру?(1 - да, все остальные символы - нет)\n");
                getline(cin, f);
                getchar();
            }
            numberOfPlatforms = 0;;
            printf("Добавить консоль?(1-да,0-нет)\n");
            getline(cin, f);
            while (f == "1") {
                printf("\nВведите название товара\n");
                getline(cin, itemName);
                printf("Введите код товара\n");
                getline(cin, itemCode);
                do {
                    printf("Введите цену\n");
                    try {
                        getline(cin, s);
                        itemPrice = stod(s);
                    }
                    catch (...) {
                        itemPrice = -1;
                    }
                } while (itemPrice < 0);
                do {
                    printf("Введите колличество товара\n");
                    try {
                        getline(cin, s);
                        itemAmount = stoi(s);
                    }
                    catch (...) {
                        itemAmount = -1;
                    }
                } while (itemAmount < 0);
                printf("Введите комплектацию( чтобы закончить вводить комплектацию введите пустую строку)\n");
                d = -1;
                do
                {
                    d++;
                    getline(cin, components[d]);
                } while (components[d] != "");
                printf("Введите платформы доступные по обратной совместимости( чтобы закончить вводить платформы введите пустую строку)\n");
                d = -1;
                do
                {
                    d++;
                    getline(cin, plusPlatforms[d]);
                } while (plusPlatforms[d] != "");
                printf("Введите издателя\n");
                getline(cin, publisher);
                platform1[numberOfPlatforms] = Platform(itemCode, itemName, itemPrice, itemAmount, components, plusPlatforms, publisher);
                numberOfPlatforms++;
                printf("Добавить еще одну консоль?(1 - да, все остальные символы - нет)\n");
                getline(cin, f);
                getchar();
            }
            store1[0] = Store(name, adress, numberOfItems, item1, numberOfGames, game1, numberOfPlatforms, platform1);
        }
        i = 0;
        max = 1;
        f = "1";
        while (f != "10") {
            store1[i].displayName();
            printf("\nВведите номер следующего действия:\n");
            printf("1 - показать информацию о магазине\n");
            printf("2 - добавить новый вид товара\n");
            printf("3 - изменить цену товара\n");
            printf("4 - изменить колличество товара\n");
            printf("5 - Добавить магазин\n");
            printf("6 - показать все магазины\n");
            printf("7 - сменить магазин\n");
            printf("8 - сложить магазины\n");
            printf("9 - добавить комплектующие к консоли или платформы на которых доступна игра\n");
            printf("10 - выйти\n");
            getline(cin, f);
            if (f == "1") {
                store1[i].display();
            }
            else if (f == "2") {
                store1[i] = store1[i]++;
            }
            else if (f == "3") {
                printf("\nВведите код товара\n");
                getline(cin, code);
                do {
                    printf("Введите новую цену\n");
                    try {
                        getline(cin, s);
                        price = stod(s);
                    }
                    catch (...) {
                        price = -1;
                    }
                } while (price < 0);
                getchar();
                store1[i].priceChange(code, price);
            }
            else if (f == "4") {
                printf("\nВведите код товара\n");
                getline(cin, code);
                printf("Введите на сколько изменилось колличество товара(если увеличилость - положительное число, если уменьшилось - отрицательное)\n");
                try {
                    getline(cin, s);
                    amountDifference = stoi(s);
                }
                catch (...) {
                    amountDifference = 0;
                }
                getchar();
                store1[i].amountChange(code, amountDifference);
            }
            else if (f == "5") {
                store1[max].read();
                i = max;
                max++;

            }
            else if (f == "6") {
                for (n = 0; n < max; n++) {
                    store1[n].displayName();
                }
            }
            else if (f == "7") {
                printf("\nВведите название магазина\n");
                getline(cin, name);
                for (n = 0; n < max; n++) {
                    if (storecmp(name, store1[n]) == 1) {
                        i = n;
                        n = max;
                    }
                }
            }
            else if (f == "8") {
                printf("\nВведите название магазина\n");
                getline(cin, name);
                for (n = 0; n < max; n++) {
                    if (storecmp(name, store1[n]) == 1) {
                        store1[i] = store1[i] + store1[n];
                        n = max;
                    }
                }
            }
            else if (f == "9") {
                printf("Введите код товара\n");
                getline(cin, code);
                store1[i].add(code);
            }
        }
    }
    return 0;
}


