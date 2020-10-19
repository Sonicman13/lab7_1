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
#include "stdio.h"
#include "time.h"
using namespace std;
#define N 100

class Item {
private:
    string code;
    string name;
    double price;
    int amount;
public:
    void read();
    void init(string code1, string name1, double price1, int amount1);
    void display();
    void setPrice(double price1);
    void setAmount(int amount1);
    string getCode();
    int getAmount();
};

void Item::read() {
    printf("\nВведите название товара\n");
    getline(cin, name);
    printf("Введите код товара\n");
    getline(cin, code);
    do {
        printf("Введите цену\n");
        scanf_s("%lf", &price);
    } while (price < 0);
    do {
        printf("Введите колличество товара\n");
        scanf_s("%d", &amount);
    } while (amount < 0);
}

void Item::init(string code, string name, double price, int amount) {
    this->name = name;
    this->code = code;
    this->price = price;
    this->amount = amount;
}

void Item::display() {
    printf("Код:");
    cout << code << endl;
    printf("Название:");
    cout << name << endl;
    printf("Цена: %lf\n", price);
    printf("Колличество: %d\n", amount);
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

class Store {
private:
    string name;
    string adress;
    int numberOfItems;
    class Item item[N];
public:
    void read();
    void init(string name1, string adress1, int numberOfItems1, string itemName1[], string itemCode1[], double itemPrice1[], int itemAmount1[]);
    void display();
    void add();
    void priceChange(string item1, double price);
    void amountChange(string item1, int amountDifference);
    void displayName();
    friend int storecmp(string name1, Store store);
    string getName() {
        return name;
    }
    Store operator + (Store store);
    void getNumber(int* number);
    void getNumber(int& number);
};


void Store::read() {
    char f;
    int i;
    printf("\nВведите название магазина\n");
    getline(cin, name);
    printf("Введите адрес магазина\n");
    getline(cin, adress);
    numberOfItems = i = 0;;
    printf("Добавить товар?(1 - да, все остальные символы - нет)\n");
    f = _getche();
    while (f == '1') {
        item[numberOfItems].read();
        numberOfItems++;
        printf("Добавить еще один товар?(1 - да, все остальные символы -нет)\n");
        f = _getche();
        getchar();
    }
}

void Store::init(string name, string adress, int numberOfItems, string itemName1[], string itemCode1[], double itemPrice1[], int itemAmount1[]) {
    int i;
    this->name = name;
    this->adress = adress;
    this->numberOfItems = numberOfItems;
    for (i = 0; i < numberOfItems; i++) {
        item[i].init(itemCode1[i], itemName1[i], itemPrice1[i], itemAmount1[i]);
    }
}

void Store::display() {
    int i;
    printf("\nНазвание магазина:");
    cout << name << endl;
    printf("Адрес:");
    cout << adress << endl;
    printf("Колличество уникальных товаров: %d\n", numberOfItems);
    for (i = 0; i < numberOfItems; i++) {
        printf("\nТовар %d\n", i + 1);
        item[i].display();
    }
}

void Store::add() {
    item[numberOfItems].read();
    numberOfItems++;
    getchar();
}

void Store::priceChange(string item1, double price) {
    int i = 0;
    while (i < numberOfItems) {
        if (item[i].getCode() == item1) {
            item[i].setPrice(price);
            i = numberOfItems;
        }
        i++;
    }
}

void Store::amountChange(string item1, int amountDifference) {
    int i = 0;
    while (i < numberOfItems) {
        if (item[i].getCode() == item1) {
            item[i].setAmount(item[i].getAmount() + amountDifference);
            i = numberOfItems;
        }
        i++;
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
    newStore.numberOfItems = this->numberOfItems + store.numberOfItems;
    for (n = 0; n < this->numberOfItems; n++) {
        newStore.item[n] = this->item[n];
    }
    i = this->numberOfItems;
    for (n = 0; n < store.numberOfItems; n++) {
        newStore.item[i] = store.item[n];
        i++;
    }
    return newStore;
}

void Store::getNumber(int *number)
{
    *number = numberOfItems;
}

void Store::getNumber(int& number)
{
    number = numberOfItems;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    class Store store1[10], * store2, * store3[10];
    int amountDifference, numberOfItems, itemAmount[N], i, max, n, *g;
    double price, itemPrice[N];
    char f;
    string s, s1[N], code, name, adress, itemCode[N], itemName[N];
    printf("Работать с переменной, указателем или указателем на массив?(1 - переменная, 2 - указатель, все остальные символы - указатель на массив)\n");
    f = _getche();
    printf("\n");

    //Переменная
    g = (int*)malloc(sizeof(int));
    if (f == '1') {
        s = "-";
        s1[0] = "-";
        printf("Использовать или read чтобы ввести данные(1 - read, все остальные символы - init)\n");
        f = _getche();
        if (f == '1') {
            store1[0].read();
        }
        else {
            printf("\nВведите название магазина\n");
            getline(cin, name);
            printf("Введите адрес магазина\n");
            getline(cin, adress);
            numberOfItems = 0;;
            printf("Добавить товар?(1-да,0-нет)\n");
            f = _getche();
            while (f == '1') {
                printf("\nВведите название товара\n");
                getline(cin, itemName[numberOfItems]);
                printf("Введите код товара\n");
                getline(cin, itemCode[numberOfItems]);
                do {
                    printf("Введите цену\n");
                    scanf_s("%lf", &itemPrice[numberOfItems]);
                } while (itemPrice[numberOfItems] < 0);
                do {
                    printf("Введите колличество товара\n");
                    scanf_s("%d", &itemAmount[numberOfItems]);
                } while (itemAmount[numberOfItems] < 0);
                numberOfItems++;
                printf("Добавить еще один товар?(1 - да, все остальные символы - нет)\n");
                f = _getche();
                getchar();
            }
            store1[0].init(name, adress, numberOfItems, itemName, itemCode, itemPrice, itemAmount);
        }
        i = 0;
        max = 1;
        f = '1';
        while (f != '10') {
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
            printf("9 - показать колличество товаров\n");
            printf("10 - выйти\n");
            f = _getche();
            if (f == '1') {
                store1[i].display();
            }
            else if (f == '2') {
                store1[i].add();
            }
            else if (f == '3') {
                printf("\nВведите код товара\n");
                getline(cin, code);
                do {
                    printf("Введите новую цену\n");
                    scanf_s("%lf", &price);
                } while (price < 0);
                getchar();
                store1[i].priceChange(code, price);
            }
            else if (f == '4') {
                printf("\nВведите код товара\n");
                getline(cin, code);
                printf("Введите на сколько изменилось колличество товара(если увеличилость - положительное число, если уменьшилось - отрицательное)\n");
                scanf_s("%d", &amountDifference);
                getchar();
                store1[i].amountChange(code, amountDifference);
            }
            else if (f == '5') {
                store1[max].read();
                i = max;
                max++;

            }
            else if (f == '6') {
                for (n = 0; n < max; n++) {
                    store1[n].displayName();
                }
            }
            else if (f == '7') {
                printf("\nВведите название магазина\n");
                getline(cin, name);
                for (n = 0; n < max; n++) {
                    if (storecmp(name, store1[n]) == 1) {
                        i = n;
                        n = max;
                    }
                }
            }
            else if (f == '8') {
                printf("\nВведите название магазина\n");
                getline(cin, name);
                for (n = 0; n < max; n++) {
                    if (storecmp(name, store1[n]) == 1) {
                        store1[i] = store1[i] + store1[n];
                        n = max;
                    }
                }
            }
            else if (f == '9') {
                printf("\n1 - out, 0 - ref\n");
                getline(cin, s);
                if (s == "1")
                {
                    store1[i].getNumber(g);
                    printf("%d\n", *g);
                }
                else
                {
                    store1[i].getNumber(&n);
                    printf("%d\n", n);
                }
            }
        }
    }

    //Указатель на масив

    else if (f == '2') {
        store2 = new Store[10];
        s = "-";
        s1[0] = "-";
        printf("Использовать или read чтобы ввести данные(1 - read, все остальные символы - init)\n");
        f = _getche();
        if (f == '1') {
            store2[0].read();
        }
        else {
            printf("\nВведите название магазина\n");
            getline(cin, name);
            printf("Введите адрес магазина\n");
            getline(cin, adress);
            numberOfItems = 0;;
            printf("Добавить товар?(1-да,0-нет)\n");
            f = _getche();
            while (f == '1') {
                printf("\nВведите название товара\n");
                getline(cin, itemName[numberOfItems]);
                printf("Введите код товара\n");
                getline(cin, itemCode[numberOfItems]);
                do {
                    printf("Введите цену\n");
                    scanf_s("%lf", &itemPrice[numberOfItems]);
                } while (itemPrice[numberOfItems] < 0);
                do {
                    printf("Введите колличество товара\n");
                    scanf_s("%d", &itemAmount[numberOfItems]);
                } while (itemAmount[numberOfItems] < 0);
                numberOfItems++;
                printf("Добавить еще один товар?(1 - да, все остальные символы - нет)\n");
                f = _getche();
                getchar();
            }
            store2[0].init(name, adress, numberOfItems, itemName, itemCode, itemPrice, itemAmount);
        }
        i = 0;
        max = 1;
        f = '1';
        while (f != '10') {
            store2[i].displayName();
            printf("\nВведите номер следующего действия:\n");
            printf("1 - показать информацию о магазине\n");
            printf("2 - добавить новый вид товара\n");
            printf("3 - изменить цену товара\n");
            printf("4 - изменить колличество товара\n");
            printf("5 - Добавить магазин\n");
            printf("6 - показать все магазины\n");
            printf("7 - сменить магазин\n");
            printf("8 - сложить магазины\n");
            printf("9 - показать колличество товаров\n");
            printf("10 - выйти\n");
            f = _getche();
            if (f == '1') {
                store2[i].display();
            }
            else if (f == '2') {
                store2[i].add();
            }
            else if (f == '3') {
                printf("\nВведите код товара\n");
                getline(cin, code);
                do {
                    printf("Введите новую цену\n");
                    scanf_s("%lf", &price);
                } while (price < 0);
                getchar();
                store2[i].priceChange(code, price);
            }
            else if (f == '4') {
                printf("\nВведите код товара\n");
                getline(cin, code);
                printf("Введите на сколько изменилось колличество товара(если увеличилость - положительное число, если уменьшилось - отрицательное)\n");
                scanf_s("%d", &amountDifference);
                getchar();
                store2[i].amountChange(code, amountDifference);
            }
            else if (f == '5') {
                store2[max].read();
                i = max;
                max++;

            }
            else if (f == '6') {
                for (n = 0; n < max; n++) {
                    store2[n].displayName();
                }
            }
            else if (f == '7') {
                printf("\nВведите название магазина\n");
                getline(cin, name);
                for (n = 0; n < max; n++) {
                    if (storecmp(name, store2[n]) == 1) {
                        i = n;
                        n = max;
                    }
                }
            }
            else if (f == '8') {
                printf("\nВведите название магазина\n");
                getline(cin, name);
                for (n = 0; n < max; n++) {
                    if (storecmp(name, store2[n]) == 1) {
                        store2[i] = store2[i] + store2[n];
                        n = max;
                    }
                }
            }
            else if (f == '9') {
                printf("\n1 - out, 0 - ref\n");
                getline(cin, s);
                if (s == "1")
                {
                    store2[i].getNumber(g);
                    printf("%d\n", *g);
                }
                else
                {
                    store2[i].getNumber(&n);
                    printf("%d\n", n);
                }
            }
        }
        delete[] store2;
    }

    //Массив указателей

    else {
        store3[0] = (class Store*)malloc(sizeof(Store));
        s = "-";
        s1[0] = "-";
        printf("Использовать или read чтобы ввести данные(1 - read, все остальные символы - init)\n");
        f = _getche();
        if (f == '1') {
            store3[0]->read();
        }
        else {
            printf("\nВведите название магазина\n");
            getline(cin, name);
            printf("Введите адрес магазина\n");
            getline(cin, adress);
            numberOfItems = 0;;
            printf("Добавить товар?(1-да,0-нет)\n");
            f = _getche();
            while (f == '1') {
                printf("\nВведите название товара\n");
                getline(cin, itemName[numberOfItems]);
                printf("Введите код товара\n");
                getline(cin, itemCode[numberOfItems]);
                do {
                    printf("Введите цену\n");
                    scanf_s("%lf", &itemPrice[numberOfItems]);
                } while (itemPrice[numberOfItems] < 0);
                do {
                    printf("Введите колличество товара\n");
                    scanf_s("%d", &itemAmount[numberOfItems]);
                } while (itemAmount[numberOfItems] < 0);
                numberOfItems++;
                printf("Добавить еще один товар?(1 - да, все остальные символы - нет)\n");
                f = _getche();
                getchar();
            }
            store3[0]->init(name, adress, numberOfItems, itemName, itemCode, itemPrice, itemAmount);
        }
        i = 0;
        max = 1;
        f = '1';
        while (f != '10') {
            store3[i]->displayName();
            printf("\nВведите номер следующего действия:\n");
            printf("1 - показать информацию о магазине\n");
            printf("2 - добавить новый вид товара\n");
            printf("3 - изменить цену товара\n");
            printf("4 - изменить колличество товара\n");
            printf("5 - Добавить магазин\n");
            printf("6 - показать все магазины\n");
            printf("7 - сменить магазин\n");
            printf("8 - сложить магазины\n");
            printf("9 - показать колличество товаров\n");
            printf("10 - выйти\n");
            f = _getche();
            if (f == '1') {
                store3[i]->display();
            }
            else if (f == '2') {
                store3[i]->add();
            }
            else if (f == '3') {
                printf("\nВведите код товара\n");
                getline(cin, code);
                do {
                    printf("Введите новую цену\n");
                    scanf_s("%lf", &price);
                } while (price < 0);
                getchar();
                store3[i]->priceChange(code, price);
            }
            else if (f == '4') {
                printf("\nВведите код товара\n");
                getline(cin, code);
                printf("Введите на сколько изменилось колличество товара(если увеличилость - положительное число, если уменьшилось - отрицательное)\n");
                scanf_s("%d", &amountDifference);
                getchar();
                store3[i]->amountChange(code, amountDifference);
            }
            else if (f == '5') {
                store3[max] = (class Store*)malloc(sizeof(Store));
                store3[max]->read();
                i = max;
                max++;

            }
            else if (f == '6') {
                for (n = 0; n < max; n++) {
                    store3[n]->displayName();
                }
            }
            else if (f == '7') {
                printf("\nВведите название магазина\n");
                getline(cin, name);
                for (n = 0; n < max; n++) {
                    if (storecmp(name, *store3[n]) == 1) {
                        i = n;
                        n = max;
                    }
                }
            }
            else if (f == '8') {
                printf("\nВведите название магазина\n");
                getline(cin, name);
                for (n = 0; n < max; n++) {
                    if (storecmp(name, *store3[n]) == 1) {
                        *store3[i] = *store3[i] + *store3[n];
                        n = max;
                    }
                }
            }
            else if (f == '9') {
                printf("\n1 - out, 0 - ref\n");
                getline(cin, s);
                if (s == "1")
                {
                    store3[i]->getNumber(g);
                    printf("%d\n", *g);
                }
                else
                {
                    store3[i]->getNumber(&n);
                    printf("%d\n", n);
                }
            }
        }
        for (n = 0; n < max; n++) {
            free(store3[n]);
        }
    }
    return 0;
}


