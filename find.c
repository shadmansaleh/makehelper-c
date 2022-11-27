#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *findResult = NULL;
static char *findResultCurrentPos = NULL;
static int findResultSize = 0;

static void findResultEnlarge() {
  const int baseSize = 512;

  if (findResultSize == 0)
    findResultSize = baseSize;
  else {
    if (findResultSize < 2048)
      findResultSize += findResultSize * 0.5;
    else
      findResultSize += 1024;
  }
  char *newAllocatedMemory = NULL;
  if (!(newAllocatedMemory = (char *)malloc(findResultSize * sizeof(char)))) {
    perror("Error : Not enough memory");
    exit(1);
  }

  if (findResult) {
    strncpy(newAllocatedMemory, findResult,
            (findResultCurrentPos - findResult));
    findResultCurrentPos =
        newAllocatedMemory + (findResultCurrentPos - findResult);
    free(findResult);
  } else {
    memset(newAllocatedMemory, 0, baseSize);
    findResultCurrentPos = newAllocatedMemory;
  }

  findResult = newAllocatedMemory;
}

static void appendResult(const char *str) {
  if (!str)
    return;

  int len = strlen(str);
  while ((findResultCurrentPos - findResult + len) >= findResultSize)
    findResultEnlarge();
  strcat(findResultCurrentPos, str);
  strcat(findResultCurrentPos + len, "\n");
  findResultCurrentPos += len + 1;
}

static void cleanFindResult() {
  free(findResult);
  findResult = NULL;
  findResultCurrentPos = NULL;
  findResultSize = 0;
}

#include <dirent.h>

#define TRUE 1
#define FALSE 0
void checkDir(const char *path, const int showHidden) {
  DIR *d;
  struct dirent *dir;
  d = opendir(path);
  if (d != NULL) {
    while ((dir = readdir(d)) != NULL) {
      if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, ".."))
        continue;
      else if (dir->d_type == DT_DIR) {
        if (!showHidden && *(dir->d_name) == '.')
          continue;
        char myPath[strlen(path) + strlen(dir->d_name) + 10];
        strcpy(myPath, path);
        strcat(myPath, "/");
        strcat(myPath, dir->d_name);
        checkDir(myPath, showHidden);
      } else if (dir->d_type == DT_REG) {
        if (!showHidden && *(dir->d_name) == '.')
          continue;
        char myPath[strlen(path) + strlen(dir->d_name) + 10];
        strcpy(myPath, path);
        strcat(myPath, "/");
        strcat(myPath, dir->d_name);
        appendResult(myPath);
      }
    }
    closedir(d);
  }
}

char *getWord(char *str, char deleminator) {
  static char *in;
  if (str)
    in = str;
  char *pos_P = in;
  if (*pos_P == 0)
    return NULL;
  int size = 0;
  while (*pos_P != deleminator && *pos_P != 0) {
    ++pos_P;
    ++size;
  }
  char *out = (char *)malloc((size + 1) * sizeof(char));
  strncpy(out, in, size);
  *(out + size) = '\0';
  in = pos_P + 1;
  return out;
}

char *getFiles(const char *path, const char *patern, int showHidden) {
  checkDir(path, showHidden);
  char *out;
  int paternLength = strlen(patern);
  if (strcmp(patern, "") && patern != NULL) {
    char *file = getWord(findResult, '\n');
    if (!file)
      return NULL;
    out = (char *)malloc(findResultSize * sizeof(char));
    char *outPos_P = out;
    do {
      char *startOfExtention = strstr(file, patern);
      char *endOfExtention = strchr(file, 0);
      if (startOfExtention && endOfExtention &&
          (endOfExtention - startOfExtention) == paternLength) {
        int len = strlen(file) - 2;
        strncpy(outPos_P, file + 2, len);
        strncpy(outPos_P + len, " ", 1);
        outPos_P += len + 1;
      }
      free(file);
    } while ((file = getWord(NULL, '\n')));
    *outPos_P = 0;
  } else
    out = strdup(findResult);
  cleanFindResult();
  return out;
}
// test checkDir
/*static void testCheckDir(){
    char *ls=getFiles(".",".c",0);
    printf("%s\n",ls);
    free(ls);
}*/
// int main(){testCheckDir();return 0;}
