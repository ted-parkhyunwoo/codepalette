
#include "bubble.h"
#include "select_sort.h"
#include "insert.h"
#include "shell.h"
#include "quick.h"
#include "helper.h"
#include "merge.h"

int main() {
    srand(time(NULL));
    void (*sort) (int*, int*)  = merge;
    is_sort_work_correctly(sort);

    const unsigned sampleSize = 100000000;

    int_arr sample;
    init_int_arr(&sample, sampleSize, 10000);

    if (sampleSize <= 20)  print_int_arr(sample);
    bench_sort_int_arr(sample, sort, 1);
    if (sampleSize <= 20)  print_int_arr(sample);

    delete_int_arr(&sample);

    return 0;
}
