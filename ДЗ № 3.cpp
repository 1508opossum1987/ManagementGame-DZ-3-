#include <iostream>
#include <stdlib.h>  

using namespace std;

// Класс игрока
class Player {
private:
    int ID;//номер игрока
    int Capital;//деньги игрока
    int Fabric;//количество обычных фабрик
    int Autofabric;//количество автоматизированных фабрик
    int ESM;//количество сырья (ЕСМ)
    int EGP;//количество готовой продукции (ЕГП)
    bool Status;//статус - банкрот или не банкрот, true - банкрот
    //int ordinaryFactories;  // количество обычных фабрик
    //int automatedFactories;  // количество автоматизированных фабрик
    //int rawMaterials;  //количество сырья (ЕСМ)
    //int finishedProducts;  // Количество готовой продукции (ЕГП)
    //int loans;  // Сумма непогашенных ссуд
    //int loanTerm;  // Срок ссуды
public:
    // Конструктор игрока
    Player(int ID, int Capital = 10000, int Fabric = 2, int Autofabric = 0, int ESM = 4, int EGP=2, bool Status=false):// int rawMaterials = 4, int finishedProducts = 2,
        //int ordinaryFactories = 2, int automatedFactories = 0, int loans = 0, int loanTerm = 0)
        ID(ID), Capital(Capital), Fabric(Fabric), Autofabric(Autofabric), ESM(ESM), EGP(EGP), Status(Status){}
        //ordinaryFactories(ordinaryFactories), automatedFactories(automatedFactories), loans(loans), loanTerm(loanTerm) {}

    // Геттеры для получения значений полей
    int getID() const { return ID; }
    int getCapital() const { return Capital; }
    int getFabric()const { return Fabric; }
    int getAutofabric()const { return Autofabric; }
    int getESM()const { return ESM; }
    int getEGP() const { return EGP; }
    int getStatus() const { return Status; }
    /*int getRawMaterials() const { return rawMaterials; }
    int getFinishedProducts() const { return finishedProducts; }
    int getOrdinaryFactories() const { return ordinaryFactories; }
    int getAutomatedFactories() const { return automatedFactories; }
    int getLoans() const { return loans; }
    int getLoanTerm() const { return loanTerm; }*/

    // Метод для оплаты постоянных издержек

    /*void payFixedCosts(int cost) {
        cash -= cost;
        if (cash < 0) {
            cout << "Игрок " << id << " банкрот!" << endl;
        }
    }*/

    // Метод для запроса сырья
    void requestRawMaterials(int amount, int price) {
        if (cash >= price * amount) {
            rawMaterials += amount;
            cash -= price * amount;
        }
        else {
            cout << "Игрок " << id << " не может купить сырье!" << endl;
        }
    }

    // Метод для производства товаров
    void produceGoods(int amount, bool useAutomatedFactory) {
        if (rawMaterials >= amount) {
            if (useAutomatedFactory && automatedFactories > 0) {
                cash -= 3000;  // Стоимость производства на автоматизированной фабрике
                finishedProducts += 2 * amount;
            }
            else if (ordinaryFactories > 0) {
                cash -= 2000;  // Стоимость производства на обычной фабрике
                finishedProducts += amount;
            }
            rawMaterials -= amount;
        }
        else {
            cout << "Игрок " << id << " does not have enough raw materials!" << endl;
        }
    }

    // Метод для продажи товаров
    void sellGoods(int amount, int price) {
        if (finishedProducts >= amount) {
            finishedProducts -= amount;
            cash += price * amount;
        }
        else {
            cout << "Player " << id << " does not have enough finished products!" << endl;
        }
    }

    // Метод для выплаты процентов по ссуде
    void payLoanInterest() {
        int interest = loans * 0.01;
        cash -= interest;
    }

    // Метод для погашения ссуд
    void repayLoans() {
        if (loanTerm == 0) {
            cash -= loans;
            loans = 0;
        }
    }

    // Метод для получения ссуды
    void takeLoan(int amount, int term) {
        if (loans + amount <= (ordinaryFactories * 5000 + automatedFactories * 10000) / 2) {
            loans += amount;
            cash += amount;
            loanTerm = term;
        }
        else {
            cout << "Player " << id << " cannot take more loans!" << endl;
        }
    }

    // Метод для строительства фабрики
    void buildFactory(bool isAutomated) {
        if (isAutomated) {
            if (cash >= 5000) {
                cash -= 5000;
                automatedFactories++;
            }
        }
        else {
            if (cash >= 5000) {
                cash -= 5000;
                ordinaryFactories++;
            }
        }
    }

    // Метод для принятия решений ИИ
    void makeDecision(int rawMaterialPrice, int finishedProductPrice, bool isSenior) {
        if (isSenior) {
            // Старший игрок может принимать более агрессивные решения
            if (cash > 5000) {
                buildFactory(true);  // Строим автоматизированную фабрику
            }
            requestRawMaterials(2, rawMaterialPrice);  // Покупаем больше сырья
            produceGoods(1, true);  // Производим товары на автоматизированной фабрике
            sellGoods(1, finishedProductPrice);  // Продаем товары
        }
        else {
            // Остальные игроки действуют более консервативно
            if (cash > 3000) {
                buildFactory(false);  // Строим обычную фабрику
            }
            requestRawMaterials(1, rawMaterialPrice);  // Покупаем сырье
            produceGoods(1, false);  // Производим товары на обычной фабрике
            sellGoods(1, finishedProductPrice);  // Продаем товары
        }
    }
};

// Класс банка
class Bank {
private:
    int currentMonth;  // Текущий месяц игры
    int marketLevel;  // Уровень рынка (1-5)
    int rawMaterialPrice;  // Цена сырья
    int finishedProductPrice;  // Цена готовой продукции
    int gameDuration;  // Продолжительность игры в месяцах
    Player* players[10];  // Массив игроков (максимум 10 игроков)
    int numPlayers;  // Количество игроков

public:
    // Конструктор банка
    Bank(int duration) : currentMonth(0), marketLevel(3), gameDuration(duration), numPlayers(0) {
        updatePrices();
    }

    // Метод для добавления игрока
    void addPlayer(Player* player) {
        if (numPlayers < 10) {
            players[numPlayers++] = player;
        }
    }

    // Метод для обновления цен на сырье и готовую продукцию
    void updatePrices() {
        switch (marketLevel) {
        case 1:
            rawMaterialPrice = 800;
            finishedProductPrice = 6500;
            break;
        case 2:
            rawMaterialPrice = 650;
            finishedProductPrice = 6000;
            break;
        case 3:
            rawMaterialPrice = 500;
            finishedProductPrice = 5500;
            break;
        case 4:
            rawMaterialPrice = 400;
            finishedProductPrice = 5000;
            break;
        case 5:
            rawMaterialPrice = 300;
            finishedProductPrice = 4500;
            break;
        }
    }

    // Метод для обновления уровня рынка
    void updateMarketLevel() {
        int random = rand() % 100;
        if (marketLevel == 1) {
            if (random < 33) marketLevel = 1;
            else if (random < 66) marketLevel = 2;
            else if (random < 83) marketLevel = 3;
            else marketLevel = 4;
        }
        else if (marketLevel == 2) {
            if (random < 25) marketLevel = 1;
            else if (random < 58) marketLevel = 2;
            else if (random < 83) marketLevel = 3;
            else marketLevel = 4;
        }
        else if (marketLevel == 3) {
            if (random < 8) marketLevel = 1;
            else if (random < 33) marketLevel = 2;
            else if (random < 66) marketLevel = 3;
            else if (random < 83) marketLevel = 4;
            else marketLevel = 5;
        }
        else if (marketLevel == 4) {
            if (random < 8) marketLevel = 2;
            else if (random < 33) marketLevel = 3;
            else if (random < 66) marketLevel = 4;
            else marketLevel = 5;
        }
        else if (marketLevel == 5) {
            if (random < 8) marketLevel = 3;
            else if (random < 41) marketLevel = 4;
            else marketLevel = 5;
        }
    }

    // Метод для перехода к следующему месяцу
    void nextMonth() {
        currentMonth++;
        updateMarketLevel();
        updatePrices();

        // Логика ежемесячных операций
        for (int i = 0; i < numPlayers; ++i) {
            players[i]->payFixedCosts(300 * players[i]->getRawMaterials() +
                500 * players[i]->getFinishedProducts() +
                1000 * players[i]->getOrdinaryFactories() +
                1500 * players[i]->getAutomatedFactories());

            players[i]->payLoanInterest();
            players[i]->repayLoans();
        }

        // Логика заявок на сырьё, производство, продажу и т.д.
        int seniorPlayerID = (currentMonth % numPlayers);
        for (int i = 0; i < numPlayers; ++i) {
            bool isSenior = (i == seniorPlayerID);
            if (i == 0) {
                // Игрок 1 управляется человеком
                int choice;
                cout << "Player 1, choose action: 1 - Buy Raw Materials, 2 - Produce Goods, 3 - Sell Goods: ";
                cin >> choice;
                if (choice == 1) {
                    players[i]->requestRawMaterials(1, rawMaterialPrice);
                }
                else if (choice == 2) {
                    players[i]->produceGoods(1, false);
                }
                else if (choice == 3) {
                    players[i]->sellGoods(1, finishedProductPrice);
                }
            }
            else {
                // Остальные игроки управляются ИИ
                players[i]->makeDecision(rawMaterialPrice, finishedProductPrice, isSenior);
            }
        }

        // Формирование ежемесячного отчёта
        generateMonthlyReport();
    }

    // Метод для генерации ежемесячного отчёта
    void generateMonthlyReport() {
        cout << "Monthly Report - Month " << currentMonth << endl;
        for (int i = 0; i < numPlayers; ++i) {
            cout << "Player " << players[i]->getID() << ": "
                << "Cash: " << players[i]->getCash() << ", "
                << "Raw Materials: " << players[i]->getRawMaterials() << ", "
                << "Finished Products: " << players[i]->getFinishedProducts() << ", "
                << "Loans: " << players[i]->getLoans() << endl;
        }
    }

    // Метод для подсчёта итоговых результатов
    void finalResults() {
        cout << "Final Results:" << endl;
        for (int i = 0; i < numPlayers; ++i) {
            int totalCapital = players[i]->getCash() +
                players[i]->getRawMaterials() * rawMaterialPrice +
                players[i]->getFinishedProducts() * finishedProductPrice +
                players[i]->getOrdinaryFactories() * 5000 +
                players[i]->getAutomatedFactories() * 10000 -
                players[i]->getLoans();

            cout << "Player " << players[i]->getID() << " Total Capital: " << totalCapital << endl;
        }
    }

    // Метод для запуска игры
    void startGame() {
        for (int month = 1; month <= gameDuration; ++month) {
            cout << "Month " << month << endl;
            nextMonth();
        }
        finalResults();
    }
};

int main() {
    system("chcp 1251>NUL");
    int numPlayers;
    int gameDuration;
    cout << "Введите количество игроков (игрой предусмотрено не более 10): "<<endl;
    cin >> numPlayers;
    cout << "Введите продолжительность игры в месяцах: "<<endl;
    cin >> gameDuration;
    Bank bank(gameDuration);
    for (int i = 1; i <= numPlayers; ++i) {
        bank.addPlayer(new Player(i));
    }
    bank.startGame();
    return 0;
}