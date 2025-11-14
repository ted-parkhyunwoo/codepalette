import java.util.ArrayList;

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
    public static void init(ArrayList<Integer> arr) {
        arr.clear();
        int[] sample = {5,2,9,3,1,4,8,0,6,7};
        for (int i = 0; i < sample.length; ++i)
            arr.add((Integer)sample[i]);
    }
    public static void initStrList(ArrayList<String> arr) {
        arr.clear();
        String[] strarr = {"c", "b", "A", "3", "5", "ab", "abc", "Ca", "aB", "Ab"};
        for (int i = 0; i < strarr.length; ++i)
            arr.add((String)strarr[i]);
    }



    public static void main(String[] args) {
        ArrayList<Integer> test = new ArrayList<>();
        boolean ascending = false;
        init(test); bubble(test, ascending); print(test);
        init(test); select(test, ascending); print(test);
        init(test); insert(test, ascending); print(test);
        init(test); shell(test, ascending); print(test);
        init(test); quick(test, ascending); print(test);
        init(test); merge(test, ascending); print(test);
        
        ArrayList<String> strTest = new ArrayList<>();
        initStrList(strTest);
        merge(strTest, true);
        print(strTest);
        
    }
}
