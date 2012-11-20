#include <iostream>
#include <string>
#include <fstream>

std::string get_line_header(std::string line);
std::string get_return_type(std::string line);
std::string get_function_name(std::string line);
void output_dmtcp_stuff(std::ofstream &output);
void output_replaced_call(std::ofstream &output, std:: string func_name, std::string params[]);
void get_parameter_names(std::string line, std::string params[]);


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
	string* params;

    ifstream inputFile(argv[1], ifstream::in);
    ofstream outputFile(outputFileName.c_str(), ofstream::out);
    
    while(getline(inputFile, inputLine))
    {
        string header = get_line_header(inputLine);
        string return_type = get_return_type(inputLine);
        string function_name = get_function_name(inputLine);
		get_parameter_names(inputLine, params);

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

void get_parameter_names(std::string line, std::string params[])
{
	using namespace std;
	cout<<"line is "<<line<<endl;
}

void output_replaced_call(std::ofstream &output, std::string func_name, std::string params[])
{
	using namespace std;
	output<<"\told_"<<func_name<<" = dlsym(RTLD_NEXT, \""<<func_name<<"\");"<<endl;
	output<<"\treturn_value = (*old_"<<func_name<<")(";
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
