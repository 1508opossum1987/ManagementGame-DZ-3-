#include <iostream>
#include <stdlib.h>  

using namespace std;

//класс игрока
class Player 
{
private:
    int ID;//номер игрока
    int Capital;//деньги игрока
    int Fabric;//количество обычных фабрик
    int Autofabric;//количество автоматизированных фабрик
    int ESM;//количество сырья (ЕСМ)
    int EGP;//количество готовой продукции (ЕГП)
    int loans;//cумма непогашенных ссуд
    int loanTerm;//cрок ссуды
    int zESM;//заявка на количество ЕСМ в раунде для покупки
    int pESM;//заявка на цену ЕСМ в раунде для покупки
    int zEGP;//заявка на количество ЕГП в раунде для продажи
    int pEGP;//заявка на цену ЕГП в раунде для продажи
    int MonthBFabric;//месяц ввода в работу фабрики
    int MonthBAutofabric;//месяц ввода в работу автофабрики
    int MonthMAutofabric;//месяц ввода в работу автофабрики после модернизации
public:
    bool Status;//статус - банкрот или не банкрот, true - банкрот
    // Конструктор игрока
    Player(int ID, int Capital = 10000, int Fabric = 2, int Autofabric = 0, int ESM = 4, int EGP = 2, bool Status = false, int loans = 0, int loanTerm=0, int zESM=0, int pESM=0,int zEGP=0,int pEGP=0, int MonthBFabric=0, int MonthBAutofabric=0, int MonthMAutofabric=0/*int useAutofabric=0*/) :
        ID(ID), Capital(Capital), Fabric(Fabric), Autofabric(Autofabric), ESM(ESM), EGP(EGP), Status(Status), loans(loans), loanTerm(loanTerm), zESM(zESM), pESM(pESM), zEGP(zEGP), pEGP(pEGP), MonthBFabric(MonthBFabric), MonthBAutofabric(MonthBAutofabric), MonthMAutofabric(MonthMAutofabric) /*useAutofabric(useAutofabric)*/ {
    }

//геттеры для получения значений полей
    int getID() const { return ID; }//номер игрока
    int getCapital() const { return Capital; }//количество денег
    int getFabric()const { return Fabric; }//количество фабрик
    int getAutofabric()const { return Autofabric; }//количество автофабрик
    int getESM()const { return ESM; }//количество сырья
    int getEGP() const { return EGP; }//количество готовой продукции
    int getStatus() const { return Status; }//статус банкротства
    int getLoans() const { return loans; }//погашение процентов по ссуде
    int getLoanTerm() const { return loanTerm; }//срок ссуды
    int getzESM() const { return zESM; }//заявка на количество ЕСМ в раунде
    int getpESM() const { return pESM; }//заявка на цену покупки ЕСМ в раунде
    int getzEGP() const { return zEGP; }//заявка на количество ЕГП в раунде
    int getpEGP() const { return pEGP; }//заявка на цену продажи ЕГП в раунде
    int getMonthBFabric() const {return MonthBFabric;}//месяц ввода в работу фабрики
    int getMonthBAutofabric() const { return MonthBAutofabric; }//месяц ввода в работу автофабрики
    int getMonthMAutofabric() const { return MonthMAutofabric; }//месяц ввода в работу автофабрики после модернизации
    void PlayerInfo() const//метод для отображения основных данных игрока
    {
        cout << "Капитал: " << Capital << ", ЕСМ: " << ESM << ", ЕГП: " << EGP << ", Фабрик: " << Fabric << ", Автофабрик: " << Autofabric << ", Ссуда: " << loans << ", Срок погашения ссуды: " << loanTerm << endl;
    }

    //метод для оплаты постоянных издержек игроками
    void payFixedCosts(int cost) 
    {
        Capital -= cost;
        if (Capital < 0) 
        {
            Status = true;
            cout << "Игрок " << ID << " банкрот!" << endl;
        }
    }

    //метод производства ЕГП игроком-человеком
    void produceEGPHuman()
    {
        if (ESM > 0)
        {
            int ESMforproda = 0;//ЕСМ для автофабрики
            int ESMforprodf = 0;//ЕСМ для фабрики
            if (Autofabric > 0)
            {
                cout << "Введите количество ЕСМ для переработки на автофабриках: " << endl;
                while (true)
                {
                    PlayerInfo();
                    cout << "Стоимость переработки на автофабрике: 2 ЕСМ - 3000, 1 ЕСМ - 2000, на фабрике: 1 ЕСМ - 2000 " << endl;
                    cin >> ESMforproda;
                    if (ESMforproda<0 || ESMforproda > ESM || ESMforproda % (Autofabric * 2) >= 1 || Capital < (((ESMforproda % Autofabric) * 3000) + (ESMforproda / Autofabric) * 2000))
                        cout << "Некорректное значение! Попробуйте еще!" << endl;
                    else
                        break;
                }
                Capital -=(((ESMforproda % Autofabric) * 3000) + (ESMforproda / Autofabric) * 2000);
                ESM -= ESMforproda;
                EGP += ESMforproda;
            }
            if (ESM > 0 && Fabric > 0)
            {
                cout << "У Вас сейчас нет автофабрик! " << endl;
                PlayerInfo();
                cout << "Стоимость переработки на фабрике: 1 ЕСМ - 2000 " << endl;
                cout << "Введите количество ЕСМ для переработки на обычных фабриках: " << endl;
                while (true)
                {
                    cin >> ESMforprodf;
                    if (ESMforprodf<0 || ESMforprodf > ESM || Capital < ESMforprodf * 2000 || ESMforprodf>Fabric)
                        cout << "Некорректное значение! Попробуйте еще!" << endl;
                    else
                        break;
                }
                Capital -= ESMforprodf * 2000;
                ESM -= ESMforprodf;
                EGP += ESMforprodf;
            }
            cout << "Переработка ЕСМ в ЕГП прошла успешно!" << endl;
        }
        else
            cout << "У Вас нет ресурсов для переработки!" << endl;
    }

    //метод метод производства ЕГП игроком-ботом
    void produceEGPBot()
    {
        if (ESM > 0)
        {
            int ESMforproda = 0;//ЕСМ для автофабрики
            int ESMforprodf = 0;//ЕСМ для фабрики
            if (Autofabric > 0)
            {
                while (true)
                {
                    ESMforproda = rand() % ESM;
                    if (ESMforproda % (Autofabric * 2) >= 1 || Capital < (((ESMforproda % Autofabric) * 3000) + (ESMforproda / Autofabric) * 2000))
                        continue;
                    else
                        break;
                }
                Capital -= (((ESMforproda % Autofabric) * 3000) + (ESMforproda / Autofabric) * 2000);
                ESM -= ESMforproda;
                EGP += ESMforproda;
            }
            if (ESM > 0 && Fabric > 0)
            {
                while (true)
                {

                    ESMforprodf = rand() % ESM;
                    if (Capital < ESMforprodf * 2000 || ESMforprodf>Fabric)
                        continue;
                    else
                        break;
                }
                Capital -= ESMforprodf * 2000;
                ESM -= ESMforprodf;
                EGP += ESMforprodf;
            }
            //cout << "Переработка ЕСМ в ЕГП прошла успешно!" << endl;
        }
        else
            return;
            //cout << "У игрока "<<ID<<" нет ресурсов для переработки!" << endl;
    }

    //метод для выплаты процентов по ссуде игроками
    void payLoanInterest() 
    {
        int interest = loans * 0.01;
        Capital -= interest;
        if (Capital < 0) 
        {
            Status = true;
            cout << "Игрок " << ID << " банкрот!" << endl;
        }
    }

    //метод для погашения основной суммы ссуды
    void repayLoans() 
    {
        Capital -= loans;
        loans = 0;
        loanTerm = 0;
        if (Capital < 0) 
        {
            Status = true;
            cout << "Игрок " << ID << " банкрот!" << endl;
        }
    }

    //метод для получения ссуды игроком-человеком
    void takeLoanHuman(int Month) 
    {
        if ((Fabric > 0 || Autofabric > 0)&&Status==false)
        {
            cout << "Максимальный размер возможной ссуды: " << (Fabric * 5000 + Autofabric * 10000) / 2 << endl;
            PlayerInfo();
            cout << "Введите сумму ссуды для получения. Если она не нужна, введите 0 " << endl;
            while (true)
            {
                cin >> loans;
                if (loans<0 || loans>(Fabric * 5000 + Autofabric * 10000) / 2)
                    cout << "Введены некорректные данные, попробуйте еще" << endl;
                else if (loans == 0)
                {
                    cout << "Игрок " << ID << " решил не брать ссуду!" << endl;
                    break;
                }
                else
                {
                    Capital += loans;
                    loanTerm = Month + 12;
                    cout << "Игроку " << ID <<  " выдана ссуда в размере " << loans << endl;
                    cout << "Срок погашения ссуды: " << loanTerm << " месяц" << endl;
                    break;
                }
            }
        }
    }

    //метод для получения ссуды игроком-ботом
    void takeLoanBot(int Month)
    {
        if ((Fabric > 0 || Autofabric > 0) && Status == false)
        {
            if (Capital >= 1000 && Capital <= 5000)
            {
                loans = rand() % ((Fabric * 5000 + Autofabric * 10000) / 2);
                Capital += loans;
                loanTerm = Month + 12;
                //cout << "Игроку " << ID << "Выдана ссуда в размере " << loans << endl;
                //cout << "Срок погашения ссуды: " << loanTerm << " месяц" << endl;
            }
            else
                return;
                //cout << "Игрок " << ID << " решил не брать ссуду!" << endl;
        }
    }

    //метод для строительства фабрики игроком-человеком
    void BuildFabricHuman(int Month)
    {
        if ((Fabric+Autofabric)>=6||Capital<=2500|| (MonthBFabric&& MonthBAutofabric&& MonthMAutofabric))
        {
            cout << "Операции с фабриками или автофабриками недоступны!" << endl;
        }
        else
        {
            bool flag = true;
            while (flag)
            {
                cout << "Введите код операции: 1 - строительство обычной фабрики, 2 - строительство автоматизированной фабрики, 3 - модернизация, 0 - выход из меню" << endl;
                cout << "Не забудьте об оплате ежемесячных платежей и ссуды!" << endl;
                PlayerInfo();
                cout <<"Стоимость строительства фабрики 5000, автофабрики 10000, модернизации фабрики 7000" << endl;
                cout << "Сроки ввода: фабрики - 5 мес, автофабрики - 7 мес, модернизации фабрики - 9 мес. Половина стоимости оплачивается сразу, половина - при вводе в эксплуатацию" << endl;
                cout << "Нельзя иметь больше 6 фабрик всего, а также строить и модернизировать фабрики, пока предыдущие фабрики такого же типа не построились или не были модернизированы" << endl;
                int userchoice;
                cin >> userchoice;
                switch (userchoice)
                {
                case 1:
                    if (MonthBFabric)
                    {
                        cout << "У Вас запущено строительство новой фабрики! Пока не завершится строительство, новую строить нельзя!" << endl;
                        break;
                    }
                    else
                    {
                        if (Capital >= 2500)
                        {
                            Capital -= 2500;
                            MonthBFabric = Month + 5;
                            cout << "Игрок " << ID << " построил фабрику, срок ввода - " << MonthBFabric << " месяц" << endl;
                            flag = false;
                            break;
                        }
                        else
                            cout << "Недостаточно средств!" << endl;
                        flag = false;
                        break;
                    }
                case 2:
                    if (MonthBAutofabric)
                    {
                        cout << "У Вас запущено строительство новой автофабрики! Пока не завершится строительство, новую строить нельзя!" << endl;
                        break;
                    }
                    else
                    {
                        if (Capital >= 5000)
                        {
                            Capital -= 5000;
                            MonthBAutofabric = Month + 7;
                            cout << "Игрок " << ID << " построил автофабрику, срок ввода - " << MonthBAutofabric << " месяц" << endl;
                            flag = false;
                            break;
                        }
                        else
                            cout << "Недостаточно средств!" << endl;
                        flag = false;
                        break;
                    }
                case 3:
                    if (MonthMAutofabric)
                    {
                        cout << "У Вас запущена модернизация фабрики! Пока не завершится текущая модернизация, новую начинать нельзя!" << endl;
                        break;
                    }
                    else
                    {
                        if (Capital >= 3500)
                        {
                            Capital -= 3500;
                            MonthMAutofabric = Month + 9;
                            cout << "Игрок " << ID << " запустил модернизацию фабрики, срок ввода - " << MonthMAutofabric << " месяц" << endl;
                            flag = false;
                            break;
                        }
                        else
                            cout << "Недостаточно средств!" << endl;
                        flag = false;
                        break;
                    }
                case 0:
                    flag = false;
                    break;
                default:
                    cout << "Введено неверное значение! Попробуйте еще!" << endl;
                }
            }
        }
    }

    //метод для строительства фабрики игроком-ботом
    void BuildFabricBot(int Month)
    {
        if ((Fabric + Autofabric) >= 6 || Capital <= 2500|| (MonthBFabric && MonthBAutofabric && MonthMAutofabric))
        {
            //cout << "Операции с фабриками или автофабриками недоступны!" << endl;
            return;
        }
        else
        {                
            if (Capital >= 2500 && Capital < 3500)
            {
                if (MonthBFabric)
                    return;
                else
                {
                    Capital -= 2500;
                    MonthBFabric = Month + 5;
                    //cout << "Игрок " << ID << " построил фабрику, срок ввода - " << MonthBFabric << " месяц" << endl;
                }
            }
            else if (Capital >= 3500 && Capital < 5000)
            {
                if (MonthBAutofabric)
                    return;
                else
                {
                    Capital -= 3500;
                    MonthMAutofabric = Month + 9;
                    //cout << "Игрок " << ID << " запустил модернизацию фабрики, срок ввода - " << MonthMAutofabric << " месяц" << endl;
                }
            }
            else if (Capital >= 5000)
            {
                if (MonthBAutofabric)
                    return;
                else
                {
                    Capital -= 5000;
                    MonthBAutofabric = Month + 7;
                    //cout << "Игрок " << ID << " построил автофабрику, срок ввода - " << MonthBAutofabric << " месяц" << endl;
                }
            }
            else
                return;
               //cout << "Недостаточно средств!" << endl;
        }
    }

    //метод для формирования заявки на покупку ЕСМ игроком под управлением человека
    void HumanPlayerESM(bool isSenior, int ESMPrice, int ESMSale)
    {
        bool flag = true;
        if (isSenior == true)
            cout << "Поскольку Вы - старший в раунде, можно заказать максимальное количество доступных единиц ЕСМ по минимальной цене!" << endl;
        else
            cout << "У Вас нет прав старшего игрока, поэтому действуйте аккуратно!" << endl;
        while (flag)
        {
            PlayerInfo();
            cout << "Введите количество ЕСМ к покупке, нулевое значение принимается: " << endl;
            cin >> zESM;
            cout << "Введите цену за единицу ЕСМ: " << endl;
            cin >> pESM;
            if (zESM < 0 || zESM > ESMSale || pESM<ESMPrice|| zESM * pESM>Capital)
            {
                cout << "Введенные некорректные данные! Попробуйте еще!" << endl;
            } 
            else
            {
                cout << "Ваша заявка принята!" << endl;
                flag = false;
                break;
            }
        }
    }

    //метод для формирования заявки на покупку ЕСМ игроком-ботом
    void BotPlayerESM(bool isSenior, int ESMPrice, int ESMSale)
    {
        if (Status == true)
        {
            zESM = 0;
            pESM = 0;
        }
        else if (Status == false && isSenior == true)
        {
            pESM = rand() % 100 + ESMPrice;
            if (ESMSale <= Capital / pESM)
                zESM = ESMSale;
            else
                zESM = Capital / pESM;
        }
        else if (Status == false && isSenior == false)
        {
            pESM = rand() % 300+ESMPrice;
            if (ESMSale <= Capital / pESM)
                zESM = rand() % ESMSale;
        }
    }

    //метод покупки ЕСМ игроком
    void PlayerBuyESM()
    {
        if (pESM * zESM < Capital) 
        {
            Capital -= pESM * zESM;
        }
        else 
        {
            do
            {
                zESM--;
            } while (pESM * zESM >= Capital||zESM>0);
            Capital -= pESM * zESM;
        }
        cout << "Игрок " << ID << " приобрел " << zESM << " единиц ресурсов по цене " << pESM << endl;
        ESM += zESM;
        pESM = 0;
        zESM = 0;
    }

    //метод для забора всех ресурсов в случае их нехватки
    int zzESM(int ESMSale)
    {
        return zESM = ESMSale;
    }

    //метод для формирования заявки на продажу ЕГП игроком под управлением человека
    void HumanPlayerEGP(bool isSenior, int EGPPrice, int EGPBuy)
    {
        bool flag = true;
        if (isSenior == true)
            cout << "Поскольку Вы являетесь старшим в раунде, можно продать максимальное количество доступных единиц ЕГП по максимальной цене!" << endl;
        else
            cout << "У Вас нет прав старшего игрока, поэтому действуйте аккуратно!" << endl;
        while (flag)
        {
            PlayerInfo();
            cout << "Введите количество ЕГП к продаже, нулевое значение принимается: " << endl;
            cin >> zEGP;
            cout << "Введите цену за единицу ЕГП: " << endl;
            cin >> pEGP;
            if (zEGP < 0 || zEGP>EGP||zEGP > EGPBuy || pEGP>EGPPrice)
            {
                cout << "Введенные некорректные данные! Попробуйте еще!" << endl;
            }
            else
            {
                cout << "Ваша заявка принята!" << endl;
                flag = false;
                break;
            }
        }
    }

    //метод для формирования заявки на продажу ЕГП игроком-ботом
    void BotPlayerEGP(bool isSenior, int EGPPrice, int EGPBuy)
    {
        if (Status == true)
        {
            zEGP = 0;
            pEGP = 0;
        }
        else if (Status == false && isSenior == true)
        {
            pEGP = rand() % 200 + (EGPPrice-200);
            if (EGP <= EGPBuy)
                zEGP = EGP;
            else
                zEGP = EGPBuy;
        }
        else if (Status == false && isSenior == false)
        {
            pEGP = rand() % 1000 + (EGPPrice - 1000);
            if (EGP <=EGPBuy)
                zEGP = EGP;
            else
                zEGP = EGPBuy;
        }
    }

    //метод для продажи ЕГП в случае превышения лимита банка
    int zzEGP(int EGPBuy)
    {
        return zEGP = EGPBuy;
    }

    //метод продажи ЕГП игроком
    void PlayerSaleEGP(int EGPPrice)
    {
        Capital += zEGP * pEGP;
        cout << "Игрок " << ID << " продал " << zEGP << " единиц ресурсов по цене " << pEGP << endl;
        EGP -= zEGP;
        //pEGP = EGPPrice+1;
        zEGP = 0;
    }

    //метод обнуления заявок на ЕГП
    void PlayerDelzEGP()
    {
        pEGP = 0;
    }

    //метод для ввода фабрик в работу и оплаты половины стоимости при вводе
    void ChangeFabric(int Month)
    {
        if (MonthBFabric == Month)
        {
            Fabric++;
            Capital -= 2500;
            MonthBFabric = 0;
        }
        if (MonthBAutofabric == Month)
        {
            Autofabric++;
            Capital -= 5000;
            MonthBAutofabric = 0;
        }
        if (MonthMAutofabric == Month)
        {
            Autofabric++;
            Fabric--;
            Capital -= 3500;
            MonthBAutofabric = 0;
        }
    }
};

// Класс банка
class Bank 
{
private:
    int Month;//текущий месяц игры
    int playersPlus;//количество игроков с положительным балансом
    int Level;//уровень рынка (1-5)
    int ESMPrice;//текущая минимальная цена сырья
    int ESMSale;//количество ESM к продаже
    int EGPPrice;//текущая максимальная цена ЕГП
    int EGPBuy;//количество ЕГП к покупке
    int duration;  // Продолжительность игры в месяцах
    Player* players[10];  //массив игроков всего первоначально (максимум 10 игроков)
    int numPlayers;  //количество игроков первоначально
public:
    //конструктор банка по умолчанию
    //Bank() : Month(0), playersPlus(0), Level(2), ESMPrice(0), ESMSale(0), EGPPrice(0), EGPBuy(0), duration(12), numPlayers(0) {}

    //конструктор банка с параметром продолжительности игры
    Bank(int duration) : Month(0), playersPlus(0), Level(2), ESMPrice(0), ESMSale(0), EGPPrice(0), EGPBuy(0), duration(12), numPlayers(0) 
    {
        this->duration = duration;
    }

    //метод для добавления игрока в массив игроков в начале игры
    void addPlayer(Player* player) 
    {
        if (numPlayers < 10) 
        {
            players[numPlayers++] = player;
        }
    }

    //метод для обновления цен и доступных к покупке ЕСМ и продаже ЕГП следующего уровня
    void updatePrices() 
    {
        switch (Level) 
        {
        case 1:
            ESMPrice = 800;
            ESMSale = 1.0 * playersPlus;
            EGPPrice = 6500;
            EGPBuy=3.0* playersPlus;
            break;
        case 2:
            ESMPrice = 650;
            ESMSale = 1.5 * playersPlus;
            EGPPrice = 6000;
            EGPBuy = 2.5 * playersPlus;
            break;
        case 3:
            ESMPrice = 500;
            ESMSale = 2.0 * playersPlus;
            EGPPrice = 5500;
            EGPBuy = 2.0 * playersPlus;
            break;
        case 4:
            ESMPrice = 400;
            ESMSale = 1.5 * playersPlus;
            EGPPrice = 5000;
            EGPBuy = 2.5 * playersPlus;
            break;
        case 5:
            ESMPrice = 300;
            ESMSale = 1.0 * playersPlus;
            EGPPrice = 4500;
            EGPBuy = 3.0 * playersPlus;
            break;
        }
        cout << "Минимальная цена на ЕСМ в текущем раунде: " << ESMPrice << ". ЕСМ к продаже: " << ESMSale << endl;
        cout << "Максимальная цена на ЕГП в текущем раунде: " << EGPPrice << ". ЕГП к покупке: " << EGPBuy << endl;
    }

    //метод для вычисления следующего уровня рынка
    int updateMarketLevel(int Level) 
    {
        int newLevel = 0;
        int array[5][12] = 
        {
            {1,1,1,1,2,2,2,2,3,3,4,5}, {1,1,1,2,2,2,2,3,3,3,4,5}, {1,2,2,2,3,3,3,3,4,4,4,5}, {1,2,3,3,3,4,4,4,4,5,5,5}, {1,2,3,3,4,4,4,4,5,5,5,5}
        };
        int value = rand() % 12;
        cout << "Установлен уровень: " << array[Level-1][value] << endl;
        return newLevel=array[Level-1][value];
    }

    //метод для перехода к следующему месяцу с набором игровых операций
    void nextMonth() 
    {
        Month++;
        int flag = 0;//метка для единственного игрока с плюсовым балансом
        playersPlus = playersofPlus();
        if (playersPlus == 1)
        {
            for (int i = 0; i < numPlayers; i++) 
            {
                if (players[i]->getStatus() == false)
                {
                    flag = i;
                    break;
                }
            }
            cout << "Игрок " << players[flag]->getID() << " победил!" << endl;
            finalResults();
        }
        else
        {
            Level = updateMarketLevel(Level);
            updatePrices();
            Payment();
            buyESM(isSenior(), ESMPrice, ESMSale);
            cout << "В этом раунде старший игрок: " << isSenior() << endl;
            int countESM = numPlayers;
            while (ESMSale > 0 && countESM > 0)
            {
                saleESM(isSenior());
                countESM--;
            }
            isProduct();
            buyEGP(isSenior(), EGPPrice, EGPBuy);
            int countEGP = numPlayers;
            while (EGPBuy > 0 && countEGP > 0)
            {
                saleEGP(isSenior());
                countEGP--;
            }
            for (int i = 0; i < numPlayers; i++)//цикл перебора всех игроков для обнуления заявок на продажу ЕГП
            {
                players[i]->PlayerDelzEGP();
            }
            PayLoans(Month);
            GetLoans(Month);
            BuildFabric();
            FabricTimer();
            MonthlyReport();
            system("pause");
            system("cls");
        }
    }

    //Метод оплаты ежемесячных издержек игроками
    void Payment()
    {
        for (int i = 0; i < numPlayers; i++) 
        {
            if (players[i]->getStatus() == false)
            {
                players[i]->payFixedCosts(300 * players[i]->getESM() + 500 * players[i]->getEGP() + 1000 * players[i]->getFabric() + 1500 * players[i]->getAutofabric());//ежемесячная плата
            }
            else
                cout << "Игрок " << players[i]->getID() << " банкрот!" << endl;
        }
        //cout << "Отработал метод оплаты постоянных издержек!" << endl;
    }

    //метод вычисления номера старшего игрока
    int isSenior()
    {
        int counter = Month;
        bool flag = true;
        int seniorPlayerID = 0;
        while (flag)
        {
            seniorPlayerID = counter % numPlayers;
            if (players[seniorPlayerID]->getStatus() == false)
            {
                flag = false;
                break;
            }
            else
                counter++;
        }
        //cout << "Старший в раунде игрок " << players[seniorPlayerID]->getID() << endl;
        return seniorPlayerID;
    }

    //метод сбора заявок на покупку ЕСМ
    void buyESM(int seniorPlayerID, int ESMPrice, int ESMSale)
    {
        for (int i = 0; i < numPlayers; i++)//цикл опроса игроков и сбора заявок
        {
            if (players[i]->getStatus() == false)//проверка на банкротство
            {
                bool isSenior = false;
                if (i == 0 && i == seniorPlayerID)//Игрок 0 управляется человеком и является старшим в раунде
                {
                    cout << "Игрок "<< players[i]->getID() << " сделайте заявку на покупку ЕСМ. Вы - старший в раунде"<<endl;
                    isSenior = true;
                    players[i]->HumanPlayerESM(isSenior, ESMPrice, ESMSale);
                }
                else if (i == 0&& i != seniorPlayerID)//Игрок 0 управляется человеком и не является старшим в раунде
                {
                    cout << "Игрок " << players[i]->getID() << " сделайте заявку на покупку ЕСМ. Вы - не являетесь старшим в раунде"<<endl;
                    isSenior = false;
                    players[i]->HumanPlayerESM(isSenior, ESMPrice, ESMSale);
                }
                else//для ботов
                {
                    if (i == seniorPlayerID)
                    {
                        isSenior = true;
                        players[i]->BotPlayerESM(isSenior, ESMPrice, ESMSale);
                    }
                    else
                    {
                        isSenior = false;
                        players[i]->BotPlayerESM(isSenior, ESMPrice, ESMSale);
                    }
                }
            }
            else
                cout << "Игрок " << players[i]->getID() << " банкрот!" << endl;
        }
        for (int i = 0; i < numPlayers; i++)//цикл публикации всех заявок на ЕСМ
        {
            if (players[i]->getStatus() == false)
            {
                cout << "Заявка игрока " << players[i]->getID() << " " << players[i]->getzESM() << " единиц ЕСМ, цена " << players[i]->getpESM() << endl;
            }
            else
                cout << "Игрок " << players[i]->getID() << " банкрот!" << endl;
        } 
    }

    //метод выбора заявок на покупку ЕСМ банком
    void saleESM(int seniorPlayerID)
    {
        int MaxPrice = players[0]->getpESM();
        int index = 0;//переменная, хранящая номер игрока
        for (int i = 0; i < numPlayers; i++)//цикл перебора всех игроков
        {
            if (players[i]->getStatus() == false)//проверка на банкрот
            {
                if (players[i]->getpESM() > MaxPrice) 
                {
                    MaxPrice = players[i]->getpESM();
                    index = i;
                }
                    
                if (MaxPrice == players[seniorPlayerID]->getpESM())
                {
                    MaxPrice = players[seniorPlayerID]->getpESM();
                    index = seniorPlayerID;
                }
            }
            else
                cout << "Игрок " << players[i]->getID() << " банкрот!" << endl;//игрок банкрот
        }
        if (ESMSale> players[index]->getzESM())
        {
            ESMSale = ESMSale - players[index]->getzESM();
            players[index]->PlayerBuyESM();
        }
        else
        {
            players[index]->zzESM(ESMSale);
            ESMSale = ESMSale - players[index]->getzESM();
            players[index]->PlayerBuyESM();
        }
        //cout << "Отработал метод выбора заявок на покупку ЕСМ!" << endl;
    }

    //метод формирования данных о переработке ЕСМ в ЕГП
    void isProduct()
    {
        for (int i = 0; i < numPlayers; i++)//цикл перебора всех игроков для сбора данных о строительстве или модернизации фабрик
        {
            if (players[i]->getStatus() == false)
            {
                if (i == 0)
                    players[i]->produceEGPHuman();//для игрока-человека
                else
                    players[i]->produceEGPBot();//для игрока-бота
            }
            else
                cout << "Игрок " << players[i]->getID() << " банкрот!" << endl;
        }
        //cout << "Отработал метод данных о переработке ЕСМ в ЕГП!" << endl;
    }

    //метод сбора заявок на продажу ЕГП банком
    void buyEGP(int seniorPlayerID, int EGPPrice, int EGPBuy)
    {
        for (int i = 0; i < numPlayers; i++)//цикл опроса игроков и сбора заявок
        {
            if (players[i]->getStatus() == false)//проверка на банкротство
            {
                bool isSenior = false;
                if (i == 0 && i == seniorPlayerID)//Игрок 0 управляется человеком и является старшим в раунде
                {
                    cout << "Игрок " << players[i]->getID() << " сделайте заявку на продажу ЕГП. Вы - старший в раунде" << endl;
                    isSenior = true;
                    players[i]->HumanPlayerEGP(isSenior, EGPPrice, EGPBuy);
                }
                else if (i == 0 && i != seniorPlayerID)//Игрок 0 управляется человеком и не является старшим в раунде
                {
                    cout << "Игрок " << players[i]->getID() << " сделайте заявку на продажу ЕГП. Вы - не являетесь старшим в раунде" << endl;
                    isSenior = false;
                    players[i]->HumanPlayerEGP(isSenior, EGPPrice, EGPBuy);
                }
                else//для ботов
                {
                    if (i == seniorPlayerID)
                    {
                        isSenior = true;
                        players[i]->BotPlayerEGP(isSenior, EGPPrice, EGPBuy);
                    }
                    else
                    {
                        isSenior = false;
                        players[i]->BotPlayerEGP(isSenior, EGPPrice, EGPBuy);
                    }
                }
            }
            else
                cout << "Игрок " << players[i]->getID() << " банкрот!" << endl;
        }
        for (int i = 0; i < numPlayers; i++)//цикл публикации всех заявок на ЕГП
        {
            if (players[i]->getStatus() == false)
            {
                cout << "Заявка игрока " << players[i]->getID() << " " << players[i]->getzEGP() << " единиц ЕГП, цена " << players[i]->getpEGP() << endl;
            }
            else
                cout << "Игрок " << players[i]->getID() << " банкрот!" << endl;
        }
    }

    //метод выбора заявок на продажу ЕГП игроками
    void saleEGP(int seniorPlayerID)
    {
        int MinPrice = players[0]->getpEGP();
        int index = 0;//переменная, хранящая номер игрока
        for (int i = 0; i < numPlayers; i++)//цикл перебора всех игроков
        {
            if (players[i]->getStatus() == false)//проверка на банкрот
            {
                if (players[i]->getpEGP() < MinPrice)
                {
                    MinPrice = players[i]->getpEGP();
                    index = i;
                }

                if (MinPrice == players[seniorPlayerID]->getpEGP())
                {
                    MinPrice = players[seniorPlayerID]->getpEGP();
                    index = seniorPlayerID;
                }
            }
            else
                cout << "Игрок " << players[i]->getID() << " банкрот!" << endl;//игрок банкрот
        }
        if (EGPBuy > players[index]->getzEGP())
        {
            EGPBuy = EGPBuy - players[index]->getzEGP();
            players[index]->PlayerSaleEGP(EGPPrice);
        }
        else
        {
            players[index]->zzEGP(EGPBuy);
            EGPBuy =EGPBuy - players[index]->getzEGP();
            players[index]->PlayerSaleEGP(EGPPrice);
        }
        
    }

    //метод погашения ссуды и ссудного процента
    void PayLoans(int Month)
    {
        for (int i = 0; i < numPlayers; i++)
        {
            if (players[i]->getStatus() == false)
            {
                if (players[i]->getLoans() == 0)//проверка условия наличия ссуды
                    return;
                    //cout << "У игрока " << players[i]->getID() << " нет непогашенных ссуд" << endl;
                else if (players[i]->getLoans() > 0 && players[i]->getLoanTerm() > Month)//если ссуда есть, но срок оплаты не вышел
                    players[i]->payLoanInterest();//уплата процентов
                else if (players[i]->getLoans() > 0 && players[i]->getLoanTerm() == Month)//если ссуда есть и месяц оплаты наступил
                {
                    players[i]->payLoanInterest();//уплата процентов
                    players[i]->repayLoans();//уплата основной суммы ссуды
                }
            }
            else
                cout << "Игрок " << players[i]->getID() << " банкрот!" << endl; 
        }
    }

    //метод выдачи ссуды
    void GetLoans(int Month)
    {
        for (int i = 0; i < numPlayers; i++)//перебор игроков
        {
            if (players[i]->getStatus() == false)//проверка банкротства
            {
                if (players[i]->getLoans() == 0)//проверка отсутствия неуплаченной ссуды
                {
                    if (players[i]->getID() == 0)
                    {
                        players[i]->takeLoanHuman(Month);
                    }
                    else
                        players[i]->takeLoanBot(Month);
                }
                else
                    return;
                    //cout << "Больше одной ссуды не выдается!" << endl;
            }
            else
                cout << "Игрок " << players[i]->getID() << " банкрот!" << endl;
        }
    }

    //метод для сбора заявок на строительство и модернизацию фабрик игроками
    void BuildFabric()
    {
        for (int i = 0; i < numPlayers; i++)//перебор игроков
        {
            if (players[i]->getStatus() == false)//проверка банкротства
            {
                if (players[i]->getID() == 0)
                {
                    players[i]->BuildFabricHuman(Month);
                }
                else
                    players[i]->BuildFabricBot(Month);
            }
            else
                cout << "Игрок " << players[i]->getID() << " банкрот!" << endl;
        }
    }

    //метод для контроля сроков ввода фабрик в эксплуатацию и принуждения игроков к оплате стоимости
    void FabricTimer()
    {
        for (int i = 0; i < numPlayers; i++)//перебор игроков
        {
            if (players[i]->getStatus() == false)//проверка банкротства
            {
                if (players[i]->getMonthBFabric() == Month|| players[i]->getMonthBAutofabric() == Month|| players[i]->getMonthMAutofabric() == Month)
                {
                    players[i]->ChangeFabric(Month);
                }
            }
            else
                cout << "Игрок " << players[i]->getID() << " банкрот!" << endl;
        }
    }

    //метод для генерации ежемесячного отчёта
    void MonthlyReport() 
    {
        cout << "Месячный отчет - Месяц " << Month << endl;
        for (int i = 0; i < numPlayers; i++) 
        {
            cout << "Игрок: " << players[i]->getID() << ": "
                << "Капитал: " << players[i]->getCapital() << ", "
                << "ЕСМ: " << players[i]->getESM() << ", "
                << "ЕГП: " << players[i]->getEGP() << ", "
                << "Ссуда: " << players[i]->getLoans() << ","
                << "Срок погашения ссуды: " << players[i]->getLoanTerm() << ","
                << "Фабрик: " << players[i]->getFabric() << ","
                << "Автофабрик: " << players[i]->getAutofabric() << ","
                << "Срок ввода фабрики в работу: " << players[i]->getMonthBFabric() << ","
                << "Срок ввода автофабрики в работу: " << players[i]->getMonthBAutofabric() << ","
                << "Срок ввода автофабрики в работу после модернизации: " << players[i]->getMonthMAutofabric() << endl;
        }
    }

    // Метод для подсчёта итоговых результатов
    void finalResults() 
    { 
        cout << "Итоговый результат: " << endl;
        for (int i = 0; i < numPlayers; i++) 
        {
            if (players[i]->getStatus() == true) 
            {
                cout << "Игрок " << players[i]->getID() << " банкрот!" << endl;
            }
            else
            {
                int TotalCapital = players[i]->getCapital() + players[i]->getESM() * ESMPrice + players[i]->getEGP() * EGPPrice + players[i]->getFabric() * 5000 + players[i]->getAutofabric() * 10000 - players[i]->getLoans();
                cout << "Игрок " << players[i]->getID() << " капитал: " << TotalCapital << endl;
            }
        }
    }

    // Метод для запуска игры
    void startGame() 
    {
        for (int month = 0; month <= duration; month++) 
        {
            cout << "Месяц " << month << endl;
            nextMonth();
        }
        finalResults();
    }
   
    //Метод вычисления живых игроков
    int playersofPlus()
    {
        int count = 0;
        for (int i = 0; i < numPlayers; i++) 
        {
            if (players[i]->getStatus() == false)
            count++;
        }
        //cout << "Отработал метод поиска <живых> игроков " << endl;
        return count;
    }
};

int main() {
    system("chcp 1251>NUL");
    srand(time(NULL));
    int numPlayers;
    int duration;
    bool flag = true;
    while (flag)
    {
        cout << "Введите количество игроков (игрой предусмотрено не более 10): " << endl;
        cin >> numPlayers;
        if (numPlayers < 2 || numPlayers>10)
            cout << "Введено некорректное значение игроков! Попробуйте еще!" << endl;
        else
        {
            flag = false;
            break;
        }
    }
    //по умолчанию продолжительность игры 12 месяцев
    cout << "Введите продолжительность игры в месяцах: " << endl;
    cin >> duration;
    Bank bank(duration);
    for (int i = 0; i < numPlayers; i++) {
        bank.addPlayer(new Player(i));
    }
    bank.startGame();
    return 0;
}