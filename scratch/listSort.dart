import 'dart:math';


void main(List<String> args) {
  int sampleSize = 100000000;
  List<int> sample = getRandList(sampleSize, 10000);
  bool printing = false;
  sortfunc s = quick;

  if (printing) print(sample);
  var start = DateTime.now();
  sortAuto(sample, s);
  var end = DateTime.now();
  var res = end.difference(start);
  print(res);
  if (printing) print(sample);

}


typedef void sortfunc(List<int> arr, int start, int end);

void sort(List<int> arr, int start, int end, sortfunc sf) {
  sf(arr, start, end);
}

void sortAuto(List<int>arr, sortfunc sf) {
  sf(arr, 0, arr.length - 1);
}

void bubble(List<int> arr, int start, int end) {
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

void selection(List<int> arr, int start, int end) {
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

void insertion(List<int> arr, int start, int end) {
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

void shell(List<int> arr, int start, int end) {
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

void quick(List<int> arr, int start, int end) {
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




List<int> getRandList(int size, int max) {
  List<int> res = [];
  Random rand = Random();
  for (int i = 0; i < size; ++i)
    res.add(rand.nextInt(max));
  return res;
}