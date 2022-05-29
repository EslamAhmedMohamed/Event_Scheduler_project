#pragma once
#include<iostream>
#include <assert.h>
#include <string>
#include <vector>
#include<stack>
using namespace std;
struct Event_Date {
	int Day;
	int Month;
	int Year;
};
struct Reminder_Date {
	int Day_r;
	int Month_r;
	
};



class Event
{
	string Name;
	string Place;
	bool Done;
	int Start_Time;
	Reminder_Date reminder;
	Event_Date Start;
	Event_Date Current;
	Event_Date end;
	vector<Event> Events;
	
	vector<Event> Done_Events;
	Reminder_Date r2;
	Reminder_Date r3;
	int reminder_days;
	
public:
	Event();
	Event AddFromUser();
	Reminder_Date Reminder(Event_Date start, Event_Date current);
	void Insert(Event e);
	void Reminder_Alert();
	int CalcReminderInDays(Reminder_Date reminder);
	void ShowEvents();
	void ShowDoneEvents();
	void Delete(string Name);
	void Update_an_event(string Name);
	Event update_Date(int i, std::vector<Event>::iterator it);
	void exit();
	void start();
	void done_events();
};

