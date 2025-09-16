#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>  
#include <string.h>

#define MAX_CONTACTS 10000
#define MAX_NAME_LENGTH 100
#define MAX_PHONE_LENGTH 100

// Definition of the Contact structure (name and phone)

struct Contact{

  char name[MAX_NAME_LENGTH];
  char phone[MAX_PHONE_LENGTH];
};


// Reads contacts from file and stores them in structs

void read_contacts(struct Contact contacts[], int *contact_count) {
    while (*contact_count < MAX_CONTACTS && fgets(contacts[*contact_count].name,
     sizeof(contacts[*contact_count].name), stdin) != NULL) {
      
        // Remove newline from the name
        contacts[*contact_count].name[strcspn(contacts[*contact_count].name, "\n")] = 0;

        // Read the phone number
        if (fgets(contacts[*contact_count].phone, sizeof(contacts[*contact_count].phone), stdin) != NULL) {
            // odstranenie newline charakteru z cisla
            contacts[*contact_count].phone[strcspn(contacts[*contact_count].phone, "\n")] = 0;
        }

        (*contact_count)++;
    }
}


// Checks whether contact name/phone length constraints are respected
// Verifies whther there is at least one contact available

int check_contact_lenght(struct Contact contacts[], int contact_count) {
    for (int contact_index = 0; contact_index < contact_count; contact_index++) {

        int contact_name_length = strlen(contacts[contact_index].name);
        int contact_phone_length = strlen(contacts[contact_index].phone);
        
        if ((contact_name_length > MAX_NAME_LENGTH || contact_name_length < 1) ||
            (contact_phone_length > MAX_PHONE_LENGTH || contact_phone_length < 1)) {

            fprintf(stderr, "Error: Invalid contact character length in text file.");
            return 1; 
        }
    }
    
    if (contact_count == 0){
    fprintf(stderr,"Error: No contacts found.");
    return 1;
  }
    return 0; 
}


// Compares input_number and contact_phone_number
// If a match is found -> returns true

bool check_number(const char * input_number, const char* phone_number){
  
  int input_number_index = 0;
  int phone_number_length = strlen(phone_number);
  int input_number_length = strlen(input_number);
  
  for (int phone_number_index = 0; phone_number_index < phone_number_length; phone_number_index++){

    if (phone_number[phone_number_index] == input_number[input_number_index]){
      input_number_index++;
    }
    else{
      input_number_index = 0;
    }

    if (input_number_index == input_number_length){
      return true;
    }
  }

  return false;
}


// Checks whether input_number corresponds to a sequence of letters
// in the contact name (based on phone keypad mapping)

bool check_name(const char * input_number, const char* contact_name, const char* keypad_letters[]){
    int input_number_length = strlen(input_number);
    int name_length = strlen(contact_name);
    int keypad_letters_index = 0;

    for (int name_index = 0; name_index < name_length; name_index++) {
        bool matched = false;
        int keypad_letters_length = strlen(keypad_letters[keypad_letters_index]);

        for (int keypad_letters_char = 0; keypad_letters_char < keypad_letters_length;
             keypad_letters_char++) {
            
            if (tolower(contact_name[name_index]) == 
                keypad_letters[keypad_letters_index][keypad_letters_char]) {

                matched = true;
                keypad_letters_index++;
                break;
            }
        }

        if (!matched) {
            keypad_letters_index = 0;
        }

        if (keypad_letters_index == input_number_length) {
            return true;
        }
    }
    return false;
    }


// Maps a digit to its corresponding character s on a phone keyboard

const char* digit_to_char(char digit) {
    switch (digit) {
        case '2': return "abc";
        case '3': return "def";
        case '4': return "ghi";
        case '5': return "jkl";
        case '6': return "mno";
        case '7': return "pqrs";
        case '8': return "tuv";
        case '9': return "wxyz";
        case '0': return "+";
        default: return ""; 
    }
}
  

int main(int argc, char *argv[]) {

  char * input_number = argv[1];

  struct Contact contacts[MAX_CONTACTS];
  int contact_count = 0;

  read_contacts(contacts, &contact_count); 
 
  if (check_contact_lenght(contacts, contact_count) != 0) {
        return 1; 
    }

  // If no search number is provided, print all contacts
  if (argc < 2){

    for (int x = 0; x < contact_count; x++){
      printf("%s, %s\n", contacts[x].name, contacts[x].phone);
    }
  }

  // Check whether too many arguments are provided
  else if(argc > 2){
    fprintf(stderr,"Error: Too many arguments provided.");
    return 1;
  }

  int length_of_number;
  length_of_number = strlen(input_number);

  const char *keypad_letters [length_of_number];

  // Convert each digit of input_number to possible characters
  for (int input_number_index = 0; input_number_index < length_of_number; input_number_index++) {
        keypad_letters[input_number_index] = digit_to_char(input_number[input_number_index]);
    }

  int printed_contacts_sum = 0;

  // Print contacts if they match by phone number or by name
  for (int contact_index = 0; contact_index < contact_count; contact_index++){
    if (check_number(input_number, contacts[contact_index].phone )){

      printf("%s, %s\n", contacts[contact_index].name, contacts[contact_index].phone);
      printed_contacts_sum++;
    }
    else if(check_name(input_number, contacts[contact_index].name, keypad_letters )){
      printf("%s, %s\n", contacts[contact_index].name, contacts[contact_index].phone);
      printed_contacts_sum++;
    }
  }

  // If no matches were found
  if (printed_contacts_sum == 0){
    printf("Not found\n");
  }
  
  return 0;
}