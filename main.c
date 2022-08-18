//libraries which i want
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <winsock2.h>
#include "cJSON.h"
#include <unistd.h>
#include <time.h>
//------------------------------------------------




//prototypes
int initialize (void);
void start (int server_socket);
void signup (int client_socket, char* buffer);
void login (int client_socket, char* buffer);
void sendTweet (int client_socket, char* buffer);
void search (int client_socket, char* buffer);
void like (int client_socket, char* buffer);
void comment (int cient_socket, char* buffer);
void follow (int client_socket, char* buffer);
void unfollw (int client_socket, char* buffer);
void setBio (int client_socket, char* buffer);
void logout (int client_socket, char* buffer);
void tweetProfile (int client_socket, char* buffer);
void changePassword (int client_socket, char* buffer);
void refresh (int client_socket, char* buffer);
void delete (int client_socket, char* buffer);
void retweet (int client_socket, char* buffer);
void tweetSearch (int client_socket, char* buffer);
void addFavorite (int client_socket, char* buffer);
void showFavorite (int client_socket, char* buffer);
void deleteFavorite (int client_socket, char* buffer);
void notification (int client_socket, char* buffer);
//------------------------------------------------




int server_socket_global;




//------------------------------------------------
int main() {
    int server_socket = initialize();
    server_socket_global = server_socket;
    if (server_socket != INVALID_SOCKET){
        start(server_socket);
    }
    return 0;
}
//------------------------------------------------
int initialize (void)
{
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2,2), &wsadata);
    int wsa_res = WSAStartup(MAKEWORD(2,2), &wsadata);
    if(wsa_res != 0){
        printf("Failed to run wsadata");
        return INVALID_SOCKET;
    }
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET){
        printf("Could not create socket");
        return INVALID_SOCKET;
    }
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(88);
    int bind_res = bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (bind_res == SOCKET_ERROR){
        printf("Bind failed");
        return INVALID_SOCKET;
    }
    listen(server_socket, SOMAXCONN);
    return server_socket;
}
//------------------------------------------------
void start (int server_socket)
{
    int len = sizeof(struct sockaddr_in);
    int client_socket;
    struct sockaddr_in client_addr;
    while((client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &len)) != INVALID_SOCKET){
        char buffer[1000];
        memset(buffer, 0, 1000);
        recv(client_socket, buffer, 999, 0);
        //---------------------------
        if (buffer[0] == 's' && buffer[1] == 'i' && buffer[2] == 'g' && buffer[3] == 'n' && buffer[4] == 'u' && buffer[5] == 'p' && buffer[6] == ' ' && buffer[strlen(buffer)-1] == '\n'){
            int comma_counter = 0;
            int space_counter = 0;
            for (int i = 0; i<strlen(buffer); ++i){
                if(buffer[i] == ','){
                    if (buffer[i+1] == ' '){
                        comma_counter += 1;
                    }
                }
                if(buffer[i] == ' '){
                    space_counter += 1;
                }
            }
            if(comma_counter == 1 && space_counter == 2){
                signup(client_socket, buffer);
            }
            else{
                char main_error[100] = "{\"type\":\"Error\",\"message\":\"Bad request format.\"}";
                int main_error_len = strlen(main_error);
                send(client_socket, main_error, main_error_len, 0);
            }
        }
        //---------------------------
        if (buffer[0] == 'l' && buffer[1] == 'o' && buffer[2] == 'g' && buffer[3] == 'i' && buffer[4] == 'n' && buffer[5] == ' ' && buffer[strlen(buffer)-1] == '\n'){
            int comma_counter = 0;
            int space_counter = 0;
            for (int i = 0; i<strlen(buffer); ++i){
                if(buffer[i] == ','){
                    if (buffer[i+1] == ' '){
                        comma_counter += 1;
                    }
                }
                if(buffer[i] == ' '){
                    space_counter += 1;
                }
            }
            if(comma_counter == 1 && space_counter == 2){
                login(client_socket, buffer);
            }
            else{
                char main_error[100] = "{\"type\":\"Error\",\"message\":\"Bad request format.\"}";
                int main_error_len = strlen(main_error);
                send(client_socket, main_error, main_error_len, 0);
            }
        }
        //---------------------------
        if (buffer[0] == 's' && buffer[1] == 'e' && buffer[2] == 'n' && buffer[3] == 'd' && buffer[4] == ' ' && buffer[5] == 't' && buffer[6] == 'w' && buffer[7] == 'e' && buffer[8] == 'e' && buffer[9] == 't' && buffer[10] == ' ' && buffer[strlen(buffer)-1] == '\n'){
            int comma_counter = 0;
            for (int i = 0; i<strlen(buffer); ++i){
                if(buffer[i] == ','){
                    if (buffer[i+1] == ' '){
                        comma_counter += 1;
                    }
                }
            }
            if(comma_counter == 1){
                sendTweet(client_socket, buffer);
            }
            else{
                char main_error[100] = "{\"type\":\"Error\",\"message\":\"Bad request format.\"}";
                int main_error_len = strlen(main_error);
                send(client_socket, main_error, main_error_len, 0);
            }
        }
        //---------------------------
        if (buffer[0] == 's' && buffer[1] == 'e' && buffer[2] == 'a' && buffer[3] == 'r' && buffer[4] == 'c' && buffer[5] == 'h' && buffer[6] == ' ' && buffer[strlen(buffer)-1] == '\n'){
            int comma_counter = 0;
            int space_counter = 0;
            for (int i = 0; i<strlen(buffer); ++i){
                if(buffer[i] == ','){
                    if (buffer[i+1] == ' '){
                        comma_counter += 1;
                    }
                }
                if(buffer[i] == ' '){
                    space_counter += 1;
                }
            }
            if(comma_counter == 1 && space_counter == 2){
                search(client_socket, buffer);
            }
            else{
                char main_error[100] = "{\"type\":\"Error\",\"message\":\"Bad request format.\"}";
                int main_error_len = strlen(main_error);
                send(client_socket, main_error, main_error_len, 0);
            }
        }
        //---------------------------
        if (buffer[0] == 'l' && buffer[1] == 'i' && buffer[2] == 'k' && buffer[3] == 'e' && buffer[4] == ' ' && buffer[strlen(buffer)-1] == '\n'){
            int comma_counter = 0;
            int space_counter = 0;
            for (int i = 0; i<strlen(buffer); ++i){
                if(buffer[i] == ','){
                    if (buffer[i+1] == ' '){
                        comma_counter += 1;
                    }
                }
                if(buffer[i] == ' '){
                    space_counter += 1;
                }
            }
            int counter = 0;
            int digit_counter = 0;
            for (int j = 0; j<strlen(buffer); ++j){
                if (buffer[j] == ','){
                    if (buffer[j+1] == ' '){
                        for (int k = j+2; k<strlen(buffer); ++k){
                            counter += 1;
                            if (isdigit(buffer[k])){
                                digit_counter += 1;
                            }
                        }
                    }
                }
            }
            if(comma_counter == 1 && space_counter == 2 && digit_counter == counter-1){
                like(client_socket, buffer);
            }
            else{
                char main_error[100] = "{\"type\":\"Error\",\"message\":\"Bad request format.\"}";
                int main_error_len = strlen(main_error);
                send(client_socket, main_error, main_error_len, 0);
            }
        }
        //---------------------------
        if (buffer[0] == 'c' && buffer[1] == 'o' && buffer[2] == 'm' && buffer[3] == 'm' && buffer[4] == 'e' && buffer[5] == 'n' && buffer[6] == 't' && buffer[7] == ' ' && buffer[strlen(buffer)-1] == '\n'){
            int comma_counter = 0;
            for (int i = 0; i<strlen(buffer); ++i){
                if(buffer[i] == ','){
                    if (buffer[i+1] == ' '){
                        comma_counter += 1;
                    }
                }
            }
            int counter = 0;
            int digit_counter = 0;
            for (int j = 0; j<strlen(buffer); ++j){
                if (buffer[j] == ','){
                    if (buffer[j+1] == ' '){
                        for (int k = j+2; k<strlen(buffer); ++k){
                            if (buffer[k] == ','){
                                break;
                            }
                            counter += 1;
                            if (isdigit(buffer[k])){
                                digit_counter += 1;
                            }
                        }
                    }
                    break;
                }
            }
            if(comma_counter == 2 && digit_counter == counter){
                comment(client_socket, buffer);
            }
            else{
                char main_error[100] = "{\"type\":\"Error\",\"message\":\"Bad request format.\"}";
                int main_error_len = strlen(main_error);
                send(client_socket, main_error, main_error_len, 0);
            }
        }
        //---------------------------
        if (buffer[0] == 'f' && buffer[1] == 'o' && buffer[2] == 'l' && buffer[3] == 'l' && buffer[4] == 'o' && buffer[5] == 'w' && buffer[6] == ' ' && buffer[strlen(buffer)-1] == '\n'){
            int comma_counter = 0;
            int space_counter = 0;
            for (int i = 0; i<strlen(buffer); ++i){
                if(buffer[i] == ','){
                    if (buffer[i+1] == ' '){
                        comma_counter += 1;
                    }
                }
                if(buffer[i] == ' '){
                    space_counter += 1;
                }
            }
            if(comma_counter == 1 && space_counter == 2){
                follow(client_socket, buffer);
            }
            else{
                char main_error[100] = "{\"type\":\"Error\",\"message\":\"Bad request format.\"}";
                int main_error_len = strlen(main_error);
                send(client_socket, main_error, main_error_len, 0);
            }
        }
        //---------------------------
        if (buffer[0] == 'u' && buffer[1] == 'n' && buffer[2] == 'f' && buffer[3] == 'o' && buffer[4] == 'l' && buffer[5] == 'l' && buffer[6] == 'o' && buffer[7] == 'w' && buffer[8] == ' ' && buffer[strlen(buffer)-1] == '\n'){
            int comma_counter = 0;
            int space_counter = 0;
            for (int i = 0; i<strlen(buffer); ++i){
                if(buffer[i] == ','){
                    if (buffer[i+1] == ' '){
                        comma_counter += 1;
                    }
                }
                if(buffer[i] == ' '){
                    space_counter += 1;
                }
            }
            if(comma_counter == 1 && space_counter == 2){
                unfollw(client_socket, buffer);
            }
            else{
                char main_error[100] = "{\"type\":\"Error\",\"message\":\"Bad request format.\"}";
                int main_error_len = strlen(main_error);
                send(client_socket, main_error, main_error_len, 0);
            }
        }
        //---------------------------
        if (buffer[0] == 's' && buffer[1] == 'e' && buffer[2] == 't' && buffer[3] == ' ' && buffer[4] == 'b' && buffer[5] == 'i' && buffer[6] == 'o' && buffer[7] == ' ' && buffer[strlen(buffer)-1] == '\n'){
            int comma_counter = 0;
            for (int i = 0; i<strlen(buffer); ++i){
                if(buffer[i] == ','){
                    if (buffer[i+1] == ' '){
                        comma_counter += 1;
                    }
                }
            }
            if(comma_counter == 1){
                setBio(client_socket, buffer);
            }
            else{
                char main_error[100] = "{\"type\":\"Error\",\"message\":\"Bad request format.\"}";
                int main_error_len = strlen(main_error);
                send(client_socket, main_error, main_error_len, 0);
            }
        }
        //---------------------------
        if (buffer[0] == 'l' && buffer[1] == 'o' && buffer[2] == 'g' && buffer[3] == 'o' && buffer[4] == 'u' && buffer[5] == 't' && buffer[6] == ' ' && buffer[strlen(buffer)-1] == '\n'){
            int space_counter = 0;
            for (int i = 0; i<strlen(buffer); ++i){
                if(buffer[i] == ' '){
                    space_counter += 1;
                }
            }
            if(space_counter == 1){
                logout(client_socket, buffer);
            }
            else{
                char main_error[100] = "{\"type\":\"Error\",\"message\":\"Bad request format.\"}";
                int main_error_len = strlen(main_error);
                send(client_socket, main_error, main_error_len, 0);
            }
        }
        //---------------------------
        if (buffer[0] == 'p' && buffer[1] == 'r' && buffer[2] == 'o' && buffer[3] == 'f' && buffer[4] == 'i' && buffer[5] == 'l' && buffer[6] == 'e' && buffer[7] == ' ' && buffer[strlen(buffer)-1] == '\n'){
            int space_counter = 0;
            for (int i = 0; i<strlen(buffer); ++i){
                if(buffer[i] == ' '){
                    space_counter += 1;
                }
            }
            if(space_counter == 1){
                tweetProfile(client_socket, buffer);
            }
            else{
                char main_error[100] = "{\"type\":\"Error\",\"message\":\"Bad request format.\"}";
                int main_error_len = strlen(main_error);
                send(client_socket, main_error, main_error_len, 0);
            }
        }
        //---------------------------
        if (buffer[0] == 'c' && buffer[1] == 'h' && buffer[2] == 'a' && buffer[3] == 'n' && buffer[4] == 'g' && buffer[5] == 'e' && buffer[6] == ' ' && buffer[7] == 'p' && buffer[8] == 'a' && buffer[9] == 's' && buffer[10] == 's' && buffer[11] == 'w' && buffer[12] == 'o' && buffer[13] == 'r' && buffer[14] == 'd' && buffer[15] == ' ' && buffer[strlen(buffer)-1] == '\n'){
            int comma_counter = 0;
            int space_counter = 0;
            for (int i = 0; i<strlen(buffer); ++i){
                if(buffer[i] == ','){
                    if (buffer[i+1] == ' '){
                        comma_counter += 1;
                    }
                }
                if(buffer[i] == ' '){
                    space_counter += 1;
                }
            }
            if(comma_counter == 2 && space_counter == 4){
                changePassword(client_socket, buffer);
            }
            else{
                char main_error[100] = "{\"type\":\"Error\",\"message\":\"Bad request format.\"}";
                int main_error_len = strlen(main_error);
                send(client_socket, main_error, main_error_len, 0);
            }
        }
        //---------------------------
        if (buffer[0] == 'r' && buffer[1] == 'e' && buffer[2] == 'f' && buffer[3] == 'r' && buffer[4] == 'e' && buffer[5] == 's' && buffer[6] == 'h' && buffer[7] == ' ' && buffer[strlen(buffer)-1] == '\n'){
            int space_counter = 0;
            for (int i = 0; i<strlen(buffer); ++i){
                if(buffer[i] == ' '){
                    space_counter += 1;
                }
            }
            if(space_counter == 1){
                refresh(client_socket, buffer);
            }
            else{
                char main_error[100] = "{\"type\":\"Error\",\"message\":\"Bad request format.\"}";
                int main_error_len = strlen(main_error);
                send(client_socket, main_error, main_error_len, 0);
            }
        }
        //---------------------------
        if (buffer[0] == 'd' && buffer[1] == 'e' && buffer[2] == 'l' && buffer[3] == 'e' && buffer[4] == 't' && buffer[5] == 'e' && buffer[6] == ' ' && buffer[7] != 'f' && buffer[8] != 'a' && buffer[strlen(buffer)-1] == '\n'){
            int comma_counter = 0;
            int space_counter = 0;
            for (int i = 0; i<strlen(buffer); ++i){
                if(buffer[i] == ','){
                    if (buffer[i+1] == ' '){
                        comma_counter += 1;
                    }
                }
                if(buffer[i] == ' '){
                    space_counter += 1;
                }
            }
            int counter = 0;
            int digit_counter = 0;
            for (int j = 0; j<strlen(buffer); ++j){
                if (buffer[j] == ','){
                    if (buffer[j+1] == ' '){
                        for (int k = j+2; k<strlen(buffer); ++k){
                            counter += 1;
                            if (isdigit(buffer[k])){
                                digit_counter += 1;
                            }
                        }
                    }
                    break;
                }
            }
            if (comma_counter == 1 && space_counter == 2 && digit_counter == counter-1){
                delete(client_socket, buffer);
            }
            else{
                char main_error[100] = "{\"type\":\"Error\",\"message\":\"Bad request format.\"}";
                int main_error_len = strlen(main_error);
                send(client_socket, main_error, main_error_len, 0);
            }
        }
        if (buffer[0] == 'r' && buffer[1] == 'e' && buffer[2] == 't' && buffer[3] == 'w' && buffer[4] == 'e' && buffer[5] == 'e' && buffer[6] == 't' && buffer[7] == ' ' && buffer[strlen(buffer)-1] == '\n'){
            int comma_counter = 0;
            int space_counter = 0;
            for (int i = 0; i<strlen(buffer); ++i){
                if(buffer[i] == ','){
                    if (buffer[i+1] == ' '){
                        comma_counter += 1;
                    }
                }
                if(buffer[i] == ' '){
                    space_counter += 1;
                }
            }
            int counter = 0;
            int digit_counter = 0;
            for (int j = 0; j<strlen(buffer); ++j){
                if (buffer[j] == ','){
                    if (buffer[j+1] == ' '){
                        for (int k = j+2; k<strlen(buffer); ++k){
                            counter += 1;
                            if (isdigit(buffer[k])){
                                digit_counter += 1;
                            }
                        }
                    }
                    break;
                }
            }
            if(comma_counter == 1 && space_counter == 2 && digit_counter == counter-1){
                retweet(client_socket, buffer);
            }
            else{
                char main_error[100] = "{\"type\":\"Error\",\"message\":\"Bad request format.\"}";
                int main_error_len = strlen(main_error);
                send(client_socket, main_error, main_error_len, 0);
            }
        }
        //---------------------------
        if (buffer[0] == 't' && buffer[1] == 'w' && buffer[2] == 'e' && buffer[3] == 'e' && buffer[4] == 't' && buffer[5] == ' ' && buffer[6] == 's' && buffer[7] == 'e' && buffer[8] == 'a' && buffer[9] == 'r' && buffer[10] == 'c' && buffer[11] == 'h' && buffer[12] == ' ' && buffer[strlen(buffer)-1] == '\n'){
            int comma_counter = 0;
            int space_counter = 0;
            for (int i = 0; i<strlen(buffer); ++i){
                if(buffer[i] == ','){
                    if (buffer[i+1] == ' '){
                        comma_counter += 1;
                    }
                }
                if(buffer[i] == ' '){
                    space_counter += 1;
                }
            }
            if (comma_counter == 1 && space_counter == 3){
                tweetSearch(client_socket, buffer);
            }
            else{
                char main_error[100] = "{\"type\":\"Error\",\"message\":\"Bad request format.\"}";
                int main_error_len = strlen(main_error);
                send(client_socket, main_error, main_error_len, 0);
            }
        }
        //---------------------------
        if (buffer[0] == 'a' && buffer[1] == 'd' && buffer[2] == 'd' && buffer[3] == ' ' && buffer[4] == 'f' && buffer[5] == 'a' && buffer[6] == 'v' && buffer[7] == 'o' && buffer[8] == 'r' && buffer[9] == 'i' && buffer[10] == 't' && buffer[11] == 'e' && buffer[12] == ' ' && buffer[strlen(buffer)-1] == '\n'){
            int comma_counter = 0;
            int space_counter = 0;
            for (int i = 0; i<strlen(buffer); ++i){
                if(buffer[i] == ','){
                    if (buffer[i+1] == ' '){
                        comma_counter += 1;
                    }
                }
                if(buffer[i] == ' '){
                    space_counter += 1;
                }
            }
            if (comma_counter == 1 && space_counter == 3){
                addFavorite(client_socket, buffer);
            }
            else{
                char main_error[100] = "{\"type\":\"Error\",\"message\":\"Bad request format.\"}";
                int main_error_len = strlen(main_error);
                send(client_socket, main_error, main_error_len, 0);
            }
        }
        //---------------------------
        if (buffer[0] == 's' && buffer[1] == 'h' && buffer[2] == 'o' && buffer[3] == 'w' && buffer[4] == ' ' && buffer[5] == 'f' && buffer[6] == 'a' && buffer[7] == 'v' && buffer[8] == 'o' && buffer[9] == 'r' && buffer[10] == 'i' && buffer[11] == 't' && buffer[12] == 'e' && buffer[13] == ' ' && buffer[strlen(buffer)-1] == '\n'){
            int space_counter = 0;
            for (int i = 0; i<strlen(buffer); ++i){
                if(buffer[i] == ' '){
                    space_counter += 1;
                }
            }
            if (space_counter == 2){
                showFavorite(client_socket, buffer);
            }
            else{
                char main_error[100] = "{\"type\":\"Error\",\"message\":\"Bad request format.\"}";
                int main_error_len = strlen(main_error);
                send(client_socket, main_error, main_error_len, 0);
            }
        }
        //---------------------------
        if (buffer[0] == 'd' && buffer[1] == 'e' && buffer[2] == 'l' && buffer[3] == 'e' && buffer[4] == 't' && buffer[5] == 'e' && buffer[6] == ' ' && buffer[7] == 'f' && buffer[8] == 'a' && buffer[9] == 'v' && buffer[10] == 'o' && buffer[11] == 'r' && buffer[12] == 'i' && buffer[13] == 't' && buffer[14] == 'e' && buffer[15] == ' ' && buffer[strlen(buffer)-1] == '\n'){
            int comma_counter = 0;
            int space_counter = 0;
            for (int i = 0; i<strlen(buffer); ++i){
                if(buffer[i] == ','){
                    if (buffer[i+1] == ' '){
                        comma_counter += 1;
                    }
                }
                if(buffer[i] == ' '){
                    space_counter += 1;
                }
            }
            if (comma_counter == 1 && space_counter == 3){
                deleteFavorite(client_socket, buffer);
            }
            else{
                char main_error[100] = "{\"type\":\"Error\",\"message\":\"Bad request format.\"}";
                int main_error_len = strlen(main_error);
                send(client_socket, main_error, main_error_len, 0);
            }
        }
        //---------------------------
        if (buffer[0] == 'n' && buffer[1] == 'o' && buffer[2] == 't' && buffer[3] == 'i' && buffer[4] == 'f' && buffer[5] == 'i' && buffer[6] == 'c' && buffer[7] == 'a' && buffer[8] == 't' && buffer[9] == 'i' && buffer[10] == 'o' && buffer[11] == 'n' && buffer[12] == ' ' &&  buffer[strlen(buffer)-1] == '\n'){
            int space_counter = 0;
            for (int i = 0; i<strlen(buffer); ++i){
                if(buffer[i] == ' '){
                    space_counter += 1;
                }
            }
            if (space_counter == 1){
                notification(client_socket, buffer);
            }
            else{
                char main_error[100] = "{\"type\":\"Error\",\"message\":\"Bad request format.\"}";
                int main_error_len = strlen(main_error);
                send(client_socket, main_error, main_error_len, 0);
            }
        }
        //---------------------------
        else{
            char main_error[100] = "{\"type\":\"Error\",\"message\":\"Bad request format.\"}";
            int main_error_len = strlen(main_error);
            send(client_socket, main_error, main_error_len, 0);
        }
        //---------------------------
        closesocket(client_socket);
    }
}
//------------------------------------------------
void signup (int client_socket, char* buffer)
{
    int buffer_len = strlen(buffer);
//    buffer[strlen(buffer)-1] = '\0';
    buffer_len -= 1;
    char char_username[50];
    char char_password[50];
    char strings[2][50];
    int strings_counter = 0;
    for (int i = 0; i < buffer_len-1; ++i) {

        if (buffer[i] == ' '){

            int j = i+1;
            while(buffer[j] != ' ' && buffer[j] != '\0'){
                strings[strings_counter][j-i-1] = buffer[j];
                j += 1;
            }
            strings[strings_counter][j-i-1] = '\0';
            strings_counter += 1;
        }
    }
    strcpy(char_username, strings[0]);
    strcpy(char_password, strings[1]);
    char_username[strlen(char_username)-1] = '\0';
    char_password[strlen(char_password)-1] = '\0';

    if (strlen(char_password) >16){
        char x[100] = "{\"type\":\"Error\",\"message\":\"To long.\"}";
        int x_len = strlen(x);
        send(client_socket, "{\"type\":\"Error\",\"message\":\"To long.\"}", x_len, 0);
    }
    else {

        if (access(char_username, F_OK) == 0) {
            char x[100] = "{\"type\":\"Error\",\"message\":\"This username is already taken.\"}";
            int x_len = strlen(x);
            send(client_socket, "{\"type\":\"Error\",\"message\":\"This username is already taken.\"}", x_len, 0);
        } else {

            char *out;
            cJSON *root, *username, *password, *bio, *followers, *followings, *personalTweets, *favoriteTweets, *favorite;
            root = cJSON_CreateObject();
            username = cJSON_CreateString(char_username);
            password = cJSON_CreateString(char_password);
            bio = cJSON_CreateString("");
            followers = cJSON_CreateArray();
            followings = cJSON_CreateArray();
            personalTweets = cJSON_CreateArray();
            favoriteTweets = cJSON_CreateArray();
            favorite = cJSON_CreateArray();
            cJSON_AddItemToObject(root, "username", username);
            cJSON_AddItemToObject(root, "password", password);
            cJSON_AddItemToObject(root, "bio", bio);
            cJSON_AddItemToObject(root, "followers", followers);
            cJSON_AddItemToObject(root, "followings", followings);
            cJSON_AddItemToObject(root, "personalTweets", personalTweets);
            cJSON_AddItemToObject(root, "favoriteTweets", favoriteTweets);
            cJSON_AddItemToObject(root, "favorites", favorite);
            out = cJSON_PrintUnformatted(root);
            FILE *cfptr;
            cfptr = fopen(char_username, "a");
            fprintf(cfptr, "%s\n", out);
            char x[100] = "{\"type\":\"Successful\",\"message\":\"\"}";
            int x_len = strlen(x);
            send(client_socket, "{\"type\":\"Successful\",\"message\":\"\"}", x_len, 0);
            //free(root);
            //cJSON_Delete(root);
            fclose(cfptr);


            //for advanced search
            if (access("AllUsernames", F_OK) == 0){
                FILE *Allusernames_file;
                Allusernames_file = fopen("AllUsernames", "r");
                char Allusernames_stufs[10000];
                fgets(Allusernames_stufs, 10000, Allusernames_file);
                cJSON *instead_of_root = cJSON_Parse(Allusernames_stufs);
                cJSON *array = cJSON_GetObjectItem(instead_of_root, "allusernames");
                cJSON *string = cJSON_CreateString(char_username);
                cJSON_AddItemToArray(array, string);
                fclose(Allusernames_file);
                FILE *Allusernames_file_2;
                Allusernames_file_2 = fopen("AllUsernames", "w");
                fprintf(Allusernames_file_2, "%s", cJSON_PrintUnformatted(instead_of_root));
                fclose(Allusernames_file_2);
            }
            else{
                FILE *Allusernames_file;
                Allusernames_file = fopen("AllUsernames", "w");
                cJSON *Allusernames_main_json, *AllusernamesArray;
                Allusernames_main_json = cJSON_CreateObject();
                AllusernamesArray = cJSON_CreateArray();
                cJSON_AddItemToObject(Allusernames_main_json, "allusernames", AllusernamesArray);
                cJSON *username_json = cJSON_CreateString(char_username);
                cJSON_AddItemToArray(AllusernamesArray, username_json);
                fprintf(Allusernames_file, "%s", cJSON_PrintUnformatted(Allusernames_main_json));
                fclose(Allusernames_file);
            }
            //end of for advanced search
        }
//        return start(server_socket_global);
    }
}
//------------------------------------------------
//this is my 2D aray which I save users and their tokens
char user_token[1000][22];
int counter = 0;
void login (int client_socket, char* buffer)
{
    int buffer_len = strlen(buffer);
    char char_username[50];
    char char_password[50];
    char strings[2][50];
    int strings_counter = 0;
    for (int i = 0; i < buffer_len; ++i) {
        if (buffer[i] == ' '){
            int j = i+1;
            while(buffer[j] != ' '){
                strings[strings_counter][j-i-1] = buffer[j];
                j += 1;
            }
            strings[strings_counter][j-i-1] = '\0';
            strings_counter += 1;
        }
    }
    strcpy(char_username, strings[0]);
    strcpy(char_password, strings[1]);
    char_username[strlen(char_username)-1] = '\0';
    char_password[strlen(char_password)-1] = '\0';
    //checking if the user is login or not
    int is_login_or_not = 1;
    for (int jdk = 0; jdk<counter; ++jdk){
        if (strcmp(user_token[jdk], char_username) == 0){
            is_login_or_not = 0;
        }
    }
    //end of checking if the user is login or not
    if (counter == 0 || is_login_or_not == 1) {
        if (access(char_username, F_OK) != 0) {
            char x[100] = "{\"type\":\"Error\",\"message\":\"This username is not valid.\"}";
            int x_len = strlen(x);
            send(client_socket, "{\"type\":\"Error\",\"message\":\"This username is not valid.\"}", x_len, 0);
        } else {
            char file_lines[10000];
            FILE *my_file_ptr;
            my_file_ptr = fopen(char_username, "r");
            fgets(file_lines, 10000, my_file_ptr);
            cJSON *my_new_root = cJSON_Parse(file_lines);
            cJSON *get_object = cJSON_GetObjectItem(my_new_root, "password");
            char *true_password_2;
            true_password_2 = cJSON_Print(get_object);
            strcpy(true_password_2, true_password_2 + 1);
            true_password_2[strlen(true_password_2) - 1] = '\0';
//            char_password[strlen(char_password) - 1] = '\0';
            if (strcmp(true_password_2, char_password) == 0) {
                //building token
                char token[22];
                srand(time(0));
                int i = 0;
                while (i <= 20) {
                    int capital_char = rand() % 26 + 65;
                    token[i] = (char) capital_char;
                    i += 1;
                    int small_char = rand() % 26 + 97;
                    token[i] = (char) small_char;
                    i += 1;
                    int number_char = rand() % 10 + 48;
                    token[i] = (char) number_char;
                    i += 1;
                }
                token[21] = '\0';
                //end of building token
                char login_response[100] = "{\"type\":\"Token\",\"message\":\"";
                strcat(login_response, token);
                strcat(login_response, "\"}");
                int login_response_len = strlen(login_response);
                send(client_socket, login_response, login_response_len, 0);
                strcpy(user_token[counter], token);
                counter += 1;
                strcpy(user_token[counter], char_username);
                counter += 1;
            } else {
                char x[100] = "{\"type\":\"Error\",\"message\":\"Incorrect password.\"}";
                int x_len = strlen(x);
                send(client_socket, "{\"type\":\"Error\",\"message\":\"Incorrect password.\"}", x_len, 0);
            }
        }
    }
    else{
        char errors[75] = "{\"type\":\"Error\",\"message\":\"The user alinz is already logged in.\"}";
        int errors_len = strlen(errors);
        send(client_socket, errors, errors_len, 0);
    }
    return;
}
//------------------------------------------------
void sendTweet (int client_socket, char* buffer)
{
    int buffer_len = strlen(buffer);
    buffer_len -= 1;
    char token[22];
    char tweet[1000];
    char strings[2][1000];
    int strings_counter = 0;
    for (int i = 0; i < buffer_len; ++i) {
        if (buffer[i] == ','){
            for (int j = i-1; j>=0; --j){
                if (buffer[j] == ' '){
                    for (int k = j+1; k<i; ++k){
                        strings[strings_counter][k-j-1] = buffer[k];
                    }
                    strings[strings_counter][i-j-1] = '\0';
                    strings_counter += 1;
                    break;
                }
            }
            int m;
            for (m = i+2; m<buffer_len; ++m){
                strings[strings_counter][m-i-2] = buffer[m];
            }
            strings[strings_counter][m-i-2] = '\0';
            strings_counter += 1;
        }
    }
    strcpy(token, strings[0]);
    strcpy(tweet, strings[1]);
    //tweet[strlen(tweet)-1] = '\0';
    char username[30] = "*~";
    for (int l = 0; l<=100; ++l){
        if (strcmp(user_token[l], token) == 0){
            strcpy(username, user_token[l+1]);
            break;
        }
    }
    if (strcmp(username, "*~") == 0 && username[0] == '*' && username[1] == '~'){
        char token_error[100] = "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}";
        int token_error_len = strlen(token_error);
        send(client_socket, token_error, token_error_len, 0);
    }
    else {
        char *tweet_id_in_string_mode;
        int tweets_counter;
        for (tweets_counter = 1; tweets_counter <= 100000; ++tweets_counter) {
            sprintf(tweet_id_in_string_mode, "%d", tweets_counter);
            if (access(tweet_id_in_string_mode, F_OK) != 0) {
                char file_stufs[1000];
                FILE *user_file;
                user_file = fopen(username, "r");
                fgets(file_stufs, 1000, user_file);
//            fscanf(user_file, "%s", file_stufs);
                cJSON *my_new_root = cJSON_Parse(file_stufs);
                cJSON *tweet_number;
                tweet_number = cJSON_CreateNumber(tweets_counter);
                cJSON *personalTweet = cJSON_GetObjectItem(my_new_root, "personalTweets");
                cJSON_AddItemToArray(personalTweet, tweet_number);
                fclose(user_file);
                user_file = fopen(username, "w");
                fprintf(user_file, "%s", cJSON_PrintUnformatted(my_new_root));
                //creating tweets file
                cJSON *root, *id, *author, *content, *comments, *likes, *seen, *liked, *retweeted;
                root = cJSON_CreateObject();
                id = cJSON_CreateNumber(tweets_counter);
                cJSON_AddItemToObject(root, "id", id);
                author = cJSON_CreateString(username);
                cJSON_AddItemToObject(root, "author", author);
                content = cJSON_CreateString(tweet);
                cJSON_AddItemToObject(root, "content", content);
                seen = cJSON_CreateArray();
                cJSON_AddItemToObject(root, "seen", seen);
                retweeted = cJSON_CreateArray();
                cJSON_AddItemToObject(root, "retweeted", retweeted);
                comments = cJSON_CreateObject();
                liked = cJSON_CreateArray();
                cJSON_AddItemToObject(root, "liked", liked);
                cJSON_AddItemToObject(root, "comments", comments);
                likes = cJSON_CreateNumber(0);
                cJSON_AddItemToObject(root, "likes", likes);
                FILE *tweet_file;
                tweet_file = fopen(tweet_id_in_string_mode, "w");
                fprintf(tweet_file, "%s", cJSON_PrintUnformatted(root));
                char *response = "{\"type\":\"Successful\",\"message\":\"Tweet is sent successfully.\"}";
                int response_len = strlen(response);
                send(client_socket, response, response_len, 0);
                //end of creating tweets file
//                fclose(user_file);
                fclose(tweet_file);
                fclose(user_file);
                break;
            }
        }

        int does_it_have_hashtak_or_not = 0;
        for (int w = 0; w<strlen(tweet); ++w){
            if (tweet[w] == '#'){
                does_it_have_hashtak_or_not = 1;
                break;
            }
        }
        if (does_it_have_hashtak_or_not == 1){
            if (access("favoriteFile", F_OK) == 0){
                FILE *favoriteFile;
                favoriteFile = fopen("favoriteFile", "r");
                char favoriteFile_stufs[10000];
                fgets(favoriteFile_stufs, 10000, favoriteFile);
                cJSON *main_json = cJSON_Parse(favoriteFile_stufs);
                cJSON *first_array = cJSON_GetObjectItem(main_json, "hashtak");
                fclose(favoriteFile);
                for (int e = 0; e<cJSON_GetArraySize(first_array); ++e){
                    cJSON *everytime_json = cJSON_GetArrayItem(first_array, e);
                    char everytime_char[1000];
                    strcpy(everytime_char, cJSON_Print(everytime_json));
                    strcpy(everytime_char, everytime_char+1);
                    everytime_char[strlen(everytime_char)-1] = '\0';
                    char* fake = strstr(tweet, everytime_char);
                    if (fake != NULL){
                        cJSON *second_array = cJSON_GetObjectItem(main_json, "user");
                        cJSON *found = cJSON_GetArrayItem(second_array, e);
                        char user_for_adding[100];
                        strcpy(user_for_adding, cJSON_Print(found));
                        strcpy(user_for_adding, user_for_adding+1);
                        user_for_adding[strlen(user_for_adding)-1] = '\0';

                        FILE *user_file;
                        user_file = fopen(user_for_adding, "r");
                        char user_file_stufs_for_add[10000];
                        fgets(user_file_stufs_for_add, 10000, user_file);
                        cJSON *favorite_main_json = cJSON_Parse(user_file_stufs_for_add);
                        cJSON *favorites_array = cJSON_GetObjectItem(favorite_main_json, "favoriteTweets");
                        cJSON *number = cJSON_CreateNumber(tweets_counter);
                        cJSON_AddItemToArray(favorites_array, number);
                        fclose(user_file);

                        FILE *user_file_2;
                        user_file_2 = fopen(user_for_adding, "w");
                        fprintf(user_file_2, "%s", cJSON_PrintUnformatted(favorite_main_json));
                        fclose(user_file_2);
                    }
                }
            }
        }


//        return start(server_socket_global);
    }
}
//------------------------------------------------
void search (int client_socket, char* buffer)
{
    int buffer_len = strlen(buffer);
    buffer_len -= 1;
    char token[22];
    char username_for_search[50];
    char strings[2][50];
    int strings_counter = 0;
    for (int i = 0; i < buffer_len; ++i) {
        if (buffer[i] == ','){
            for (int j = i-1; j>=0; --j){
                if (buffer[j] == ' '){
                    for (int k = j+1; k<i; ++k){
                        strings[strings_counter][k-j-1] = buffer[k];
                    }
                    strings[strings_counter][i-j-1] = '\0';
                    strings_counter += 1;
                    break;
                }
            }
            int m;
            for (m = i+2; m<buffer_len; ++m){
                strings[strings_counter][m-i-2] = buffer[m];
            }
            strings[strings_counter][m-i-2] = '\0';
            strings_counter += 1;
        }
    }
    strcpy(token, strings[0]);
    strcpy(username_for_search, strings[1]);
    char username[30] = "*~";
    for (int l = 0; l<=100; ++l){
        if (strcmp(user_token[l], token) == 0){
            strcpy(username, user_token[l+1]);
            break;
        }
    }
    if (strcmp(username, "*~") == 0 && username[0] == '*' && username[1] == '~'){
        char token_error[100] = "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}";
        int token_error_len = strlen(token_error);
        send(client_socket, token_error, token_error_len, 0);
    }
    else {
        if (access(username_for_search, F_OK) == 0) {
            char search_response[10000] = "{\"type\":\"Profile\",\"message\":{\"username\":";
            FILE *search_file;
            search_file = fopen(username_for_search, "r");
            char search_stuf[5000];
            fgets(search_stuf, 10000, search_file);
//            fscanf(search_file, "%s", search_stuf);
            cJSON *search_json = cJSON_Parse(search_stuf);
            char *every_part_char;
            cJSON *every_part_json;
            every_part_json = cJSON_GetObjectItem(search_json, "username");
            every_part_char = cJSON_Print(every_part_json);
            strcat(search_response, every_part_char);
            strcat(search_response, ",\"bio\":");
            every_part_json = cJSON_GetObjectItem(search_json, "bio");
            every_part_char = cJSON_Print(every_part_json);
            strcat(search_response, every_part_char);
            strcat(search_response, ",\"numberOfFollowers\":");
            every_part_json = cJSON_GetObjectItem(search_json, "followers");
            every_part_char = cJSON_Print(every_part_json);
            int counter = 0;
            for (int i = 0; i < strlen(every_part_char); ++i) {
                if (every_part_char[i] == ',') {
                    counter += 1;
                }
            }
            if (strlen(every_part_char) == 2) {
                counter = -1;
            }
            sprintf(every_part_char, "%d", counter + 1);
            strcat(search_response, every_part_char);
            strcat(search_response, ",\"numberOfFollowings\":");
            every_part_json = cJSON_GetObjectItem(search_json, "followings");
            every_part_char = cJSON_Print(every_part_json);
            counter = 0;
            for (int i = 0; i < strlen(every_part_char); ++i) {
                if (every_part_char[i] == ',') {
                    counter += 1;
                }
            }
            if (strlen(every_part_char) == 2) {
                counter = -1;
            }
            sprintf(every_part_char, "%d", counter + 1);
            strcat(search_response, every_part_char);
            strcat(search_response, ",\"followStatus\":");
            cJSON *every_part_json_2 = cJSON_GetObjectItem(search_json, "followers");
            int is_folowed_or_not = 0;
            cJSON *wow;
            for (int q = 0; q < 1000; ++q) {
                wow = cJSON_DetachItemFromArray(every_part_json_2, 0);
                char *zzz = cJSON_Print(wow);
                if (zzz == NULL) {
                    break;
                }
                strcpy(zzz, zzz + 1);
                zzz[strlen(zzz) - 1] = '\0';

                if (strcmp(zzz, username) == 0) {
                    is_folowed_or_not = 1;
                }
            }
            if (is_folowed_or_not == 0) {
                strcat(search_response, "\"NotFollowed\"");
            }
            if (is_folowed_or_not == 1) {
                strcat(search_response, "\"Followed\"");
            }
            strcat(search_response, ",\"allTweets\":[");
            every_part_json_2 = cJSON_GetObjectItem(search_json, "personalTweets");
            char *tweet_number;
            for (int b = 0; b < 10; ++b) {
                wow = cJSON_DetachItemFromArray(every_part_json_2, 0);
                tweet_number = cJSON_Print(wow);
                if (tweet_number == NULL) {
                    break;
                }
                FILE *tweet_file;
                tweet_file = fopen(tweet_number, "r");
                char tweet_number_new[10000];
                fgets(tweet_number_new, 10000, tweet_file);
//            fscanf(tweet_file, "%s", tweet_number_new);
                strcat(search_response, tweet_number_new);
                strcat(search_response, ",");
            }
            search_response[strlen(search_response) - 1] = '\0';
            strcat(search_response, "]}}");
            send(client_socket, search_response, strlen(search_response), 0);
        }
        else {
            char advanced_search_response[5000] = "[";
            FILE *allusers_file;
            allusers_file = fopen("AllUsernames", "r");
            char allusers_string[10000];
            fgets(allusers_string, 10000, allusers_file);
            cJSON *main_json = cJSON_Parse(allusers_string);
            cJSON *array = cJSON_GetObjectItem(main_json, "allusernames");
            for (int y = 0; y<cJSON_GetArraySize(array); ++y){
                cJSON *everytime_json = cJSON_GetArrayItem(array, y);
                char everytime_char[100];
                strcpy(everytime_char, cJSON_Print(everytime_json));
                strcpy(everytime_char, everytime_char+1);
                everytime_char[strlen(everytime_char)-1] = '\0';
                if (strstr(everytime_char, username_for_search) != NULL){
                    strcat(advanced_search_response, everytime_char);
                    strcat(advanced_search_response, ",");
                }
            }
            fclose(allusers_file);
            if (strlen(advanced_search_response) == 1) {
                char x[100] = "{\"type\":\"Error\",\"message\":\"This username is not valid.\"}";
                int x_len = strlen(x);
                send(client_socket, "{\"type\":\"Error\",\"message\":\"This username is not valid.\"}", x_len, 0);
            }
            else{
                advanced_search_response[strlen(advanced_search_response)-1] = '\0';
                strcat(advanced_search_response, "]");
                send(client_socket, advanced_search_response, strlen(advanced_search_response), 0);
            }
        }
        return;
    }
}
//------------------------------------------------
void tweetSearch (int client_socket, char* buffer)
{
    int buffer_len = strlen(buffer);
    buffer_len -= 1;
    char token[22];
    char comment[200] = "#";
    char strings[2][200];
    int strings_counter = 0;
    for (int i = 0; i < buffer_len; ++i) {
        if (buffer[i] == ','){
            for (int j = i-1; j>=0; --j){
                if (buffer[j] == ' '){
                    for (int k = j+1; k<i; ++k){
                        strings[strings_counter][k-j-1] = buffer[k];
                    }
                    strings[strings_counter][i-j-1] = '\0';
                    strings_counter += 1;
                    break;
                }
            }
            int m;
            for (m = i+2; m<buffer_len; ++m){
                strings[strings_counter][m-i-2] = buffer[m];
            }
            strings[strings_counter][m-i-2] = '\0';
            strings_counter += 1;
        }
    }
    strcpy(token, strings[0]);
    strcat(comment, strings[1]);
    //tweet[strlen(tweet)-1] = '\0';
    char username[30] = "*~";
    for (int l = 0; l<=100; ++l){
        if (strcmp(user_token[l], token) == 0){
            strcpy(username, user_token[l+1]);
            break;
        }
    }
    if (strcmp(username, "*~") == 0 && username[0] == '*' && username[1] == '~'){
        char token_error[100] = "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}";
        int token_error_len = strlen(token_error);
        send(client_socket, token_error, token_error_len, 0);
    }
    else{
        char tweet_search_response[10000] = "[";
        for (int e = 0; e<2000; ++e){
            char tweets_id_string_mode[20];
            sprintf(tweets_id_string_mode, "%d", e);
            if (access(tweets_id_string_mode, F_OK) == 0){
                FILE *everytime_file;
                everytime_file = fopen(tweets_id_string_mode, "r");
                char everytime_file_stufs[10000];
                fgets(everytime_file_stufs, 10000, everytime_file);
                cJSON *everytime_file_main_json = cJSON_Parse(everytime_file_stufs);
                cJSON *content_string = cJSON_GetObjectItem(everytime_file_main_json, "content");
                char content_string_type[1000];
                strcpy(content_string_type, cJSON_Print(content_string));
                strcpy(content_string_type, content_string_type+1);
                content_string_type[strlen(content_string_type)-1] = '\0';
                if (strstr(content_string_type, comment) != NULL){
                    strcat(tweet_search_response, everytime_file_stufs);
                    strcat(tweet_search_response, ",");
                }
                fclose(everytime_file);
            }
        }
        if (strlen(tweet_search_response) == 1){
            char x[100] = "{\"type\":\"Error\",\"message\":\"No such tweet.\"}";
            int x_len = strlen(x);
            send(client_socket, "{\"type\":\"Error\",\"message\":\"No such tweet.\"}", x_len, 0);
        }
        else{
            tweet_search_response[strlen(tweet_search_response)-1] = '\0';
            strcat(tweet_search_response, "]");
            send(client_socket, tweet_search_response, strlen(tweet_search_response), 0);
        }
    }
}
//------------------------------------------------
void like (int client_socket, char* buffer)
{
//    int buffer_len = strlen(buffer);
//    buffer_len -= 1;
//    char tweet_id_for_like[50];
//    char strings[1][50];
//    int strings_counter = 0;
//    for (int i = 0; i < buffer_len; ++i) {
//        if (buffer[i] == ','){
//            int m;
//            for (m = i+2; m<buffer_len; ++m){
//                strings[strings_counter][m-i-2] = buffer[m];
//            }
//            strings[strings_counter][m-i-2] = '\0';
//            strings_counter += 1;
//        }
//    }
//    strcpy(tweet_id_for_like, strings[0]);
    int buffer_len = strlen(buffer);
    buffer_len -= 1;
    char token[22];
    char tweet_id_for_like[50];
    char strings[2][50];
    int strings_counter = 0;
    for (int i = 0; i < buffer_len; ++i) {
        if (buffer[i] == ','){
            for (int j = i-1; j>=0; --j){
                if (buffer[j] == ' '){
                    for (int k = j+1; k<i; ++k){
                        strings[strings_counter][k-j-1] = buffer[k];
                    }
                    strings[strings_counter][i-j-1] = '\0';
                    strings_counter += 1;
                    break;
                }
            }
            int m;
            for (m = i+2; m<buffer_len; ++m){
                strings[strings_counter][m-i-2] = buffer[m];
            }
            strings[strings_counter][m-i-2] = '\0';
            strings_counter += 1;
        }
    }
    strcpy(token, strings[0]);
    strcpy(tweet_id_for_like, strings[1]);
    char username[30] = "*~";
    for (int l = 0; l<=100; ++l){
        if (strcmp(user_token[l], token) == 0){
            strcpy(username, user_token[l+1]);
            break;
        }
    }
    if (strcmp(username, "*~") == 0 && username[0] == '*' && username[1] == '~'){
        char token_error[100] = "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}";
        int token_error_len = strlen(token_error);
        send(client_socket, token_error, token_error_len, 0);
    }
    else {
        if (access(tweet_id_for_like, F_OK) == 0) {
            FILE *like_file;
            like_file = fopen(tweet_id_for_like, "r");
            char like_file_stufs[10000];
            fgets(like_file_stufs, 10000, like_file);
            cJSON *like_json = cJSON_Parse(like_file_stufs);
            //
            cJSON *check_like_before = cJSON_GetObjectItem(like_json, "liked");
            int liked_before_or_not = 0;
            for (int z = 0; z<cJSON_GetArraySize(check_like_before); ++z){
                cJSON *users_whom_liked = cJSON_GetArrayItem(check_like_before, z);
                char users_whom_liked_char_type[100];
                strcpy(users_whom_liked_char_type, cJSON_Print(users_whom_liked));
                strcpy(users_whom_liked_char_type, users_whom_liked_char_type+1);
                users_whom_liked_char_type[strlen(users_whom_liked_char_type)-1] = '\0';
                if (strcmp(users_whom_liked_char_type, username) == 0){
                    liked_before_or_not += 1;
                    break;
                }
            }
            //
            if (liked_before_or_not == 0) {
                cJSON *every_time_json = cJSON_GetObjectItem(like_json, "likes");
                char everytime_char[10];
                strcpy(everytime_char, cJSON_Print(every_time_json));
                int tweet_number_in_int_type = atoi(everytime_char);
                tweet_number_in_int_type += 1;
                cJSON *xxx = cJSON_CreateNumber(tweet_number_in_int_type);
                cJSON_ReplaceItemInObject(like_json, "likes", xxx);
                cJSON *string_for_liked = cJSON_CreateString(username);
                cJSON_AddItemToArray(check_like_before, string_for_liked);
                fclose(like_file);
                FILE *like_file_2;
                like_file_2 = fopen(tweet_id_for_like, "w");
                fputs(cJSON_PrintUnformatted(like_json), like_file_2);
                fclose(like_file_2);
                char like_success[100] = "{\"type\":\"Srror\",\"message\":\"Siked before.\"}";
                int like_error_len = strlen(like_success);
                send(client_socket, like_success, like_error_len, 0);
            }
            if (liked_before_or_not == 1){
                char like_error[100] = "{\"type\":\"Error\",\"message\":\"Liked before.\"}";
                int like_error_len = strlen(like_error);
                send(client_socket, like_error, like_error_len, 0);
            }
        }
        else{
            char like_error[100] = "{\"type\":\"Error\",\"message\":\"Tweet with this id is not available.\"}";
            int like_error_len = strlen(like_error);
            send(client_socket, like_error, like_error_len, 0);
        }
    }
}
//------------------------------------------------
void comment (int cient_socket, char* buffer)
{
    int buffer_len = strlen(buffer);
    buffer_len -= 1;
    char token[22];
    char tweet_id[10];
    char message[5000];
    char strings[3][5000];
    int strings_counter = 0;
    for (int i = 0; i < buffer_len; ++i) {
        if (buffer[i] == ','){
            for (int j = i-1; j>=0; --j){
                if (buffer[j] == ' '){
                    for (int k = j+1; k<i; ++k){
                        strings[strings_counter][k-j-1] = buffer[k];
                    }
                    strings[strings_counter][i-j-1] = '\0';
                    strings_counter += 1;
                    break;
                }
            }
        }
    }
    int comma_counter = 0;
    for (int j = 0; j < buffer_len; ++j){
        if (buffer[j] == ','){
            comma_counter += 1;
            if (comma_counter == 2){
                int m;
                for (m = j+2; m<buffer_len; ++m){
                    strings[strings_counter][m-j-2] = buffer[m];
                }
                strings[strings_counter][m-j-2] = '\0';
                strings_counter += 1;
                break;
            }
        }
    }
    strcpy(token, strings[0]);
    strcpy(tweet_id, strings[1]);
    strcpy(message, strings[2]);
    char username[30] = "*~";
    for (int l = 0; l<=100; ++l){
        if (strcmp(user_token[l], token) == 0){
            strcpy(username, user_token[l+1]);
            break;
        }
    }
    if (strcmp(username, "*~") == 0 && username[0] == '*' && username[1] == '~'){
        char token_error[100] = "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}";
        int token_error_len = strlen(token_error);
        send(cient_socket, token_error, token_error_len, 0);
    }
    else {
        if (access(tweet_id, F_OK) == 0) {
            FILE *comment_file;
            comment_file = fopen(tweet_id, "r");
            char comment_file_stufs[10000];
            fgets(comment_file_stufs, 10000, comment_file);
            cJSON *comment_json = cJSON_Parse(comment_file_stufs);
            cJSON *everytime_json = cJSON_GetObjectItem(comment_json, "comments");
            cJSON *author_of_the_comment;
            author_of_the_comment = cJSON_CreateString(message);
            cJSON_AddItemToObject(everytime_json, username, author_of_the_comment);
            fclose(comment_file);
            FILE *comment_file_2;
            comment_file_2 = fopen(tweet_id, "w");
            fprintf(comment_file_2, "%s", cJSON_PrintUnformatted(comment_json));
            fclose(comment_file_2);
            char success_for_comment[100] = "{\"type\":\"Srror\",\"message\":\"Siked before.\"}";
            int success_for_comment_len = strlen(success_for_comment);
            send(cient_socket, success_for_comment, success_for_comment_len, 0);
            return;
        }
        else{
            char error_for_comment[100] = "{\"type\":\"Error\",\"message\":\"Tweet with this id is not available.\"}";
            int error_for_comment_len = strlen(error_for_comment);
            send(cient_socket, error_for_comment, error_for_comment_len, 0);
        }
    }
}
//------------------------------------------------
void follow (int client_socket, char* buffer)
{
    int buffer_len = strlen(buffer);
    buffer_len -= 1;
    char token[22];
    char user_name_to_follow[50];
    char strings[2][50];
    int strings_counter = 0;
    for (int i = 0; i < buffer_len; ++i) {
        if (buffer[i] == ','){
            for (int j = i-1; j>=0; --j){
                if (buffer[j] == ' '){
                    for (int k = j+1; k<i; ++k){
                        strings[strings_counter][k-j-1] = buffer[k];
                    }
                    strings[strings_counter][i-j-1] = '\0';
                    strings_counter += 1;
                    break;
                }
            }
            int m;
            for (m = i+2; m<buffer_len; ++m){
                strings[strings_counter][m-i-2] = buffer[m];
            }
            strings[strings_counter][m-i-2] = '\0';
            strings_counter += 1;
        }
    }
    strcpy(token, strings[0]);
    strcpy(user_name_to_follow, strings[1]);
    char username[30] = "*~";
    for (int l = 0; l<=100; ++l){
        if (strcmp(user_token[l], token) == 0){
            strcpy(username, user_token[l+1]);
            break;
        }
    }
    if (strcmp(username, "*~") == 0 && username[0] == '*' && username[1] == '~'){
        char token_error[100] = "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}";
        int token_error_len = strlen(token_error);
        send(client_socket, token_error, token_error_len, 0);
    }
    else {
        FILE *follow_file;
        follow_file = fopen(user_name_to_follow, "r");
        char follow_stufs[10000];
        fgets(follow_stufs, 10000, follow_file);
        cJSON *follow_json = cJSON_Parse(follow_stufs);
        cJSON *everytime_follow = cJSON_GetObjectItem(follow_json, "followers");
        cJSON *my_string = cJSON_CreateString(username);
        cJSON_AddItemToArray(everytime_follow, my_string);
        fclose(follow_file);
        FILE *follow_file_2;
        follow_file_2 = fopen(user_name_to_follow, "w");
        fprintf(follow_file_2, "%s", cJSON_PrintUnformatted(follow_json));
        fclose(follow_file_2);

        FILE *follow_file_3;
        follow_file_3 = fopen(username, "r");
        char follow_stufs_2[10000];
        fgets(follow_stufs_2, 10000, follow_file_3);
        cJSON *follow_json_2 = cJSON_Parse(follow_stufs_2);
        cJSON *everytime_follow_2 = cJSON_GetObjectItem(follow_json_2, "followings");
        cJSON *my_string_2 = cJSON_CreateString(user_name_to_follow);
        cJSON_AddItemToArray(everytime_follow_2, my_string_2);
        fclose(follow_file_3);
        FILE *follow_file_4;
        follow_file_4 = fopen(username, "w");
        fprintf(follow_file_4, "%s", cJSON_PrintUnformatted(follow_json_2));
        fclose(follow_file_4);
    }
}
//------------------------------------------------
void unfollw (int client_socket, char* buffer)
{
    int buffer_len = strlen(buffer);
    buffer_len -= 1;
    char token[22];
    char user_name_to_unfollow[50];
    char strings[2][50];
    int strings_counter = 0;
    for (int i = 0; i < buffer_len; ++i) {
        if (buffer[i] == ','){
            for (int j = i-1; j>=0; --j){
                if (buffer[j] == ' '){
                    for (int k = j+1; k<i; ++k){
                        strings[strings_counter][k-j-1] = buffer[k];
                    }
                    strings[strings_counter][i-j-1] = '\0';
                    strings_counter += 1;
                    break;
                }
            }
            int m;
            for (m = i+2; m<buffer_len; ++m){
                strings[strings_counter][m-i-2] = buffer[m];
            }
            strings[strings_counter][m-i-2] = '\0';
            strings_counter += 1;
        }
    }
    strcpy(token, strings[0]);
    strcpy(user_name_to_unfollow, strings[1]);
    char username[30] = "*~";
    for (int l = 0; l<=100; ++l){
        if (strcmp(user_token[l], token) == 0){
            strcpy(username, user_token[l+1]);
            break;
        }
    }
    if (strcmp(username, "*~") == 0 && username[0] == '*' && username[1] == '~'){
        char token_error[100] = "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}";
        int token_error_len = strlen(token_error);
        send(client_socket, token_error, token_error_len, 0);
    }
    else {
        FILE *follow_file;
        follow_file = fopen(user_name_to_unfollow, "r");
        char follow_stufs[10000];
        fgets(follow_stufs, 10000, follow_file);
        cJSON *follow_json = cJSON_Parse(follow_stufs);
        cJSON *everytime_follow = cJSON_GetObjectItem(follow_json, "followers");
        int which_index;
        for (int i = 0; i < 10000; ++i) {
            cJSON *index = cJSON_GetArrayItem(everytime_follow, i);
            char folowers_for_unfollow[50];
            strcpy(folowers_for_unfollow, cJSON_Print(index));
            strcpy(folowers_for_unfollow, folowers_for_unfollow + 1);
            folowers_for_unfollow[strlen(folowers_for_unfollow) - 1] = '\0';
            if (strcmp(folowers_for_unfollow, username) == 0) {
                which_index = i;
                break;
            }
        }
        cJSON_DeleteItemFromArray(everytime_follow, which_index);
        fclose(follow_file);
        FILE *follow_file_2;
        follow_file_2 = fopen(user_name_to_unfollow, "w");
        fprintf(follow_file_2, "%s", cJSON_PrintUnformatted(follow_json));
        fclose(follow_file_2);


        FILE *follow_file_3;
        follow_file_3 = fopen(username, "r");
        char follow_stufs_2[10000];
        fgets(follow_stufs_2, 10000, follow_file_3);
        cJSON *follow_json_2 = cJSON_Parse(follow_stufs_2);
        cJSON *everytime_follow_2 = cJSON_GetObjectItem(follow_json_2, "followings");
        int which_index_2;
        for (int j = 0; j < 10000; ++j) {
            cJSON *index_2 = cJSON_GetArrayItem(everytime_follow_2, j);
            char folowers_for_unfollow_2[50];
            strcpy(folowers_for_unfollow_2, cJSON_Print(index_2));
            strcpy(folowers_for_unfollow_2, folowers_for_unfollow_2 + 1);
            folowers_for_unfollow_2[strlen(folowers_for_unfollow_2) - 1] = '\0';
//        //
//        printf("%s\n", folowers_for_unfollow_2);
//        //
            if (strcmp(folowers_for_unfollow_2, user_name_to_unfollow) == 0) {
                which_index_2 = j;
                break;
            }
        }
        cJSON_DeleteItemFromArray(everytime_follow_2, which_index_2);
        fclose(follow_file_3);
        FILE *follow_file_4;
        follow_file_4 = fopen(username, "w");
        fprintf(follow_file_4, "%s", cJSON_PrintUnformatted(follow_json_2));
        fclose(follow_file_4);
    }
}
//------------------------------------------------
void setBio (int client_socket, char* buffer)
{
    int buffer_len = strlen(buffer);
    buffer_len -= 1;
    char token[22];
    char bio[500];
    char strings[2][500];
    int strings_counter = 0;
    for (int i = 0; i < buffer_len; ++i) {
        if (buffer[i] == ','){
            for (int j = i-1; j>=0; --j){
                if (buffer[j] == ' '){
                    for (int k = j+1; k<i; ++k){
                        strings[strings_counter][k-j-1] = buffer[k];
                    }
                    strings[strings_counter][i-j-1] = '\0';
                    strings_counter += 1;
                    break;
                }
            }
            int m;
            for (m = i+2; m<buffer_len; ++m){
                strings[strings_counter][m-i-2] = buffer[m];
            }
            strings[strings_counter][m-i-2] = '\0';
            strings_counter += 1;
        }
    }
    strcpy(token, strings[0]);
    strcpy(bio, strings[1]);
    char username[30] = "*~";
    for (int l = 0; l<=100; ++l){
        if (strcmp(user_token[l], token) == 0){
            strcpy(username, user_token[l+1]);
            break;
        }
    }
    if (strcmp(username, "*~") == 0 && username[0] == '*' && username[1] == '~'){
        char token_error[100] = "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}";
        int token_error_len = strlen(token_error);
        send(client_socket, token_error, token_error_len, 0);
    }
    else {
        FILE *bio_file;
        bio_file = fopen(username, "r");
        char bio_stufs[10000];
        fgets(bio_stufs, 10000, bio_file);
        cJSON *bio_json = cJSON_Parse(bio_stufs);
        cJSON *can_or_not = cJSON_GetObjectItem(bio_json, "bio");
        if (strlen(cJSON_Print(can_or_not)) == 2) {
            cJSON *everytime_bio = cJSON_CreateString(bio);
            cJSON_ReplaceItemInObject(bio_json, "bio", everytime_bio);
            fclose(bio_file);

            FILE *bio_file_2;
            bio_file_2 = fopen(username, "w");
            fprintf(bio_file_2, "%s", cJSON_PrintUnformatted(bio_json));
            fclose(bio_file_2);
            char successful[100] = "{\"type\":\"Successful\",\"message\":\"Bio is updated successfully.\"}";
            int successful_len = strlen(successful);
            send(client_socket, successful, successful_len, 0);
        } else {
            char error[100] = "{\"type\":\"Error\",\"message\":\"Bio is already updated.\"}";
            int error_len = strlen(error);
            send(client_socket, error, error_len, 0);
        }
        return;
    }
}
//------------------------------------------------
void logout (int client_socket, char* buffer)
{
    int buffer_len = strlen(buffer);
    buffer_len -= 1;
    char token[22];
    char strings[1][22];
    int strings_counter = 0;
    for (int i = 0; i < buffer_len; ++i) {
        if (buffer[i] == ' '){
            for (int j = i+1; j<buffer_len; ++j){
                strings[strings_counter][j-i-1] = buffer[j];
            }
            strings[strings_counter][buffer_len-i-1] = '\0';
            strings_counter += 1;
        }
    }
    strcpy(token, strings[0]);
    for (int i = 0; i<= 1000; ++i){
        if (strcmp(token, user_token[i]) == 0){
            strcpy(user_token[i], "null");
            strcpy(user_token[i+1], "null");
        }
    }
    return;
}
//------------------------------------------------
void tweetProfile (int client_socket, char* buffer)
{
    int buffer_len = strlen(buffer);
    buffer_len -= 1;
    char token[22];
    for (int i = 0; i<buffer_len; ++i){
        if (buffer[i] == ' '){
            for (int j = i+1; j<buffer_len; ++j){
                token[j-i-1] = buffer[j];
            }
            token[buffer_len-i-1] = '\0';
        }
    }
    char username_for_search[30] = "*~";
    for (int l = 0; l<=100; ++l){
        if (strcmp(user_token[l], token) == 0){
            strcpy(username_for_search, user_token[l+1]);
            break;
        }
    }
    if (strcmp(username_for_search, "*~") == 0 && username_for_search[0] == '*' && username_for_search[1] == '~'){
        char token_error[100] = "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}";
        int token_error_len = strlen(token_error);
        send(client_socket, token_error, token_error_len, 0);
    }
    else {
        char search_response[10000] = "{\"type\":\"Profile\",\"message\":{\"username\":";
        FILE *search_file;
        search_file = fopen(username_for_search, "r");
        char search_stuf[5000];
//        fgets(search_stuf, 10000, search_file);
        fscanf(search_file, "%s", search_stuf);
        cJSON *search_json = cJSON_Parse(search_stuf);
        char *every_part_char;
        cJSON *every_part_json;
        every_part_json = cJSON_GetObjectItem(search_json, "username");
        every_part_char = cJSON_Print(every_part_json);
        strcat(search_response, every_part_char);
        strcat(search_response, ",\"bio\":");
        every_part_json = cJSON_GetObjectItem(search_json, "bio");
        every_part_char = cJSON_Print(every_part_json);
        strcat(search_response, every_part_char);
        strcat(search_response, ",\"numberOfFollowers\":");
        every_part_json = cJSON_GetObjectItem(search_json, "followers");
        every_part_char = cJSON_Print(every_part_json);
        int counter = 0;
        for (int i = 0; i < strlen(every_part_char); ++i) {
            if (every_part_char[i] == ',') {
                counter += 1;
            }
        }
        if (strlen(every_part_char) == 2) {
            counter = -1;
        }
        sprintf(every_part_char, "%d", counter + 1);
        strcat(search_response, every_part_char);
        strcat(search_response, ",\"numberOfFollowings\":");
        every_part_json = cJSON_GetObjectItem(search_json, "followings");
        every_part_char = cJSON_Print(every_part_json);
        counter = 0;
        for (int i = 0; i < strlen(every_part_char); ++i) {
            if (every_part_char[i] == ',') {
                counter += 1;
            }
        }
        if (strlen(every_part_char) == 2) {
            counter = -1;
        }
        sprintf(every_part_char, "%d", counter + 1);
        strcat(search_response, every_part_char);
//        strcat(search_response, ",\"followStatus\":");
//        cJSON * every_part_json_2 = cJSON_GetObjectItem(search_json, "followers");
//        int is_folowed_or_not = 0;
//        cJSON * wow;
//        for (int q = 0; q<1000; ++q){
//            wow = cJSON_DetachItemFromArray(every_part_json_2, 0);
//            char* zzz = cJSON_Print(wow);
//            if (zzz == NULL){
//                break;
//            }
//            strcpy(zzz, zzz+1);
//            zzz[strlen(zzz)-1] = '\0';
//
//            if (strcmp(zzz, username) == 0){
//                is_folowed_or_not = 1;
//            }
//        }
//        if (is_folowed_or_not == 0){
//            strcat(search_response, "\"NotFollowed\"");
//        }
//        if (is_folowed_or_not == 1){
//            strcat(search_response, "\"Followed\"");
//        }
        cJSON *every_part_json_2;
        cJSON *wow;
        strcat(search_response, ",\"allTweets\":[");
        every_part_json_2 = cJSON_GetObjectItem(search_json, "personalTweets");
        char *tweet_number;
        for (int b = 0; b < 10; ++b) {
            wow = cJSON_DetachItemFromArray(every_part_json_2, 0);
            tweet_number = cJSON_Print(wow);
            if (tweet_number == NULL) {
                break;
            }
            FILE *tweet_file;
            tweet_file = fopen(tweet_number, "r");
            char tweet_number_new[10000];
            fgets(tweet_number_new, 10000, tweet_file);
//            fscanf(tweet_file, "%s", tweet_number_new);
            strcat(search_response, tweet_number_new);
            strcat(search_response, ",");
            //
            fclose(tweet_file);
            //
        }
        search_response[strlen(search_response) - 1] = '\0';
        strcat(search_response, "]}}");
        send(client_socket, search_response, strlen(search_response), 0);
        //
        fclose(search_file);
        //
        return;
    }
}
//------------------------------------------------
void changePassword (int client_socket, char* buffer)
{
    int buffer_len = strlen(buffer);
    buffer_len -= 1;
    char token[22];
    char current_password[100];
    char new_password[100];
    char strings[3][100];
    int strings_counter = 0;
    for (int i = 0; i < buffer_len; ++i) {
        if (buffer[i] == ','){
            for (int j = i-1; j>=0; --j){
                if (buffer[j] == ' '){
                    for (int k = j+1; k<i; ++k){
                        strings[strings_counter][k-j-1] = buffer[k];
                    }
                    strings[strings_counter][i-j-1] = '\0';
                    strings_counter += 1;
                    break;
                }
            }
        }
    }
    int comma_counter = 0;
    for (int j = 0; j < buffer_len; ++j){
        if (buffer[j] == ','){
            comma_counter += 1;
            if (comma_counter == 2){
                int m;
                for (m = j+2; m<buffer_len; ++m){
                    strings[strings_counter][m-j-2] = buffer[m];
                }
                strings[strings_counter][m-j-2] = '\0';
                strings_counter += 1;
                break;
            }
        }
    }
    strcpy(token, strings[0]);
    strcpy(current_password, strings[1]);
    strcpy(new_password, strings[2]);
    if (strlen(new_password) > 16){
        char error[100] = "{\"type\":\"Error\",\"message\":\"To long.\"}";
        int error_len = strlen(error);
        send(client_socket, error, error_len, 0);
    }
    else {
        char username[30] = "*~";
        for (int l = 0; l <= 100; ++l) {
            if (strcmp(user_token[l], token) == 0) {
                strcpy(username, user_token[l + 1]);
                break;
            }
        }
        if (strcmp(username, "*~") == 0 && username[0] == '*' && username[1] == '~') {
            char token_error[100] = "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}";
            int token_error_len = strlen(token_error);
            send(client_socket, token_error, token_error_len, 0);
        } else {
            FILE *change_file;
            change_file = fopen(username, "r");
            char change_stuf[10000];
            fgets(change_stuf, 10000, change_file);
            cJSON *change_json = cJSON_Parse(change_stuf);
            cJSON *everytime_change = cJSON_GetObjectItem(change_json, "password");
            char password[100];
            strcpy(password, cJSON_Print(everytime_change));
            strcpy(password, password + 1);
            password[strlen(password) - 1] = '\0';
            if (strcmp(password, current_password) != 0) {
                char error[100] = "{\"type\":\"Error\",\"message\":\"Entered current password is wrong.\"}";
                int error_len = strlen(error);
                send(client_socket, error, error_len, 0);
            } else {
                cJSON *new_pass = cJSON_CreateString(new_password);
                cJSON_ReplaceItemInObject(change_json, "password", new_pass);
                fclose(change_file);

                FILE *change_file_2;
                change_file_2 = fopen(username, "w");
                fprintf(change_file_2, "%s", cJSON_PrintUnformatted(change_json));
                fclose(change_file_2);
                char successful[100] = "{\"type\":\"Successful\",\"message\":\"Password is changed successfully.\"}";
                int successful_len = strlen(successful);
                send(client_socket, successful, successful_len, 0);
            }
            return;
        }
    }
}
//------------------------------------------------
void refresh (int client_socket, char* buffer)
{
    int buffer_len = strlen(buffer);
    buffer_len -= 1;
    char token[22];
    char strings[1][22];
    int strings_counter = 0;
    for (int i = 0; i < buffer_len; ++i) {
        if (buffer[i] == ' '){
            for (int j = i+1; j<buffer_len; ++j){
                strings[strings_counter][j-i-1] = buffer[j];
            }
            strings[strings_counter][buffer_len-i-1] = '\0';
            strings_counter += 1;
        }
    }
    strcpy(token, strings[0]);
    char username[30] = "*~";
    for (int l = 0; l<=100; ++l){
        if (strcmp(user_token[l], token) == 0){
            strcpy(username, user_token[l+1]);
            break;
        }
    }
    if (strcmp(username, "*~") == 0 && username[0] == '*' && username[1] == '~'){
        char token_error[100] = "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}";
        int token_error_len = strlen(token_error);
        send(client_socket, token_error, token_error_len, 0);
    }
    else {
        char refresh_response[10000] = "{\"type\":\"List\",\"message\":[";
        FILE *refresh_main_file;
        refresh_main_file = fopen(username, "r");
        char refresh_main_char[10000];
        fgets(refresh_main_char, 10000, refresh_main_file);
        cJSON *refresh_main_json = cJSON_Parse(refresh_main_char);
        cJSON *followers_and_followings;
        //followers
        followers_and_followings = cJSON_GetObjectItem(refresh_main_json, "followers");
        cJSON *everytime;
        char each_time_username[50];
        FILE *each_time_file;
        char users_file_stufs[10000];
        cJSON *users_file_stufs_json_main;
        cJSON *tweets_array;
        //
        int tweets_array_to_show[1000];
        int int_array_counter = 0;
        //
        for (int i = 0; i < cJSON_GetArraySize(followers_and_followings); ++i) {
            everytime = cJSON_GetArrayItem(followers_and_followings, i);
            strcpy(each_time_username, cJSON_Print(everytime));
            strcpy(each_time_username, each_time_username + 1);
            each_time_username[strlen(each_time_username) - 1] = '\0';
            each_time_file = fopen(each_time_username, "r");
            fgets(users_file_stufs, 10000, each_time_file);
            users_file_stufs_json_main = cJSON_Parse(users_file_stufs);
            tweets_array = cJSON_GetObjectItem(users_file_stufs_json_main, "personalTweets");
            for (int j = 0; j < cJSON_GetArraySize(tweets_array); ++j) {
                cJSON *tweets_number = cJSON_GetArrayItem(tweets_array, j);
                FILE *tweet_file;
                tweet_file = fopen(cJSON_Print(tweets_number), "r");
                char tweet_file_stufs[10000];
                fgets(tweet_file_stufs, 10000, tweet_file);
                cJSON *tweet_file_stufs_json = cJSON_Parse(tweet_file_stufs);
                cJSON *seen_array = cJSON_GetObjectItem(tweet_file_stufs_json, "seen");
                int seen_or_not = 0;
                for (int k = 0; k < cJSON_GetArraySize(seen_array); ++k) {
                    cJSON *everytime_seen_json = cJSON_GetArrayItem(seen_array, k);
                    char seen_users[50];
                    strcpy(seen_users, cJSON_Print(everytime_seen_json));
                    strcpy(seen_users, seen_users + 1);
                    seen_users[strlen(seen_users) - 1] = '\0';
                    if (strcmp(username, seen_users) == 0) {
                        seen_or_not = 1;
                    }
                }
                if (seen_or_not == 0) {
//                    strcat(refresh_response, tweet_file_stufs);
//                    strcat(refresh_response, ",");
                    //
                    char tweet_number_string_type[20];
                    strcpy(tweet_number_string_type, cJSON_Print(tweets_number));
                    int x = atoi(tweet_number_string_type);
                    tweets_array_to_show[int_array_counter] = x;
                    int_array_counter += 1;
                    //
                    cJSON *string = cJSON_CreateString(username);
                    cJSON_AddItemToArray(seen_array, string);
                    fclose(tweet_file);
                    FILE *tweet_file_2;
                    tweet_file_2 = fopen(cJSON_Print(tweets_number), "w");
                    fprintf(tweet_file_2, "%s", cJSON_PrintUnformatted(tweet_file_stufs_json));
                    fclose(tweet_file_2);
                }
            }
            //
            fclose(each_time_file);
            //
        }
        //
        //following
        followers_and_followings = cJSON_GetObjectItem(refresh_main_json, "followings");
        cJSON *everytime_2;
        char each_time_username_2[50];
        FILE *each_time_file_2;
        char users_file_stufs_2[10000];
        cJSON *users_file_stufs_json_main_2;
        cJSON *tweets_array_2;
        for (int i_2 = 0; i_2 < cJSON_GetArraySize(followers_and_followings); ++i_2) {
            everytime_2 = cJSON_GetArrayItem(followers_and_followings, i_2);
            strcpy(each_time_username_2, cJSON_Print(everytime_2));
            strcpy(each_time_username_2, each_time_username_2 + 1);
            each_time_username_2[strlen(each_time_username_2) - 1] = '\0';
            each_time_file_2 = fopen(each_time_username_2, "r");
            fgets(users_file_stufs_2, 10000, each_time_file_2);
            users_file_stufs_json_main_2 = cJSON_Parse(users_file_stufs_2);
            tweets_array_2 = cJSON_GetObjectItem(users_file_stufs_json_main_2, "personalTweets");
            for (int j_2 = 0; j_2 < cJSON_GetArraySize(tweets_array_2); ++j_2) {
                cJSON *tweets_number_2 = cJSON_GetArrayItem(tweets_array_2, j_2);
                FILE *tweet_file_3;
                tweet_file_3 = fopen(cJSON_Print(tweets_number_2), "r");
                char tweet_file_stufs_2[10000];
                fgets(tweet_file_stufs_2, 10000, tweet_file_3);
                cJSON *tweet_file_stufs_json_2 = cJSON_Parse(tweet_file_stufs_2);
                cJSON *seen_array_2 = cJSON_GetObjectItem(tweet_file_stufs_json_2, "seen");
                int seen_or_not_2 = 0;
                for (int k_2 = 0; k_2 < cJSON_GetArraySize(seen_array_2); ++k_2) {
                    cJSON *everytime_seen_json_2 = cJSON_GetArrayItem(seen_array_2, k_2);
                    char seen_users_2[50];
                    strcpy(seen_users_2, cJSON_Print(everytime_seen_json_2));
                    strcpy(seen_users_2, seen_users_2 + 1);
                    seen_users_2[strlen(seen_users_2) - 1] = '\0';
                    if (strcmp(username, seen_users_2) == 0) {
                        seen_or_not_2 = 1;
                    }
                }
                if (seen_or_not_2 == 0) {
//                    strcat(refresh_response, tweet_file_stufs_2);
//                    strcat(refresh_response, ",");
                    //
                    char tweet_number_string_type_2[20];
                    strcpy(tweet_number_string_type_2, cJSON_Print(tweets_number_2));
                    int x_2 = atoi(tweet_number_string_type_2);
                    tweets_array_to_show[int_array_counter] = x_2;
                    int_array_counter += 1;
                    //
                    cJSON *string_2 = cJSON_CreateString(username);
                    cJSON_AddItemToArray(seen_array_2, string_2);
                    fclose(tweet_file_3);
                    FILE *tweet_file_4;
                    tweet_file_4 = fopen(cJSON_Print(tweets_number_2), "w");
                    fprintf(tweet_file_4, "%s", cJSON_PrintUnformatted(tweet_file_stufs_json_2));
                    fclose(tweet_file_4);
                }
            }
            //
            fclose(each_time_file_2);
            //
        }
//        strcpy(refresh_response, refresh_response + 1);
//        strcat(refresh_response, "]}\0");
//        int refresh_response_len = strlen(refresh_response);
//        send(client_socket, refresh_response, refresh_response_len, 0);
        ////
        //buble sort
        for (int z = 0; z<int_array_counter; ++z){
            for (int z2 = 0; z2<int_array_counter; ++z2){
                if (tweets_array_to_show[z] > tweets_array_to_show[z2]){
                    int help = tweets_array_to_show[z];
                    tweets_array_to_show[z] = tweets_array_to_show[z2];
                    tweets_array_to_show[z2] = help;
                }
            }
        }
        //end of buble sort
        for (int t = 0; t<int_array_counter; ++t){
            FILE *sorted_tweets;
            char sorted_tweets_number_char_type[20];
            sprintf(sorted_tweets_number_char_type, "%d", tweets_array_to_show[t]);
            sorted_tweets = fopen(sorted_tweets_number_char_type, "r");
            char sorted_tweets_stufs[10000];
            fgets(sorted_tweets_stufs, 10000, sorted_tweets);
            strcat(refresh_response, sorted_tweets_stufs);
            strcat(refresh_response, ",");
            fclose(sorted_tweets);
        }
        strcpy(refresh_response, refresh_response + 1);
        strcat(refresh_response, "]}\0");
        int refresh_response_len = strlen(refresh_response);
        send(client_socket, refresh_response, refresh_response_len, 0);
        ////
        //
        //
        fclose(refresh_main_file);
        //
    }
}
//------------------------------------------------
void delete (int client_socket, char* buffer)
{
    int buffer_len = strlen(buffer);
    buffer_len -= 1;
    char token[22];
    char tweet_id_to_delete[50];
    char strings[2][50];
    int strings_counter = 0;
    for (int i = 0; i < buffer_len; ++i) {
        if (buffer[i] == ','){
            for (int j = i-1; j>=0; --j){
                if (buffer[j] == ' '){
                    for (int k = j+1; k<i; ++k){
                        strings[strings_counter][k-j-1] = buffer[k];
                    }
                    strings[strings_counter][i-j-1] = '\0';
                    strings_counter += 1;
                    break;
                }
            }
            int m;
            for (m = i+2; m<buffer_len; ++m){
                strings[strings_counter][m-i-2] = buffer[m];
            }
            strings[strings_counter][m-i-2] = '\0';
            strings_counter += 1;
        }
    }
    strcpy(token, strings[0]);
    strcpy(tweet_id_to_delete, strings[1]);
    char username[30] = "*~";
    for (int l = 0; l<=100; ++l){
        if (strcmp(user_token[l], token) == 0){
            strcpy(username, user_token[l+1]);
            break;
        }
    }
    if (strcmp(username, "*~") == 0 && username[0] == '*' && username[1] == '~'){
        char token_error[100] = "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}";
        int token_error_len = strlen(token_error);
        send(client_socket, token_error, token_error_len, 0);
    }
    else{
        if (access(tweet_id_to_delete, F_OK) == 0){
            FILE *delete_file;
            delete_file = fopen(username, "r");
            char delete_file_stufs[10000];
            fgets(delete_file_stufs, 10000,  delete_file);
            cJSON *delete_file_main_json = cJSON_Parse(delete_file_stufs);
            cJSON *Personal_tweets_json = cJSON_GetObjectItem(delete_file_main_json, "personalTweets");
            int tweet_index = -1;
            for (int i = 0; i<cJSON_GetArraySize(Personal_tweets_json); ++i){
                cJSON *every_time_json = cJSON_GetArrayItem(Personal_tweets_json, i);
                if (strcmp(tweet_id_to_delete, cJSON_Print(every_time_json)) == 0){
                    tweet_index = i;
                    break;
                }
            }

            FILE *checking_retweet;
            checking_retweet = fopen(tweet_id_to_delete, "r");
            char checking_retweet_stufs[10000];
            fgets(checking_retweet_stufs, 10000, checking_retweet);
            cJSON *checking_retweet_main_json = cJSON_Parse(checking_retweet_stufs);
            cJSON *retweet_array = cJSON_GetObjectItem(checking_retweet_main_json, "retweeted");
            int is_retweeted_or_not = 0;
            for (int i = 0; i<cJSON_GetArraySize(retweet_array); ++i){
                cJSON *array_stufs = cJSON_GetArrayItem(retweet_array, i);
                char array_stufs_string[100];
                strcpy(array_stufs_string, cJSON_Print(array_stufs));
                strcpy(array_stufs_string, array_stufs_string+1);
                array_stufs_string[strlen(array_stufs_string)-1] = '\0';
                if (strcmp(username, array_stufs_string) == 0){
                    is_retweeted_or_not = 1;
                    break;
                }
            }
            //
            fclose(checking_retweet);
            //


            if (tweet_index == -1 || is_retweeted_or_not == 1){
                char error[100] = "{\"type\":\"Error\",\"message\":\"This tweet is not yours.\"}";
                int error_len = strlen(error);
                send(client_socket, error, error_len, 0);
            }
            else{
                cJSON_DeleteItemFromArray(Personal_tweets_json, tweet_index);
                fclose(delete_file);
                FILE *delete_file_2;
                delete_file_2 = fopen(username, "w");
                fprintf(delete_file_2, "%s", cJSON_PrintUnformatted(delete_file_main_json));
                fclose(delete_file_2);

                for (int i = 0; i<cJSON_GetArraySize(retweet_array); ++i){
                    cJSON *array_stufs = cJSON_GetArrayItem(retweet_array, i);
                    char array_stufs_string[100];
                    strcpy(array_stufs_string, cJSON_Print(array_stufs));
                    strcpy(array_stufs_string, array_stufs_string+1);
                    array_stufs_string[strlen(array_stufs_string)-1] = '\0';
                    FILE *everyone_who_retweeted;
                    everyone_who_retweeted = fopen(array_stufs_string, "r");
                    char everyone_who_retweeted_stufs[10000];
                    fgets(everyone_who_retweeted_stufs, 10000, everyone_who_retweeted);
                    cJSON *everyone_who_retweeted_main_json = cJSON_Parse(everyone_who_retweeted_stufs);
                    cJSON *personal_tweet_array = cJSON_GetObjectItem(everyone_who_retweeted_main_json, "personalTweets");
                    int index;
                    for (int z = 0; z < cJSON_GetArraySize(personal_tweet_array); ++z){
                        cJSON *array_stufsss = cJSON_GetArrayItem(personal_tweet_array, z);
                        if (strcmp(tweet_id_to_delete, cJSON_Print(array_stufsss)) == 0){
                            index = z;
                            break;
                        }
                    }
                    cJSON_DeleteItemFromArray(personal_tweet_array, index);
                    fclose(everyone_who_retweeted);
                    FILE *everyone_who_retweeted_2;
                    everyone_who_retweeted_2 = fopen(array_stufs_string, "w");
                    fprintf(everyone_who_retweeted_2, "%s", cJSON_PrintUnformatted(everyone_who_retweeted_main_json));
                    fclose(everyone_who_retweeted_2);
                }



                int what = remove(tweet_id_to_delete);
                char error[100] = "{\"type\":\"Successful\",\"message\":\"No such tweet id.\"}";
                int error_len = strlen(error);
                send(client_socket, error, error_len, 0);
            }
        }
        else{
            char error[100] = "{\"type\":\"Error\",\"message\":\"No such tweet id.\"}";
            int error_len = strlen(error);
            send(client_socket, error, error_len, 0);
        }
    }
}
//------------------------------------------------
void retweet (int client_socket, char* buffer)
{
    int buffer_len = strlen(buffer);
    buffer_len -= 1;
    char token[22];
    char tweet_id_to_retweet[50];
    char strings[2][50];
    int strings_counter = 0;
    for (int i = 0; i < buffer_len; ++i) {
        if (buffer[i] == ','){
            for (int j = i-1; j>=0; --j){
                if (buffer[j] == ' '){
                    for (int k = j+1; k<i; ++k){
                        strings[strings_counter][k-j-1] = buffer[k];
                    }
                    strings[strings_counter][i-j-1] = '\0';
                    strings_counter += 1;
                    break;
                }
            }
            int m;
            for (m = i+2; m<buffer_len; ++m){
                strings[strings_counter][m-i-2] = buffer[m];
            }
            strings[strings_counter][m-i-2] = '\0';
            strings_counter += 1;
        }
    }
    strcpy(token, strings[0]);
    strcpy(tweet_id_to_retweet, strings[1]);
    char username[30] = "*~";
    for (int l = 0; l<=100; ++l){
        if (strcmp(user_token[l], token) == 0){
            strcpy(username, user_token[l+1]);
            break;
        }
    }
    if (strcmp(username, "*~") == 0 && username[0] == '*' && username[1] == '~'){
        char token_error[100] = "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}";
        int token_error_len = strlen(token_error);
        send(client_socket, token_error, token_error_len, 0);
    }
    else{
        if (access(tweet_id_to_retweet, F_OK) == 0){
            FILE *user_who_retweeted;
            user_who_retweeted = fopen(username, "r");
            char user_who_retweeted_stuf[10000];
            fgets(user_who_retweeted_stuf, 10000, user_who_retweeted);
            cJSON *user_who_retweeted_main_json = cJSON_Parse(user_who_retweeted_stuf);
            cJSON *personal_tweet_json = cJSON_GetObjectItem(user_who_retweeted_main_json, "personalTweets");
            int tweet_number = atoi(tweet_id_to_retweet);
            cJSON *tweet_number_int_type = cJSON_CreateNumber(tweet_number);
            cJSON_AddItemToArray(personal_tweet_json, tweet_number_int_type);
            fclose(user_who_retweeted);
            FILE *user_who_retweeted_2;
            user_who_retweeted_2 = fopen(username, "w");
            fprintf(user_who_retweeted_2, "%s", cJSON_PrintUnformatted(user_who_retweeted_main_json));
            fclose(user_who_retweeted_2);


            FILE *tweet_which_retweeted;
            tweet_which_retweeted = fopen(tweet_id_to_retweet, "r");
            char tweet_which_retweeted_stuf[10000];
            fgets(tweet_which_retweeted_stuf, 10000, tweet_which_retweeted);
            cJSON *tweet_which_retweeted_main_json = cJSON_Parse(tweet_which_retweeted_stuf);
            cJSON *retweeted_array = cJSON_GetObjectItem(tweet_which_retweeted_main_json, "retweeted");
            int previously_retweeted_or_not = 0;
            for (int i = 0; i < cJSON_GetArraySize(retweeted_array); ++i) {
                cJSON *array_item = cJSON_GetArrayItem(retweeted_array, i);
                char array_item_string[100];
                strcpy(array_item_string, cJSON_Print(array_item));
                strcpy(array_item_string, array_item_string + 1);
                array_item_string[strlen(array_item_string) - 1] = '\0';
                if (strcmp(array_item_string, username) == 0) {
                    previously_retweeted_or_not = 1;
                    break;
                }
            }
            if (previously_retweeted_or_not == 1) {
                char error[100] = "{\"type\":\"Error\",\"message\":\"Perivously retweeted.\"}";
                int error_len = strlen(error);
                send(client_socket, error, error_len, 0);
            }
            if (previously_retweeted_or_not == 0) {
                cJSON *json_string = cJSON_CreateString(username);
                cJSON_AddItemToArray(retweeted_array, json_string);
                fclose(tweet_which_retweeted);

                FILE *tweet_which_retweeted_2;
                tweet_which_retweeted_2 = fopen(tweet_id_to_retweet, "w");
                fprintf(tweet_which_retweeted_2, "%s", cJSON_PrintUnformatted(tweet_which_retweeted_main_json));
                fclose(tweet_which_retweeted_2);
                char error[100] = "{\"type\":\"Successfull\",\"message\":\"Completed.\"}";
                int error_len = strlen(error);
                send(client_socket, error, error_len, 0);
            }
        }
        else{
            char error[100] = "{\"type\":\"Error\",\"message\":\"Out of range.\"}";
            int error_len = strlen(error);
            send(client_socket, error, error_len, 0);
        }
    }
}
//------------------------------------------------
void addFavorite (int client_socket, char* buffer)
{
    int buffer_len = strlen(buffer);
    buffer_len -= 1;
    char token[22];
    char favorite[500];
    char strings[2][500];
    int strings_counter = 0;
    for (int i = 0; i < buffer_len; ++i) {
        if (buffer[i] == ','){
            for (int j = i-1; j>=0; --j){
                if (buffer[j] == ' '){
                    for (int k = j+1; k<i; ++k){
                        strings[strings_counter][k-j-1] = buffer[k];
                    }
                    strings[strings_counter][i-j-1] = '\0';
                    strings_counter += 1;
                    break;
                }
            }
            int m;
            for (m = i+2; m<buffer_len; ++m){
                strings[strings_counter][m-i-2] = buffer[m];
            }
            strings[strings_counter][m-i-2] = '\0';
            strings_counter += 1;
        }
    }
    strcpy(token, strings[0]);
    strcpy(favorite, strings[1]);
    char username[30] = "*~";
    for (int l = 0; l<=100; ++l){
        if (strcmp(user_token[l], token) == 0){
            strcpy(username, user_token[l+1]);
            break;
        }
    }
    //favorite must have #
    int does_it_hava_hashtak_or_not;
    if (favorite[0] == '#'){
        does_it_hava_hashtak_or_not = 1;
    }
    else{
        does_it_hava_hashtak_or_not = 0;
    }
    //
    if (strcmp(username, "*~") == 0 && username[0] == '*' && username[1] == '~'){
        char token_error[100] = "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}";
        int token_error_len = strlen(token_error);
        send(client_socket, token_error, token_error_len, 0);
    }
    else{
        if (does_it_hava_hashtak_or_not == 0){
            char token_error[100] = "{\"type\":\"Error\",\"message\":\"Your message does not have #.\"}";
            int token_error_len = strlen(token_error);
            send(client_socket, token_error, token_error_len, 0);
        }
        else{
            FILE *username_file;
            username_file = fopen(username, "r");
            char username_file_stufs[10000];
            fgets(username_file_stufs, 10000, username_file);
            cJSON *username_main_json = cJSON_Parse(username_file_stufs);
            cJSON *favorite_array = cJSON_GetObjectItem(username_main_json, "favorites");
            cJSON *string = cJSON_CreateString(favorite);
            cJSON_AddItemToArray(favorite_array, string);
            fclose(username_file);

            FILE *username_file_2;
            username_file_2 = fopen(username, "w");
            fprintf(username_file_2, "%s", cJSON_PrintUnformatted(username_main_json));
            fclose(username_file_2);


            if (access("favoriteFile", F_OK) == 0) {
                FILE *favorite_file;
                favorite_file = fopen("favoriteFile", "r");
                char favorite_file_stufs[10000];
                fgets(favorite_file_stufs, 10000, favorite_file);
                cJSON *main_json = cJSON_Parse(favorite_file_stufs);
                cJSON *first_array = cJSON_GetObjectItem(main_json, "hashtak");
                cJSON *second_array = cJSON_GetObjectItem(main_json, "user");
                cJSON *first_string = cJSON_CreateString(favorite);
                cJSON *second_string = cJSON_CreateString(username);
                cJSON_AddItemToArray(first_array, first_string);
                cJSON_AddItemToArray(second_array, second_string);
                fclose(favorite_file);


                FILE *favorite_file_2;
                favorite_file_2 = fopen("favoriteFile", "w");
                fprintf(favorite_file_2, "%s", cJSON_PrintUnformatted(main_json));
                fclose(favorite_file_2);
            }
            else {
                FILE *making_favorite_file;
                making_favorite_file = fopen("favoriteFile", "w");
                cJSON *making_main_json, *hashtak, *user;
                making_main_json = cJSON_CreateObject();
                hashtak = cJSON_CreateArray();
                user = cJSON_CreateArray();
                cJSON_AddItemToObject(making_main_json, "hashtak", hashtak);
                cJSON_AddItemToObject(making_main_json, "user", user);
                fprintf(making_favorite_file, "%s", cJSON_PrintUnformatted(making_main_json));
                fclose(making_favorite_file);

                FILE *favorite_file;
                favorite_file = fopen("favoriteFile", "r");
                char favorite_file_stufs[10000];
                fgets(favorite_file_stufs, 10000, favorite_file);
                cJSON *main_json = cJSON_Parse(favorite_file_stufs);
                cJSON *first_array = cJSON_GetObjectItem(main_json, "hashtak");
                cJSON *second_array = cJSON_GetObjectItem(main_json, "user");
                cJSON *first_string = cJSON_CreateString(favorite);
                cJSON *second_string = cJSON_CreateString(username);
                cJSON_AddItemToArray(first_array, first_string);
                cJSON_AddItemToArray(second_array, second_string);
                fclose(favorite_file);


                FILE *favorite_file_2;
                favorite_file_2 = fopen("favoriteFile", "w");
                fprintf(favorite_file_2, "%s", cJSON_PrintUnformatted(main_json));
                fclose(favorite_file_2);
            }
            char token_error[100] = "{\"type\":\"Successful\",\"message\":\"completed.\"}";
            int token_error_len = strlen(token_error);
            send(client_socket, token_error, token_error_len, 0);
        }
    }
}
//------------------------------------------------
void showFavorite (int client_socket, char* buffer)
{
    int buffer_len = strlen(buffer);
    buffer_len -= 1;
    char token[22];
    char strings[1][22];
    int strings_counter = 0;
    int space_counter = 0;
    for (int i = 0; i < buffer_len; ++i) {
        if (buffer[i] == ' '){
            space_counter += 1;
            if (space_counter == 2) {
                for (int j = i + 1; j < buffer_len; ++j) {
                    strings[strings_counter][j - i - 1] = buffer[j];
                }
                strings[strings_counter][buffer_len - i - 1] = '\0';
                strings_counter += 1;
            }
        }
    }
    strcpy(token, strings[0]);
    char username[30] = "*~";
    for (int l = 0; l<=100; ++l){
        if (strcmp(user_token[l], token) == 0){
            strcpy(username, user_token[l+1]);
            break;
        }
    }
    if (strcmp(username, "*~") == 0 && username[0] == '*' && username[1] == '~'){
        char token_error[100] = "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}";
        int token_error_len = strlen(token_error);
        send(client_socket, token_error, token_error_len, 0);
    }
    else {
        char show_favorite_response[3000] = "[";
        FILE *show_favorite_file;
        show_favorite_file = fopen(username, "r");
        char show_favorite_file_stufs[10000];
        fgets(show_favorite_file_stufs, 10000, show_favorite_file);
        cJSON *show_favorite_main_json = cJSON_Parse(show_favorite_file_stufs);
        cJSON *array = cJSON_GetObjectItem(show_favorite_main_json, "favorites");
        for (int q = 0; q<cJSON_GetArraySize(array); ++q){
            cJSON *everytime = cJSON_GetArrayItem(array, q);
            strcat(show_favorite_response, cJSON_Print(everytime));
            strcat(show_favorite_response, ",");
        }
        show_favorite_response[strlen(show_favorite_response)-1] = '\0';
        strcat(show_favorite_response, "]");
        send(client_socket, show_favorite_response, strlen(show_favorite_response), 0);
    }
}
//------------------------------------------------
void deleteFavorite (int client_socket, char* buffer)
{
    int buffer_len = strlen(buffer);
    buffer_len -= 1;
    char token[22];
    char favorite_index[50];
    char strings[2][50];
    int strings_counter = 0;
    for (int i = 0; i < buffer_len; ++i) {
        if (buffer[i] == ','){
            for (int j = i-1; j>=0; --j){
                if (buffer[j] == ' '){
                    for (int k = j+1; k<i; ++k){
                        strings[strings_counter][k-j-1] = buffer[k];
                    }
                    strings[strings_counter][i-j-1] = '\0';
                    strings_counter += 1;
                    break;
                }
            }
            int m;
            for (m = i+2; m<buffer_len; ++m){
                strings[strings_counter][m-i-2] = buffer[m];
            }
            strings[strings_counter][m-i-2] = '\0';
            strings_counter += 1;
        }
    }
    strcpy(token, strings[0]);
    strcpy(favorite_index, strings[1]);
    char username[30] = "*~";
    for (int l = 0; l<=100; ++l){
        if (strcmp(user_token[l], token) == 0){
            strcpy(username, user_token[l+1]);
            break;
        }
    }
    if (strcmp(username, "*~") == 0 && username[0] == '*' && username[1] == '~'){
        char token_error[100] = "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}";
        int token_error_len = strlen(token_error);
        send(client_socket, token_error, token_error_len, 0);
    }
    else{
        int favorite_index_int = atoi(favorite_index);
        favorite_index_int -= 1;
        FILE *username_file;
        username_file = fopen(username, "r");
        char username_file_stufs[10000];
        fgets(username_file_stufs, 10000, username_file);
        cJSON *username_main_json = cJSON_Parse(username_file_stufs);
        cJSON *favorites_array = cJSON_GetObjectItem(username_main_json, "favorites");
        if (favorite_index_int >= cJSON_GetArraySize(favorites_array)){
            char token_error[100] = "{\"type\":\"Error\",\"message\":\"Entered number is out of range.\"}";
            int token_error_len = strlen(token_error);
            send(client_socket, token_error, token_error_len, 0);
        }
        else {
            cJSON_DeleteItemFromArray(favorites_array, favorite_index_int);
            fclose(username_file);

            FILE *username_file_2;
            username_file_2 = fopen(username, "w");
            fprintf(username_file_2, "%s", cJSON_PrintUnformatted(username_main_json));
            fclose(username_file_2);
            char token_error[100] = "{\"type\":\"Successful\",\"message\":\"Completed.\"}";
            int token_error_len = strlen(token_error);
            send(client_socket, token_error, token_error_len, 0);
        }
    }
}
//------------------------------------------------
void notification (int client_socket, char* buffer)
{
    int buffer_len = strlen(buffer);
    buffer_len -= 1;
    char token[22];
    char strings[1][22];
    int strings_counter = 0;
    for (int i = 0; i < buffer_len; ++i) {
        if (buffer[i] == ' '){
            for (int j = i+1; j<buffer_len; ++j){
                strings[strings_counter][j-i-1] = buffer[j];
            }
            strings[strings_counter][buffer_len-i-1] = '\0';
            strings_counter += 1;
        }
    }
    strcpy(token, strings[0]);
    char username[30] = "*~";
    for (int l = 0; l<=100; ++l){
        if (strcmp(user_token[l], token) == 0){
            strcpy(username, user_token[l+1]);
            break;
        }
    }
    if (strcmp(username, "*~") == 0 && username[0] == '*' && username[1] == '~'){
        char token_error[100] = "{\"type\":\"Error\",\"message\":\"Authentication failed!\"}";
        int token_error_len = strlen(token_error);
        send(client_socket, token_error, token_error_len, 0);
    }
    else{
        char notification_response[10000] = "{\"type\":\"List\",\"message\":[";

        FILE *main_user_notif;
        main_user_notif = fopen(username, "r");
        char main_user_notif_stuf[10000];
        fgets(main_user_notif_stuf, 10000, main_user_notif);
        cJSON *main_json = cJSON_Parse(main_user_notif_stuf);
        cJSON *favorite_array = cJSON_GetObjectItem(main_json, "favoriteTweets");
        for (int q = 0; q<cJSON_GetArraySize(favorite_array); ++q){
            cJSON *everytime_cjson = cJSON_GetArrayItem(favorite_array, q);
            char everytime_char[20];
            strcpy(everytime_char, cJSON_Print(everytime_cjson));

            if (access(everytime_char, F_OK) == 0) {
                FILE *favorite_tweets;
                favorite_tweets = fopen(everytime_char, "r");
                char favorite_tweets_stuf[10000];
                fgets(favorite_tweets_stuf, 10000, favorite_tweets);
                strcat(notification_response, favorite_tweets_stuf);
                strcat(notification_response, ",");
                fclose(favorite_tweets);
            }
        }
        fclose(main_user_notif);
        notification_response[strlen(notification_response)-1] = '\0';
        strcat(notification_response, "]}\0");
        send(client_socket, notification_response, strlen(notification_response), 0);



        for (int w = 0; w<cJSON_GetArraySize(favorite_array); ++w){
            cJSON_DeleteItemFromArray(favorite_array, 0);
        }

        FILE *main_user_notif_2;
        main_user_notif_2 = fopen(username, "w");
        fprintf(main_user_notif_2, "%s", cJSON_PrintUnformatted(main_json));
        fclose(main_user_notif_2);
    }
}
//------------------------------------------------