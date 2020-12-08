#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* morse[55] = {
    ".-",     "-...",   "-.-.",   "-..",     ".",      "..-.",     "--.",
    "....",   "..",     ".---",   "-.-",     ".-..",   "--",       "-.",
    "---",    ".--.",   "--.-",   ".-.",     "...",    "-",        "..-",
    "...-",   ".--",    "-..-",   "-.--",    "--..",   "-----",    ".----",
    "..---",  "...--",  "....-",  ".....",   "-....",  "--...",    "---..",
    "----.",  ".-.-.-", "--..--", "..--..",  ".----.", "-.-.--",   "-..-.",
    "-.--.",  "-.--.-", ".-...",  "---...",  "-.-.-.", "-...-",    ".-.-.",
    "-....-", "..--.-", ".-..-.", "...-..-", ".--.-.", "...---..."};
const char* ascii[55] = {
    "A", "B", "C", "D", "E", "F", "G", "H", "I", "J",  "K", "L", "M",  "N",
    "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X",  "Y", "Z", "0",  "1",
    "2", "3", "4", "5", "6", "7", "8", "9", ".", ",",  "?", "'", "!",  "/",
    "(", ")", "&", ":", ";", "=", "+", "-", "_", "\"", "$", "@", "SOS"};

char* decode_morse(const char* morse_code)
{
    char** massage = (char**)malloc(sizeof(char*) * 100);
    int i = 0;
    int j = 0;
    const char break_sign[2] = " ";
    char* inner_morse = (char*)morse_code;
    char* token = strtok(inner_morse, break_sign);

    while (token)
    {
        for (i = 0; i < 55; ++i)
        {
            if (0 == strcmp(token, morse[i]))
            {
                massage[j] = (char*)ascii[i];
                ++j;
                break;
            }

            token = strtok(NULL, break_sign);
        }
    }
    massage[i] = '\0';

    return *massage;
}

char* decode_morse(const char* morse_code);

int main()
{
    printf("%s\n",
           decode_morse(".... . -.--   .--- ..- -.. .")); /* "HEY JUDE" */

    return (0);
}
