Your objective is to code the Pipex program. 
여러분의 목표는 Pipex 프로그램을 작성하는 것입니다.
It should be executed in this way:
여러분이 작성하신 프로그램은 다음과 같이 실행될 것입니다. :

    $> ./pipex file1 cmd1 cmd2 file2

Just in case: file1 and file2 are file names, cmd1 and cmd2 are shell commands with their parameters.
예를 들어, `file1`및 `file2`는 파일 이름이고 `cmd1` 및 `cmd2`는 매개변수에 대응하는 Shell 명령어 입니다.

The execution of the pipex program should do the same as the next shell command:
여러분의 Pipex 프로그램은 아래의 명령을 Shell에서 실행되는 것과 동일하게 처리해야 합니다.

    $> < file1 cmd1 | cmd2 > file2


## redirection 개요도

![pipex](./pipex.PNG)

child process에서 infile을 인풋으로한 cmd1을 실행시켜 pipe에 아웃풋.
pipe를 인풋으로 한 parent process에서 cmd2를 실행시켜 outfile로 아웃풋.