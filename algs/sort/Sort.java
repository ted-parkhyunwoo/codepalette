import java.util.Random;
import java.util.function.BiConsumer;
import java.util.Arrays;
import java.util.LinkedHashMap;
import java.util.Map;

// ArrayList 사용시 배열 접근이 너무 느려서 전통적 배열로 작성.
// 퀵정렬 / 병합정렬에서 insert를 호출시키기 위해 index기반 정렬도 구현됨
// 병합정렬은 기초구현(좌우측 배열 재할당) 방식과 sbMerge(버퍼를 미리 한번 할당하여 재활용)방식이 구현됨.


class Sort {
    // ---- HELPER: 가독성을 위해 함수를 모두 축소시키는 것을 추천.  ----

    public static void print(int[] arr) {
        System.out.print("[ ");
        int sz =                        arr.length;
        if (sz > 0)                     System.out.print(arr[0]);
        for (int i = 1; i < sz; ++i)    System.out.print(", " + arr[i]);
        System.out.print(" ]\n");
    }

    public static void swap(int[] arr, int i, int j) {
        int buffer =    arr[i];
        arr[i] =        arr[j];
        arr[j] =        buffer;
    }

    public static boolean isNeedSwap(int a, int b, boolean ascending) {
        return ascending? a > b : a < b;
    }

    public static int[] getRandArr(int size, int max) {
        Random random =                 new Random();
        int[] res =                     new int[size];
        for (int i = 0; i < size; ++i)  res[i] = random.nextInt(max) + 1;
        return res;
    }

    public static void doTest
    (
        // parameter
        int[]                       sample,
        BiConsumer<int[], Boolean>  algorithm,
        String                      funcName
    ) 
    {   
        // definition
        boolean ascending =             false;
        int[] copy =                    sample.clone();
        long start =                    System.currentTimeMillis();
        algorithm.accept(copy, ascending);
        long spent =                    System.currentTimeMillis() - start;

        System.out.println(
            "sort: " + funcName + "\t sample size: " + (copy.length) + "\tspent: " + spent + " ms \t (" + (spent / 1000.0) + " s)"
        );
    }

    public static boolean isCorrectlySorted(int[] sorted, int[] originalSample, boolean ascending) {
        // 정렬검사: originalSample 원본 정렬함.
        javaSort(originalSample, ascending);
        return Arrays.equals(sorted, originalSample);
    }


    // ---- SORT ALGORITHM ----

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

    public static void _insert(int[] arr, int startIdx, int endIdx, boolean ascending) {
        // 삽입정렬:index기반 - quick,  merge 등 에서 쉽게 사용하기 위함
        for (int i = startIdx + 1; i <= endIdx; ++i) {
            int bf = arr[i];
            int j;
            for (j = i; j > startIdx && isNeedSwap(arr[j - 1], bf, ascending); --j)
                arr[j] = arr[j - 1];
            if (j != i)
                arr[j] = bf;
        }
    }

    public static void _quick(int[] arr, int startIdx, int endIdx, boolean ascending) {
        // 아주 작은 배열이 재귀 실행되는것을 막기 위해 크기가 작아지면 insert로 전환
        if (endIdx - startIdx <= 256) { _insert(arr, startIdx, endIdx, ascending);      return;}

        int lIdx = startIdx;
        int rIdx = endIdx;
        int pivot = arr[(lIdx + rIdx) / 2];

        while (lIdx <= rIdx) {
            while (ascending ?
                    arr[lIdx] < pivot :
                    arr[lIdx] > pivot) 
                    lIdx++;
            while (ascending ?
                    arr[rIdx] > pivot :
                    arr[rIdx] < pivot) 
                    rIdx--;
            if (lIdx <= rIdx) {
                swap(arr, lIdx, rIdx);
                lIdx++;
                if (rIdx > 0) rIdx--;       // idx 가 unsigned 자료형이라면 필요한 조건식임. 정수형은 rIdx--만으로도 충분
            }
        }

        if (startIdx < rIdx) _quick(arr, startIdx, rIdx, ascending);
        if (endIdx > lIdx) _quick(arr, lIdx, endIdx, ascending);
    }

    public static void quick(int[] arr, boolean ascending) {
        _quick(arr, 0, arr.length - 1, ascending);
    }

    public static void _merge(int[] arr, int[] left, int[] right, boolean ascending) {
        int aSize = arr.length, lSize = left.length, rSize = right.length;
        int aIdx = 0, lIdx = 0, rIdx = 0;

        while (aIdx < aSize && lIdx < lSize && rIdx < rSize) {
            boolean cond =      left[lIdx] < right[rIdx];
                    cond =      ascending ? cond : !cond;

            if (cond)           arr[aIdx++] =   left[lIdx++];
            else                arr[aIdx++] =   right[rIdx++];
        }

        while (lIdx < lSize)    arr[aIdx++] = left[lIdx++];
        while (rIdx < rSize)    arr[aIdx++] = right[rIdx++];
    }

    public static void merge(int[] arr, boolean ascending) {
        int sz = arr.length;
        if (sz <= 1) return;
        
        if (sz <= 128) {
            insert(arr, ascending);
            return;
        }

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


    public static void _sbMerge(int[] arr, int startIdx, int endIdx, int[] bf, boolean ascending) {
        // 기저조건
        int sz = endIdx - startIdx + 1;
        if (sz <= 1) return;
        if (sz <= 64) {
            _insert(arr, startIdx, endIdx, ascending);
            return;
        }

        // 분할위치선정
        int leftSz = (int)(sz / 2);
        int rightSz = sz - leftSz;

        // 정복
        _sbMerge(arr, startIdx, startIdx + leftSz - 1, bf, ascending);
        _sbMerge(arr, startIdx + leftSz, startIdx + sz - 1, bf, ascending);

        // 합병
        int lBegin = startIdx, rBegin = startIdx + leftSz, bIdx = startIdx;         // 시작점 인덱스기반,
        int lEnd = startIdx + leftSz, rEnd = lEnd + rightSz, bEnd = endIdx;         // 주의: 도달하면 안됨
        while (lBegin < lEnd && rBegin < rEnd && bIdx < bEnd) {
            boolean cond = ascending? arr[lBegin] < arr[rBegin] : arr[lBegin] > arr[rBegin];
            if (cond) {
                bf[bIdx++] = arr[lBegin++];
            } else {
                bf[bIdx++] = arr[rBegin++];
            }
        }

        while (lBegin < lEnd)   bf[bIdx++] = arr[lBegin++];
        while (rBegin < rEnd)   bf[bIdx++] = arr[rBegin++];

        // 결과 적용 bf -> arr
        for (int i = startIdx; i <= endIdx; ++i)    arr[i] = bf[i];
        // System.arraycopy(bf, startIdx, arr, startIdx, endIdx - startIdx + 1);    // 아주 미세한 성능향상

    }


    public static void sbMerge(int[] arr, boolean ascending) {
        // 버퍼공간을 미리 할당하여 재사용.
        int sz = arr.length;
        int[] bf = new int[sz];
        _sbMerge(arr, 0, sz - 1, bf, ascending);
    }

    // 속도비교를 위한 기본 Arrays의 정렬
    public static void javaSort(int[] arr, boolean ascending) {
        java.util.Arrays.sort(arr);

        // 억지로 구현한 내림차순. 작동은 되나 가능하면 리펙토링 필요
        if (!ascending) {
            int arrSize = arr.length;
            int[] cp = new int[arrSize];
            for (int i = 0; i < arrSize; ++i) {
                cp[i] = arr[arrSize - i - 1];
            }
            
            for (int i = 0; i < arrSize; ++i) {
                arr[i] = cp[i];
            }

        }
    }

    //! MAIN

    public static void main(String[] args) {
        
        boolean[] test = { 
            // 테스트 실행 스위치. 필요한 것만 최소로 골라 실행할 수록 측정결과가 좋게 나오는 경향이 있음(특히 sbMerge)
            true, true, true, true 
        };

        // 1. 출력 육안확인
        if (test[0]) { 
            System.out.println("\n--- 1. print sorted ---");
            int[] sample = getRandArr(10, 100);
            print(sample);
            sbMerge(sample, true);
            print(sample);
            sbMerge(sample, false);
            print(sample);
        }

        // 2. 정렬 신뢰성 검증 (비교정렬은 isCorrectlySorted 내부에서 java.util.Arrays.sort() 를 사용함)
        if (test[1]) {
            System.out.println("\n--- 2. validate the sort ---");
            BiConsumer<int[], Boolean> sortAlg = Sort::     sbMerge;      // 변경가능

            int sampleSize = 30000;
            int[] sample = getRandArr(sampleSize, 10000);
            int[] cpSample = sample.clone();

            sortAlg.accept(sample, true);                                           // 정렬진행
            boolean res = isCorrectlySorted(sample, cpSample, true);     // 비교정렬 진행후 결과산출
            System.out.println(String.format("[오름차순 %s]: 길이 %d 배열", res?"성공":"실패", sampleSize));
            
            if (res) {  // 오름차순이 성공하면 진행됨. 샘플 오염된 채로 그대로 다시 사용(개선할 필요 없음. 어차피 재정렬)
                sortAlg.accept(sample, false);
                res = isCorrectlySorted(sample, cpSample, false);
                System.out.println(String.format("[내림차순 %s]: 길이 %d 배열", res?"성공":"실패", sampleSize));
            }
        }

        // 3. 기본 벤치마크
        if (test[2]) {
            System.out.println("\n--- 3. benchmark sorting ---");
            int[] sample = getRandArr(30000, 10000);
            Map<String, BiConsumer<int[], Boolean>> sortAlgs = new LinkedHashMap<>();
            sortAlgs.put("bubble", Sort::bubble);
            sortAlgs.put("select", Sort::select);
            sortAlgs.put("insert", Sort::insert);
            sortAlgs.put("shell", Sort::shell);
            sortAlgs.put("merge", Sort::merge);
            sortAlgs.put("quick", Sort::quick);
            sortAlgs.put("sbMerge", Sort::sbMerge);

            for (String key : sortAlgs.keySet()) {
                doTest(sample, sortAlgs.get(key), key);
            }
        }

        // 4. 고부하 정렬 벤치마크
        if (test[3]) {
            System.out.println("\n--- 4. High Perfomance Sort ---");
            int[] sample = getRandArr(100000000, 10000);
            doTest(sample, Sort::merge, "merge");
            doTest(sample, Sort::sbMerge, "sbMerge");
            doTest(sample, Sort::quick, "quick");
            doTest(sample, Sort::javaSort, "javaSort");
        }
    }
}

