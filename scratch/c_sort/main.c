#include "helper.h"
#include "bubble.h"
#include "select_sort.h"
#include "insert.h"
#include "shell.h"
#include "quick.h"
#include "merge.h"



int main() {
    srand(time(NULL));

    const void (*sortArr[])(int*, int*)  = {

        // bubble, select_sort, insert,         // 사용시 샘플사이즈 주의(느림)
        shell, merge, quick
    };

    const unsigned sampleSize = 100000000;
    int_arr sample;

    for (unsigned i = 0; i < sizeof(sortArr) / sizeof(sortArr[0]); i++) {
        const void (*sort)(int*, int*) = sortArr[i];
        is_sort_work_correctly(sort);

        init_int_arr(&sample, sampleSize, 10000);

        if (sampleSize <= 20)  print_int_arr(sample);
        bench_sort_int_arr(sample, sort, 1);
        if (sampleSize <= 20)  print_int_arr(sample);
        delete_int_arr(&sample);
    }

    return 0;
}
