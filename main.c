#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void filecreat(double X1, int N, double delta, double result, char group_name [6], char student_name [20]);
void binop(double X1, double X2, int N, double delta, double result, char group_name [6], char student_name [20]);

int main()
{
    double X1, X2, delta, result;
    int N;
    char group_name[6], student_name[20];
    FILE * f_input, * f_output, * f_outbin, * f_inbin;
    f_input = fopen("Text.txt", "r");
    fscanf(f_input, "%lf %lf %d %lf %s ", &X1, &X2, &N, &delta, &group_name);
    fgets(&student_name, 20, f_input);
    fclose(f_input);
    filecreat(X1, N, delta, result, group_name, student_name);
    binop(X1, X2, N, delta, result, group_name, student_name);
}

void filecreat(double X1, int N, double delta, double result, char group_name [6], char student_name [20])
{
    FILE * f_output = fopen ("fintext.txt", "w");
    FILE* f_outbin = fopen("binar.bin", "w+b");
    if (f_output==NULL||f_outbin==NULL)
    {
        printf("\n ERROR. CANNOT OPEN THE FILE.");
        exit(1);
    }
    fprintf(f_output, "\n***************************************");
    fprintf(f_output, "\n*     N     *     F      *     F(X)   *");
    fprintf(f_output, "\n***************************************");
    for(int i=1; i<=N; ++i)
    {
        result=-4*pow(X1,3)-3*pow(X1,2)+2*pow(X1,2)-5*X1-25;;
        fwrite( &i, sizeof(int), 1, f_outbin );
        fwrite( &X1, sizeof(double), 1, f_outbin );
        fwrite( &result, sizeof(double), 1, f_outbin );
        fprintf(f_output, "\n|%11.0d|%12.2f|%12.2f|\n",i,X1,result);
        fprintf(f_output,"\n+-----------+------------+------------+");
        X1+=delta;
    }
    fclose(f_outbin);
    fprintf(f_output, "\n\n %s \n %s", group_name, student_name );
    fclose(f_output);
}

void binop(double X1, double X2, int N, double delta, double result, char group_name [6], char student_name [20])
{
    FILE * f_inbin = fopen( "binar.bin", "rb" );
    if (f_inbin==NULL)
    {
        printf("\nCAN'T OPEN THE FILE");
        exit(1);
    }
    else
    {
        printf("\nReceived data:");
        printf("\n X1: %.3lf\n X2 = %.3lf\n N = %d\n Delta = %.3lf\n Group = %s\n Name = %s\n\n", X1, X2, N, delta, group_name, student_name);
        printf("\n***************************************");
        printf("\n*     N     *     F      *     F(X)   *");
        printf("\n***************************************");
        for (int i=1; i<=N; i++)
        {
            fread( &i, sizeof(int), 1, f_inbin );
            fread( &X1, sizeof(double), 1, f_inbin );
            fread( &result, sizeof(double), 1, f_inbin );
            printf ("\n|%11.0d|%12.2f|%12.2f|\n",i,X1,result);
            printf("\n+-----------+------------+------------+");
        }
        fclose(f_inbin);
    }
}
