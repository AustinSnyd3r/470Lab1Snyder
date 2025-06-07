#include "Austin_libFS.h"
#include <ctype.h>  // For tolower()

// Function to display the menu
void displayMenu() {
    printf("\n--- Menu ---\n");
    printf("1. Create a file\n");
    printf("2. Open a file\n");
    printf("3. Write to a file\n");
    printf("4. Read from a file\n");
    printf("5. Close a file\n");
    printf("6. Delete a file\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

// Function to wait for user input to continue
void waitForUser() {
    printf("\nPress Enter to continue...");
    getchar();  // Wait for Enter key
    getchar();  // Clear the newline character from the buffer
}

int main() {
    char filename[MAX_FILENAME];
    char introduction[] = "Hello, my name is Austin Snyder.\n\n"
                          "I am a computer science student, graduating after this quarter.\n"
                          "This project is helping me to learn about some file system topics in the C language.\n"
                          "Have a good summer, and congrats if graduating.\n\n"
                          "This paragraph is about how much cooler C is than C++\n"
                          "C is cooler because it has a shorter name and it uses raw pointers.\n"
                          "C++ has references, ewwwwww.\n\n ";
    int file_index = -1;  // Track the currently open file
    int choice;
    char buffer[MAX_FILE_SIZE];

    while (1) {
        displayMenu();
        scanf("%d", &choice);  // Get user choice
        getchar();  // Clear the newline character from the buffer

        switch (choice) {
            case 1:  // Create a file
                printf("Enter the filename to create: ");
                fgets(filename, MAX_FILENAME, stdin);
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                if (fileCreate(filename) != 0) {
                    printf("Error creating file.\n");
                }
                waitForUser();
                break;

            case 2:  // Open a file
                printf("Enter the filename to open: ");
                fgets(filename, MAX_FILENAME, stdin);
                filename[strcspn(filename, "\n")] = '\0';
                file_index = fileOpen(filename);
                if (file_index == -1) {
                    printf("Error opening file.\n");
                }
                waitForUser();
                break;

            case 3:  // Write to a file
                if (file_index == -1) {
                    printf("Error: No file is open. Please open a file first.\n");
                } else {
                    printf("Writing introduction to file '%s'...\n", filename);
                    if (fileWrite(file_index, introduction) != 0) {
                        printf("Error writing to file.\n");
                    }
                }
                waitForUser();
                break;

            case 4:  // Read from a file 
                printf("Attempting to read from the open file. \n");
                if(fileRead(file_index, buffer, MAX_FILE_SIZE) == 0){
                    printf("File contents read successfully.\n");
                }
                else{
                    printf("Failed to read contents from the file.\n");
                }

                break;
            
            case 5: // close the file that is currently open. 
                printf("Attempting to close file at index %d. \n", file_index);
                if(fileClose(file_index) == 0){
                    file_index = -1;
                }
                else{
                    printf("Failed to close the file. \n");
                }

                waitForUser();
                break;
            case 6: // delete a file
                printf("Enter the filename to delete: \n");
                fgets(filename, MAX_FILENAME, stdin);
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline

                if(fileDelete(filename) == 0){
                    printf("Sucessfully deleted the file.\n");
                }else{
                    printf("Failed to delete the file.\n");
                }
                break;

            case 7:  // Exit
                printf("Exiting the program. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                waitForUser();
                break;
        }
    }

    return 0;
}