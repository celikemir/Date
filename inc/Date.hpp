#ifndef DATE_H
#define DATE_H

#include <iosfwd>
#include <ctime>
#include <array>
#include <string_view>
#include <iostream>

constexpr std::array<std::string_view, 12> month_names = {
    "Ocak", "Şubat", "Mart", "Nisan", "Mayıs", "Haziran",
    "Temmuz", "Ağustos", "Eylül", "Ekim", "Kasım", "Aralık"
};
constexpr std::array<std::string_view, 7> day_names = {
    "Pazartesi", "Salı", "Çarşamba", "Perşembe", "Cuma", "Cumartesi", "Pazar"
};

std::array<int, 12> days_in_month = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


namespace project {
	class Date {
	public:
		static constexpr int year_base = 1900;  //1
		static constexpr int random_min_year = 1940;  //2
		static constexpr int random_max_year = 2020;  //3
		enum class Weekday { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday }; //4
		Date(); //5 
		Date(int d, int m, int y);  //6
		explicit Date(const char* p);  //7
		explicit Date(std::time_t timer); //8
		
		[[nodiscard]] int get_month_day()const; //9
		[[nodiscard]] std::string_view get_month()const; //10
		[[nodiscard]] int get_year()const; //11
		[[nodiscard]] int get_year_day()const; //12
		[[nodiscard]] Weekday get_week_day()const; //13

		Date& set_month_day(int day); //14
		Date& set_month(int month); //15
		Date& set_year(int year); //16
		Date& set(int day, int mon, int year); //17
		[[nodiscard]] Date operator-(int days)const; //18
		Date& operator+=(int day); //19
		Date& operator-=(int day); //20
		Date& operator++(); //21
		Date operator++(int); //22
		Date& operator--(); //23
		Date operator--(int); //24

		friend bool operator<(const Date& lhs, const Date& rhs){
						if (lhs.year_ < rhs.year_) {
				return true;
			} else if (lhs.year_ == rhs.year_) {
				if (lhs.month_ < rhs.month_) {
					return true;
				} else if (lhs.month_ == rhs.month_) {
					return lhs.day_ < rhs.day_; // Son olarak gün karşılaştırılır
				}
			}
			return false;
		}; //27

		friend bool operator==(const Date& lhs, const Date& rhs)
		{
			if (lhs.year_ == rhs.year_ && lhs.month_ == rhs.month_ && lhs.day_ == rhs.day_) {
				return true;
			} 
			
			return false;
		}; //27

		[[nodiscard]] static Date random_date(); //25

		constexpr bool is_leap_year(int const year)const;
		static constexpr bool isleap(int y); //26

		friend std::ostream& operator<<(std::ostream& os, const Date& date)
		{
				    os << date.day_ << '/' << date.month_ << '/' << date.year_;
    		return os;

		} //31
		friend std::istream& operator>>(std::istream& is, Date& date); //32

		static const char* to_string(Weekday day) {
        switch (day) {
            case Weekday::Sunday:    return "Sunday";
            case Weekday::Monday:    return "Monday";
            case Weekday::Tuesday:   return "Tuesday";
            case Weekday::Wednesday: return "Wednesday";
            case Weekday::Thursday:  return "Thursday";
            case Weekday::Friday:    return "Friday";
            case Weekday::Saturday:  return "Saturday";
        }
        return "Unknown";
    }
	    
	
	private:
		unsigned int day_;
		unsigned int month_;
		unsigned int year_;
	};

	[[nodiscard]] bool operator<=(const Date&, const Date&); //27
	[[nodiscard]] bool operator>(const Date&, const Date&); //27
	[[nodiscard]] bool operator>=(const Date&, const Date&); //27
	[[nodiscard]] bool operator!=(const Date&, const Date&); //27

	[[nodiscard]] int operator-(const Date& d1, const Date& d2); //28
	[[nodiscard]] Date operator+(const Date& date, int n); //29
	[[nodiscard]] Date operator+(int n, const Date&); //29
	
	Date::Weekday& operator++(Date::Weekday& r); //30
	Date::Weekday operator++(Date::Weekday& r, int); //30
	Date::Weekday& operator--(Date::Weekday& r); //30
	Date::Weekday operator--(Date::Weekday& r, int); //30}
};

#endif
