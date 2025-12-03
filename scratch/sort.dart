import 'dart:math';
import 'dart:typed_data';

void main(List<String> args) {

  // sortBench(quick, 100_000_000, useInt32List: true);
  sortBench(quick, 10, useInt32List: true, printArray: true);

}


// 정렬 벤치마킹
void sortBench(sortfunc sf, int sampleSize, { required bool useInt32List, bool printArray = false}) {
  // sample의 자료형은 런타임환경에 결정된다.
  DateTime initArrayStart = DateTime.now();
  dynamic sample = useInt32List? getRandInt32Array(sampleSize, 10000) : getRandList(sampleSize, 10000);
  DateTime initArrayEnd = DateTime.now();

  if (printArray && sampleSize < 50)    // printArray: true라도, 50개가 넘는 길이는 출력하지 않도록 강제한다.
    print(sample);
  DateTime start = DateTime.now();
  sort(sample, sf);
  DateTime res = DateTime.now();
  if (printArray && sampleSize < 50)
    print(sample);
  print("sort: ${res.difference(start).inMicroseconds / 1_000_000} \tinit sample: ${initArrayEnd.difference(initArrayStart).inMicroseconds / 1_000_000}");
}



// 정렬을 선택 할 수 있게 alias.
typedef void sortfunc(var arr, int start, int end);
void sortRange(var arr, int start, int end, sortfunc sf) {
  sf(arr, start, end);
}
void sort(var arr, sortfunc sf) {
  sortRange(arr, 0, arr.length - 1, sf);
}


void bubble(var arr, int start, int end) {
  for (int i = start; i <= end - 1; ++i) {
    for (int j = start; j <= end - 1 - i; ++j) {
      if (arr[j] > arr[j + 1]) {
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
      int tmp = arr[i];
      arr[i] = arr[bfIdx];
      arr[bfIdx] = tmp;
    }
  }
}


void insertion(var arr, int start, int end) {
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
  if (start >= end) return;
  int sz = end - start + 1;
  if (sz <= 256) {
    insertion(arr, start, end);
    return;
  }

  int left = start;
  int right = end;
  int pivot = arr[(start + (sz / 2).toInt()) - 1];

  while (left <= right) {
    while (arr[left] < pivot) left++;
    while (arr[right] > pivot) right--;
    if (left <= right) {
      int tmp = arr[left];
      arr[left] = arr[right];
      arr[right] = tmp;
      left++;
      right--;
    }
  }

  if (right < end) quick(arr, start, right);
  if (left > start) quick(arr, left, end);

}


// Int32List 자료형: 전통적인 int* 혹은 int[] 등의 배열과 유사
Int32List getRandInt32Array(int size, int max) {
  Int32List res = Int32List(size);
  Random rand = Random();
  for (int i = 0; i < size; ++i)
    res[i] = rand.nextInt(max);
  return res;
}

// 가변크기 배열(std::vector와 유사)
List<int> getRandList(int size, int max) {
  // add 방식으로 사용할 때 배열생성시간(20~30%), 정렬(2~ 3%) 정도 느림

  // List<int> res = [];                          // add 방식으로 사용할 때
  List<int> res = List.filled(size, 0);         // index기반으로 사용할 때
  Random rand = Random();
  for (int i = 0; i < size; ++i)
    // res.add(rand.nextInt(max));
    res[i] = rand.nextInt(max);
  return res;
}