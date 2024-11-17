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
       
     

        
};