#include <iostream>
#include <map>
#include <vector>

int N_STATES = 6;         //number of states
float EPSILON = 0.9;      // greedy policy
float ALPHA = 0.1;        //learning rate
float GAMMA = 0.9;        //discount factor
int MAX_EPISODES = 15;    //number of episodes the agent is going to play
float REFRESH_RATE = 0.3; //time for one move

std::string a_left = "left";
std::string a_right = "right";
std::vector<std::string> ACTIONS{"left", "right"};

std::vector<std::pair<std::string, double>> q_table;
std::vector<std::pair<std::string, double>> q_table_main;

std::vector<std::pair<std::string, double>> Build_Q_Table(int n_states, std::vector<std::string> actions)
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

std::vector<std::pair<std::string, double>> RUN_RL()
{

    q_table = Build_Q_Table(N_STATES, ACTIONS);
    int ijk = 0;
    for (auto &i  : q_table){

        std::cout<<"state :: "<< ijk << "action : "<< i.first << "value : " << i.second << std::endl;
        ijk++;
    }
}
int main()
{
q_table_main = RUN_RL();
}
