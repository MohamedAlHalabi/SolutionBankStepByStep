#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsString.h"

#include <string> 
#include <fstream> 
#include <vector> 

class clsBankClient : public clsPerson
{
private:
    enum enMode { EmptyMode = 0, UpdateMode = 1 };
    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;

    static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#") {
        vector<string> Client = clsString::Split(Line, Seperator);

        if (Client.size() < 7) {
            return _GetEmptyClientObject();
        }

        return clsBankClient(enMode::UpdateMode, Client[0], Client[1], Client[2], Client[3], Client[4], Client[5], stof(Client[6]));
    }

    static clsBankClient _GetEmptyClientObject() {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

public:
    clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance)
        : clsPerson(FirstName, LastName, Email, Phone) {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
    }

    bool IsEmpty() {
        return (_Mode == enMode::EmptyMode);
    }

    string GetAccountNumber() {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode) {
        _PinCode = PinCode;
    }

    string GetPinCode() {
        return _PinCode;
    }

    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float accountBalance) {
        _AccountBalance = accountBalance;
    }

    float GetAccountBalance() {
        return _AccountBalance;
    }

    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    string FullName() { return FirstName + " " + LastName; }

    void Print() {
        cout << "\n Client Card :";
        cout << "\n_____________________";
        cout << "\n First Name  :" << FirstName;
        cout << "\n Last Name   :" << LastName;
        cout << "\n Full Name   :" << FullName();
        cout << "\n Email       :" << Email;
        cout << "\n Phone       :" << Phone;
        cout << "\n Acc. Number :" << _AccountNumber;
        cout << "\n Password    :" << _PinCode;
        cout << "\n Balance     :" << _AccountBalance;
        cout << "\n_____________________\n";
    }

    static clsBankClient Find(string AccountNumber) {
        fstream FileClient;
        FileClient.open("Clients.txt", ios::in);

        if (!FileClient.is_open()) {
            return _GetEmptyClientObject();
        }

        string Line = "";
        while (getline(FileClient, Line)) {
            clsBankClient Client = _ConvertLineToClientObject(Line);
            if (Client.GetAccountNumber() == AccountNumber) {
                FileClient.close();
                return Client;
            }
        }

        FileClient.close();
        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode) {
        fstream FileClient;
        FileClient.open("Clients.txt", ios::in);

        if (!FileClient.is_open()) {
            return _GetEmptyClientObject();
        }

        string Line = "";
        while (getline(FileClient, Line)) {
            clsBankClient Client = _ConvertLineToClientObject(Line);
            if (Client.GetAccountNumber() == AccountNumber && Client.PinCode == PinCode) {
                FileClient.close();
                return Client;
            }
        }

        FileClient.close();
        return _GetEmptyClientObject();
    }
    static bool IsClientExist(string AccountNumber)
    {

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        return (!Client1.IsEmpty());
    }
};
