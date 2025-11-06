
void swap(double* a, double* b) {
    double tmp = *b;
    *b = *a;
    *a = tmp;
}

// bubble
void sort(double* arr, unsigned sz) {
    if (sz < 2) return;
    for (unsigned i = 0; i < sz - 1; ++i) {
        for (unsigned j = 0; j < sz - i - 1; ++j) {
            const double left = arr[j], right = arr[j + 1];
            if (left > right) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

