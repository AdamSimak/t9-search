# T9 Contact Search (C)
A C program that emulates a simplified T9 contact search, like on mobile phones. Users provide a sequence of digits (0–9), and the program filters contacts from (`phonebook.txt`) whose names or phone numbers match the corresponding character sequences.

This project was implemented as part of a university assignment to practice C programming, algorithmic problem solving, and working with structured data.

## Features
- Read contacts from a text file (`phonebook.txt`) with name and phone number.  
- Supports a large number of contacts with names and phone numbers up to 100 characters each.
- Case-insensitive search by name or phone number.  
- T9-style numeric input mapping: digits map to multiple letters.  
- Prints all matching contacts or `Not found` if none match.

## How to Compile and Run

1. Compile the program:

   ```bash
   gcc -std=c11 -Wall -Wextra -Werror tnine.c -o tnine
2. Run the program with numeric filter:

   ```bash
   ./tnine 38 < phonebook.txt
2. Run the program without a filter (print all contacts):

   ```bash
   ./tnine  < phonebook.txt

## Commands / Arguments
The program accepts the following arguments:

- `NUMBER`  
  A sequence of digits (0–9) used as a search filter.  
  - If provided, only contacts whose name or number matches the T9 mapping for this sequence will be printed.  
  - If omitted, all contacts from the `phonebook.txt` will be printed.

## Input File Format
The contact list is stored in text file as plain text. Each contact consists of two lines:
1. A line with the contact’s name
2. A line with the phone number

Example (`phonebook.txt`):
  ```bash
  Petr Dvorak
  603123456
  Jana Novotna
  777987654
  Bedrich Smetana ml.
  541141120
  ```
## T9 Mapping
The digit-to-letter mapping used by the program is:
```bash
2 → a b c
3 → d e f
4 → g h i
5 → j k l
6 → m n o
7 → p q r s
8 → t u v
9 → w x y z
0 → +
1 → 1
```
## Example Runs
```bash
./tnine < phonebook.txt
# Output:
petr dvorak, 603123456
jana novotna, 777987654
bedrich smetana ml., 541141120

./tnine 12 < phonebook.txt
# Output:
petr dvorak, 603123456
bedrich smetana ml., 541141120

./tnine 111 < phonebook.txt
# Output:
Not found
```
