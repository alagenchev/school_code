#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

std::string get_line_header(std::string line);
std::string get_return_type(std::string line);
std::string get_function_name(std::string line);
void output_dmtcp_stuff(std::ofstream &output);
void output_replaced_call(std::ofstream &output, std:: string func_name, std::vector<std::string> params);
std::vector<std::string> get_parameter_names(std::string line);
void output_headers(std::ofstream &output);
static inline std::string &ltrim(std::string &s);
static inline std::string &trim(std::string &s);
std::string extract_parm_name(std::string text);


int main(int argc, char** argv)
{
	using namespace std;
	/*
	   if(argc != 3)
	   {
	   std::cout<<"USAGE: create_wrapper inputFile outputFile"<<endl;
	   }*/

	string inputLine;
	string outputFileName = "output.txt";

	ifstream inputFile(argv[1], ifstream::in);
	ofstream outputFile(outputFileName.c_str(), ofstream::out);

	output_headers(outputFile);
	while(getline(inputFile, inputLine))
	{
		string header = get_line_header(inputLine);
		string return_type = get_return_type(inputLine);
		string function_name = get_function_name(inputLine);
		vector<string> params = get_parameter_names(inputLine);

		outputFile<<header<<endl;
		outputFile<<"{"<<endl;
		if(return_type != "void")
		{
			outputFile<<"\t"<<return_type<<" return_value;"<<endl;
		}
		outputFile<<"\ttypeof("<<function_name<<") *old_"<<function_name<<";"<<endl;
		output_dmtcp_stuff(outputFile);
		output_replaced_call(outputFile, function_name, params);
		outputFile<<"}"<<endl;
		//outputFile<<inputLine<<endl;
	}

	return 0;
}
void output_headers(std::ofstream &output)
{
	using namespace std;
	output<<"#include <stdio.h>"<<endl;
	output<<"#include <stdlib.h>"<<endl;
	output<<"#include <stdarg.h>"<<endl;
	output<<"#include <unistd.h>"<<endl;
	output<<"#include <sys/types.h>"<<endl;
	output<<"#include <dlfcn.h>"<<endl;
	output<<"include \"dmtcpaware.h\""<<endl;
	output<<endl;
}
std::vector<std::string> get_parameter_names(std::string line)
{
	using namespace std;

	vector <string> parameters;
	int start = line.find("(");
	int end = line.find(")");
	line = line.substr(start + 1, end - start - 1);
	line = trim(line);

	if(line.length() == 0)//we have no params
	{
		return parameters;
	}

	int index = (int)string::npos;

	do
	{
		index = line.find_first_of(',');
		string parm_name = "";

		if(index == string::npos)//parse single parm
		{
			line = trim(line);
			parm_name = extract_parm_name(line);
			index = line.find_first_of(parm_name);
			line = line.substr(index + parm_name.length(), line.length() - parm_name.length());
		}
		else
		{
			string temp = line.substr(0, index);
			temp = trim(temp);
			parm_name = extract_parm_name(temp);

			line = line.substr(index + 1, line.length() - index);
		}

		parameters.push_back(parm_name);

		line = trim(line);
	}
	while(line.length() != 0);

	return parameters;
}

std::string extract_parm_name(std::string text)
{
	using namespace std;
	string name = "";
	int index = text.find_last_of(" ");//get beginning of parm name
	if(index == -1)
	{
		index = text.find("...");//variable list parameter
		if(index > -1)
		{
			return "...";
		}
	}
	name = text.substr(index + 1, text.length() - index - 1);

	char *name_ptr = new char[name.length() + 1];
	std::copy(name.begin(), name.end(), name_ptr);

	while(*name_ptr == '*')
	{
		name_ptr++;
	}
	
	name = string(name_ptr);

	delete[] name_ptr;
	return name;
}

void output_replaced_call(std::ofstream &output, std::string func_name, std::vector<std::string> params)
{
	using namespace std;
	output<<"\told_"<<func_name<<" = dlsym(RTLD_NEXT, \""<<func_name<<"\");"<<endl;
	output<<"\treturn_value = (*old_"<<func_name<<")(";
	cout<<"params"<<endl;

	for(std::vector<string>::size_type i = 0; i < params.size(); i++)
	{
		cout<<params[i]<<endl;
	}
	//output<< output all parameters here
	output<<"\treturn return_value;"<<endl;
}

void output_dmtcp_stuff(std::ofstream &output)
{
	using namespace std;
	output<<endl;
	output<<"\tif(dmtcpIsEnabled())"<<endl;
	output<<"\t{"<<endl;
	output<<"\t\tdmtcpCheckpoint();"<<endl;
	output<<"\t}"<<endl;
	output<<endl;

}

std::string get_function_name(std::string line)
{
	using namespace std;

	int open_paren_pos = line.find_first_of("(");
	string temp = line.substr(0, open_paren_pos - 1);
	int index = temp.find_last_of(" ");

	temp = temp.substr(index + 1,temp.length());

	return temp;

}

std::string get_return_type(std::string line)
{
	using namespace std;

	int open_paren_pos = line.find_first_of("(");
	string temp = line.substr(0, open_paren_pos);
	int hasExtern = temp.find("extern");

	if(hasExtern >= 0)
	{
		temp = temp.substr(hasExtern + 7, temp.length());
	}

	int hasPtr = temp.find("*");

	if(hasPtr >= 0)
	{
	}
	else
	{
		int index = temp.find(" ");
		string return_type = temp.substr(0, index);
		return return_type;
	}

	return "";
}

std::string get_line_header(std::string line)
{
	using namespace std;
	int semicolon_pos = line.find_last_of(";");
	string header = line.substr(0, semicolon_pos);
	return header;
}


// trim from start
static inline std::string &ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
	return ltrim(rtrim(s));
}
