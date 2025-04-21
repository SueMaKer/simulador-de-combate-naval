#pragma once

#include "Ship.hpp"


using namespace std;
using namespace std::chrono;

class SetShip : public Ship {
private:
    Set set; 
    
public:
    SetShip();  
    
    void setSet();

    int search(int key);


    int getPower() override;
    
};