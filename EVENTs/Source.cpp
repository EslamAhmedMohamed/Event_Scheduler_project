#include "Event.h"
 

int main()
{
	
	int Choice;
	Event Temp_Event;
	char Continue;
	string Update_Name, Delete_Name;
	Temp_Event.start();
	Temp_Event.done_events();
	do
	{
		Temp_Event.Reminder_Alert();

		cout << "Enter '1' To Add New Event " << endl;
		cout << "Enter '2' To Update An Existing Event" << endl;
		cout << "Enter '3' To Show Your Events" << endl;
		cout << "Enter '4' To Delete An Event  " << endl;
		cout << "Enter '5' To Show Done Events " << endl;
		cout << "Enter '6' To EXIT  " << endl;
		cin >> Choice;

		switch (Choice)
		{
		case 1:
		{

			Temp_Event.Insert(Temp_Event.AddFromUser());
			cout << "			__________________________________			\n\n";
			break;

		}
		case 2:
		{
			cout << "Please Enter The Name Of The Event You Want To Update: " << endl;
			cin >> Update_Name;
			Temp_Event.Update_an_event(Update_Name);
			cout << "			__________________________________			\n\n";
			break;
		}
		case 3:
		{
			Temp_Event.ShowEvents();
			cout << "			__________________________________			\n\n";
			break;
		}
		case 4:
		{
			cout << "Please  Enter The Name Of The Event You Want To Update: " << endl;
			cin >> Delete_Name;
			Temp_Event.Delete(Delete_Name);
			cout << "			__________________________________			\n\n";
			break;
		}
		case 5: {
			Temp_Event.ShowDoneEvents();
			cout << "			__________________________________			\n\n";
			break;
		}
			
		}
	}
		while (Choice != 6);
		Temp_Event.exit();
	}

