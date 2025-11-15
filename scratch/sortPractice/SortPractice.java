import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Random;
import java.util.function.BiConsumer;

class SortPractice {

    // HELPER MEMBER FUNCS : 배열출력, swap, 스왑조건검사(제네릭 객체간 직접비교연산자 사용불능으로 인한), 샘플배열 생성메서드, 정렬성능 검사메서드
    // algorithm엔 중요하지 않으므로 코드 읽는데 시간 낭비 하지 말 것.

    // print arraylist
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
        T buffer = arr.get(i);
        arr.set(i, arr.get(j));
        arr.set(j, buffer);
    }

    // compare condition helper : 스왑이 필요한 상태인지 return boolean. 입력된 매개변수가 a, b, true 라면 a > b 시 return true. a <= b 시 false.
    public static <T extends Comparable<T>> boolean isNeedSwap(T a, T b, boolean ascending) {
        return ascending? a.compareTo(b) > 0 : a.compareTo(b) < 0;
    }

    // random sample arraylist initialize helper
    // args: array size(length), maximum random integer(크든 작든 랜덤생성 및 아래 정렬 속도에는 의미 없음)
    public static ArrayList<Integer> getRandArr(int size, int max) {
        Random random = new Random();
        ArrayList<Integer> res = new ArrayList<>();
        for (int i = 0; i < size; ++i) 
            res.add(random.nextInt(max) + 1);
        return res;
    }

    // benchmark test
    public static void doTest(
                                ArrayList<Integer> sample,                              // sample 배열(원본을 수정하면 테스트가 공정하지 않으므로, 내부에서 복사생성됨)
                                BiConsumer<ArrayList<Integer>, Boolean> algorithm,      // sort methods 를 매개변수로 받음
                                String funcName                                         // sort 의 이름을 지정: 결과출력용으로만 쓰임
                            ) {
        boolean ascending = false;                          // you can change.
        ArrayList<Integer> copy = new ArrayList<>(sample);
        long start = System.currentTimeMillis();
        algorithm.accept(copy, ascending);
        long spent = System.currentTimeMillis() - start;
        System.out.println("sort: " + funcName + "\t sample size: " + (copy.size()) + ",\tspent: " + spent + " ms \t (" + (spent / 1000.0) + " s)");
    }


    // SORT ALGORITHM
    // 공통사항
    // method type: static void methods(None return)  -> arr를 직접 수정함
    // args:        ArrayList<compareTo 가능한 참조자료형> 정렬대상배열,  boolean 오름차순여부(true / false) 

    // bubble sort: 배열 우측부터 확정정렬. 매 루프에서 우측방향으로 인접한 요소끼리 swap됨.
    public static <T extends Comparable<T>> void bubble(ArrayList<T> arr, boolean ascending) {
        int sz = arr.size();
        for (int i = 0; i < sz - 1; ++i) {
            for (int j = 0; j < sz - i - 1; ++j) {
                if (isNeedSwap(arr.get(j), arr.get(j + 1), ascending)) 
                    swap(arr, j, j + 1);
            }
        }
    }

    // select sort: 배열 좌측부터 확정정렬. buffer 는 index를 기록하며, 매 루프에서 최소값(혹은 최대값)의 index를 찾아 swap
    public static <T extends Comparable<T>> void select(ArrayList<T> arr, boolean ascending) {
        int sz = arr.size();
        for (int i =0; i < sz; ++i) {
            int idxBuffer = i;
            for (int j = i; j < sz; ++j) {
                if (isNeedSwap(arr.get(idxBuffer), arr.get(j), ascending))
                    idxBuffer = j;
            }
            if (idxBuffer != i)
                swap(arr, i, idxBuffer);
        }
    }

    // insert sort: buffer의 삽입위치를 buffer의 idx 기준 좌측부터 탐색하며, 삽입위치를 찾을때까지 요소들을 밀어냄
    public static <T extends Comparable<T>> void insert(ArrayList<T> arr, boolean ascending) {
        int sz = arr.size();
        for (int i = 1; i < sz; ++i) {
            // set buffer
            T buffer = arr.get(i);

            // find insert position (and shifting)
            int j; 
            for (j = i; j > 0 && isNeedSwap(arr.get(j - 1), buffer, ascending); --j)
                arr.set(j, arr.get(j - 1));

            // insert buffer
            if (j != i)
                arr.set(j, buffer);
        }
    }

    // shell sort: insert의 매우 잦은 이동을 줄이기 위해 처음엔 띄엄띄엄 크게(step) 이동하며 줄여감.(step 아무렇게나 해도 상관없지만(size / 2로 업데이트가 스탠다드, 현재 코드는 커누스 갭 수열 사용) 마지막엔 step=1(삽입정렬) 회 실시해야하나, insert 특징이 정렬에 가까울수록 매우 빠르므로, insert에 비해 여러번 실행되더라도 획기적인 속도상승)
    public static <T extends Comparable<T>> void shell(ArrayList<T> arr, boolean ascending) {
        int sz = arr.size();

        // init step(gap) : knuth gap
        int step = 1;
        while (step < sz / 3) step = step * 3 + 1;

        // update gap: insert의 너무 잦은 이동을 step만큼 점프 뛰어서 오버헤드를 크게 줄이기 위함
        while(step > 0) {
            // 1 대신 step으로 초기화/ 업데이트 되는 부분 빼고 instert 와 같음.
            for (int i = step; i < sz; ++i) {      // i 는 step으로 초기화 되어 1씩 증가하며, j는 i로 초기화 되어 0보다 클때까지 step만큼 감소
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

    // quick sort core : 분할(pivot기준 좌/우 배열에서 swap)/정복(pivot기준 좌측, 우측 재귀호출)
    public static <T extends Comparable<T>> void _quick(ArrayList<T> arr, int startIdx, int endIdx, boolean ascending) {
        // divide: set pivot, divide left and right arrays.
        int lIdx = startIdx;
        int rIdx = endIdx;
        T pivot = arr.get((lIdx + rIdx) / 2);
        // find and swap
        while(lIdx <= rIdx) {
            // find need swap elements, 오름차순/ 내림차순 적용중.
            while(ascending? 
                    arr.get(lIdx).compareTo(pivot) < 0 : 
                    arr.get(lIdx).compareTo(pivot) > 0)         lIdx++;
            while(ascending? 
                    arr.get(rIdx).compareTo(pivot) > 0 : 
                    arr.get(rIdx).compareTo(pivot) < 0)         rIdx--;
            // swap
            if (lIdx <= rIdx) {
                swap(arr, lIdx, rIdx);
                lIdx++;
                if (rIdx > 0)       rIdx--;         // rIdx--; 만 해도 되나, unsigned 타입을 사용하던 습관
            }
        }
        
        // Conquer: recursive call
        if (startIdx < rIdx)        _quick(arr, startIdx, rIdx, ascending);
        if (endIdx > lIdx)          _quick(arr, lIdx, endIdx, ascending);
    }

    // quick sort wrapper
    public static <T extends Comparable<T>> void quick(ArrayList<T> arr, boolean ascending) {
        _quick(arr, 0, arr.size() - 1, ascending);
    }

    // merge sort core : 현재 index기반이 아님. left, right 배열 재할당중.
    public static <T extends Comparable<T>> void _merge(ArrayList<T> arr, ArrayList<T> left, ArrayList<T> right, boolean ascending) {
        if (arr.size() <= 1) {
            System.out.println("test: 크기 1에 도달. return");
            return;
        }
        // maximum size
        int aSize = arr.size(), lSize = left.size(), rSize = right.size();
        // index buffer
        int aIdx = 0, lIdx = 0, rIdx = 0;

        // merge
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

    //  merge sort wrapper
    public static <T extends Comparable<T>> void merge(ArrayList<T> arr, boolean ascending) {
        // divide
        int sz = arr.size();
        if (sz <= 1)        return;
        int lSize = sz / 2;
        // TODO: 일단 쉽게 left, right 할당. 나중에 index 기반으로 수정
        // left, right 초기화 및 arr 분할할당
        ArrayList<T> left = new ArrayList<>();
        ArrayList<T> right = new ArrayList<>();
        for (int i= 0; i < sz; ++i) {
            if (i < lSize)      left.add(arr.get(i));
            else                right.add(arr.get(i));   
        }

        // conquer
        merge(left, ascending);
        merge(right, ascending);

        // merge
        _merge(arr, left, right, ascending);
    }


    public static void main(String[] args) {
        ArrayList<Integer> sample;
        
        // SIMPLE TEST
        sample = getRandArr(29, 100);
        merge(sample, true);      print(sample);
        merge(sample, false);     print(sample);

        
        // BENCHMARK
        boolean runBenchmark = false;
        if (!runBenchmark) return;
        
        sample = getRandArr(50000, 10000);
        Map<String, BiConsumer<ArrayList<Integer>, Boolean>> sortAlgs = new LinkedHashMap<>();
        sortAlgs.put("bubble", SortPractice::bubble);
        sortAlgs.put("select", SortPractice::select);
        sortAlgs.put("insert", SortPractice::insert);
        sortAlgs.put("shell", SortPractice::shell);
        sortAlgs.put("merge", SortPractice::merge);
        sortAlgs.put("quick", SortPractice::quick);
        
        for (String key : sortAlgs.keySet())        { doTest(sample, sortAlgs.get(key), key); }
    

        // HIGH PERFOMANCE
        sample = getRandArr(10000000, 10000);
        System.out.println("\nHigh Perfomance Sort:");
        doTest(sample, SortPractice::shell, "shell");
        doTest(sample, SortPractice::merge, "merge");
        doTest(sample, SortPractice::quick, "quick");
    }

}

