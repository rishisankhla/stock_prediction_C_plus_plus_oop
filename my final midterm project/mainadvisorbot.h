#pragma once

#include <string> //importing all the dependencies
#include <map>
#include <iostream>
#include "OrderBook.h"

// our main mainadvisorbot class
class mainadvisorbot
{
    //public variable and functions
    public:
        int x;
        mainadvisorbot(int my_order); //constructor function
        void print_menu(); //main execution function
        OrderBook orderBook{ "20200601.csv" }; //variable to store our csv file

    //private variable and functions
    private:
        std::map<int,std::string> our_time_step_data;
        int our_c = 0;
        std::string currentTime;
};
