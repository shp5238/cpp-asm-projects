# Project: Building a Shell
This project is a custom shell program that provides essential command-line functionalities, including displaying files in the current directory, changing to the home and root directories, and showing a usage message for user guidance. It also features background process management with notifications and supports sending signals to specific processes, allowing users to execute commands like kill and sleep on targeted process IDs. Designed to demonstrate key operating system concepts such as process control, signal handling, and directory navigation, this shell offers a simplified yet functional environment for both learning and practical use.


## Author
- [@shp5238](https://www.github.com/shp5238)


## Screenshots

![Results Screenshot](screenshot.png)

## Lessons Learned

While building this custom shell project, I gained practical experience with core operating system concepts such as process management, inter-process communication, and signal handling. I developed strong skills in using system calls like fork(), execvp(), and handling signals (SIGINT, SIGCHLD) to manage foreground and background processes effectively. One significant challenge was implementing asynchronous background process management without impacting shell responsiveness. I overcame this by designing an efficient SIGCHLD signal handler that properly reaps child processes, preventing zombie processes and maintaining smooth user interaction. Additionally, I enhanced my expertise in command-line parsing and dynamic memory management to ensure reliable input processing and prevent memory leaks. This project strengthened my abilities in low-level system programming, C/C++ development, and building robust, user-friendly command-line interfaces—skills that are highly valuable for roles in systems programming, embedded development, and software engineering.


## License

[MIT](https://choosealicense.com/licenses/mit/)
