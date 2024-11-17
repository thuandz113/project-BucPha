#pragma once

#include <iostream>
#include <string>
using namespace std;
class UserAccount
{
    private:
        int roles, credits, sex;//0 : khách hàng bth, 1: nhân viên , 2: quản lý
        string password, username,number,address;
    public:
        UserAccount(string username, string password, int roles , int credits, int sex, string number, string address)
        {
            this->roles = roles;
            this->credits = credits;
            this->username = username;
            this->password = password;
            this->sex = sex;
            this->number = number;
            this->address = address;
        }
        string getUsername() const { return username; }
        string getPassword() const { return password; }
        int getRoles() const { return roles; }
        int getCredits() const { return credits; }
        int getSex() const { return sex; }
        string getNumber() const { return number; }
        string getAddress() const { return address; }
        void accountDeposit(int credits)
        {
            this->credits += credits;
        }
        void setAttributes(string newUsername, string newPassword, int newRoles, int newCredits, int newSex, string newNumber, string newAddress) {
            username = newUsername;
            password = newPassword;
            roles = newRoles;
            credits = newCredits;
            sex = newSex;
            number = newNumber;
            address = newAddress;
        }
        void setUsername(const string& newUsername) {
            username = newUsername;
        }

     

        
};