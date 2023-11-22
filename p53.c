#include <stdio.h>
#include <pthread.h>
#include <ctype.h>
int vowelCount = 0;
int consonantCount = 0;
void *countVowels(void *arg) {
char *text = (char *)arg;
for (int i = 0; text[i] != '\0'; i++) {
char c = tolower(text[i]);
if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
vowelCount++;
}}
pthread_exit(NULL);
}
void *countConsonants(void *arg) {
char *text = (char *)arg;
for (int i = 0; text[i] != '\0'; i++) {
char c = tolower(text[i]);
if (isalpha(c) && c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u') {
consonantCount++;
}
}
pthread_exit(NULL);
}
int main() {
pthread_t vowelThread, consonantThread;
char text[] = "THORAT AMEY ARUN";
pthread_create(&vowelThread, NULL, countVowels, (void *)text);
pthread_create(&consonantThread, NULL, countConsonants, (void *)text);
pthread_join(vowelThread, NULL);
pthread_join(consonantThread, NULL);
printf("Vowel Count: %d\n", vowelCount);
printf("Consonant Count: %d\n", consonantCount);
return 0;
}
