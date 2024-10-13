#include "Date.hpp"
#include <iostream>

using namespace project;

int main() {
    Date mydateint_(02,10,2024);
    Date mydate_("10/03/2025");

    std::cout << mydate_.get_year() << "\n";
    std::cout << mydate_.get_month() << "\n";
    std::cout << mydate_.get_year_day() << "\n";
    std::cout << Date::to_string(mydate_.get_week_day()) << "\n";

    Date new_date = mydate_ - 15;  // Subtract 15 days
    std::cout << new_date.get_year_day() << new_date.get_month() << new_date.get_year() << "\n";

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
    
    std::cout << "Testing random_date() function:\n";
    
    // 10 rastgele tarih oluştur ve yazdır
    for (int i = 0; i < 10; ++i) {
        Date random_date = Date::random_date();
        std::cout << "Random date " << i + 1 << ": " << random_date << std::endl;
    }

    Date date8;
    std::cout << "Tarihi giriniz (gg/aa/yyyy): ";
    try {
        std::cin >> date8;
        Date::Weekday weekday = date8.get_week_day();
        std::cout << date8 << "\n";
        std::cout << "Girilen tarih haftanın " << static_cast<int>(weekday) + 1 << ". günü." << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}