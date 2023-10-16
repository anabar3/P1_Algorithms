/*
STUDENT 1: Javier Carballal Morgade       LOGIN 1: javier.carballal.morgade@udc.es
STUDENT 2: Diego Martínez Novoa           LOGIN 2: diego.martinez6@udc.es
STUDENT 3: Ana Barrera Novas              LOGIN 3: ana.barrera@udc.es
GROUP: 6.1
DATE: 30/09/23
*/

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

int maxSubSum1(int v[], int n) {
    int i, j;
    long thisSum, maxSum = 0;
    for (i = 0; i < n; i++) {
        thisSum = 0;
        for (j = i; j < n; j++) {
            thisSum += v[j];
            if (thisSum > maxSum) {
                maxSum = thisSum;
            }
        }
    }
    return maxSum;
}

int maxSubSum2(int v[], int n) {
    int j;
    long thisSum = 0, maxSum =0;
    for (j = 0; j < n;j++){
        thisSum=thisSum+v[j];
        if (thisSum>maxSum) maxSum=thisSum;
        else if (thisSum<0) thisSum=0;
    }
    return maxSum;
}

void print_array(int v[], int n){
    int i;
    for (i=0; i<n; i++){
        printf("%3d ", v[i]);
    }
}

void init_seed() {
    srand(time(NULL));
/* set the seed of a new sequence of pseudo-random integers */
}

void random_init(int v [], int n) {
    int i, m=2*n+1;
    for (i=0; i < n; i++)
    v[i] = (rand() % m) - n;
    /* generate pseudo-random numbers between -n and +n */
}

double microseconds() { /* obtains the system time in microseconds */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
    return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void print_answer(int ans, int sol){
    if(ans == sol){
        printf("\033[32m%3d\033[0m", ans); //green
    }
    else{
        printf("\033[31m%3d\033[0m", ans); //red
    }
}

void test1() {
    int test_sequences[6][5] = {
        {-9, 2, -5, -4, 6},
        {4, 0, 9, 2, 5},
        {-2, -1, -9, -7, -1},
        {9, -2, 1, -7, -8},
        {15, -2, -5, -4, 16},
        {7, -5, 6, 7, -7}
    };
    int test_solutions[6] = {6, 20, 0, 9, 20, 15};
    int a, b;

    printf("test 1 (test cases)\n");
    printf("%26s%16s%16s%16s\n", "", "maxSubSum1", "maxSubSum2", "Expected");
    for (int i=0; i<6; i++) {

        print_array(test_sequences[i], 5);
        a = maxSubSum1(test_sequences[i], 5);
        b = maxSubSum2(test_sequences[i], 5);

        printf("%15s", "");
        print_answer(a, test_solutions[i]);
        printf("%15s", "");
        print_answer(b, test_solutions[i]);
        printf("%15d\n", test_solutions[i]);
    }
}

void test2() {
    int a, b;
    int v[9];
    printf("\n\ntest 2 (random numbers)\n");
    printf("%38s%15s%15s\n", "", "maxSubSum1", "maxSubSum2");
    for (int i=0; i<10; i++) {
        random_init(v, 9);
        print_array(v, 9);
        a = maxSubSum1(v, 9);
        b = maxSubSum2(v, 9);
        printf("%15d%15d\n", a, b);
    }
}

void test3(int rep) {
    int sizes[7] = {500, 1000, 2000, 4000, 8000, 16000, 32000};
    printf("\n\ntest 3 (execution times in microseconds)\nRepetitions: %d\n", rep);

    double totalTime;
    double testTimeA;
    double testTimeB;
    int a, i, j, k;

    for(a = 0; a < 2; a++){
        double meandivdiff = 0;
        
        printf("\nALGORITHM %d:\n\n", a+1);
        if(a == 0){
            printf("%6s%16s%20s%15s%15s\n", "Size", "t(n)", "t(n)/n^1.8", "t(n)/n^2", "t(n)/n^2.2");
        }else{
            printf("%6s%16s%20s%15s%15s\n", "Size", "t(n)", "t(n)/n^0.8", "t(n)/n", "t(n)/n^1.2");
        }
        
        for (i=0; i<7; i++) { //iterate through the different sizes
            
            int testArray[sizes[i]];
            totalTime = 0;

            for(j = 0; j < rep; j++){ //make the given repetitions
                random_init(testArray, sizes[i]);
                
                if(a == 0){ //take first measure
                    testTimeA = microseconds(); //start measure
                    maxSubSum1(testArray, sizes[i]);
                    testTimeB = microseconds(); //stop measure
                }else{
                    testTimeA = microseconds(); //start measure
                    maxSubSum2(testArray, sizes[i]);
                    testTimeB = microseconds(); //stop measure
                }
                
                if(testTimeB - testTimeA >= 500){ //big times
                    totalTime += testTimeB - testTimeA; //sumar al totalTime1
                }
                else{ //small times
                    if(a == 0){
                        testTimeA = microseconds(); //start measure
                        for(k = 0; k < 1000; k++){ //repeat 1000 times
                            maxSubSum1(testArray, sizes[i]);
                        }
                        testTimeB = microseconds(); //stop measure
                    }else{
                        testTimeA = microseconds(); //start measure
                        for(k = 0; k < 1000; k++){ //repeat 1000 times
                            maxSubSum2(testArray, sizes[i]);
                        }
                        testTimeB = microseconds(); //stop measure
                    }
                    totalTime += (testTimeB - testTimeA) / 1000;
                }
            }
            totalTime = totalTime/rep;
            if(a == 0){
                printf("  %-5d%15.3lf%20.6lf%15.6lf%15.6lf\n", sizes[i], totalTime, totalTime/(pow(sizes[i],1.8)), totalTime/(pow(sizes[i],2)), totalTime/(pow(sizes[i],2.2)));
                meandivdiff += totalTime/(pow(sizes[i],2));
            }else{
                printf("  %-5d%15.3lf%20.6lf%15.6lf%15.6lf\n", sizes[i], totalTime, totalTime/(pow(sizes[i],0.8)), totalTime/sizes[i], totalTime/(pow(sizes[i],1.2)));
                meandivdiff += totalTime/sizes[i];
            }
        }
        printf("%57.6lf\n", meandivdiff/7);
    }
}

int main() {
    init_seed();
    test1();
    test2();
    test3(50);
    return 0;
}