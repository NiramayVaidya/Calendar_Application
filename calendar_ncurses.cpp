#include <iostream>
#include <iomanip>
#include <ncurses.h>
#define NUM_OF_DAYS_IN_YEAR 365
#define NUM_OF_MONTHS 12
#define NUM_OF_DAYS_IN_WEEK 7
using namespace std;

class Calendar {
    const static int startYear = 1970; 
    const static int startDay = 3;
    int inputYear;
    int columns;
    int firstDay;
    const char *days[7];
    const char *months[12];
    bool isLeap(int year);
    int getFirstDay();
    void printYear();
    int getNumOfDays(int month);
    void printMonth(int numOfDaysInMonth);
    void initDays();
    void initMonths();
    public:
    Calendar(int year, int columns);
};

Calendar::Calendar(int year, int columns) {
    inputYear = year;
    this->columns = columns;
    firstDay = getFirstDay();
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
    int row, col;
    getyx(stdscr, row, col);
    col = 0;
    while(currMonth < NUM_OF_MONTHS) {
        mvprintw(row, col + 12, "%s\n", months[currMonth]);
        getyx(stdscr, row, col);
        col = 0;
        for(currDay = 0; currDay < NUM_OF_DAYS_IN_WEEK - 1; currDay++) {
            mvprintw(row, col, "%s", days[currDay]);
            col += 5;
        }
        mvprintw(row, col, "%s\n", days[currDay]);
        numOfDays = getNumOfDays(currMonth + 1);
        if(currMonth == 1 && isLeap(inputYear))
            numOfDays += 1;
        printMonth(numOfDays);
        currMonth++;
        getyx(stdscr, row, col);
        col = 0;
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

void Calendar::printMonth(int numOfDaysInMonth) {
    int dayCount = 1;
    int count;
    static int firstDayOfYear = firstDay;
    int countDays = firstDayOfYear - 1;
    int row, col;
    getyx(stdscr, row, col);
    col = 0;
    col += 5 * firstDayOfYear;
    while(numOfDaysInMonth - (dayCount - 1) > 0) {
        for(count = firstDayOfYear; (count < NUM_OF_DAYS_IN_WEEK - 1) && (dayCount <= numOfDaysInMonth); count++) {
            mvprintw(row, col, "%d", dayCount);
            getyx(stdscr, row, col);
            if(dayCount > 9)
                col += 3;
            else
               col += 4;
            dayCount++;
            countDays++;
        }
        if(dayCount <= numOfDaysInMonth) {
            mvprintw(row, col, "%d\n", dayCount);
            dayCount++;
            countDays++;
            getyx(stdscr, row, col);
            col = 0;
        }
        else {
            mvprintw(row, col, "\n");
            getyx(stdscr, row, col);
            col = 0;
        }
        firstDayOfYear = 0;
    }
    if(count <= NUM_OF_DAYS_IN_WEEK && countDays % NUM_OF_DAYS_IN_WEEK != 6)
        firstDayOfYear = count;
    else
        firstDayOfYear = 0;
    getyx(stdscr, row, col);
    col = 0;
    mvprintw(row, col, "\n");
}

void Calendar::initDays() {
    days[0] = "Mon";
    days[1] = "Tue";
    days[2] = "Wed";
    days[3] = "Thu";
    days[4] = "Fri";
    days[5] = "Sat";
    days[6] = "Sun";
}

void Calendar::initMonths() {
    months[0] = "January";
    months[1] = "February";
    months[2] = "March";
    months[3] = "April";
    months[4] = "May";
    months[5] = "June";
    months[6] = "July";
    months[7] = "August";
    months[8] = "September";
    months[9] = "October";
    months[10] = "November";
    months[11] = "December";
}
    
int main() {
    initscr();
    int year, column;
    int row, col;
    mvprintw(0, 0, "Input year:\n");
    getyx(stdscr, row, col);
    col = 0;
    mvscanw(row, col, "%d", &year);
    getyx(stdscr, row, col);
    col = 0;
    mvprintw(row, col, "Input no. of columns:\n");
    getyx(stdscr, row, col);
    col = 0;
    mvscanw(row, col, "%d", &column);
    getyx(stdscr, row, col);
    col = 0;
    mvprintw(row, col, "\n");
    Calendar calendar(year, column);
    refresh();
    getch();
    endwin();
    return 0;
} 
