#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    // The  getcwd()  function copies an absolute pathname of the current working directory to the array pointed to
    // by buf, which is of length size.

    //RETURN VALUE
    //  On success, these functions return a pointer to a string containing the pathname of the current working  directory.
    //  On  failure, these functions return NULL
    char buff[100];
    printf("%s\n", getcwd(buff, 100));
    
    
    
    // chdir() changes the current working directory of the calling process to the directory specified in path.
    //RETURN VALUE
    // On success it returns 0, -1 on error;
    
    char s[100];

    printf("%s\n", getcwd(s, 100));
    char *newdir = "/home/mbrouk/donot";
    chdir(newdir);

    printf("%s\n", getcwd(s, 100));



    // setenv()---> this set an env variable (its name, its value, overwrite it or not)  *****NOT ALLOWED IN MINISHELL*****
    // getenv()---> searches  the environment list to find the environment variable name, and returns a pointer to the corresponding value string.
    char *name = "HASSAN";
    char *value= "STUDENT";
    setenv(name, value, 1);
    printf("%s \n",getenv(name));

    return 0;
}
