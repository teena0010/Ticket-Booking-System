#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

# define MAX 4

typedef struct{
    int ticket_id;
    char name[100];
    int age;
}Passenger;

Passenger queue[MAX];
int front = MAX-1, rear = MAX-1;
int ticket_number = 101;

int Full(){
    return (front == (rear+1)%MAX);
}

int Empty(){
    return (front == rear);
}

void Save(Passenger P){
    FILE *fp = fopen("booking.txt","a");
    if(fp!=NULL){
        fprintf(fp, "%d,%s,%d\n", P.ticket_id, P.name, P.age);
        fclose(fp);
    }
    else{
        printf("\033[1;31mError saving booking.\n\033[0m");
    }
}

void Enqueue(){
    if(Full()){
        printf("\033[1;31mSeats are full. No more tickets can be booked.\033[0m\n");;
    }
    else{
        Passenger P;
        P.ticket_id = ticket_number++;
        printf("Enter name: ");
        fgets(P.name, sizeof(P.name), stdin);
        P.name[strcspn(P.name, "\n")] = '\0';
        printf("Enter age: ");
        scanf("%d", &P.age);
        rear = (rear+1)%MAX;
        queue[rear] = P;
        Save(P);
        printf("\033[1;36mTicket booked successfully!\nYour Ticket ID is %d\n\033[0m",P.ticket_id);
    }
}   

Passenger Dequeue(){
    Passenger C = {0, "", 0}; 
    if (Empty()){
        printf("No tickets to cancel.\n");
        return C;
    }
    int id, found = 0;
    printf("Enter Ticket ID to cancel: ");
    scanf("%d", &id);
    int i = (front + 1) % MAX;
    int pos = -1;
    while (1) {
        if (queue[i].ticket_id == id) {
            found = 1;
            pos = i;
            break;
        }
        if (i == rear)
            break;
        i = (i + 1) % MAX;
    }
    if (!found) {
        printf("Ticket ID %d not found.\n", id);
        return C;
    }
    C = queue[pos]; 
    while (pos != rear) {
        int next = (pos + 1) % MAX;
        queue[pos] = queue[next];
        pos = next;
    }
    queue[rear] = (Passenger){0, "", 0};
    rear = (rear - 1 + MAX) % MAX;
    printf("\033[1;36m❌ Ticket cancelled: %d\033[0m\n", C.ticket_id);
    return C;
}

void Display(){
    if(Empty()){
        printf("No bookings yet.\n");
        return;
    }
    printf("\033[1;33mCurrent bookings: \033[0m\n");
    int i = (front+1)%MAX;
    while(1){
        printf("Ticket ID: %d, Name: %s, Age: %d\n",queue[i].ticket_id, queue[i].name, queue[i].age);
        if(i==rear)
        break;
        i = (i+1)%MAX;
    }
}

void SearchByID(){
    if(Empty()){
        printf("No bookings yet.");
    }
    else{
    int id, found = 0, i=front;
    printf("Enter Ticket ID: ");
    scanf("%d",&id);
        while (1) {
        if (queue[i].ticket_id == id) {
            printf("🔍 Found: Ticket ID: %d, Name: %s, Age: %d\n", queue[i].ticket_id, queue[i].name, queue[i].age);
            found = 1;
            break;
        }
        if (i == rear) 
        break;
        i = (i + 1) % MAX;
    }
    if (!found)
     printf("Ticket ID %d not found.\n", id);
    }
}

void SearchByName(){
    if(Empty()){
        printf("No bookings yet.");
    }
    else{
        char name[100];
        int found = 0 , i = front;
        printf("Enter name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';
        while (1) {
        if (strcasecmp(queue[i].name, name) == 0) {
            printf("🔍 Found: Ticket ID: %d, Name: %s, Age: %d\n", queue[i].ticket_id, queue[i].name, queue[i].age);
            found = 1;
        }
        if (i == rear) 
        break;
        i = (i + 1) % MAX;
    }
    if (!found) 
    printf("No booking found for name: %s\n", name);
    }
}

void Edit(){
    if(Empty()){
        printf("No bookings yet.");
    }
    else{
        int id, i=front;
        printf("Enter the ticket id : ");
        scanf("%d",&id);
        while (1) {
        if (queue[i].ticket_id == id) {
            printf("✏️ Editing Ticket ID %d\n", id);
            printf("Current Name: %s, Age: %d\n", queue[i].name, queue[i].age);
            printf("Enter new name: ");
            getchar();
            fgets(queue[i].name, sizeof(queue[i].name), stdin);
            queue[i].name[strcspn(queue[i].name, "\n")] = '\0';
            printf("Enter new age: ");
            scanf("%d", &queue[i].age);
            printf("✅ Details updated successfully.\n");
            return;
        }
        if (i == rear)
         break;
        i = (i + 1) % MAX;
    }
    printf("Ticket ID %d not found.\n", id);
    }
}

void flushInput() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void waitandclear() {
    flushInput();
    printf("\nPress Enter to continue...");
    while (getchar() != '\n'); // Wait for Enter
    system("cls");  // Use "clear" for Linux/macOS
}

void menu() {
    printf(
                                                                                        
"\033[1;35m _____ _     _       _      _____         _   _            _____         _             \033[0m\n"
"\033[1;35m|_   _|_|___| |_ ___| |_   | __  |___ ___| |_|_|___ ___   |   __|_ _ ___| |_ ___ _____ \033[0m\n"
"\033[1;35m  | | | |  _| '_| -_|  _|  | __ -| . | . | '_| |   | . |  |__   | | |_ -|  _| -_|     |\033[0m\n"
"\033[1;35m  |_| |_|___|_,_|___|_|    |_____|___|___|_,_|_|_|_|_  |  |_____|_  |___|_| |___|_|_|_|\033[0m\n"
"\033[1;35m                                                   |___|        |___|                  \033[0m\n"
                                                                                       
                                                                                       
                                                                                       
                                                                                       
                                                                                       
                                                                                       
    );
    printf("\033[1;34m1. Book Ticket\033[0m\n");
    printf("\033[1;34m2. Cancel Ticket\033[0,m\n");
    printf("\033[1;34m3. View Bookings\033[0m\n");
    printf("\033[1;34m4. Search by Ticket ID\033[0m\n");
    printf("\033[1;34m5. Search by Name\033[0m\n");
    printf("\033[1;34m6. Edit Customer Details\033[0m\n");
    printf("\033[1;34m7. Exit\033[0m\n");
    printf("\033[1;33mEnter your choice: \033[0m");
}

int main(){
    int choice;
while (1) {
    menu();            // Shows the menu
    scanf("%d", &choice);
    getchar();         // Clear newline

        if (choice == 1) {
            Enqueue();
            waitandclear();
        }
         else if (choice == 2) {
            Dequeue();
            waitandclear();
        } 
        else if (choice == 3) {
            Display();
            waitandclear();
        } 
        else if (choice == 4) {
            SearchByID();
            waitandclear();
        } 
        else if (choice == 5) {
            SearchByName();
            waitandclear();
        } 
        else if (choice == 6) {
            Edit();
            waitandclear();
        } 
        else if (choice == 7) {
            printf("\033[1;32m👋 Exiting system. Goodbye!\033[0m\n");
            break;
        } 
        else {
            printf("\033[1;31mInvalid choice. Try again.\033[0m\n");
        }
    }
    return 0;
}
