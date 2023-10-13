#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure to act as a tuple
struct data{
        float sales;
        char month[50];
    };

//average function 
double avg(int begin, int end, struct data data_info[]){
    double sum;
    sum = 0.0;
    for (int i = begin; i < end; i++){
        sum += data_info[i].sales;
    }
    double avg;
    avg = sum / (end - begin);
    return avg;
}

//minimum function 
struct data data_min(struct data data_info[], int size){
    struct data min = data_info[0];
    for (int i=0; i< size; i++){
        if (data_info[i].sales < min.sales){
            min = data_info[i];
        }
    }
    return min;
}

//maximum function 
struct data data_max(struct data data_info[], int size){
    struct data max = data_info[0];
    for (int i = 0; i < size; i++){
        if (data_info[i].sales > max.sales){
            max = data_info[i];
        }
    }
    return max;
}

int compare(const void *a, const void *b){
    double valA = ((struct data *)a)->sales;
    double valB = ((struct data *)b)->sales;
    
    if (valA < valB) return 1;  
    if (valA > valB) return -1;
    return 0;
}

void sortSales(struct data *data_info, size_t n) {
    qsort(data_info, n, sizeof(struct data), compare);
}


int main() {
    char string[50]; 
    char months[12][20] = {"January", "Februrary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    char c;
    struct data data_info[12];
    char* end;
    int count=0;

    FILE* file;
    file = fopen("testfile.txt", "r");
    if (file == NULL) {
        printf("Error opening the file");
        return 1;
    }

    int line = 0;
    while (!feof(file)) {
        
        char ch = fgetc(file);
        if (ch != EOF){
            string[line] = ch;
            line++;
        }

        
        if (ch == '\n' || ch == EOF){
            data_info[count].sales = strtod(string, &end);

            for (int i = 0; i < 20; i++){
                data_info[count].month[i] = months[count][i];
            }
            strcpy(string,"");
            count++;
            line = 0;
            continue;
        }
    }
    fclose(file);

    //Monthly Report//
    printf("Monthly sales report for 2022:\n\n");
    printf("Month\t\t Sales \n\n");
    for (int i=0; i<12; i++){
        printf("%-10s \t $%-10.2f\n", months[i], data_info[i].sales);
    }


    //calculate
    double average = avg(0, 12, data_info);

    struct data minimum;
    minimum = data_min(data_info, 12);

    struct data maximum;
    maximum = data_max(data_info, 12);

    //sales summary
    printf("\n\nSales summary: \n");
    printf("Minimum sales:   %-8.2f (%s)\n",minimum.sales, minimum.month);
    printf("Maximum sales:   %-8.2f (%s)\n", maximum.sales, maximum.month);
    printf("Average sales:   %.2f\n", average);

    //six-month moving average report
    printf("\nSix-Month Moving Average Report: \n");
    char startmonth[20];
    char endmonth[20];
    for (int i=0; i < 7; i++){
        strcpy(startmonth, months[i]);
        strcpy(endmonth, months[i+5]);
        printf("%-10s \t - \t %-10s \t\t $%-10.2f\n", startmonth, endmonth, avg(i, i+6, data_info));
    }

    //sales report (highest to lowest)
    printf("\nSales Report (Highest to Lowest):\n\n");
    printf("Month\t\tSales\n\n");
    sortSales(data_info, 12);
    for (int i = 0; i < 12; i++)
    {
        printf("%-10s \t $ %-10.2f", data_info[i].month, data_info[i].sales);
        printf("\n");
    }



    return 0;
}

