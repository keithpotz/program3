// Keith Pottratz
// September 25, 2014
// The purpose of this program is to log the total hours and pay rate 
// for each employee and display it in a easy to read format.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;
void printtitles(ofstream &outf)
{
	outf << setw(45) << "MESA MANUFACTURING COMPANY"
		<< endl << setw(35) << "Payroll"
		<< endl << endl << setw(2) << "Employ" << setw(4)
		<< "Pay" << setw(54) << "Total" << setw(8) << "TotHour"
		<< setw(7) << "Gross" << endl << setw(4) << "Num"
		<< setw(7) << "Rate" << setw(9) << "Monday" << setw(9)
		<< "Tuesday" << setw(10) << "Wednsday" << setw(10) << "Thursday"
		<< setw(7) << "Friday" << setw(8) << "Hours" << setw(8)
		<< "Rounded" << setw(8) << "Salary" << endl;
}
void printchar(char ch, int n, ofstream &outf)
{
	int i;
	for (i = 1; i <= n; i++)outf << ch; 
	outf << endl;
}
double sumhhmm(int hhmm, int hhmm1)
{
	int answer;
	double hours, hours1, mins, mins1, hourstotal, mintotal;

	hours = hhmm / 100;
	mins = hhmm % 100;
	hours1 = hhmm1 / 100;
	mins1 = hhmm1 % 100;
	hourstotal = hours + hours1;
	mintotal = mins + mins1;
	if (mintotal >= 60)
	{
		hourstotal++;
		mintotal -= 60;
	}
	answer = hourstotal * 100 + mintotal;
	return answer;
}
double HHMMtodouble(int hhmm)
{
	double answer, hour, min, quartermin;
	min = hhmm % 100;
	hour = hhmm - min;
	hour = hour / 100;
	if (min >= 52)
		quartermin = 1;
	else if (min >= 37)
		quartermin = .75;
	else if (min >= 22)
		quartermin = .5;
	else if (min >= .7)
		quartermin = .25;
	else
		quartermin = 0;
	answer = hour + quartermin * 1.0;
	return answer;
}
double getsalary(double payr, double hours)
{
	double answer;
	if (hours > 40)
		answer = (hours - 40) * (payr *1.5) + (40 * payr);
	else
		answer = payr * hours;

	return answer;
	
}
double roundem(double salary)
{
	int x;
	x = salary * 100 + .05;
	salary = x / 100.0;
	
	return salary;
}
void main()
{
	int i, Employnum, Monday, Tuesday, Wednsday, Thursday, Friday, hoursw, thourmon, thourtues, thourwed, thourthurs, thourfri,
		thoursw;
	double payr,hourswquar,gross, rgross, tgross,thourwr;

	ifstream inf;
	ofstream outf;
	inf.open("program3.dat");
	outf.open("program3.ot");
	outf.setf(ios::fixed);
	outf.precision(2);
	printtitles(outf);
	printchar('-', 81, outf);
	tgross = 0;
	thoursw = 0;
	thourmon = 0;
	thourtues = 0;
	thourwed = 0;
	thourthurs = 0;
	thourfri = 0;
	thourwr = 0;


	while (!inf.eof())
	{
		inf >> Employnum >> payr >> Monday >> Tuesday >> Wednsday
			>> Thursday >> Friday;
		hoursw = sumhhmm(Monday, Tuesday);
		hoursw = sumhhmm(hoursw, Wednsday);
		hoursw = sumhhmm(hoursw, Thursday);
		hoursw = sumhhmm(hoursw, Friday);
		hourswquar = HHMMtodouble(hoursw);
		gross = getsalary(payr, hourswquar);
		rgross = roundem(gross);
		tgross += rgross;
		thourwr += hourswquar;
		thourmon = sumhhmm(thourmon, Monday);
		thourtues = sumhhmm(thourtues, Tuesday);
		thourwed = sumhhmm(thourwed, Wednsday);
		thourthurs = sumhhmm(thourthurs, Thursday);
		thourfri = sumhhmm(thourfri, Friday);
		thoursw = sumhhmm(thourtues, thourmon);
		thoursw = sumhhmm(thourwed, thoursw);
		thoursw = sumhhmm(thoursw, thourthurs);
		thoursw = sumhhmm(thoursw, thourfri);


		outf <<setw(1)<< Employnum << setw(6) << payr << setw(8) << Monday << setw(8) << Tuesday
			<< setw(10) << Wednsday << setw(10) << Thursday << setw(7) << Friday << setw(10)  << hoursw
			<<setw(7) <<hourswquar <<setw(9)<<rgross<<  endl;
		

	}
	printchar('-', 81, outf);
	outf << setw(20) << thourmon << setw(8) << thourtues << setw(9) << thourwed
		<< setw(10) << thourthurs << setw(7) << thourfri << setw(10) << thoursw
		<< setw(8) << thourwr << setw(9) << tgross << endl;
    		system("pause");
}
