// Keith Pottratz
// September 25, 2014
// The purpose of this program is to log the total hours and pay rate 
// for each employee and display it in a easy to read format.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

void printtitles(std::ofstream& outf)
{
    outf << std::setw(45) << "MESA MANUFACTURING COMPANY"
         << '\n' << std::setw(35) << "Payroll"
         << '\n' << '\n' << std::setw(2) << "Employ" << std::setw(4)
         << "Pay" << std::setw(54) << "Total" << std::setw(8) << "TotHour"
         << std::setw(7) << "Gross" << '\n' << std::setw(4) << "Num"
         << std::setw(7) << "Rate" << std::setw(9) << "Monday" << std::setw(9)
         << "Tuesday" << std::setw(10) << "Wednesday" << std::setw(10) << "Thursday"
         << std::setw(7) << "Friday" << std::setw(8) << "Hours" << std::setw(8)
         << "Rounded" << std::setw(8) << "Salary" << '\n';
}

void printchar(char ch, int n, std::ofstream& outf)
{
    for (int i = 1; i <= n; i++)
        outf << ch;
    outf << '\n';
}

int sumhhmm(int hhmm1, int hhmm2)
{
    int hh1 = hhmm1 / 100;
    int mm1 = hhmm1 % 100;
    int hh2 = hhmm2 / 100;
    int mm2 = hhmm2 % 100;

    int hhSum = hh1 + hh2;
    int mmSum = mm1 + mm2;
    if (mmSum >= 60) {
        hhSum++;
        mmSum -= 60;
    }

    return hhSum * 100 + mmSum;
}

double HHMMtodouble(int hhmm)
{
    int hh = hhmm / 100;
    int mm = hhmm % 100;
    double fraction = mm / 60.0;
    return hh + fraction;
}

double getsalary(double payr, double hours)
{
    if (hours > 40)
        return (hours - 40) * (payr * 1.5) + (40 * payr);
    else
        return payr * hours;
}

double roundem(double salary)
{
    return static_cast<int>(salary * 100 + 0.5) / 100.0;
}

int main()
{
    int Employnum, Monday, Tuesday, Wednesday, Thursday, Friday;
    double payr, gross, rgross, totalGross = 0, totalHours = 0;

    std::ifstream inf("program3.dat");
    std::ofstream outf("program3.ot");
    outf.setf(std::ios::fixed);

    printtitles(outf);
    printchar('-', 81, outf);

    outf << std::setw(1) << std::setfill(' ');

    while (inf >> Employnum >> payr >> Monday >> Tuesday >> Wednesday >> Thursday >> Friday)
    {
        int totalDayHours = sumhhmm(Monday, sumhhmm(Tuesday, sumhhmm(Wednesday, sumhhmm(Thursday, Friday))));
        double totalDayHoursQuar = HHMMtodouble(totalDayHours);
        double dailyGross = getsalary(payr, totalDayHoursQuar);
        double roundedGross = roundem(dailyGross);

        totalGross += roundedGross;
        totalHours += totalDayHoursQuar;

        outf << std::setw(4) << Employnum << std::setw(7) << payr << std::setw(9) << Monday << std::setw(9) << Tuesday
             << std::setw(10) << Wednesday << std::setw(10) << Thursday << std::setw(7) << Friday << std::setw(10) << totalDayHours
             << std::setw(7) << std::setprecision(2) << totalDayHoursQuar << std::setw(9) << roundedGross << '\n';
    }

    printchar('-', 81, outf);
    outf << std::setw(20) << std::setfill(' ') << sumhhmm(sumhhmm(Monday, Tuesday), sumhhmm(Wednesday, sumhhmm(Thursday, Friday))) << std::setw(8) << Tuesday
         << std::setw(9) << Wednesday << std::setw(10) << Thursday << std::setw(7) << Friday
         << std::setw(10) << totalHours << std::setw(8) << totalHours << std::setw(9) << std::setprecision(2) << totalGross << '\n';

    std::cin.ignore(); // Wait for user input before closing the console window

    return 0;
}
