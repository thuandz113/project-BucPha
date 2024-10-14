#pragma once

#include <iostream>
#include <string>
using namespace std;
class UserAccount
{
    private:
        int roles, credits;//0 : khách hàng bth, 1: nhân viên , 2: quản lý
        string password, username;
    public:
        UserAccount(string username, string password, int roles , int credits)
        {
            this->roles = roles;
            this->credits = credits;
            this->username = username;
            this->password = password;
        }
        //nạp tiền , trừ tiền.
        string getUsername(){ return username; }
        int getCredits(){ return credits; }
        void accountDeposit(int credits)
        {
            this->credits += credits;
        }        
};