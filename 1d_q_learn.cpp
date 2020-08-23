#include <iostream>
#include <map>
#include <vector>
#include <thread> //wait
#include<chrono> //wait
#include<stdlib.h> //rsrand, rand
#include<time.h> //random


int N_STATES = 6;         //number of states
float EPSILON = 0.8;      // greedy policy
float ALPHA = 0.1;        //learning rate
float GAMMA = 0.9;        //discount factor
int MAX_EPISODES = 15;    //number of episodes the agent is going to play
int REFRESH_RATE = 300; //time for one move

std::string a_left = "left";
std::string a_right = "right";
std::vector<std::string> ACTIONS{"left", "right"};

std::vector<std::pair<std::string, double>> q_table;
std::vector<std::pair<std::string, double>> q_table_main;




auto Choose_Action(int state, std::vector<std::pair<std::string, double>> q_table){
    float rand_value = rand()%10/10.0;
    std::cout<<":: "<< rand_value << std::endl;

    double value_state_1 = q_table[state].second;
    double value_state_2 = q_table[state+1].second;


    if ((rand_value>EPSILON) || ((value_state_1 == 0) && (value_state_2 == 0)))
    {
        std::cout<<"value 0"<< std::endl;
    }
    else {
        std::cout<<" higher value" << std::endl;
    }
}


void Update_Env(int state, int episode, int step_counter)
{

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

//std::vector<std::pair<std::string, double>> Build_Q_Table(int n_states) //, std::vector<std::string> actions)
auto Build_Q_Table(int n_states)
{

    std::vector<std::pair<std::string, double>> q_tab;

    for (int i = 0; i < n_states; i++)
    {
        //temp_map.insert(i, std::make_pair)
        q_tab.push_back(std::make_pair("left", 0.0));
        q_tab.push_back(std::make_pair("right", 0.0));
    }

    return q_tab;
}

//std::vector<std::pair<std::string, double>>
auto Run_Rl()
{

   q_table = Build_Q_Table(N_STATES);//, ACTIONS);
    int ijk = 0;
    for (auto &i : q_table)
    {

        std::cout << "state :: " << ijk << ":: action :: " << i.first << ":: value :: " << i.second << std::endl;
        ijk++;
    }
    return q_table;
}


int main()
{

    srand(time(NULL));
    q_table_main = Run_Rl();
    Update_Env(0, 10, 10);
    Choose_Action(2, q_table);

    return 0;
}
