import java.util.Random;
import java.util.function.BiConsumer;
import java.util.LinkedHashMap;
import java.util.Map;

// SortPractice.java의 전통적인 배열 사용버전. ArrayList와 Integer 사용시보다 quick정렬이 20초 -> 4초로 5배 빨라짐

class SortPracticeArray {

    public static void print(int[] arr) {
        System.out.print("[");
        int sz = arr.length;
        if (sz > 0) System.out.print(arr[0]);
        for (int i = 1; i < sz; ++i)
            System.out.print(", " + arr[i]);
        System.out.println("]");
    }

    public static void swap(int[] arr, int i, int j) {
        int buffer = arr[i];
        arr[i] = arr[j];
        arr[j] = buffer;
    }

    public static boolean isNeedSwap(int a, int b, boolean ascending) {
        return ascending? a > b : a < b;
    }

    public static int[] getRandArr(int size, int max) {
        Random random = new Random();
        int[] res = new int[size];
        for (int i = 0; i < size; ++i)
            res[i] = random.nextInt(max) + 1;
        return res;
    }

    public static void doTest(
            int[] sample,
            BiConsumer<int[], Boolean> algorithm,
            String funcName
    ) {
        boolean ascending = false;
        int[] copy = sample.clone();
        long start = System.currentTimeMillis();
        algorithm.accept(copy, ascending);
        long spent = System.currentTimeMillis() - start;
        System.out.println("sort: " + funcName + "\t sample size: " + (copy.length) + ",\tspent: " + spent + " ms \t (" + (spent / 1000.0) + " s)");
    }

    public static void bubble(int[] arr, boolean ascending) {
        int sz = arr.length;
        for (int i = 0; i < sz - 1; ++i) {
            for (int j = 0; j < sz - i - 1; ++j) {
                if (isNeedSwap(arr[j], arr[j + 1], ascending))
                    swap(arr, j, j + 1);
            }
        }
    }

    public static void select(int[] arr, boolean ascending) {
        int sz = arr.length;
        for (int i = 0; i < sz; ++i) {
            int idxBuffer = i;
            for (int j = i; j < sz; ++j) {
                if (isNeedSwap(arr[idxBuffer], arr[j], ascending))
                    idxBuffer = j;
            }
            if (idxBuffer != i)
                swap(arr, i, idxBuffer);
        }
    }

    public static void insert(int[] arr, boolean ascending) {
        int sz = arr.length;
        for (int i = 1; i < sz; ++i) {
            int buffer = arr[i];
            int j;
            for (j = i; j > 0 && isNeedSwap(arr[j - 1], buffer, ascending); --j)
                arr[j] = arr[j - 1];
            if (j != i)
                arr[j] = buffer;
        }
    }

    public static void shell(int[] arr, boolean ascending) {
        int sz = arr.length;
        int step = 1;
        while (step < sz / 3) step = step * 3 + 1;

        while (step > 0) {
            for (int i = step; i < sz; ++i) {
                int buffer = arr[i];
                int j;
                for (j = i; j >= step && isNeedSwap(arr[j - step], buffer, ascending); j -= step)
                    arr[j] = arr[j - step];
                if (j != i)
                    arr[j] = buffer;
            }
            step /= 3;
        }
    }

    public static void _quick(int[] arr, int startIdx, int endIdx, boolean ascending) {
        int lIdx = startIdx;
        int rIdx = endIdx;
        int pivot = arr[(lIdx + rIdx) / 2];

        while (lIdx <= rIdx) {
            while (ascending ?
                    arr[lIdx] < pivot :
                    arr[lIdx] > pivot) lIdx++;
            while (ascending ?
                    arr[rIdx] > pivot :
                    arr[rIdx] < pivot) rIdx--;
            if (lIdx <= rIdx) {
                swap(arr, lIdx, rIdx);
                lIdx++;
                if (rIdx > 0) rIdx--;
            }
        }

        if (startIdx < rIdx) _quick(arr, startIdx, rIdx, ascending);
        if (endIdx > lIdx) _quick(arr, lIdx, endIdx, ascending);
    }

    public static void quick(int[] arr, boolean ascending) {
        _quick(arr, 0, arr.length - 1, ascending);
    }

    public static void _merge(int[] arr, int[] left, int[] right, boolean ascending) {
        if (arr.length <= 1) {
            System.out.println("test: 크기 1에 도달. return");
            return;
        }

        int aSize = arr.length, lSize = left.length, rSize = right.length;
        int aIdx = 0, lIdx = 0, rIdx = 0;

        while (aIdx < aSize && lIdx < lSize && rIdx < rSize) {
            int leftBuffer = left[lIdx];
            int rightBuffer = right[rIdx];
            boolean cond = leftBuffer < rightBuffer;
            cond = ascending ? cond : !cond;

            if (cond) arr[aIdx++] = left[lIdx++];
            else arr[aIdx++] = right[rIdx++];
        }

        while (lIdx < lSize) arr[aIdx++] = left[lIdx++];
        while (rIdx < rSize) arr[aIdx++] = right[rIdx++];
    }

    public static void merge(int[] arr, boolean ascending) {
        int sz = arr.length;
        if (sz <= 1) return;
        int lSize = sz / 2;

        int[] left = new int[lSize];
        int[] right = new int[sz - lSize];
        for (int i = 0; i < sz; ++i) {
            if (i < lSize) left[i] = arr[i];
            else right[i - lSize] = arr[i];
        }

        merge(left, ascending);
        merge(right, ascending);

        _merge(arr, left, right, ascending);
    }

    public static void main(String[] args) {
        int[] sample;

        sample = getRandArr(29, 100);
        merge(sample, true); print(sample);
        merge(sample, false); print(sample);

        sample = getRandArr(100000000, 10000);
        doTest(sample, SortPracticeArray::quick, "quick");

        boolean runBenchmark = true;
        if (!runBenchmark) return;

        sample = getRandArr(50000, 10000);
        Map<String, BiConsumer<int[], Boolean>> sortAlgs = new LinkedHashMap<>();
        sortAlgs.put("bubble", SortPracticeArray::bubble);
        sortAlgs.put("select", SortPracticeArray::select);
        sortAlgs.put("insert", SortPracticeArray::insert);
        sortAlgs.put("shell", SortPracticeArray::shell);
        sortAlgs.put("merge", SortPracticeArray::merge);
        sortAlgs.put("quick", SortPracticeArray::quick);

        for (String key : sortAlgs.keySet()) {
            doTest(sample, sortAlgs.get(key), key);
        }

        sample = getRandArr(10000000, 10000);
        System.out.println("\nHigh Perfomance Sort:");
        doTest(sample, SortPracticeArray::shell, "shell");
        doTest(sample, SortPracticeArray::merge, "merge");
        doTest(sample, SortPracticeArray::quick, "quick");
    }
}
