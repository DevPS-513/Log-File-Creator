#ifndef _LOG_H_
#define _LOG_H_

/* This library writes to a single log file */
// known issues 1. you cannot have the log file open while the program is running, most forums say this is the norm
//              2. The class only writes to a single file, a new instance of Log may work 
//              3. Use forward slash / within filedirectory variable, "\" wont work i.e C:/Users, not C:\User
//				4. not set up to return error flags
//		Agust 16thh Class functions:
//      
//      Log.setup("C:/Users/Mbethune-Waddell/Desktop/test_directory/", "Log_File.txt");		Puts the file at the specified directory
//      Log.write_line("test");																will write a line to the file
//      Log.write_line_with_timestamp("test");												i.e will write "test :Mon Aug 15th 16:41:43"
//      Log.append("test");		
//      Log.close_log_file();                                                                Close the file, can then be edited on disk
//      Log.reopen_log_file();                                                                re-open the same file
//      Log.reset_log_file();																Create a new log file, erase contents
//      Log.delete_log_file;																Delete the file off the disk
//      Log.timestamp();                                                                    Append a timestamp
//      Log.newline();																	    Write a new line
//      Log.shutdown();                                                                     free up all space that has been pre-allocated, with malloc

#include	"stdafx.h"     
#include	"LogClass.h"
#include	<stdlib.h>		// C++ standard library
#include	<string>		// Library for string functions, i.e strlen
#include	"malloc.h"      // Library for memory allocation
#include	<time.h>		// Library for system time stamp


#define MAX_LINE_LENGTH 200			// Maximum Bytes of a log file line, .csv cannot exceed 250 b per wow
#define HALF_LINE_LENGTH 175		// Half of the maxium, for combining two charecter arrays

using std::string;


class LogClass
{
public:
	FILE *pFile;

	// Initialize File pointer for log file
	string logline;
	string filename;
	string filedirectory;
	string fullpath;

	void setup(string logfile_directory, string logfile_name)
	{

		// i.e Log.setup("C:/Users/Mbethune-Waddell/Desktop/test_directory/", "Log_File.txt");
		//		Directory must have forward slash "/", not backward slashes.
		// Allocate 250 bytes for each line,
		filename = logfile_name;					// Allocate 50b for filename
		filedirectory = logfile_directory;		// aAllocate 250b for directory
		fullpath = filedirectory + filename;
		// Store the filename

		// combine directory and name for the full path


		// Open Log file for writing

		pFile = fopen(fullpath.c_str(), "w");	// Open Log file for writing

												// Write a header for the log file
		append(" *** ");
		append(fullpath.c_str());
		append(" *** ");
		newline();
		append(" *** ");
		append("Created\t");
		timestamp();
		append(" *** ");

		newline();
		newline();
	}


	void write_line(string logline)					// Function to write a line to the file
	{
		fprintf(pFile, logline.c_str());					// Write the input line
		fprintf(pFile, "\n");						// Write a new line charecter
	}

	void write_line_with_timestamp(string logline)		// Function to write a line to the file
	{
		timestamp();
		fprintf(pFile, logline.c_str());						// Write the input line	
		newline();												// Write a time stamp

	}

	void append(string logline)					// Function to append to the current line
	{
		fprintf(pFile, logline.c_str());				// Write the input line
	}



	void reopen_log_file()
	{
		pFile = fopen(fullpath.c_str(), "a");	// appends to the file, without eraseing the content
	}

	void close_log_file()
	{
		fclose(pFile);
	}


	void reset_log_file()
	{
		fclose(pFile);
		setup(filedirectory, filename);
	}


	void delete_log_file()
	{
		fclose(pFile);
		remove(fullpath.c_str());
	}

	void timestamp()
	{
		char *date;
		time_t timer;											/* calendar time */
		timer = time(NULL);
		date = asctime(localtime(&timer));						/* get current cal time */
		date[strlen(date) - 1] = '\0';							//remove default newline charecter
		fprintf(pFile, "%s \t ", date);
	}


	void newline()
	{
		fprintf(pFile, "\n");
	}

	// Constructor and Destructor, not sure what these do
	LogClass();
	~LogClass();
};


// Assume an instance of this class is used elsewhere as "Log"
extern LogClass Log;

#endif 