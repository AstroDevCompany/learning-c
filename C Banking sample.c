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

int login(char *username, char *password, size_t userlen, size_t passlen)
{
  CLEAR;
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

      if (strcmp(username, "test") != 0)
      {
        printf("Unknown username.\n");
        system("pause");
        continue;
      }
      else
      {
        CLEAR;

        printf("Enter your password: ");
        if (fgets(password, (int)passlen, stdin) == NULL)
          return 0;
        password[strlen(password) - 1] = '\0';

        if (strcmp(password, "test123") != 0)
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

int main()
{
  char username[64] = {0};
  char password[64] = {0};
  int loginRes = login(username, password, sizeof(username), sizeof(password));
  if (loginRes == 1)
  {
    authOk(username);
  }
  else
  {
    exit(1);
  }
  return 0;
}