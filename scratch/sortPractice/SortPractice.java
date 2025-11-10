public class SortPractice {
    public static void swap(int[] arr, int i, int j) {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    public static void printArray(int[] arr) {
        int size = arr.length;
        if (size < 0) return;
        System.out.print("{" + arr[0]);
        for (int i = 1; i < size; ++i) {
            System.out.print(", " + arr[i]);
        }
        System.out.println('}');
    }

    public static void bubble(int[] arr) {
        int size = arr.length;
        for (int i = 0; i < size - 1; ++i) {
            for (int j = 0; j < size - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr, j, j + 1);
                }
            }
        }
    }

    public static void select(int[] arr) {
        int size = arr.length;
        for (int i = 0; i < size; ++i) {
            int minIndex = i;
            for (int j = i; j < size; ++j) {
                if (arr[j] < arr[minIndex])     minIndex = j;
            }
            if (minIndex != i)          swap(arr, i, minIndex);
        }
    }

    public static void insert(int[] arr) {
        int size = arr.length;
        for (int i = 1; i < size; ++i) {
            int buffer = arr[i];
            int j = i;
            while (j > 0 && arr[j - 1] > buffer) {
                arr[j] = arr[j - 1];
                --j;
            }
            arr[j] = buffer;
        }
    }

    public static void shell(int[] arr) {
        int size = arr.length;
        for (int step = size / 2; step > 0; step /= 2) {
            System.out.println("step: " + step);
            for (int i = step; i < size; ++i) {
                int buffer = arr[i];
                int j = i;
                for (; j >= step && arr[j - step] > buffer; j -= step) {
                    arr[j] = arr[j - step];
                }
                if (j != i) arr[j] = buffer;
            }

        }
    }

    public static void main(String[] args) {
        int[] test = new int[] { 2, 3, 7, 1, 9, 6, 0, 5, 4, 8 };
        printArray(test);
        shell(test);
        printArray(test);
    }
}
