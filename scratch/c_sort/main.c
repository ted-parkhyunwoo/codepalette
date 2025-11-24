
#include "bubble.h"
#include "select.h"
#include "insert.h"
#include "shell.h"
#include "quick.h"
#include "helper.h"

int main() {
    void (*sort) (int*, int*)  = quick;
    is_sort_work_correctly(sort);

    const int print = 0;
    const unsigned sampleSize = 100000000;

    int_arr sample;
    init_int_arr(&sample, sampleSize, 10000);

    if (print)  print_int_arr(sample);
    bench_sort_int_arr(sample, sort, 1);
    if (print)  print_int_arr(sample);

    delete_int_arr(&sample);

    return 0;
}
