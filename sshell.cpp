#include <iostream>
#include <string>
#include <unistd.h>
#define MAX_LINE 80

using namespace std;

int main(int argc, char const *argv[])
{
    printf("Works!\n");

    // char *args[MAX_LINE / 2 + 1]; /* max of 40 arguments */
    string args;
    int should_run = 1;
    int i, upper, wstatus;
    pid_t pid, w;

    while (should_run)
    {
        printf("osh>");
        fflush(stdout);

        /** fork a child to execute command (using one of the exec calls)
             Break out of loop if user types ‘quit’ or ‘exit’ then exit
        program **/
        getline(cin, args); // second argument is of type streamsize and not int
        cout << args << endl;

        if (args == "exit" || args == "quit")
        {
            should_run = 0;
        }
        else
        {
            pid = fork(); // errors on my mingw env on windows (unistd not included?)
            switch (pid)
            {
            case -1:
                perror("fork creation failed");
                break;
            case 0:
                // execlp(args);
                printf("fork finished\n");
                break;
            default:
                printf("parent finished\n");

                // waiting for children to finish
                w = wait(&wstatus);
                if (!WIFEXITED(wstatus))
                {
                    printf("child not terminated normally\n");
                }
                break;
            }
        }
    }

    return 0;
}
