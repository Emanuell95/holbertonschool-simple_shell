 Simple Shell

Description

The gates of shell is a project , that helps student to understand the advanced concepts behind the shell program include process, system call, bit manipulation, file managment, error handling, etc. Shell is a simple UNIX command interpreter that replicates functionalities of the simple shell (sh). This program was written entirely in C Language.A custom shell implementation for Linux, developed on Ubuntu. This project is a foundational exploration of how command-line shells work, showcasing skills in systems programming, process management, and file I/O.
______________________________________________________________________________________________________________________________

Table of Contents:

• Features

• Getting Started

• Usage

• Built-ins

• Contributors

_____________________________________________________________________________________________________________________________
 Features:

• Display a prompt and wait for the user to type a command. A command line always ends with a new line.
• If an executable cannot be found, print an error message and display the prompt again.
• Handle errors.
• Handling the “end of file” condition (Ctrl+D)
• Hanling the command line with arguments
• Handle the PATH
• Support the exit features and the exit status
• Handle the Ctrl-C to not terminate the shell
• Handling the command seperator ;
• Handling && and || logical operators
• Handle variable replacements $? and $$
• Handle the comments #
• Support the history feature
• Support the file input

____________________________________________________________________________________________________________________________
 Getting Started:
To compile and use this project we will need:

• A GCC compiler:-Wall -Werror -Wextra -pedantic -std=gnu89

____________________________________________________________________________________________________________________________
 Prerequisites

• Ubuntu 20.04 or later
• GCC (GNU Compiler Collection)
• Make (optional but recommended)
____________________________________________________________________________________________________________________________
 Installation

1. Clone this repository:

   bash
   git clone https://github.com/Emanuell95/simple_shell.git
   cd simple_shell

_____________________________________________________________________________________________________________________________
Builtins:

Our shell has support for the following built-in commands:

• cd - change directory
• pwd- print working directory
• echo- print text to the console
• env- print environment variables
• export- set environment variables

______________________________________________________________________________________________________________________________

Contributors:

Authors that contributed to this project :

• Emanuel Mendoza- github.com/Emanuell95
• Joan Martinez- github.com/Joan938

If you’d like to contribute, please fork this repository, make your changes, and submit a pull request.
