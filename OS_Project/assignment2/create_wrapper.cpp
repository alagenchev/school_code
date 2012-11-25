#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>


using namespace std;

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
int count_stars(const char *text);

int main(int argc, char** argv)
{
    /*
       if(argc != 3)
       {
       std::cout<<"USAGE: create_wrapper inputFile outputFile"<<endl;
       }*/

    string inputLine;
    string outputFileName = "output.c";

    ifstream inputFile(argv[1], ifstream::in);
    ofstream outputFile(outputFileName.c_str(), ofstream::out);

    output_headers(outputFile);
    while(getline(inputFile, inputLine))
    {
        if(inputLine.length() > 1 && inputLine[0]=='/' && inputLine[1] == '/')
        {
            continue;
        }

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

        output_dmtcp_stuff(outputFile);

        output_replaced_call(outputFile, function_name, params);

        outputFile<<"}"<<endl;
    }

    return 0;
}

void output_headers(std::ofstream &output)
{
    output<<"#define _GNU_SOURCE"<<endl;
    output<<"#include <stdio.h>"<<endl;
    output<<"#include <stdlib.h>"<<endl;
    output<<"#include <stdarg.h>"<<endl;
    output<<"#include <unistd.h>"<<endl;
    output<<"#include <sys/types.h>"<<endl;
    output<<"#include <dlfcn.h>"<<endl;
    output<<"#include \"dmtcpaware.h\""<<endl;
    output<<endl;
}
std::vector<std::string> get_parameter_names(std::string line)
{

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

            parameters.push_back(parm_name);
            break;//if we've parsed the last parm, don't parse anymore
            //index = line.find_first_of(parm_name);
            //int start = index + parm_name.length();
            // int length = line.length() - parm_name.length();
            //	line = line.substr(start, length);
        }
        else
        {
            string temp = line.substr(0, index);
            temp = trim(temp);
            parm_name = extract_parm_name(temp);

            line = line.substr(index + 1, line.length() - index);

            parameters.push_back(parm_name);
        }


        line = trim(line);
    }
    while(line.length() != 0);

    return parameters;
}

std::string extract_parm_name(std::string text)
{
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

    const char *name_ptr = name.c_str();

    while(*name_ptr == '*')
    {
        name_ptr++;
    }

    name = string(name_ptr);

    return name;
}
void replace_varargs_call(std::ofstream &output, std::string func_name, std::vector<std::string> params)
{
    output<<"\treturn_value = ";
    if(func_name.find("fscanf") != std::string::npos )
    {
        output<<"vfscanf(";
    }
    else if(func_name.find("sscanf") != std::string::npos )
    {
        output<<"vsscanf(";
    }
    else if(func_name.find("scanf") != std::string::npos )
    {
        output<<"vscanf(";
    }
}

void output_replaced_call(std::ofstream &output, std::string func_name, std::vector<std::string> params)
{

    output<<endl;
    output<<"\tFILE *fp;"<<endl;
    output<<"\tfp=fopen(\"trace.txt\",\"a\");"<<endl;
    output<<"\tfprintf(fp,\"REPLACED: "<<func_name<< "\\n\");"<< endl;
    output<<"\tfclose(fp);"<<endl;
    output<<endl;

    bool hasVarArgs = false;

    for(std::vector<string>::size_type i = 0; i < params.size(); i++)
    {
        if(i < params.size() - 1 && params[i+1] == "...")
        {
            output<<"\tva_list args;"<<endl;
            output<<"\tva_start(args, __format);"<<endl;
            hasVarArgs = true;
        }
    }


    if(hasVarArgs)
    {
        replace_varargs_call(output, func_name, params);
    }
    else
    {

        output<<"\ttypeof("<<func_name<<") *old_"<<func_name<<";"<<endl;
        output<<"\told_"<<func_name<<" = dlsym(RTLD_NEXT, \""<<func_name<<"\");"<<endl;
        output<<"\treturn_value = (*old_"<<func_name<<")(";
    }

    for(std::vector<string>::size_type i = 0; i < params.size(); i++)
    {
        if(i < params.size() - 1 && params[i+1] == "...")
        {

            output<<params[i];

            output<<", args";
        }
        else if(params[i]!="..." && params[i]!="void")
        {
            output<<params[i];
        }
        if(i != params.size() - 1 && params[i+1] != "...")
            //we check for varargs before we are actually at the varargs args, so skip the comma
        {
            output<<", ";
        }
    }

    output<<");"<<endl;


    if(hasVarArgs)
    {
        output<<"\tva_end(args);"<<endl;
    }
    output<<"\treturn return_value;"<<endl;
}

void output_dmtcp_stuff(std::ofstream &output)
{
    output<<endl;
    output<<"\tif(dmtcpIsEnabled())"<<endl;
    output<<"\t{"<<endl;
    output<<"\t\tdmtcpCheckpoint();"<<endl;
    output<<"\t}"<<endl;
    output<<endl;

}

std::string get_function_name(std::string line)
{

    int open_paren_pos = line.find_first_of("(");
    string temp = line.substr(0, open_paren_pos - 1);
    int index = temp.find_last_of(" ");

    temp = temp.substr(index + 1,temp.length());

    const char *temp_ptr = temp.c_str();

    while(*temp_ptr == '*')
    {
        temp_ptr++;
    }

    temp = string(temp_ptr);

    return temp;

}

std::string get_return_type(std::string line)
{

    string return_type = "";
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
        int index = temp.find(" ");
        return_type = temp.substr(0, index);
        return_type = trim(return_type);
        return_type +=" ";  //this combined with the above might be weird, 
        //but I'm making sure the # of spaces is consistent

        int num_stars = count_stars(temp.c_str());

        for(int i = 0; i < num_stars; i++)
        {
            return_type += "*";
        }

    }
    else
    {
        int index = temp.find(" ");
        return_type = temp.substr(0, index);
    }

    return return_type;
}

int count_stars(const char *text)
{

    const char * ptr = text;
    int count = 0;

    while(*ptr != '\0')
    {
        if(*ptr == '*')
        {
            count++;
        }

        ptr++;
    }

    return count;

}

std::string get_line_header(std::string line)
{
    int semicolon_pos = line.find_last_of(";");
    string header = line.substr(0, semicolon_pos);

    int index = header.find("__THROW");

    if(index >=0)
    {
        string temp = header.substr(0, index);
        temp += header.substr(index + 7, header.length() - index - 7); 
        header = temp;
    }
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
