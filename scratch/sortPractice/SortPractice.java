import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Random;
import java.util.function.BiConsumer;

class SortPractice {

    // print arraylist helper
    public static <T> void print(ArrayList<T> arr) {
        System.out.print("[");
        int sz = arr.size();
        if (sz > 0) System.out.print(arr.get(0));
        for (int i = 1; i < sz; ++i)
            System.out.print(", " + arr.get(i));
        System.out.println("]");
    }

    // swap helper
    public static <T> void swap(ArrayList<T> arr, int i, int j) {
        T tmp = arr.get(i);
        arr.set(i, arr.get(j));
        arr.set(j, tmp);
    }

    // compare condition helper
    public static <T extends Comparable<T>> boolean isNeedSwap(T a, T b, boolean ascending) {
        return ascending? a.compareTo(b) > 0 : a.compareTo(b) < 0;
    }


    public static <T extends Comparable<T>> void bubble(ArrayList<T> arr, boolean ascending) {
        int sz = arr.size();
        for (int i = 0; i < sz - 1; ++i) {
            for (int j = 0; j < sz - i - 1; ++j) {
                if (isNeedSwap(arr.get(j), arr.get(j + 1), ascending)) 
                    swap(arr, j, j + 1);
            }
        }
    }

    public static <T extends Comparable<T>> void select(ArrayList<T> arr, boolean ascending) {
        int sz = arr.size();
        for (int i =0; i < sz; ++i) {
            int minIdxBuffer = i;
            for (int j = i; j < sz; ++j) {
                if (isNeedSwap(arr.get(minIdxBuffer), arr.get(j), ascending))
                    minIdxBuffer = j;
            }
            if (minIdxBuffer != i)
                swap(arr, i, minIdxBuffer);
        }
    }

    public static <T extends Comparable<T>> void insert(ArrayList<T> arr, boolean ascending) {
        int sz = arr.size();
        for (int i = 1; i < sz; ++i) {
            T buffer = arr.get(i);
            int j; 
            for (j = i; j > 0 && isNeedSwap(arr.get(j - 1), buffer, ascending); --j)
                arr.set(j, arr.get(j - 1));
            if (j != i)
                arr.set(j, buffer);
        }
    }

    public static <T extends Comparable<T>> void shell(ArrayList<T> arr, boolean ascending) {
        int sz = arr.size();
        int step = 1;
        while (step < sz / 3) step = step * 3 + 1;      // knuth gap.
        while(step > 0) {
            for (int i = step; i < sz; ++i) {
                T buffer = arr.get(i);
                int j;
                for (j = i; j >= step && isNeedSwap(arr.get(j-step), buffer, ascending); j -= step)
                    arr.set(j, arr.get(j - step));
                if (j != i)
                    arr.set(j, buffer);
            }
            step /= 3;
        }
    }

    public static <T extends Comparable<T>> void _quick(ArrayList<T> arr, int startIdx, int endIdx, boolean ascending) {
        int lIdx = startIdx;
        int rIdx = endIdx;
        T pivot = arr.get((lIdx + rIdx) / 2);

        while(lIdx <= rIdx) {
            if (ascending) {
                while(arr.get(lIdx).compareTo(pivot) < 0)       lIdx++;
                while(arr.get(rIdx).compareTo(pivot) > 0)       rIdx--;
            }
            else {
                while(arr.get(lIdx).compareTo(pivot) > 0)       lIdx++;
                while(arr.get(rIdx).compareTo(pivot) < 0)       rIdx--;
            }

            if (lIdx <= rIdx) {
                T buffer = arr.get(lIdx);
                arr.set(lIdx, arr.get(rIdx));
                arr.set(rIdx, buffer);
                lIdx++;
                if (rIdx > 0)       rIdx--;
            }
        }
        
        if (startIdx < rIdx)        _quick(arr, startIdx, rIdx, ascending);
        if (endIdx > lIdx)          _quick(arr, lIdx, endIdx, ascending);
    }

    public static <T extends Comparable<T>> void quick(ArrayList<T> arr, boolean ascending) {
        _quick(arr, 0, arr.size() - 1, ascending);
    }

    public static <T extends Comparable<T>> void _merge(ArrayList<T> arr, ArrayList<T> left, ArrayList<T> right, boolean ascending) {
        int aSize = arr.size(), lSize = left.size(), rSize = right.size(), aIdx = 0, lIdx = 0, rIdx = 0;
        while (aIdx < aSize && lIdx < lSize && rIdx < rSize) {
            T leftBuffer = left.get(lIdx);
            T rightBuffer = right.get(rIdx);
            boolean cond = leftBuffer.compareTo(rightBuffer) < 0;
            cond = ascending? cond : !cond;
            if (cond)           arr.set(aIdx++, left.get(lIdx++));
            else                arr.set(aIdx++, right.get(rIdx++));
        }
        while (lIdx < lSize)    arr.set(aIdx++, left.get(lIdx++));
        while (rIdx < rSize)    arr.set(aIdx++, right.get(rIdx++));
    }

    public static <T extends Comparable<T>> void merge(ArrayList<T> arr, boolean ascending) {
        int sz = arr.size();
        if (sz <= 1)        return;
        int lSize = sz / 2;
        ArrayList<T> left = new ArrayList<>();
        ArrayList<T> right = new ArrayList<>();
        for (int i= 0; i < sz; ++i) {
            if (i < lSize)      left.add(arr.get(i));
            else                right.add(arr.get(i));   
        }

        merge(left, ascending);
        merge(right, ascending);
        _merge(arr, left, right, ascending);
    }


    // init sample arraylist helper.
    public static void initStrList(ArrayList<String> arr) {
        arr.clear();
        String[] strarr = {"c", "b", "A", "3", "5", "ab", "abc", "Ca", "aB", "Ab"};
        for (int i = 0; i < strarr.length; ++i)
            arr.add((String)strarr[i]);
    }

    public static ArrayList<Integer> getRandArr(int size, int max) {
        Random random = new Random();
        ArrayList<Integer> res = new ArrayList<>();
        for (int i = 0; i < size; ++i) {
            res.add(random.nextInt(max));
        }
        return res;
    }

    public static void doTest(ArrayList<Integer> rand, BiConsumer<ArrayList<Integer>, Boolean> algorithm, String funcName) {
        
        boolean ascending = false;
        ArrayList<Integer> copy = new ArrayList<>(rand);
        long start = System.currentTimeMillis();
        algorithm.accept(copy, ascending);
        long end = System.currentTimeMillis();

        System.out.println((end - start) + "ms (" + ((end - start)/ 1000.0) + "s),  sort: " + funcName + ", sample size: " + (copy.size()));
    }

    public static void main(String[] args) {
        ArrayList<Integer> rand;

        System.out.println("Normal Sort:");
        rand = getRandArr(100000, 10000);
        doTest(rand, SortPractice::bubble, "bubble");
        doTest(rand, SortPractice::select, "select");
        doTest(rand, SortPractice::insert, "insert");
        doTest(rand, SortPractice::shell, "shell");
        doTest(rand, SortPractice::merge, "merge");
        doTest(rand, SortPractice::quick, "quick");        

        System.out.println("\nHigh Perfomance Sort:");
        rand = getRandArr(10000000, 10000);
        doTest(rand, SortPractice::shell, "shell");
        doTest(rand, SortPractice::merge, "merge");
        doTest(rand, SortPractice::quick, "quick");
    }

}
