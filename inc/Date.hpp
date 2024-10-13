#ifndef DATE_H
#define DATE_H

#include <iosfwd>
#include <ctime>
#include <array>
#include <string_view>

namespace project {

class Date {
public:
    static constexpr int year_base = 1900;
    static constexpr int random_min_year = 1940;
    static constexpr int random_max_year = 2020;
    enum class Weekday { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };

    Date();
    Date(int d, int m, int y);
    explicit Date(const char* p);
    explicit Date(std::time_t timer);

    [[nodiscard]] int get_month_day() const;
    [[nodiscard]] std::string_view get_month() const;
    [[nodiscard]] int get_year() const;
    [[nodiscard]] int get_year_day() const;
    [[nodiscard]] Weekday get_week_day() const;

    Date& set_month_day(int day);
    Date& set_month(int month);
    Date& set_year(int year);
    Date& set(int day, int mon, int year);
    [[nodiscard]] Date operator-(int days) const;
    Date& operator+=(int day);
    Date& operator-=(int day);
    Date& operator++();
    Date operator++(int);
    Date& operator--();
    Date operator--(int);

    [[nodiscard]] static Date random_date();

    constexpr bool is_leap_year(int const year) const;
    static constexpr bool isleap(int y);

    static const char* to_string(Weekday day);

    friend bool operator<(const Date& lhs, const Date& rhs);
    friend bool operator==(const Date& lhs, const Date& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
    friend std::istream& operator>>(std::istream& is, Date& date);

private:
    unsigned int day_;
    unsigned int month_;
    unsigned int year_;
};

[[nodiscard]] bool operator<=(const Date& lhs, const Date& rhs);
[[nodiscard]] bool operator>(const Date& lhs, const Date& rhs);
[[nodiscard]] bool operator>=(const Date& lhs, const Date& rhs);
[[nodiscard]] bool operator!=(const Date& lhs, const Date& rhs);
[[nodiscard]] int operator-(const Date& d1, const Date& d2);
[[nodiscard]] Date operator+(const Date& date, int n);
[[nodiscard]] Date operator+(int n, const Date& date);

Date::Weekday& operator++(Date::Weekday& r);
Date::Weekday operator++(Date::Weekday& r, int);
Date::Weekday& operator--(Date::Weekday& r);
Date::Weekday operator--(Date::Weekday& r, int);

} // namespace project

// Global constants
extern const std::array<std::string_view, 12> month_names;
extern const std::array<std::string_view, 7> day_names;
extern const std::array<int, 12> days_in_month;

#endif // DATE_H