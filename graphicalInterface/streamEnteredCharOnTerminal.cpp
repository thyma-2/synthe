#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <iostream>

int main()
{
    struct termios oldTerminalConf, newTerminalConf;
    unsigned char keyEntered;

    /* get the terminal settings for stdin */
    tcgetattr(STDIN_FILENO,&oldTerminalConf);
    /* we want to keep the old setting to restore them a the end */
    newTerminalConf = oldTerminalConf;

    /* disable canonical mode (buffered i/o) and local echo */
    newTerminalConf.c_lflag &=(~ICANON & ~ECHO);

    /* set the new settings immediately */
    tcsetattr(STDIN_FILENO,TCSANOW,&newTerminalConf);

    while (1)
    {
        keyEntered = getchar();
        std::cout << keyEntered << std::endl;
    }

    /* restore the former settings */
    tcsetattr(STDIN_FILENO,TCSANOW,&oldTerminalConf);

    return 0;
  }
