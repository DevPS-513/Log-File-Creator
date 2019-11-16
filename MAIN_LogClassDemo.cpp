
#include	"stdafx.h"
#include	"LogClass.h"
#include	<stdlib.h>
#include	<iostream>
#include	<string>
#include	"stdlib.h"
#include	"malloc.h"

using namespace std; // needed for console window and string class
LogClass Log;
FILE * pFile;

int main()
{
	string directory = "./";
	string file_name = "Log_file.txt";
	int command_number;

	Log.setup(directory, file_name);

	cout << "testing the log class,file is at: \t " << directory << endl;


	Log.write_line_with_timestamp("this line happened at this time");
	Log.write_line_with_timestamp("and then this line happened after");
	Log.write_line("This is a line without a timstamp");
	Log.write_line("Here is another line without a timestamp");

	Log.timestamp();
	Log.append("\t a custom timestamp line by calling timestamp(), then append(), then newline()");
	Log.newline();
	Log.write_line(" now lets close the file, you can now edit the file on disk");
	Log.close_log_file();
	// tell user whats going on
	cout << "The file is now closed and can be opened on disk, press any key to reopen file" << endl;
	system("pause");
	Log.reopen_log_file();
	Log.write_line(" file re-opened! here is a new line");
	cout << " a new line was added to the file" << endl;
	Log.close_log_file();
	cout << " if you want to delete the text file, enter 1" << endl;
	cin >> command_number;
	if (command_number == 1)
	{
		Log.delete_log_file();
	}
	system("pause");





	return 0;
}


