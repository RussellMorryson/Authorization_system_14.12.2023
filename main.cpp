#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool LoginIsOk(string login) {
    string symbols = ".,:;!?^%$#@`~()[]{}-_=+|/*-+\'\"";
    string numbers = "0123456789";

    for (char a: login) {
        for(char b : symbols) { if (a == b) { return false; } }
        for(char c : numbers) { if (a == c) { return false; } }
    }
    return true;    
}

bool CheckLogPass(string login, string password) {
    ifstream file;
    file.open("Info.txt", ios_base::in);
    string line;
    int log, pass;
    while(getline(file, line)) {
        log = line.find(login);
        pass = line.find(password);
        if (log != -1 && pass != -1) { return true; }
    }
    return false;
}

int main() {   
    string login = "";
    string password = "";
    string line = "";
    int choice = 0;
    int repeat = 0;
    while(true) {
        cout << "#############################################################" << endl;
        cout << "#   Программа для авторизации и регистрации пользователей   #" << endl;
        cout << "#############################################################" << endl;
        cout << "#                      Выберите пункт!                      #" << endl;
        cout << "# [1] Войти в аккаунт                                       #" << endl;
        cout << "# [2] Создать аккаунт                                       #" << endl;
        cout << "#############################################################" << endl;
        
        cin >> choice;
        
        if (choice == '1' || choice == 1) {
            repeat = 0;
            while(repeat < 3) {
                cout << "Выбрано: вход в аккаунт" << endl;
                cout << "Введите логин: ";
                cin >> login;
                cout << "Введите пароль: ";
                cin >> password;
                if (CheckLogPass(login, password)) { cout << "Выполнен вход в аккаунт!" << endl; break; } 
                else { cout << "Логин или пароль указан неверно! Повторите попытку!\n" << endl; }
                repeat +=1;
            }            
        } else if (choice == '2' || choice == 2) {
            ofstream fout;
            cout << "Выбрано: создание аккаунта" << endl;
            while(true) { 
                login = "";
                cout << "Введите новый логин: ";
                cin >> login;
                if (LoginIsOk(login)) { break; } 
                else{ cout << "Имя пользователя: " + login + " - имеет недопустимые символы. Повторите попытку!\n" << endl; }
            }
            while(true) {
                password = "";
                cout << "Введите пароль: ";
                cin >> password;
                if (password.length() < 8) { cout << "Пароль состоит менее чем 8 символов. Повторите попытку!\n" << endl; } 
                else { break; }
            } 
            fout.open("Info.txt", ios_base::app);
            fout << login << ';' << password << '\n';
            cout << "Пользователь создан!" << endl;
            fout.close();
        } else { cout << "Некорректный ввод, повторите попытку!" << endl; }
    }
    return 0;
}