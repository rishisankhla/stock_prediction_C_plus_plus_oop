#include "mainadvisorbot.h" //importing all the dependencies
#include <iostream>
#include <string>
#include <utility>
#include <iterator>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include "CSVReader.h"
#include "OrderBookEntry.h"

//building the constructor function
mainadvisorbot::mainadvisorbot(int my_order)
{
	x = my_order;
    currentTime = orderBook.getEarliestTime(); //setting the current time
    our_c = our_c + 1;
    our_time_step_data[our_c] = currentTime; //adding the current time to our record list

}

//writing the main execution function
void mainadvisorbot::print_menu()
{
    // main loop for statistically analysis functions
    while(true)
    {
        std::cout << "type your command" << std::endl;
        
        std::string line;
        std::getline(std::cin, line);  //getting the string input from user

        //creating variable list to check the input entered by user
        std::string input_final_1 = "prod";
        std::string input_final_2 = "help";
        std::string input_final_3 = "help avg";
        std::string input_final_4 = "help min";
        std::string input_final_5 = "help max";
        std::string input_final_6 = "help time";
        std::string input_final_7 = "help step";
        std::string input_final_8 = "help prod";
        std::string input_final_9 = "help variance";
        std::string input_final_10 = "time";
        std::string input_final_11 = "step";
        std::string input_final_12 = "help predict";

        // command for prod
        if (line == input_final_1)
        {
            std::string in_str = "";
            std::vector<std::string> our_prods = orderBook.getKnownProducts(); //getting all the unique product list
            int match_size = our_prods.size();
            int c=1;

            // creating a single string for our produt list
            for (std::string const& p : our_prods)
            {
                std::string mid(",");
                in_str = in_str + p;
                if (c != match_size)
                {
                    in_str = in_str + mid;
                }
                c = c + 1;
            }
            std::cout << in_str << std::endl;
        }

        // command for help
        else if (line == input_final_2)
        {
            std::cout << "The available commands are help, help <cmd>, prod, avg, variance, predict, min, max, step, time" << std::endl;
        }

        // command for help avg
        else if (line == input_final_3)
        {
            std::cout << "avg ETH/BTC bid 10 -> average ETH/BTC bid over last 10 time steps" << std::endl;
        }

        // command for help min
        else if (line == input_final_4)
        {
            std::cout << "min ETH/BTC ask -> minimum ask for ETH/BTC in current time step" << std::endl;
        }

        // command for help max
        else if (line == input_final_5)
        {
            std::cout << "max ETH/BTC ask -> maximum ask for ETH/BTC in current time step" << std::endl;
        }

        // command for help time
        else if (line == input_final_6)
        {
            std::cout << "time -> it will show the current time step like  2020/03/17 17:01:24" << std::endl;
        }

        // command for help step
        else if (line == input_final_7)
        {
            std::cout << "step -> it will shift the current time step to next step and will show the output like now at 2020/03/17 17:01:30" << std::endl;
        }

        // command for help prod
        else if (line == input_final_8)
        {
            std::cout << "prod -> will list all the products like BTC/USDT,DOGE/BTC,DOGE/USDT,ETH/BTC,ETH/USDT" << std::endl;
        }

        // command for help variance
        else if (line == input_final_9)
        {
            std::cout << "variance ETH/BTC bid 10 -> variance ETH/BTC bid over last 10 time steps" << std::endl;
        }

        // command for help predict
        else if (line == input_final_12)
        {
            std::cout << "predict max ETH/BTC ask -> predict the max ETH/BTC ask in next time step" << std::endl;
        }

        // command for time
        else if (line == input_final_10)
        {
            std::cout << currentTime << std::endl;
        }

        // command for step
        else if (line == input_final_11)
        {
            currentTime = orderBook.getNextTime(currentTime); //shifting to next time step
            our_c = our_c + 1;
            our_time_step_data[our_c] = currentTime;
            std::cout << "now at " << currentTime << std::endl; //and the time step to our record list
        }

        //in else part I have written the code for Stats functions
        else 
        {
            std::vector<std::string> tokens = CSVReader::tokenise(line, ' '); //extracting the input string entered by user, through tokenise function
            
            //creating variable list to check the input entered by user
            std::string our_min("min");
            std::string our_max("max");
            std::string our_avg("avg");
            std::string our_variance("variance");
            std::string our_ask("ask");
            std::string our_bid("bid");
            std::string our_predict("predict");

            //command for min
            if (tokens[0] == our_min)
            {
                std::vector<OrderBookEntry> entries;

                //extracting the entries according to user input
                if (tokens[2] == our_ask)
                {
                    entries = orderBook.getOrders(OrderBookType::ask, tokens[1], currentTime);
                }
                else if (tokens[2] == our_bid)
                {
                    entries = orderBook.getOrders(OrderBookType::bid, tokens[1], currentTime);
                }

                //finding the minimum value
                double min = entries[0].price;
                for (OrderBookEntry& e : entries)
                {
                    if (e.price < min)min = e.price;
                }
                std::cout << "The min " << tokens[2] << " for " << tokens[1] << " is " << min << std::endl;
            }

            //command for max
            else if (tokens[0] == our_max)
            {
                std::vector<OrderBookEntry> entries;

                //extracting the entries according to user input
                if (tokens[2] == our_ask)
                {
                    entries = orderBook.getOrders(OrderBookType::ask, tokens[1], currentTime);
                }
                else if (tokens[2] == our_bid)
                {
                    entries = orderBook.getOrders(OrderBookType::bid, tokens[1], currentTime);
                }

                //finding the maximum value
                double max = entries[0].price;
                for (OrderBookEntry& e : entries)
                {
                    if (e.price > max)max = e.price;
                }
                std::cout << "The max " << tokens[2] << " for " << tokens[1] << " is " << max << std::endl;
            }

            //command for avg
            else if (tokens[0] == our_avg)
            {
                if ((std::stoi(tokens[3])<= our_time_step_data.size()) && (std::stoi(tokens[3])>=1))
                {
                    std::vector<OrderBookEntry> full_entries;
                    int common_c = 1;
                    std::map<int, std::string>::reverse_iterator it;

                    //filtering the number of time steps according to user input
                    for (it = our_time_step_data.rbegin(); it != our_time_step_data.rend(); it++)
                    {
                        std::vector<OrderBookEntry> entries;

                        //extracting the entries according to user input
                        if (tokens[2] == our_ask)
                        {
                            entries = orderBook.getOrders(OrderBookType::ask, tokens[1], it->second);
                        }
                        else if (tokens[2] == our_bid)
                        {
                            entries = orderBook.getOrders(OrderBookType::bid, tokens[1], it->second);
                        }
                        full_entries.insert(full_entries.end(), entries.begin(), entries.end());
                        if (common_c == std::stoi(tokens[3]))
                        {
                            break;
                        }
                        common_c = common_c + 1;
                    }

                    //calculating the average value
                    double our_final_avg = 0;
                    for (OrderBookEntry& e : full_entries)
                    {
                        our_final_avg = our_final_avg + e.price;
                    }
                    our_final_avg = our_final_avg / full_entries.size();
                    std::cout << "The average " << tokens[1] << " " << tokens[2] << " price over last " << tokens[3] << " timesteps was " << our_final_avg << std::endl;
                }

                //if user input is not appropriate then else part will be executed
                else
                {
                    std::cout << "Please enter valid time step number" << std::endl;
                }
            }

            // Task 2: own command for variance
            else if (tokens[0] == our_variance)
            {
                if ((std::stoi(tokens[3]) <= our_time_step_data.size()) && (std::stoi(tokens[3]) >= 1))
                {
                    std::vector<OrderBookEntry> full_entries;
                    int common_c = 1;
                    std::map<int, std::string>::reverse_iterator it;

                    //filtering the number of time steps according to user input
                    for (it = our_time_step_data.rbegin(); it != our_time_step_data.rend(); it++)
                    {
                        std::vector<OrderBookEntry> entries;

                        //extracting the entries according to user input
                        if (tokens[2] == our_ask)
                        {
                            entries = orderBook.getOrders(OrderBookType::ask, tokens[1], it->second);
                        }
                        else if (tokens[2] == our_bid)
                        {
                            entries = orderBook.getOrders(OrderBookType::bid, tokens[1], it->second);
                        }
                        full_entries.insert(full_entries.end(), entries.begin(), entries.end());
                        if (common_c == std::stoi(tokens[3]))
                        {
                            break;
                        }
                        common_c = common_c + 1;
                    }

                    //calculating the average value
                    unsigned int n_item = full_entries.size();
                    double our_avg = 0.0;
                    double power = 0.0;
                    double sum = 0.0;
                    for (OrderBookEntry& e : full_entries)
                    {
                        our_avg += e.price;
                    }
                    double our_total = our_avg / n_item;

                    //calculating the variance value
                    for (OrderBookEntry& e : full_entries)
                    {
                        power = std::pow((e.price - our_total), 2);
                        sum += power;
                    }
                    double final_result = sum / n_item;
                    std::cout << "The variance " << tokens[1] << " " << tokens[2] << " price over last " << tokens[3] << " timesteps was " << final_result << std::endl;
                }

                //if user input is not appropriate then else part will be executed
                else
                {
                    std::cout << "Please enter valid time step number" << std::endl;
                }
            }

            //command for predict
            else if (tokens[0] == our_predict)
            {
                //filtering the entry according to max
                if (tokens[1] == our_max)
                {
                    std::vector<OrderBookEntry> entries;
                    std::vector<int> n_entries;

                    //extracting the entries according to user input
                    if (tokens[3] == our_ask)
                    {
                        entries = orderBook.getOrders(OrderBookType::ask, tokens[2], orderBook.getNextTime(currentTime));
                    }
                    else if (tokens[3] == our_bid)
                    {
                        entries = orderBook.getOrders(OrderBookType::bid, tokens[2], orderBook.getNextTime(currentTime));
                    }
                    int c1 = 0;
                    for (OrderBookEntry& e : entries)
                    {
                        n_entries.push_back(c1);
                        c1 = c1 + 1;
                        
                    }

                    //initialising variables for liner regression
                    double n = n_entries.size();
                    double m_x = 0.0;
                    double m_y = 0.0;
                    double multi_total1 = 0.0;
                    double multi_total2 = 0.0;
                    int c2 = 0;

                    //calculating our theta_0 and theta_1
                    for (OrderBookEntry& e : entries)
                    {
                        m_x = m_x + n_entries[c2];
                        m_y = m_y + e.price;
                        multi_total1 = (n_entries[c2] * e.price) + multi_total1;
                        multi_total2 = multi_total2 + (n_entries[c2] * n_entries[c2]);
                        c2 = c2 + 1;

                    }
                    m_y = m_y / n;
                    m_x = m_x / n;
                    double SS_xy = multi_total1 - (n * m_y * m_x);
                    double SS_xx = multi_total2 - (n * m_x * m_x);
                    double b_1 = SS_xy / SS_xx;
                    double b_0 = m_y - (b_1 * m_x);
                    double our_final_predict = 0.0;

                    //predicting our output using theta variables
                    if (b_1 >= 0)
                    {
                        our_final_predict = b_0 + (b_1 * (n - 1));
                    }
                    else
                    {
                        our_final_predict = b_0 + (b_1 * 0);
                    }
                    std::cout << "The max " << tokens[3] << " for " << tokens[2] << " might be " << our_final_predict << std::endl;
                }

                //filtering the entry according to min
                else if (tokens[1] == our_min)
                {
                    std::vector<OrderBookEntry> entries;
                    std::vector<int> n_entries;

                    //extracting the entries according to user input
                    if (tokens[3] == our_ask)
                    {
                        entries = orderBook.getOrders(OrderBookType::ask, tokens[2], orderBook.getNextTime(currentTime));
                    }
                    else if (tokens[3] == our_bid)
                    {
                        entries = orderBook.getOrders(OrderBookType::bid, tokens[2], orderBook.getNextTime(currentTime));
                    }
                    int c1 = 0;
                    for (OrderBookEntry& e : entries)
                    {
                        n_entries.push_back(c1);
                        c1 = c1 + 1;

                    }

                    //initialising variables for liner regression
                    double n = n_entries.size();
                    double m_x = 0.0;
                    double m_y = 0.0;
                    double multi_total1 = 0.0;
                    double multi_total2 = 0.0;
                    int c2 = 0;

                    //calculating our theta_0 and theta_1
                    for (OrderBookEntry& e : entries)
                    {
                        m_x = m_x + n_entries[c2];
                        m_y = m_y + e.price;
                        multi_total1 = (n_entries[c2] * e.price) + multi_total1;
                        multi_total2 = multi_total2 + (n_entries[c2] * n_entries[c2]);
                        c2 = c2 + 1;

                    }
                    m_y = m_y / n;
                    m_x = m_x / n;
                    double SS_xy = multi_total1 - (n * m_y * m_x);
                    double SS_xx = multi_total2 - (n * m_x * m_x);
                    double b_1 = SS_xy / SS_xx;
                    double b_0 = m_y - (b_1 * m_x);
                    double our_final_predict = 0.0;

                    //predicting our output using theta variables
                    if (b_1 <= 0)
                    {
                        our_final_predict = b_0 + (b_1 * (n - 1));
                    }
                    else
                    {
                        our_final_predict = b_0 + (b_1 * 0);
                    }
                    std::cout << "The min " << tokens[3] << " for " << tokens[2] << " might be " << our_final_predict << std::endl;
                }
            }

            //if user input is not appropriate then else part will be executed
            else
            {
                std::cout << "Please enter a valid command" << std::endl;
            }
        }
    }
}


