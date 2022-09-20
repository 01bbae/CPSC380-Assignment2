#include <iostream>
#include <string>
#include <unistd.h>
#define MAX_LINE 80

using namespace std;

int main(int argc, char const *argv[])
{
    printf("Works!");
    
    char *args[MAX_LINE/2 + 1]; /* max of 40 arguments */
    int should_run = 1;
    int i, upper;

    while (should_run) {   
        printf("osh>");
        fflush(stdout);
        
        /** fork a child to execute command (using one of the exec calls)
             Break out of loop if user types ‘quit’ or ‘exit’ then exit   
        program **/
        string userInput = "";
        cin >> userInput;
        if (userInput == "quit" || userInput == "exit"){
            should_run = 0;
        }else if(!userInput.empty() and userInput != "\n"){
            userInput.pop_back();
            // pid_t fork();
            // exec();
        }
   }

    return 0;
}
