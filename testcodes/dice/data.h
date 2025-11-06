#ifndef DATA_H
#define DATA_H

#define SIZE 6

typedef struct dataStruct {
    long count[10];
} data; 

void initData(data* d); 
void descData(data* d); 
void plusElement(data* d, unsigned num);

#endif // DATA_H