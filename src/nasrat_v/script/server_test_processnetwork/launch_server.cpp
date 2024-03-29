
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <string>
#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

# define BUFF_SIZE	4096
# define UTIME_WAIT	50000
# define PATH		"/home/nasrat_v/Dev/srv_fire/src/nasrat_v/input/image/sample-image"

int main(int ac, char **av)
{
    static size_t id = 0;
    std::string path = "";
    std::string netcat_arg = "";
    ssize_t ret;
    char buff[(BUFF_SIZE + sizeof(char))] = { 0 };
    int pipefd[2];

    if (ac < 2)
    {
	std::cout << "./server port" << std::endl;
	return (1);
    }
    pipe(pipefd);
    if (fork() == 0)
    {
	dup2(pipefd[0], 0);
	close(pipefd[1]);
	netcat_arg = ("nc -l -p " + std::string(av[1]));
	system(netcat_arg.c_str());
    }
    else
    {
	dup2(pipefd[1], 1);
	close(pipefd[0]);
	ret = read(0, buff, BUFF_SIZE);
	buff[ret] = '\0';
	while (42)
	{
	    write(2, std::to_string(id).c_str(), std::to_string(id).size());
	    write(2, "\n", 1);
	    path = (std::string(PATH) + std::to_string(id++) + std::string(".jpg"));
	    write(1, path.c_str(), strlen(path.c_str()));
	    path = "";
	    usleep(UTIME_WAIT);
	}
	waitpid(-1, NULL, 0);
    }
    return (0);
}
