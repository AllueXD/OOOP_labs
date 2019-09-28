#ifndef LAB6_DIFFERENT_LABS_TM_FUNCTIONS_H
#define LAB6_DIFFERENT_LABS_TM_FUNCTIONS_H

#include<iostream>
#include<ctime>

using namespace std;

ostream& operator << (ostream& stream, tm& time) {
    string day="", month="", hour="", min="", sec="";
    if (time.tm_mday<10) day='0';
    if (time.tm_mon<10) month='0';
    if (time.tm_hour<10) hour='0';
    if (time.tm_min<10) min='0';
    if (time.tm_sec<10) sec='0';
    stream<<day<<time.tm_mday<<'.'<<month<<time.tm_mon<<'.'<<time.tm_year<<' '
          <<hour<<time.tm_hour<<':'<<min<<time.tm_min<<':'<<sec<<time.tm_sec;
    return stream;
}

istream& operator >> (istream& stream, tm& time) {
    int day, month, year, hour, min, sec;
    stream>>day>>month>>year>>hour>>min>>sec;
    time.tm_mday = day;
    time.tm_mon = month;
    time.tm_year = year;
    time.tm_hour = hour;
    time.tm_min = min;
    time.tm_sec = sec;
    return stream;
}

tm random_time () {
    tm time;
    time.tm_mday = rand()%31+1;
    time.tm_mon = rand()%12+1;
    time.tm_year = rand()%21+2000;
    return time;
}

bool operator< (tm& left, tm& right) {
    if (left.tm_year>right.tm_year) return false;
    else if (left.tm_year<right.tm_year) return true;

    if (left.tm_mon>right.tm_mon) return false;
    else if (left.tm_mon<right.tm_mon) return true;

    return (left.tm_mday<right.tm_mday);
}

bool operator<= (tm& left, tm& right) {
    if (left.tm_year>right.tm_year) return false;
    else if (left.tm_year<right.tm_year) return true;

    if (left.tm_mon>right.tm_mon) return false;
    else if (left.tm_mon<right.tm_mon) return true;

    return (left.tm_mday<=right.tm_mday);
}

bool operator> (tm& left, tm& right) {
    if (left.tm_year>right.tm_year) return true;
    else if (left.tm_year<right.tm_year) return false;

    if (left.tm_mon>right.tm_mon) return true;
    else if (left.tm_mon<right.tm_mon) return false;

    return (left.tm_mday>right.tm_mday);
}

bool operator>= (tm& left, tm& right) {
    if (left.tm_year>right.tm_year) return true;
    else if (left.tm_year<right.tm_year) return false;

    if (left.tm_mon>right.tm_mon) return true;
    else if (left.tm_mon<right.tm_mon) return false;

    return (left.tm_mday>=right.tm_mday);
}

bool operator == (tm& left, tm& right) {
    return (left.tm_year == right.tm_year && left.tm_mon==right.tm_mon && left.tm_mday==right.tm_mday);
}

tm stotm (const string& to_convert) {
    tm result;
    string substr;

    substr = to_convert[0]+to_convert[1];
    result.tm_mday = stoi(substr);
    substr = to_convert[3]+to_convert[4];
    result.tm_mon = stoi(substr);
    substr = "";

    for (int i = 5; i < to_convert.size(); i++) {substr += to_convert[i];}
    result.tm_year = stoi(substr);
    return result;
}

#endif
