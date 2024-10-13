#include "Date.hpp"
#include <iostream>
#include <string>
#include <chrono>
#include <random>
#include <stdexcept>

namespace project {

// Define global constants
const std::array<std::string_view, 12> month_names = {
    "Ocak", "Şubat", "Mart", "Nisan", "Mayıs", "Haziran",
    "Temmuz", "Ağustos", "Eylül", "Ekim", "Kasım", "Aralık"
};

const std::array<std::string_view, 7> day_names = {
    "Pazartesi", "Salı", "Çarşamba", "Perşembe", "Cuma", "Cumartesi", "Pazar"
};

std::array<int, 12> days_in_month = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

Date::Date() : Date(1, 1, Date::year_base) {
    std::cout << "Date const." << std::endl;
}

Date::Date(int d, int m, int y) : day_(d), month_(m), year_(y) {
    std::cout << "Day: " << day_ << " Month: " << month_ << " Year: " << year_ << std::endl;
}

Date::Date(const char* p) {
    if (sscanf(p, "%d/%d/%d", &day_, &month_, &year_) != 3) {
        throw std::invalid_argument("Invalid date format");
    }
    std::cout << "char " << "Day: " << day_ << " Month: " << month_ << " Year: " << year_ << std::endl;
}

Date::Date(std::time_t timer) {
    std::tm* timeinfo = std::localtime(&timer);
    day_ = timeinfo->tm_mday;
    month_ = timeinfo->tm_mon + 1;
    year_ = timeinfo->tm_year + 1900;
}

int Date::get_month_day() const {
    return day_;
}

std::string_view Date::get_month() const {
    return month_ >= 1 && month_ <= 12 ? month_names[month_ - 1] : "Invalid Month";
}

int Date::get_year() const {
    return year_;
}

constexpr bool Date::is_leap_year(int const year) const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

constexpr bool Date::isleap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Date::get_year_day() const {
    int day_of_year = day_;
    for (int i = 0; i < month_ - 1; ++i) {
        day_of_year += days_in_month[i];
    }
    if (month_ > 2 && is_leap_year(year_)) {
        day_of_year++;
    }
    return day_of_year;
}

Date::Weekday Date::get_week_day() const {
    int y = year_;
    int m = month_;
    int d = day_;

    if (m < 3) {
        m += 12;
        y -= 1;
    }
    int h = (d + 13 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
    return static_cast<Weekday>((h + 5) % 7);
}

Date& Date::set_month_day(int day) {
    if (day < 1 || day > days_in_month[month_ - 1]) {
        throw std::invalid_argument("Invalid day for the current month");
    }
    day_ = day;
    return *this;
}

Date& Date::set_month(int month) {
    if (month < 1 || month > 12) {
        throw std::invalid_argument("Invalid month");
    }
    month_ = month;
    return *this;
}

Date& Date::set_year(int year) {
    if (year < year_base) {
        throw std::invalid_argument("Invalid year");
    }
    year_ = year;
    return *this;
}

Date& Date::set(int day, int mon, int year) {
    set_year(year);
    set_month(mon);
    set_month_day(day);
    
}

Date Date::random_date() {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> year_dist(random_min_year, random_max_year);
    std::uniform_int_distribution<> month_dist(1, 12);
    
    int year = year_dist(gen);
    int month = month_dist(gen);
    int max_day = (month == 2 && isleap(year)) ? 29 : days_in_month[month - 1];
    std::uniform_int_distribution<> day_dist(1, max_day);
    int day = day_dist(gen);

    return Date(day, month, year);
}

Date Date::operator-(int days) const {
    Date result = *this;
    result -= days;
    return result;
}

Date& Date::operator+=(int days) {
    while (days > 0) {
        int days_in_current_month = (month_ == 2 && is_leap_year(year_)) ? 29 : days_in_month[month_ - 1];
        if (day_ + days <= days_in_current_month) {
            day_ += days;
            break;
        }
        days -= (days_in_current_month - day_ + 1);
        day_ = 1;
        if (++month_ > 12) {
            month_ = 1;
            ++year_;
        }
    }
    return *this;
}

Date& Date::operator-=(int days) {
    while (days > 0) {
        if (day_ > days) {
            day_ -= days;
            break;
        }
        days -= day_;
        if (--month_ < 1) {
            month_ = 12;
            --year_;
        }
        day_ = (month_ == 2 && is_leap_year(year_)) ? 29 : days_in_month[month_ - 1];
    }
    return *this;
}

Date& Date::operator++() {
    return *this += 1;
}

Date Date::operator++(int) {
    Date temp = *this;
    ++(*this);
    return temp;
}

Date& Date::operator--() {
    return *this -= 1;
}

Date Date::operator--(int) {
    Date temp = *this;
    --(*this);
    return temp;
}

const char* Date::to_string(Weekday day) {
    static const char* weekday_names[] = {
        "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
    };
    return weekday_names[static_cast<int>(day)];
}

bool operator<(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year_, lhs.month_, lhs.day_) < std::tie(rhs.year_, rhs.month_, rhs.day_);
}

bool operator==(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year_, lhs.month_, lhs.day_) == std::tie(rhs.year_, rhs.month_, rhs.day_);
}

bool operator<=(const Date& lhs, const Date& rhs) { return !(rhs < lhs); }
bool operator>(const Date& lhs, const Date& rhs) { return rhs < lhs; }
bool operator>=(const Date& lhs, const Date& rhs) { return !(lhs < rhs); }
bool operator!=(const Date& lhs, const Date& rhs) { return !(lhs == rhs); }

int operator-(const Date& d1, const Date& d2) {
    // This is a simplified version. For a more accurate implementation,
    // consider using a library like Howard Hinnant's date library.
    int days = 0;
    Date earlier = (d1 < d2) ? d1 : d2;
    Date later = (d1 < d2) ? d2 : d1;
    
    while (earlier != later) {
        earlier += 1;
        days++;
    }
    
    return (d1 < d2) ? -days : days;
}

Date operator+(const Date& date, int n) {
    Date result = date;
    result += n;
    return result;
}

Date operator+(int n, const Date& date) {
    return date + n;
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.day_ << '/' << date.month_ << '/' << date.year_;
    return os;
}

std::istream& operator>>(std::istream& is, Date& date) {
    char separator1, separator2;
    if (is >> date.day_ >> separator1 >> date.month_ >> separator2 >> date.year_) {
        if (separator1 != '/' || separator2 != '/') {
            is.setstate(std::ios::failbit);
            throw std::invalid_argument("Invalid separator format. Use format dd/mm/yyyy");
        }
        if (date.year_ < Date::year_base || date.month_ < 1 || date.month_ > 12 || 
            date.day_ < 1 || date.day_ > (date.month_ == 2 && date.is_leap_year(date.year_) ? 29 : days_in_month[date.month_ - 1])) {
            is.setstate(std::ios::failbit);
            throw std::invalid_argument("Invalid date values");
        }
    } else {
        is.setstate(std::ios::failbit);
        throw std::invalid_argument("Invalid input format. Use format dd/mm/yyyy");
    }
    return is;
}

Date::Weekday& operator++(Date::Weekday& r) {
    r = static_cast<Date::Weekday>((static_cast<int>(r) + 1) % 7);
    return r;
}

Date::Weekday operator++(Date::Weekday& r, int) {
    Date::Weekday temp = r;
    ++r;
    return temp;
}

Date::Weekday& operator--(Date::Weekday& r) {
    r = static_cast<Date::Weekday>((static_cast<int>(r) + 6) % 7);
    return r;
}

Date::Weekday operator--(Date::Weekday& r, int) {
    Date::Weekday temp = r;
    --r;
    return temp;
}

} // namespace project