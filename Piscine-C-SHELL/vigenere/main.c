#include "vigenere.h"

int main(void)
{
    char msg[] = "The temperature here is equal to your grade!";
    char key[] = "Penguin";
    char res[46];
    cipher(key, msg, res);
    printf("%s\n", res);
    decipher(key, res, msg);
    printf("%s\n", msg);
}
