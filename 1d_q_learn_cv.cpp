#include <iostream>
#include <map>
#include <vector>
#include <thread>   //wait
#include <chrono>   //wait
#include <stdlib.h> //rsrand, rand
#include <time.h>   //random


//#include "opencv2/opencv.hpp"
//========================================================================================

int N_STATES = 6;      //number of states
double EPSILON = 0.9;   // greedy policy
double ALPHA = 0.1;     //learning rate
double GAMMA = 0.9;     //discount factor
int MAX_EPISODES = 15; //number of episodes the agent is going to play
int REFRESH_RATE = 20; //time for one move

std::string a_left = "left";
std::string a_right = "right";
std::vector<std::string> ACTIONS{"left", "right"};
//std::string rl_action;

std::vector<std::pair<double, double>> q_table;
std::vector<std::pair<double, double>> q_table_main;

//========================================================================================

auto Choose_Action(int state, std::vector<std::pair<double, double>> q_table)
{

    std::string action{};
    double value_state_1 = q_table[state].first;
    double value_state_2 = q_table[state].second;

    double rand_value = ((double)rand() / (RAND_MAX));

    std::cout << "rand value :: " << rand_value << std::endl;

    if ((rand_value > EPSILON) || ((value_state_1 == 0) && (value_state_2 == 0)))
    {
        std::cout << "choosing random, Exploration ... " << std::endl;
        if ((double)rand() / RAND_MAX >= 0.5)
        {
            action = "left";
        }
        else
        {
            action = "right";
        }
    }
    else
    {
        std::cout << " follow the Explotation policy..." << std::endl;
        if (value_state_1 >= value_state_2)
        {
            action = "left"; //q_table[state].first;
        }
        else
        {
            action = "right"; //q_table[state].first;
        }
    }

    return action;
}

//========================================================================================

void Update_Env(int state, int episode, int step_counter)
{

    //std::cout << "your current state ::" << state << std::endl;

    std::vector<std::string> env_temp;

    for (int i = 0; i < N_STATES - 1; i++)
    {
        env_temp.push_back("-");
    }
    env_temp.push_back("T");
    env_temp[state] = "o";

    std::cout << "-----------" << std::endl;
    for (auto &j : env_temp)
    {

        std::cout << j;
    }
    std::cout << "\n-----------" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(REFRESH_RATE));
}
//========================================================================================
// void Update_Env_cv(int _state){

// cv::Mat img(200, 1400, CV_8UC3);
// img.setTo(0);

// CvScalar robot = CV_RGB(0,0,255);
// CvScalar terminal = CV_RGB(255,0,0);

// int y1 = 10;
// int y2 = 100;
// int step = 110;
// int state =4;

// for (int i = 0; i<N_STATES; i++){

//     //y1 = y1 + i*y1;
//     //y2 = y2 + i*y2;
    

// //cv::rectangle(img, cv::Rect(y1, y1, y2, y2), CV_RGB(255, 0, 0), -100);
// if ((i+1)==N_STATES){
// cv::rectangle(img, cv::Rect(y1 + step*i, y1, y2, y2), terminal, -100);}

// if (i == state){
// cv::rectangle(img, cv::Rect(y1 + step*i, y1, y2, y2), robot, -100);}

// else{
//  cv::rectangle(img, cv::Rect(y1 + step*i, y1, y2, y2), CV_RGB(0,0,255), 3);   
// }

// }

 


// cv::imshow("show000000", img);


// }



//========================================================================================

//std::vector<std::pair<std::string, double>> Build_Q_Table(int n_states) //, std::vector<std::string> actions)
auto Build_Q_Table(int n_states)
{
    //std::vector<std::vector<std::pair<std::string, double>>> q_tab;
    std::vector<std::pair<double, double>> q_tab;

    for (int i = 0; i < n_states; i++)
    {
        //temp_map.insert(i, std::make_pair)
        //temp_vector.push_back(std::make_pair("left", 0.0));
        q_tab.push_back(std::make_pair(0.0, 0.0));
        //q_tab.push_back(temp_vector);
    }

    int state{0};
    for (auto &i : q_tab)
    {

        std::cout << " state :: " << state << " left :: " << i.first << " right :: " << i.second << std::endl;
        state++;
    }

    return q_tab;
}

//========================================================================================

auto Get_Env_Feedback(int state, std::string action)
{

    std::string terminal{};
    int next_state{};
    int reward{};
    std::vector<int> return_vector{};

    if (action == "right")
    {
        if (state == (N_STATES - 2))
        {
            next_state = -999; //terminal
            reward = 1;
        }
        else
        {
            next_state = state + 1;
            reward = 0;
        }
    }
    else
    {
        reward = 0;
        if (state == 0)
        {
            next_state = state;
        }
        else
        {
            next_state = state - 1;
        }
    }

    return_vector.push_back(next_state);
    return_vector.push_back(reward);

    return return_vector;
}

//========================================================================================
//std::vector<std::pair<std::string, double>>
auto Run_Rl()
{
    int state{};
    int step_counter{};
    int ijk = 0;
    bool is_terminated{};
    std::string action{};
    std::vector<int> return_vector{};
    int next_state{};
    int reward{};
    double q_target{};
    double q_predict{};
    double q_value_next_state_action{};

    q_table = Build_Q_Table(N_STATES); //, ACTIONS);

    // for (auto &i : q_table)
    // {

    //     std::cout << "state :: " << ijk << ":: left :: " << i.first << ":: right :: " << i.second << std::endl;
    //     ijk++;
    // }

    std::cout<<"check FOR Loop " << std::endl;

    for (int episode = 0; episode < MAX_EPISODES; episode++)
    {
        std::cout << " TABLE UPDATE " << std::endl;
        ijk = 0;
        for (auto &i : q_table)
        {

            std::cout << "state :: " << ijk << ":: left :: " << i.first << ":: right :: " << i.second << std::endl;
            ijk++;
        }
        //std::cin.get();
        
        std::cout << "-------------------------------------------------------------EPISODE NR ::: " << episode << std::endl;
        step_counter = 0;
        state = 0;
        is_terminated = false;
        Update_Env(state, episode, step_counter);

        while (!is_terminated)
        {

            action = Choose_Action(state, q_table);
            std::cout << "STATE :: " << state << " NEXT ACTION ::: " << action << std::endl;
            return_vector = Get_Env_Feedback(state, action);

            //==============
            // q_predict = q_table.loc[S, A]

            if (action == "left"){ q_predict = q_table[state].first;}
            if (action == "right"){ q_predict = q_table[state].second;}


            //=========

            next_state = return_vector[0];
            reward = return_vector[1];
            std::cout << "NEXT STATE ::" << next_state << "  REWARD :: " << reward << std::endl;

            // if (q_table[next_state].first >= q_table[next_state].second)
            // {
            //     q_value_next_state_action = q_table[next_state].first;
            // }
            // else
            // {
            //     q_value_next_state_action = q_table[next_state].second;
            // }
            q_value_next_state_action = std::max(q_table[next_state].first, q_table[next_state].second);
            std::cout << " q_value_next_state_action :::::: " << q_value_next_state_action << std::endl;

            if (next_state != -999) //terminal
            {

                q_target = reward + GAMMA * q_value_next_state_action;
            }
            else
            {
                q_target = reward;
                is_terminated = true;
            }

            if (action == "left")
            {
                 
                q_table[state].first = q_table[state].first + ALPHA * (q_target - q_predict);
                std::cout<<"update for state:: "<< state << " and action :: " << action << " with value :: " << q_table[state].first << std::endl;
            }

            if (action == "right")
            {
          
                q_table[state].second = q_table[state].second + ALPHA * (q_target - q_predict);
                std::cout<<"update for state:: "<< state << " and action :: " << action << " with value :: " << q_table[state].second << std::endl;
            }

            state = next_state;
            //std::cout << "next state ::" << next_state << std::endl;
            Update_Env(state, episode, step_counter + 1);
           // Update_Env_cv(state);
        }
    }

    return q_table;
}

//=======================
//      MAIN
//=======================

int main()
{
    int ij = 0;
    srand(time(NULL));
    q_table_main = Run_Rl();
    //Build_Q_Table(6);
    std::cout<< " Q table " << std::endl;
    for (auto &i : q_table_main){

            std::cout << "state :: " << ij << ":: left :: " << i.first << ":: right :: " << i.second << std::endl;
            ij++;

    }
    return 0;
}
