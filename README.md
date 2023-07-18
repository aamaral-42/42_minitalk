# 42_minitalk

In this project we have to transmit a message from the Client process to the Server process.

run ```cmake```

run ```./server```

run ```./client <server_pid> <message to transmit>```

# CONTENTS
1. [New Knowledge](https://github.com/aamaral-42/42_minitalk/edit/main/README.md#new-knowledge)
2. [Recicled Knowledge](https://github.com/aamaral-42/42_minitalk/edit/main/README.md#recicled-knowledge)
3. [Client functions](https://github.com/aamaral-42/42_minitalk/edit/main/README.md#-client-functions-)
4. [Server functions](https://github.com/aamaral-42/42_minitalk/edit/main/README.md#-server-functions-)
5. [For future improvements](https://github.com/aamaral-42/42_minitalk/edit/main/README.md#for-future-improvements)

## _______New KNOWLEDGE_______

- **int kill(pid_t pid, int sig)**

system call to send a specific signal to a process with pid number

- **void (\*signal(int signo, void (\*func )(int)))(int)**

receives the signal as an int (see list of possible signals) and performs the function specified in the second argument

- **SIGUSR1 , SIGUSR2**

user-defined signal 1 ; user-defined signal 2

- **pid_t variable type**

## Recicled KNOWLEDGE
- **static variables (get_next_line)**
- **atoi and itoa (libft and Piscine)**
- **Euclidean division (primary school)**

| MSB |	2^7 | 2^6 | 2^5 | 2^4 | 2^3 | 2^2 | 2^1	| 2^0 |	LSB |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|     |   = | =   | =	| =   | =   | =   | = |  =  |       |
|     |128	|64	|32|	16|	8|	4|	2|	1|	|
|index|	0|	1|	2|	3|	4|	5|	6|	7| |	
|bit   |7|  6 |5|	4|	3|	2|	1|	0| |

ps: remember that MSB at left is computer architecture dependent

---
## ****** CLIENT FUNCTIONS ******
---
- **int main(int argc, char \*\*argv)**
	- receives the arguments from CLI
	- checks if arguments are correct
	- converts the server pid [arg 1] into an integer
	- transmits bit by bit to server pid

- **int invalid_arg(int argc, char \*\*argv)**

checks if the arguments are correct:

 1. 3 arguments(argc)
 2. entered an integer (argv 1) 
 3. string message isn't empty (argv 2)

- **int ft_atoi(const char \*pid_str)**
  
converts string of characters representing numbers to an integer to get server *pid process number*, variable type for pid is unsigned int or pid_t

- **int transmmit_ascii_binary(char \*message, pid_t server_process_id)**
  
goes through each character and decomposes each caracter ascii value into 8 bits (in CLI run ```man ascii 3``` to find the correspondence character value)

to transmit each bit it uses the Euclidean algorithm (the division method learned in primary school) (**1 byte = 8 bits**)
 1. starts by the Most Significant Bit - MSB (2^7 = 128) this will be always zero since I only deal with ASCII characters (from 0 to 127) sends a SIGUSR2 to represent a '0'
 2. goes to the next bit (2^6 = 64) if ascii value is greater than 64 then sends a SIGUSR1 to represent '1' and subtract from ascii number the value 64; if the value is lower sends a SIGUSR2 to represent a '0'
 3. goes to the next bit (2^5 = 32) and follow the same algorithm (of Euclidean division)
 4. until the Least Significant Bit - LSB (1 = 2^0)

gives 242 microseconds for the server to make some calculations

###### **(optional)**

- **void send_signal_sleep(pid_t s_id, int signal_nbr,unsigned int microsec)**

Use this option if your computer is slow. Slow either computer's own architecture or computer is running heavily programs

substitute lines kill(server_process_id, SIGUSR1) and kill(server_process_id, SIGUSR2); with the following lines send_signal_sleep(server_process_id, 10, 24); send_signal_sleep(server_process_id, 12, 24);

---
## ***** SERVER FUNCTIONS *****
---
- **int main(void)**
	- writes it's own pid
	- assigns what function should be activated when receives SIGUSR1 and SIGUSR2
	- waits until receives a system call signal

- **void ft_itoa(pid_t number)**
  
an exquisite and extremely compact itoa. (just see it to believe it)

- **void save_str_bit(int sig)**
  
uses static variables to mantain the information when the function is repeatedly called (after receiving each signal from Client representing one bit - or zero or one)

after 8 bits (1 byte - 1 ascii character) the string stored is converted into an ascii value representing an character by the function convert_bits_to_char.

- **void convert_bits_to_char(char \*binary_str)**
  
receives the string of zeros and ones (8 characters) and will convert it into an integer using the oposite calculations used in the Client algorithm.
 1. Starts with MSB (2^7) that will be zero (since we deal only with ascii numbers from 0 to 127)
 2. goes to the next bit (2^6) if the character is '1' means that we are going to add 64
 3. goes to the next bit (2^5 or 2^6/2) if the character is '1' means that we are going to add 32
 4.at the LSB (2^0 or 2^1/2) if the character is '1' means that we are going to add 1
after all these sums the final value will be the correspondent ascii character

and finally it will write in the STDOUT the respective character

These 2 last functions will be called as many times as many characters were written in the CLI (command line)

## For future improvements
- make the bonus part using bitwise operators and CRC

- create a Makefile or bash scripting to use only one command (example ./minitalk )
 	- create a variable and assign the string to be transmitted from the command ./minitalk
	- compile the server and client c files - runs the ./server - goes to the server output and retrieves the pid number
	- stores pid in a variable
	- runs the ./client and use as [argv 1] [argv 2] the variables created before
	- waits for new messages to be inserted in the command line

If you have the time and ability to make this Make file or bash scripting please help me
