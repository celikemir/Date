#include <Date.hpp>
#include <iostream>
#include <string>

using namespace project;

Date::Date(){
    Date(1,1,Date::year_base);
    std::cout << "Date const." << std::endl;
};

Date::Date(int d, int m, int y):day_(d),month_(m),year_(y) {
    std::cout << "Day: " << day_ << " Moth: " << month_ << " Year: " << year_ << std::endl;
}

Date:: Date(const char* p){
    sscanf(p, "%d/%d/%d", &day_, &month_, &year_);
    std::cout << "char" << "Day: " << day_ << " Moth: " << month_ << " Year: " << year_ << std::endl;
    
}


int main(){
    // Date mydate;

    Date mydate_("10/03/1999");

}