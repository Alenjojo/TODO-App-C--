#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include <vector>
#include <iterator>
#include <bits/stdc++.h>
using namespace std;
std::vector<std::string> names,done;
int lists(bool c , bool d);
void display(){
        lists(false,false);
        if(names.size()==0){
         cout << "There are no pending todos! \n";
        }else{
           for(int n=names.size()-1;n>=0;n--){
           cout<< "["<< n+1 <<"] "<<names[n]<< "\n";
        }
      }
   }
void help(){
std::cout<<"Usage :-\n";
std::cout<<"$ ./todo add \"todo item\"  # Add a new todo\n";
std::cout<<"$ ./todo ls               # Show remaining todos\n";
std::cout<<"$ ./todo del NUMBER       # Delete a todo\n";
std::cout<<"$ ./todo done NUMBER      # Complete a todo\n";
std::cout<<"$ ./todo help             # Show usage\n";
std::cout<<"$ ./todo report           # Statistics\n";
}
int lists(bool c,bool d){
    int count=0;
    if(d){
        std::ifstream file("done.txt");
        std::string input;
        names.clear();
        while(getline(file,input)){
            ++count;
            names.push_back(input);}
         }else{
             std::ifstream file("todo.txt");
             std::string input;
             names.clear();
             while(getline(file,input)){
               ++count;
                names.push_back(input);
               }
             }
     if(c){
            return count;
        }
}
string time_ret()
{
	time_t ti;
	ti = time(NULL);
	struct tm time = *localtime(&ti);
	return (to_string(1900 + time.tm_year) + "-" +
		(((1 + time.tm_mon) < 10) ? "0" + to_string(1 + time.tm_mon) : to_string(1 + time.tm_mon)) + "-" + (((time.tm_mday) < 10) ? "0" + to_string(time.tm_mday) : to_string(time.tm_mday)) + " ");
}
void report(){
    int count1=lists(true,false),count2=lists(true,true);
cout << time_ret() << "Pending : " << count1 << " Completed : " << count2 << "\n";
}
int main(int argc, char* argv[])
{
	string Error;
	switch (argc) {
case 1:
help();
        break;
case 2:
        if (strcmp(argv[1], "help") == 0) {         help();
        }else if (strcmp(argv[1], "ls") == 0) {         display();
        }else if (strcmp(argv[1], "report") == 0) {        report();
    } else if (strcmp(argv[1], "add") == 0)
            cout << "Error: Missing todo string. Nothing added! \n";
        else if (strcmp(argv[1], "del") == 0)
            cout << "Error: Missing NUMBER for deleting todo. \n";
        else if (strcmp(argv[1], "done") == 0)
            cout << "Error: Missing NUMBER for marking todo as done. \n";
        break;
case 3:
   if (strcmp(argv[1], "add") == 0) {

           		    std::ofstream file("todo.txt",std::ios::app);
                	    file<<argv[2]<<"\n";
            		    file.close();
   			    cout<<"Added todo: "<<"\""<<argv[2]<<"\" \n";

         }else if (strcmp(argv[1], "done") == 0) {
		int count=lists(true,false);
              	if(count!=0 && !(strcmp(argv[2], "0") == 0) && (stoi(argv[2]) <= names.size()))
		{
              	 std::ofstream donefile("done.txt",std::ios::app);
                    done.push_back("x "+ time_ret()  + names[stoi(argv[2]) - 1]);
                    ostream_iterator<string> o_iter2(donefile, "\n");
                    copy(done.begin(), done.end(), o_iter2);donefile.close();

                     std::ofstream file("todo.txt");
                    names.erase(names.begin() + stoi(argv[2]) - 1);
                    ostream_iterator<string> o_iter(file, "\n");
                    copy(names.begin(), names.end(), o_iter);file.close();
                    cout<<"Marked todo #"<< argv[2]<<" as done.\n";
                 }else if (count == 0)
                     cout<<"There are no pending todos!\n";
                  else
                     cout<<"Error: todo #0 does not exist.\n";
	 }else if (strcmp(argv[1], "del") == 0){

       			int count=lists(true,false);
         		if(lists(true,false)!=0 && (stoi(argv[2]) <= names.size()) && (strcmp(argv[2], "0") != 0)){
         		std::ofstream wrfile("todo.txt");
         		names.erase(names.begin() + stoi(argv[2]) - 1);
         		ostream_iterator<string> o_iter(wrfile, "\n");
         		copy(names.begin(), names.end(), o_iter);
         		wrfile.close();
         		cout << "Deleted todo #" << argv[2] << "\n"; 
	}else if (count == 0)
                     cout<<"There are no pending todos!\n";
                  else
                     cout<<"Error: todo #"<<argv[2]<<" does not exist. Nothing deleted.\n";
        }
    }
	return 0;
}


