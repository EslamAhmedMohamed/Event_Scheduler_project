#define _CRT_SECURE_NO_WARNINGS
#include "Event.h"
#include<iostream>
#include<string.h>
#include<cmath>
#include<fstream>
#include<string>
#include<ctime>
using namespace std;
void Event::start() {
	
	Event temp;
	fstream events;
	events.open("event.txt");
	string a[9];
	string tem;
	int count = 0;
	while (getline(events, tem, '|')) {
		a[count] = tem;
		count++;
		if (count == 9) {
			count = 0;
			temp.Name = a[0];
			temp.Place = a[1];
			temp.Start.Day = stoi(a[2]);
			temp.Start.Month = stoi(a[3]);
			temp.Start.Year = stoi(a[4]);
			temp.end.Day = stoi(a[5]);
			temp.end.Month = stoi(a[6]);
			temp.end.Year = stoi(a[7]);
			temp.Start_Time = stoi(a[8]);
			
			Insert(temp);
		}
	}
	//file of done event
	fstream done;
	done.open("done_event.txt");
	 count = 0;
	while (getline(done, tem, '|')) {
		a[count] = tem;
		count++;
		if (count == 9) {
			count = 0;
			temp.Name = a[0];
			temp.Place = a[1];
			temp.Start.Day = stoi(a[2]);
			temp.Start.Month = stoi(a[3]);
			temp.Start.Year = stoi(a[4]);
			temp.end.Day = stoi(a[5]);
			temp.end.Month = stoi(a[6]);
			temp.end.Year = stoi(a[7]);
			temp.Start_Time = stoi(a[8]);

			Done_Events.push_back(temp);
		}
	}
}
Event::Event() {

	
	Done = false;
	Start_Time = 0;
	reminder.Day_r = reminder.Month_r = 0;
	Start.Day = Start.Month = Start.Year = 0;
	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);

	Current.Day = now->tm_mday;
	Current.Month = now->tm_mon + 1;
	Current.Year = now->tm_year + 1900;

}
Event Event::AddFromUser()
{
	Event TempEvent;	
	cout << "Please Enter Event Name " << endl;
	cin>>TempEvent.Name;
	cout << "Please Enter Event Place  " << endl;
	cin>>TempEvent.Place;
	cout << "Please Enter Event Start Date by Order Day / Month / Year  " << endl;
	cin >> TempEvent.Start.Day;
	cin >> TempEvent.Start.Month;
	cin >> TempEvent.Start.Year;
	cout << "Please Enter Event End Date by Order Day / Month / Year " << endl;
	cin >> TempEvent.end.Day;
	cin >> TempEvent.end.Month;
	cin >> TempEvent.end.Year;
	if (TempEvent.Start.Year > TempEvent.end.Year || (TempEvent.end.Year == TempEvent.Start.Year && TempEvent.Start.Month > TempEvent.end.Month) || (TempEvent.end.Year == TempEvent.Start.Year && TempEvent.Start.Month == TempEvent.end.Month && TempEvent.Start.Day > TempEvent.end.Day)) {
		cout <<"invalid end date!!"<<endl;
			return AddFromUser();
	}
	if (TempEvent.Current.Year > TempEvent.Start.Year || (TempEvent.Current.Year == TempEvent.Start.Year && TempEvent.Current.Month > TempEvent.Start.Month) || (TempEvent.Current.Year == TempEvent.Start.Year && TempEvent.Current.Month == TempEvent.Start.Month && TempEvent.Current.Day > TempEvent.Start.Day)) {
		cout << "invalid current or start date!!" << endl;
		return AddFromUser();
	}
	cout << "Please Enter Event Start Time " << endl;
	cin >> TempEvent.Start_Time;
	r2 = Reminder(TempEvent.Start,TempEvent.Current);
	cout << " Reminder Time To Start is "  << r2.Month_r << " Month " << r2.Day_r << " Day " << endl;
	return TempEvent;
}
Reminder_Date Event::Reminder(Event_Date start, Event_Date current)
{
		if (current.Month < start.Month)
		{
			if (start.Day >= current.Day) {
			
				reminder.Month_r = start.Month - current.Month;
				reminder.Day_r = start.Day - current.Day;

			}
			else {
				
				reminder.Month_r = start.Month - current.Month - 1;
				reminder.Day_r = (30 - current.Day) + start.Day;
			}


		}

		else if (current.Month = start.Month)
		{
				reminder.Month_r = 0;
				if (start.Day > current.Day) {

					reminder.Day_r = start.Day - current.Day;
				}
				else {
					Done = true;
					reminder.Day_r = 0;
				}
		}
			else if (start.Month < current.Month || (current.Month = start.Month && start.Day < current.Day)) {
				cout << "This Event is done\n";
				reminder.Month_r = reminder.Day_r = 0;
				Done = true;

			}
			return reminder;
}
void Event::Insert(Event e)
{
	int i = 0;
	vector<Event>::iterator it;
	it = Events.begin();
	r2 = Reminder(e.Start, e.Current);
	int ReminderDays = CalcReminderInDays(r2);

	if (Events.size() == 0)
	{
		Events.push_back(e);
	}
	else {
		for (i = 0; it < Events.end(); i++, it++)
		{
			if (Events[i].CalcReminderInDays(Events[i].Reminder(Events[i].Start, Events[i].Current)) > ReminderDays)
			{//if we insert in index 0
				if (i == 0) {
					if (Events[i].Start.Month < e.end.Month || (Events[i].Start.Month == e.end.Month && Events[i].Start.Day <= e.end.Day))
					{
						cout << "Sorry This Time Alrady Contain An Event";
						break;
					}
					else {
						Events.insert(it, e);
						break;
					}
				}
				//if we insert in index > 0
				else if (i > 0) {
					// we can't insert if end date of event > start date of next event
					if (Events[i].Start.Month < e.end.Month || (Events[i].Start.Month == e.end.Month && Events[i].Start.Day <= e.end.Day))
					{
						cout << "Sorry This Time Alrady Contain An Event" << endl;
						break;
					}
					//we can't insert if start date of event > end date of previous event
					else if (e.Start.Month < Events[i - 1].end.Month || (e.Start.Month == Events[i - 1].end.Month && e.Start.Day <= Events[i - 1].end.Day))
					{
						cout << "Sorry This Time Alrady Contain An Event" << endl;
						break;
					}
					//ok now we can insert
					else {
						Events.insert(it, e);
						break;
					}
				}

			}
			// if we insert in last index
			else if (ReminderDays > Events.back().CalcReminderInDays(Events.back().Reminder(Events.back().Start, Events.back().Current)))
			{
				if (Events.back().end.Month > e.Start.Month || (Events.back().end.Month == e.Start.Month && Events.back().end.Day >= e.Start.Day))
				{
					cout << "Sorry This Time Alrady Contain An Event" << endl;
					break;
				}

				else {
					Events.push_back(e);
					break;
				}
			}
			
			else if (ReminderDays == 0 && Events[0].Start.Month < e.Current.Month || Events[0].Start.Month ==e.Current.Month && Events[0].Start.Day < e.Current.Day)
			{
				cout << "there is already an event in progress" << endl;
				Events.insert(it, e);
				break;
			}
		}
	}
}
int Event::CalcReminderInDays(Reminder_Date reminder)
{//to compare integers not struct
	int r;
	r = (reminder.Month_r * 30) + reminder.Day_r;
	return r;
}
void Event::ShowEvents()
{	
	cout<<  "________________________________________________________________________________" <<endl
		<<"Name" << "	| " << "Place" << "	| " << "Start Date" <<"	| " << "End Date" << "	| " << "Start hour " <<"	| " << "reminder day" << "| " << endl
		<< "________________________________________________________________________________" << endl;
	for (int i = 0; i < Events.size(); i++)
	{	

		cout << Events[i].Name << "	| " << Events[i].Place << "	| " << Events[i].Start.Day << "/" << Events[i].Start.Month << "/" << Events[i].Start.Year <<"	| " << Events[i].end.Day << "/" << Events[i].end.Month << "/" << Events[i].end.Year <<"	| " << Events[i].Start_Time << "		| " << Events[i].CalcReminderInDays(Events[i].Reminder(Events[i].Start, Events[i].Current) )<< endl;
	}
	cout << "________________________________________________________________________________" << endl;
}
void Event::ShowDoneEvents()
{
	if (Done_Events.size() == 0) {
		cout << "there is no done events " << endl;
	}
	else {
		cout << "________________________________________________________________________________" << endl
			<< "Name" << "	| " << "Place" << "	| " << "Start Date" << "	| " << "End Date" << "	| " << "Start hour " << "	| " << "reminder day" << "| " << endl
			<< "________________________________________________________________________________" << endl;
		for (int i = 0; i < Done_Events.size(); i++)
		{
			cout << Done_Events[i].Name << "	| " << Done_Events[i].Place << "	| " << Done_Events[i].Start.Day << "/" << Done_Events[i].Start.Month << "/" << Done_Events[i].Start.Year << "	| " << Done_Events[i].end.Day << "/" << Done_Events[i].end.Month << "/" << Done_Events[i].end.Year << "	| " << Done_Events[i].Start_Time << "		| " << Done_Events[i].reminder_days << endl;
		}
		cout << "________________________________________________________________________________" << endl;
	}
}
void Event::Delete(string EventName)
{
	int Test = 0;
	int i=0;
	vector<Event>::iterator it;
	it = Events.begin();
	for (i = 0; it < Events.end(); i++, it++) {
		if (Events[i].Name == EventName)
		{
			Events.erase(it);
			Test++;
			break;
			
		}
	}
	if (Test == 0)
	{
		cout << "Can't Found This Event ";
	}
	
	}
void Event::Update_an_event(string EventName)
{
	int Test = 0;
	int i = 0;
	vector<Event>::iterator it;
	it = Events.begin();
	for (i = 0; it < Events.end(); i++, it++) {
		if (Events[i].Name == EventName)
		{
			

			Test++;
			int a;
			cout << "To Update Event Name Press (1) " << endl;
			cout << "To Update Place Press (2) " << endl;
			cout << "To Update Start Date Press (3) " << endl;
			cout << "To Update End  Date Press (4) " << endl;
			cout << "To Update Start Time Press (5) " << endl;
			cout << "To Update All Detils Press (6)" << endl;
			cin >> a;
			switch (a)
			{
			case 1:
			{
				string name;
				cout << "enter new name" << endl;
				cin >> name;
				Events[i].Name = name;
				break;
			}
			case 2:
			{
				string place;
				cout << "enter new place" << endl;
				cin >> place;
				Events[i].Place = place;
				break;
			}
			case 3:
			{
				Event_Date r;
				Event e;
				e.Name = Events[i].Name;
				e.Place = Events[i].Place;
				cout << "enter new start day/month/year" << endl;
				cin >> r.Day >> r.Month >> r.Year;
				e.Start.Day = r.Day;
				e.Start.Month = r.Month;
				e.Start.Year = r.Year;
				e.end.Day = Events[i].end.Day;
				e.end.Month = Events[i].end.Month;
				e.Start_Time = Events[i].Start_Time;
				Events.erase(it);
				Insert(e);
				break;
			}
			case 4:
			{
				Event_Date r;
				Event e;
				e.Name = Events[i].Name;
				e.Place = Events[i].Place;
				e.Start.Day = Events[i].Start.Day;
				e.Start.Month = Events[i].Start.Month;
				e.Start_Time = Events[i].Start_Time;
				cout << "enter new start day/month/year" << endl;
				cin >> r.Day >> r.Month >> r.Year;
				e.end.Day = r.Day;
				e.end.Month = r.Month;
				e.end.Year = r.Year;
				Events.erase(it);
				Insert(e);

				break;
			}
			case 5:
			{
				cout << "Enter New Start Hour";
				int h;
				cin >> h;
				Events[i].Start_Time = h;
				break;
			}
			case 6:
			{    Events.erase(it);
			Insert(AddFromUser());
			}
			default:
			{	cout << "Invalid choice";

			}
			}


			break;
		}

	}
	if (Test == 0) {
		cout << "Can't Found This Event ";

	}
}

void Event::Reminder_Alert() {
	if (Events.size() == 0) {
		cout << " There is no upcoming Events" << endl;
	}
	else {


		r2 = Reminder(Events[0].Start, Events[0].Current);
		cout << " Your Upcoming Event is in " << r2.Month_r << " months " << r2.Day_r << " days" << endl << endl;
	}
}

void Event::exit() {
	ofstream file("event.txt");
	file << "";
	fstream Events_file;
	Events_file.open("event.txt", ios::app);
	for (int i = 0; i< Events.size(); i++) {
		Events_file << Events[i].Name << '|' << Events[i].Place << '|' << Events[i].Start.Day << '|' << Events[i].Start.Month << '|' << Events[i].Start.Year << '|' << Events[i].end.Day << '|' << Events[i].end.Month << '|' << Events[i].end.Year << '|' << Events[i].Start_Time << '|';	
	}
	Events_file.close();
	//the file of done events
	ofstream done("done_event.txt");
	done << "";
	fstream Events_done;
	Events_done.open("done_event.txt", ios::app);
	for (int i = 0; i < Done_Events.size(); i++) {
		Events_done << Done_Events[i].Name << '|' << Done_Events[i].Place << '|' << Done_Events[i].Start.Day << '|' << Done_Events[i].Start.Month << '|' << Done_Events[i].Start.Year << '|' << Done_Events[i].end.Day << '|' << Done_Events[i].end.Month << '|' << Done_Events[i].end.Year << '|' << Done_Events[i].Start_Time << '|';
	}
	Events_done.close();
}
	
void Event::done_events() {
	for (int i = 0; i < Events.size(); i++) {
		if (Events[i].CalcReminderInDays(Events[i].Reminder(Events[i].Start, Events[i].Current)) == 0) {
			if (Events[i].end.Month < Events[i].Current.Month || (Events[i].end.Month == Events[i].Current.Month && Events[i].end.Day < Events[i].Current.Day)) {
			Events[i].Done = true;
			Done_Events.push_back(Events[i]);
			Delete(Events[i].Name);
		}
		}
	
	}
}
	
