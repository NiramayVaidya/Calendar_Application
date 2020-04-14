#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#define NUM_OF_DAYS_IN_YEAR 365
#define NUM_OF_MONTHS 12
#define NUM_OF_DAYS_IN_WEEK 7
using namespace std;

class Calendar {
    const static int startYear = 1970; 
    const static int startDay = 3;
    int inputYear;
    int firstDay;
    vector<string> days;
    vector<string> months;
    bool isLeap(int year);
    int getFirstDay();
    void printYear();
    int getNumOfDays(int month);
    void printMonth(int month, int numOfDaysInMonth);
    void initDays();
    void initMonths();
    public:
    Calendar(int year);
};

Calendar::Calendar(int year) {
    inputYear = year;
    firstDay = getFirstDay();
    //cout << firstDay << endl;
    initDays();
    initMonths();
    printYear();
}

bool Calendar::isLeap(int year) {
    if((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))
        return true;
    else
        return false;
}

int Calendar::getFirstDay() {
    int currYear = startYear;
    int totalDays = 0;
    while(currYear < inputYear) {
        if(isLeap(currYear))
            totalDays += NUM_OF_DAYS_IN_YEAR + 1;
        else
            totalDays += NUM_OF_DAYS_IN_YEAR;
        currYear++;
    }
    return (startDay + totalDays) % NUM_OF_DAYS_IN_WEEK;
}

void Calendar::printYear() {
    int currMonth = 0;
    int currDay;
    int numOfDays;
    while(currMonth < NUM_OF_MONTHS) {
        cout << setw(18) << months[currMonth] << endl;
        for(currDay = 0; currDay < NUM_OF_DAYS_IN_WEEK - 1; currDay++)
            cout << days[currDay] << setw(5);
        cout << days[currDay] << endl;
        numOfDays = getNumOfDays(currMonth + 1);
        if(currMonth == 1 && isLeap(inputYear))
            numOfDays += 1;
        printMonth(currMonth, numOfDays);
        currMonth++;
    }
}

int Calendar::getNumOfDays(int month) {
    if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        return 31;
    else if(month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    else
        return 28;
}

void Calendar::printMonth(int month, int numOfDaysInMonth) {
    int dayCount = 1;
    int count;
    //int countDays = firstDay;
    static int firstDayOfYear = firstDay;
    int countDays = firstDayOfYear - 1;
    cout << setw(3 + 5 * firstDayOfYear);
    while(numOfDaysInMonth - (dayCount - 1) > 0) {
        for(count = firstDayOfYear; (count < NUM_OF_DAYS_IN_WEEK - 1) && (dayCount <= numOfDaysInMonth); count++) {
            cout << dayCount << setw(5);
            dayCount++;
            countDays++;
        }
        if(dayCount <= numOfDaysInMonth) {
            cout << dayCount << endl;
            dayCount++;
            countDays++;
            cout << setw(3);
        }
        else
            cout << endl;
        firstDayOfYear = 0;
    }
    if(count <= NUM_OF_DAYS_IN_WEEK && countDays % NUM_OF_DAYS_IN_WEEK != 6)
        firstDayOfYear = count;
    else
        firstDayOfYear = 0;
    cout << endl;
}

void Calendar::initDays() {
    days.push_back("Mon");
    days.push_back("Tue");
    days.push_back("Wed");
    days.push_back("Thu");
    days.push_back("Fri");
    days.push_back("Sat");
    days.push_back("Sun");
}

void Calendar::initMonths() {
    months.push_back("January");
    months.push_back("February");
    months.push_back("March");
    months.push_back("April");
    months.push_back("May");
    months.push_back("June");
    months.push_back("July");
    months.push_back("August");
    months.push_back("September");
    months.push_back("October");
    months.push_back("November");
    months.push_back("December");
}
    
int main() {
    int year;
    cin >> year;
    Calendar calendar(year);
    return 0;
}