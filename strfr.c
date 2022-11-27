#include <stdlib.h>
#include <string.h>
char *strfr(char *a, char *f, char *r) {
  char *s = a;
  int sizeS = strlen(s);
  int sizeF = strlen(f);
  int sizeR = strlen(r);
  int sizeM = sizeS + (sizeS * sizeR / sizeF) + 1;
  char *m = malloc(sizeof(char) * sizeM);
  char *p = NULL;
  int j = 0;
  int k = 0;
  char *i = s;
  char *rr = r;
  for (; i < s + sizeS;) {
    if ((p = strstr(s, f)) == NULL) {
      p = a + sizeS;
    }
    while (i < p) {
      *(m + j) = *i;
      j++;
      i++;
      s++;
    }
    if (p != a + sizeS) {
      while (k < sizeR) {
        *(m + j) = *rr;
        j++;
        rr++;
        k++;
      }
      rr = r;
      k = 0;
      i += sizeF;
      s += sizeF;
    } else
      break;
  }
  *(m + j) = '\0';
  return m;
}

void strrm(char *data, char *removerKey) {
  char *startOfKey_p = data;
  while ((startOfKey_p = strstr(startOfKey_p, removerKey))) {
    char *endOfKey_p = startOfKey_p + strlen(removerKey);
    memmove(startOfKey_p, endOfKey_p, strlen(endOfKey_p) + 1);
  }
}

// static void testStrrm()
//{
//     char string[] = "I am 'who|is' 'who|was' shadman who are you?";
//     puts(string);
//     puts("removing 'am'");
//     strrm(string,"am");
//     puts(string);
//     puts("removing 'who'");
//     strrm(string,"who");
//     puts(string);
//     puts("removing 'what the'");
//     strrm(string,"what the");
//     puts(string);
//     puts("removing 'a'");
//     strrm(string,"a");
//     puts(string);
// }
// int main() {testStrrm();return 0;}
