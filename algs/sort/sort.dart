import 'dart:math';
import 'dart:typed_data';

/*
  흥미로운점: 
    aot 방식이 jit 방식에 비해 실행되는 속도는 빠르다고 일반적으로 알려져있으나, 아주 큰 크기의 메모리, 연산 집약 작업에는 오히려 느린 현상.
    추측하자면 jit은 아주 공격적인 최적화가 진행되지만, aot 환경에서는 안정적인 실행우선이며, gc 타이밍이나 memory->cache->register->cpu 이동간 오버헤드 증가 버그가 있는듯 함.

  컴파일 방식: 
    js: 몇천줄이 넘음. 같은알고리즘이지만, js로 짠 것보다 압도하도록 느림.
    aot-snapshot: 최소한의 바이너리만 포함하여 용량을 줄이고, dartaotruntime sort.aot 식으로 실행.
    jit-snapshot: javac 같은 역할과 비슷함. 중간언어로 컴파일. dart sort.jit 등으로 실행. 속도는 jit과 동일

  속도비교: 
    dart -> js:         quick: 9,   merge: 24 로 js  (quick: 5    merge: 11)처럼 같은 알고리즘의 js로 짠 코드보다 거의 두배 느림
    jit, jit-snapshot:  quick: 3.8, merge: 5.9로 java(quick: 4.0, merge:6.8)와 비슷하거나 약간 빠름
    aot, aot-snapshot:  quick: 21   merge: 37 로 가장 느리지만, 실사용은 가능한 정도.
*/



//! ---- MAIN ----
void main(List<String> args) {

  sortBench(dartsort, 100_000_000, useInt32List: true);
  sortBench(merge, 100_000_000, useInt32List: true);
  sortBench(quick, 100_000_000, useInt32List: true);
  // sortBench(merge, 20, useInt32List: true, printArray: true);

}



// 정렬 벤치마킹
void sortBench(sortfunc sf, int sampleSize, { required bool useInt32List, bool printArray = false}) {
  // sample의 자료형은 런타임환경에 결정. 두가지 자료구조(List<int>, Int32List) 사용 가능
  DateTime initArrayStart = DateTime.now();
  dynamic sample = useInt32List? getRandInt32Array(sampleSize, 10000) : getRandList(sampleSize, 10000);
  DateTime initArrayEnd = DateTime.now();

  // printArray: true라도, 50개가 넘는 길이는 출력하지 않도록 강제
  if (printArray && sampleSize < 50)    print(sample);
  DateTime start = DateTime.now();
  sort(sample, sf);
  DateTime res = DateTime.now();
  if (printArray && sampleSize < 50)    print(sample);
  print("sort: ${res.difference(start).inMicroseconds / 1_000_000} \tinit sample: ${initArrayEnd.difference(initArrayStart).inMicroseconds / 1_000_000}");
}


// 정렬을 선택 할 수 있게 alias
typedef void sortfunc(var arr, int start, int end);
void sortRange(var arr, int start, int end, sortfunc sf)  { sf(arr, start, end); }
void sort     (var arr, sortfunc sf)                      { sortRange(arr, 0, arr.length - 1, sf); }
void dartsort(var arr, int start, int end)                { arr.sort();}  // 기본 정렬 sort()를 sortfunc로 사용할 수 있도록 랩핑



// ---- 무작위 샘플 생성 ----

Int32List getRandInt32Array(int size, int max) {    // Int32List 자료형: 전통적인 int* 혹은 int[] 등의 배열과 유사
  Int32List res = Int32List(size);
  Random rand =   Random();
  for (int i = 0; i < size; ++i)    res[i] = rand.nextInt(max);
  return res;
}

List<int> getRandList(int size, int max) {        // 가변크기 배열(std::vector와 유사)
  // add 방식으로 사용할 때 배열생성시간(20~30%), 정렬(2~ 3%) 정도 느림

  // List<int> res = [];                          // add 방식으로 사용할 때
  List<int> res = List.filled(size, 0);           // index기반으로 사용할 때
  Random rand =   Random();
  for (int i = 0; i < size; ++i)
    // res.add(rand.nextInt(max));
    res[i] = rand.nextInt(max);
  return res;
}


// ---- 정렬알고리즘 ----

void bubble(var arr, int start, int end) {
  for (int i = start; i <= end - 1; ++i) {
    for (int j = start; j <= end - 1 - i; ++j) {
      if (arr[j] > arr[j + 1]) {
        // swap
        int tmp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = tmp;
      }
    }
  }
}


void selection(var arr, int start, int end) {
  for (int i = start; i <= end; ++i) {
    int bfIdx = i;
    for (int j = i; j <= end; ++j) {
      if (arr[j] < arr[bfIdx]) {
        bfIdx = j;
      }
    }
    if (bfIdx != i) {
      // swap
      int tmp = arr[i];
      arr[i] = arr[bfIdx];
      arr[bfIdx] = tmp;
    }
  }
}


void insertion(var arr, int start, int end) {
  // quick, merge 에 종속성 있음
  for (int i = start + 1; i <= end; ++i) {
    int bf = arr[i];
    int j = i;
    for (; j > start && arr[j - 1] > bf; --j) {
      arr[j] = arr[j - 1];
    }
    if (j != i) {
      arr[j] = bf;
    }
  }
}


void shell(var arr, int start, int end) {
  int gap = 1;
  while (gap < (arr.length / 3).toInt()) {
    gap = gap * 3 + 1;
  }

  while (gap > 0) {
    for (int i = start + gap; i <= end; ++i) {
      int bf = arr[i];
      int j = i;
      while (j >= gap && arr[j - gap] > bf) {
        arr[j] = arr[j - gap];
        j -= gap;
      }
      if (j != i) {
        arr[j] = bf;
      }
    }
    gap = (gap / 3).toInt();
  }

}


void quick(var arr, int start, int end) {
  // 기저
  if (start >= end) return;
  int sz = end - start + 1;
  if (sz <= 256) {      // 임계 도달시 삽입전환
    insertion(arr, start, end);
    return;
  }
  
  // 분할
  int left =  start;
  int right = end;
  int pivot = arr[(start + (sz / 2).toInt()) - 1];

  while (left <= right) {
    while (arr[left] < pivot)   ++left;
    while (arr[right] > pivot)  --right;
    if (left <= right) {
      // swap
      int tmp = arr[left];
      arr[left] = arr[right];
      arr[right] = tmp;

      ++left;
      --right;
    }
  }

  // 정복
  if (right < end)  quick(arr, start, right);
  if (left > start) quick(arr, left, end);
}


void _merge(var arr, int start, int end, var bf) {
  // 코어 (점화의 bf 재귀식 재활용)

  // 기저
  int size =        end - start + 1;
  if (start >= end) return;
  if (size <= 1)    return;
  if (size <= 64) {     // 임계 도달시 삽입전환
    insertion(arr, start, end);
    return;
  }

  // 경계 설정
  int halfSize =    (size / 2).toInt();
  int leftStart =   start;
  int leftEnd =     leftStart + halfSize - 1;
  int rightStart =  leftEnd + 1;
  int rightEnd =    end;

  // 정복
  _merge(arr, leftStart, leftEnd, bf);
  _merge(arr, rightStart, rightEnd, bf);

  // 병합
  int bfStart = start;
  while (leftStart <= leftEnd && rightStart <= rightEnd) {
    if (arr[leftStart] < arr[rightStart])   bf[bfStart++] = arr[leftStart++];
    else                                    bf[bfStart++] = arr[rightStart++];
  }

  // 소진되고 남은 한쪽 병합
  while (leftStart <= leftEnd)              bf[bfStart++] = arr[leftStart++];
  while (rightStart <= rightEnd)            bf[bfStart++] = arr[rightStart++];
  
  // 버퍼->원본 덮어쓰기(자주 실수하는 부분. 인덱스 설정 주의)
  arr.setRange(start, end + 1, bf, start);
} 


void merge(var arr, int start, int end) {
  // 점화 wrapper
  dynamic bf = arr.sublist(0, arr.length);    //? 동적타입에 0으로 할당하는 법을 몰라 일단 복사(둘이 초기화 방식이 다름)
  _merge(arr, start, end, bf);
}
