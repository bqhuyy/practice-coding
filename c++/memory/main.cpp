#include <iostream>
#include <stdio.h>

using namespace std;

struct data {
    int a;
    float b;
    char c;
};

// ref: https://riptutorial.com/gcc/example/31724/attribute-packed
struct __attribute__((__packed__)) packed_data {
    int a;
    float b;
    char c;
};
  
// Alignment requirements
// (typical 32 bit machine)
  
// char         1 byte
// short int    2 bytes
// int          4 bytes
// double       8 bytes
  
// structure A
typedef struct structa_tag
{
   char        c;
   short int   s;
} structa_t;
  
// structure B
typedef struct structb_tag
{
   short int   s;
   char        c;
   int         i;
} structb_t;
  
// structure C
typedef struct structc_tag
{
   char        c;
   double      d;
   int         s;
} structc_t;
  
// structure D
typedef struct structd_tag
{
   double      d;
   int         s;
   char        c;
} structd_t;

int main(int argc, char** argv) {
    cout << "sizeof 'data' = " << sizeof(struct data) << endl;
    cout << "sizeof 'data' = " << sizeof(struct packed_data) << endl;

    printf("sizeof(structa_t) = %lu\n", sizeof(structa_t));
    printf("sizeof(structb_t) = %lu\n", sizeof(structb_t));
    printf("sizeof(structc_t) = %lu\n", sizeof(structc_t));
    printf("sizeof(structd_t) = %lu\n", sizeof(structd_t));

    return 0;
}