#include <Date.hpp>
#include <iostream>
#include <string>

using namespace project;


Date::Date(){
    Date(1, 1, Date::year_base);
    std::cout << "Date const." << std::endl;
};

Date::Date(int d, int m, int y): day_(d), month_(m), year_(y) {
    std::cout << "Day: " << day_ << " Month: " << month_ << " Year: " << year_ << std::endl;
}

Date::Date(const char* p){
    sscanf(p, "%d/%d/%d", &day_, &month_, &year_);
    std::cout << "char " << "Day: " << day_ << " Month: " << month_ << " Year: " << year_ << std::endl;
    
}

int Date::get_month_day()const{
    return day_;
}

std::string_view Date::get_month()const{
    
    return month_ >= 1 && month_ <= 12 ? month_names[month_ - 1] : "Invalid Month";
}

int Date::get_year()const{
    return year_;
}

constexpr bool Date::is_leap_year(int const year)const{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Date::get_year_day()const{

    if (is_leap_year(year_)) {
        days_in_month[1] = 29;  // February has 29 days in a leap year
    }

    // Calculate the day of the year
    int day_of_year = 0;

    // Add the days of the previous months
    for (unsigned int i = 0; i < month_ - 1; ++i) {
        day_of_year += days_in_month[i];
    }

    // Add the current day's value
    day_of_year += day_;

    return day_of_year;
}

Date::Weekday Date::get_week_day()const{

    int y = year_;
    int m = month_;
    int d = day_;

    int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
     
    // if month is less than 3 reduce year by 1
    if (m < 3)
        y -= 1;
    
    
    auto a = static_cast<Weekday>(((y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7));
    return a;

}

Date& Date::set_month_day(int day){
    day_ = day;
}

Date& Date::set_month(int month){
    month_ = month;
}

Date& Date::set_year(int year){
    year_ = year;
}

Date& Date::set(int day, int mon, int year){
    day_ = day;
    month_ = mon;
    year_ = year;

}

[[nodiscard]] Date Date::operator-(int days)const{

    int day = day_;
    int month = month_;
    int year = year_;

    if(is_leap_year(year))
        days_in_month[1] = 29;

    while(days > 0){
        if(day > days){
            day -= days;
            days = 0;

        }
        else{
            days -= day;
            month -=1;
            if(month == 0){
                year -= 1;
                if(is_leap_year(year))
                    days_in_month[1] = 29;
                else
                    days_in_month[1] = 28;

            }

        day = days_in_month[month -1];
        }
        
    }

    return Date(day, month, year);
}

Date& Date::operator+=(int day){

    day_ += day;

    while (day_ > (month_ == 2 && is_leap_year(year_) ? 29 : days_in_month[month_ - 1])) {
        day_ -= (month_ == 2 && is_leap_year(year_) ? 29 : days_in_month[month_ - 1]);
        month_++;

        // If month exceeds 12, adjust the year
        if (month_ > 12) {
            month_ = 1;
            year_++;
        }
    }

    // Adjust for negative days (in case day_ becomes less than 1)
    while (day_ < 1) {
        month_--;

        if (month_ < 1) {
            month_ = 12;
            year_--;
        }
        day_ += (month_ == 2 && is_leap_year(year_) ? 29 : days_in_month[month_ - 1]);
    }

    return *this;

}

Date& Date::operator-=(int day) {
    return operator+=(-day);
}



// Date& Date::operator-=(int day){

//     day_ -= day;

//     while (day_ < 1) {
//         month_--;

//         if (month_ < 1) {
//             month_ = 12;
//             year_--;
//         }
//         day_ += (month_ == 2 && is_leap_year(year_) ? 29 : days_in_month[month_ - 1]);
//     }

//     return *this;

// }

Date& Date::operator++(){
    return *this +=1;
}

Date Date::operator++(int){
    Date temp = *this;
    ++(*this);
    return temp;

}

Date& Date::operator--(){
    return *this -=1;
}

Date Date::operator--(int){
    Date temp = *this;
    --(*this);
    return temp;
}

bool operator<=(const Date& lhs, const Date& rhs) { return !(rhs < lhs); }
bool operator>(const Date& lhs, const Date& rhs) { return rhs < lhs; }
bool operator>=(const Date& lhs, const Date& rhs) { return !(lhs < rhs); }
bool operator!=(const Date& lhs, const Date& rhs) { return !(lhs == rhs); }


// global overloadları burada yapınca neden error alıyorum anlamadım yaw  ? 


// [[nodiscard]] Date operator+(const Date& date, int n) {
//     Date result = date;
//     result += n;
//     return result;
// }

// [[nodiscard]] Date operator+(int n, const Date& date){
//     return date + n;
// }

int main(){
    // Date mydate;
    Date mydateint_(02,10,2024);
    Date mydate_("10/03/2025");

    std::cout << mydate_.get_year() << "\n";
    std::cout << mydate_.get_month() << "\n";
    std::cout << mydate_.get_year_day() << "\n";
    std::cout << Date::to_string(mydate_.get_week_day()) << "\n";

    Date new_date = mydate_ - 15;  // Subtract 15 days
    std::cout << new_date.get_year_day() << new_date.get_month() << new_date.get_year() << "\n";          // Print the new date

    Date date1(15, 10, 2020);
    Date date2(16, 10, 2020);

    if (date1 < date2) {
        std::cout << date1 << " is earlier than " << date2 << std::endl;
    }
    else {
        std::cout << date1 << " is not earlier than " << date2 << std::endl;
    }
        if (date1 == date2) {
        std::cout << date1 << " is same date " << date2 << std::endl;
    }
    else {
        std::cout << date1 << " is not same date " << date2 << std::endl;
    }

    Date today(28, 2, 2020); // February 28, 2020 (leap year)
    today += 5;              // Adding 5 days (should move to March 4, 2020)
    std::cout << "New date is: " << today << std::endl;

    Date date3(28, 02, 2023);
    Date date4(28, 02, 2024);

    int daysBetween = date3 - date4;
    std::cout << "Days between " << date1 << " and " << date2 << ": " << daysBetween << std::endl;


    Date date5 = date1 + 5;  // 5 gün sonrası
    std::cout << "5 days after " << date1 << " is " << date5 << std::endl;

    Date date6 = 10 + date1;  // 10 gün sonrası
    std::cout << "10 days after " << date1 << " is " << date6 << std::endl;


    if(date3 < date4)
        std::cout << date3 << " is smaller than " << date4 << std::endl;
    

    Date date8;
    std::cout << "Tarihi giriniz (gg/aa/yyyy): ";
    try {
        std::cin >> date8;
        Date::Weekday weekday = date8.get_week_day();
        std::cout << date8 << "\n";
        std::cout << "Girilen tarih haftanın " << static_cast<int>(weekday) << ". günü." << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

}