#include <stdio.h>
#include <string.h>
#include "infix.h"
#include "error.h"
#include "rpn.h"


#define BUFFER_STRING 160

int main(int argc, char **argv) {
    FILE *infile, *outfile;
    char inputString[BUFFER_STRING];
    char rpnString[BUFFER_STRING];
    int status;
    double value;

    if(argc != 3)
    {
        printf("usage: ./%s <infile.txt> <outfile.txt>\n", argv[0]);
        return -1;
    }

     infile = fopen(argv[1], "r");
    //infile = fopen("PS5-infix.txt", "r");

    if(infile == NULL)
    {
        printf("Could not open %s for readng\n",argv[1]);
        return -1;
    }

    outfile = fopen(argv[2], "w");
    //outfile = fopen("output.txt", "w");

    if(outfile == NULL)
    {
        printf("Could not open %s for writing\n",argv[2]);
        return -1;
    }


    while(fgets(inputString, BUFFER_STRING-1, infile))
    {
        infix_to_rpn(inputString, rpnString, &status);
        if(status != SUCCESS)
        {
            printf("%s\n", errorMessages[status]);
        }
        //  fprintf(outfile,"%s\n",rpnString);
        else {
            value = evaluate(rpnString, &status);
        }
        if(status != SUCCESS)
        {
            printf("%s\n", errorMessages[status]);
        }
        fprintf(outfile,"%f\n",value);

    }


    fclose(infile);
    fclose(outfile);

    return 0;

}
