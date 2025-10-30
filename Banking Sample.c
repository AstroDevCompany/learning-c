#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#ifdef _WIN32
#define CLEAR system("cls");
#else
#define CLEAR system("clear");
#endif

char askChar(char *question)
{
  printf("%s\n", question);
  char response = _getch();
  return response;
}

void createAccount(char *newUsername, char *newPassword)
{
  printf("No existing account found. Creating a new account.\n");
  char username[64] = {0};
  char password[64] = {0};
  printf("Enter a new username: ");
  if (fgets(username, sizeof(username), stdin) == NULL)
    createAccount(username, password);
  username[strcspn(username, "\n")] = 0; // Remove newline character
  printf("Enter a new password: ");
  if (fgets(password, sizeof(password), stdin) == NULL)
    createAccount(username, password);
  password[strcspn(password, "\n")] = 0; // Remove newline character

  FILE *fp = fopen("creds.txt", "w");
  if (fp == NULL)
  {
    printf("Error creating account file.\n");
    exit(1);
  }
  fprintf(fp, "username: %s\n", username);
  fprintf(fp, "password: %s\n", password);
  fclose(fp);

  strcpy(newUsername, username);
  strcpy(newPassword, password);
}

void readCredentials(char *username, char *password)
{
  printf("Reading credentials function called.\n");
  FILE *fp = fopen("creds.txt", "r");
  if (fp == NULL)
  {
    char newUsername[64] = {0};
    char newPassword[64] = {0};
    createAccount(newUsername, newPassword);
    strcpy(username, "test");
    strcpy(password, "test");
    return;
  }

  char buffer[256];
  printf("Reading credentials from creds.txt\n");

  while (fgets(buffer, sizeof(buffer), fp) != NULL)
  {
    // Each line
    if (strstr(buffer, "username:") != NULL)
    {
      char *usernameCheck = strchr(buffer, ':');
      if (!usernameCheck)
      {
        strcpy(username, "test");
        printf("Username not found.\n");
        break;
      }
      usernameCheck++; // Move past the colon
      if (*usernameCheck == ' ')
        usernameCheck++; // Skip space if present
      strcpy(username, usernameCheck);
    }
    else if (strstr(buffer, "password:") != NULL)
    {
      char *passwordCheck = strchr(buffer, ':');
      if (!passwordCheck)
      {
        strcpy(password, "test");
        printf("Password not found.\n");
        break;
      }
      passwordCheck++; // Move past the colon
      if (*passwordCheck == ' ')
        passwordCheck++; // Skip space if present
      strcpy(password, passwordCheck);
    }
  }
  fclose(fp);
}

int login(char *username, char *password, size_t userlen, size_t passlen)
{
  CLEAR;
  char correctUsername[64] = {0};
  char correctpassword[64] = {0};
  readCredentials(correctUsername, correctpassword);

  if (correctUsername[strlen(correctUsername) - 1] == '\n')
    correctUsername[strlen(correctUsername) - 1] = '\0';
  if (correctpassword[strlen(correctpassword) - 1] == '\n')
    correctpassword[strlen(correctpassword) - 1] = '\0';

  printf("Correct Username: %s\n", correctUsername);
  printf("Correct Password: %s\n", correctpassword);

  char response = askChar("Do you have an account? [y/n]");
  if (response == 'y' || response == 'Y')
  {
    while (1)
    {
      CLEAR;

      printf("Enter your username: ");
      if (fgets(username, (int)userlen, stdin) == NULL)
        return 0;
      username[strlen(username) - 1] = '\0';

      if (strcmp(username, correctUsername) != 0)
      {
        printf("Unknown username.\n");
        system("pause");
        continue;
      }
      else
      {
        break;
      }
    }

    while (1)
    {
      CLEAR;

      printf("Enter your password: ");
      if (fgets(password, (int)passlen, stdin) == NULL)
        return 0;
      password[strlen(password) - 1] = '\0';

      if (strcmp(password, correctpassword) != 0)
      {
        printf("Wrong password.\n");
        system("pause");
        continue;
      }
      else
      {
        return 1;
      }
    }
  }
  else if (response == 'n' || response == 'N')
  {
    CLEAR;
    char response = askChar("Do you want to create an account? [y/n]");
    if (response == 'y' || response == 'Y')
    {
    }
    else if (response == 'n' || response == 'N')
    {
    }
    else
    {
      login(username, password, userlen, passlen);
    }
  }
  else
  {
    login(username, password, userlen, passlen);
  }
}

void authOk(char *username)
{
  CLEAR;
  printf("Welcome back, %s.\n", username);
  system("pause");
}

int getBalance()
{
  FILE *fp = fopen("balance.txt", "rw");
  if (fp == NULL)
  {
    fprintf(fp, "0");
    fclose(fp);
    return 0;
  }
  int balance = 0;
  fscanf(fp, "%d", &balance);
  fclose(fp);
  return balance;
}

void withdraw(int *balance)
{
  int withdrawAmount = 0;
  printf("How much would you like to withdraw?\n");
  printf("$");
  scanf("%d", withdrawAmount);
  if (withdrawAmount > *balance)
  {
    printf("Insufficient funds.\n");
    return;
  }
  *balance -= withdrawAmount;
  printf("Withdrew $%d. New balance is $%d.\n", withdrawAmount, *balance);
}

void mainMenu(char *username)
{
  CLEAR;
  int balance = getBalance();
  printf("=== Banking Application ===\n");
  printf("--- User Info ---\n");
  printf("Username: %s\n", username);
  printf("--- Options ---\n");
  printf("1. View Balance\n");
  printf("2. Withdraw Funds\n");
  printf("3. Exit\n");
  printf("4. Change username\n");
  printf("5. Change password\n");

  char option = askChar("Select an option:");
  if (option != NULL)
  {
    CLEAR;
    switch (option)
    {
    case '1':
      printf("Your balance is $%d.\n", balance);
      system("pause");
      break;

    case '2':
      withdraw(&balance);
      system("pause");
      break;

    case '3':
      printf("Your balance is $1000.\n");
      system("pause");
      break;

    case '4':
      exit(1);
      break;

    case '5':
      printf("Your balance is $1000.\n");
      system("pause");
      break;

    case '6':
      printf("Your balance is $1000.\n");
      system("pause");
      break;

    default:
      printf("Invalid option.\n");
      mainMenu(username);
    }
  }
  mainMenu(username);
}

int main()
{
  char username[64] = {0};
  char password[64] = {0};

  int loginRes = login(username, password, sizeof(username), sizeof(password));
  if (loginRes == 1)
  {
    authOk(username);
    mainMenu(username);
  }
  else
  {
    exit(1);
  }
  return 0;
}
