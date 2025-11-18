function swap(array, i, j) {
    const tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

// next line 없이 콘솔 출력. 귀찮아서 작성
const print = (obj) => { process.stdout.write(obj.toString()) }
// 배열을 줄바꿈 없이 출력(console.log 찍으면 이쁘게 정렬되는걸 막음)
const printArr = (array) => {
    const sz = array.length;
    print("{ ");
    if (sz >= 1)  print(array[0]);
    for (let i = 1; i < sz; ++i) {
        print(", ");
        print(array[i]);
    }
    print(" }\n");
}

// sort: 함수 선언식, 함수 표현식, 화살표함수등을 골고루 섞어서 선언하였으며, 반복문은 while, for 문을 바꿔서 쓰기도 함.

function bubble(array) {
    const size = array.length;
    for (let i = 0; i < size - 1; ++i) {
        for (let j = 0; j < size - i - 1; ++j) {
            if (array[j] > array[j + 1])        swap(array, j, j + 1);
        }
    }
}

const select = function(array) {
    const size = array.length;
    for (let i = 0; i < size; i++) {
        let minIdx = i;
        let j = i;
        while (j < size) {
            if (array[j] < array[minIdx])       minIdx = j;
            ++j;
        }
        if (minIdx !== i)                        swap(array, i, minIdx);
    }
}

const insert = (array) => {
    const size = array.length;
    for (let i = 1; i < size; ++i) {
        let bf = array[i];
        let j = i; 
        while (j > 0 && array[j - 1] > bf)      array[j] = array[--j];
        if (j != i)                             array[j] = bf;
    }
}

const shell = function(array) {
    const size = array.length;
    let step = 1;
    while (step < Math.floor(size / 3))
        step = step * 3 + 1;

    for (;step > 0; step = Math.floor(step /= 3)) {
        for (let i = step; i < size; ++i) {
            const bf = array[i];
            let j;
            for (j = i; j >= step && array[j - step] > bf; j -= step)
                array[j] = array[j - step];
            if (j !== i)
                array[j] = bf;
        }
    
    }
}

const _quick = function(array, startIdx, endIdx) {
    let leftIdx = startIdx;
    let rightIdx = endIdx;
    const centerIdx = startIdx + Math.floor((endIdx - startIdx) / 2);
    const pivot = array[centerIdx];
    
    while (leftIdx <= rightIdx) {
        while (array[leftIdx] < pivot)      leftIdx++;
        while (array[rightIdx] > pivot)     rightIdx--;
        if (leftIdx <= rightIdx)            swap(array, leftIdx++, rightIdx--);
    }

    if (startIdx < rightIdx)                _quick(array, startIdx, rightIdx);
    if (endIdx > leftIdx)                   _quick(array, leftIdx, endIdx);
}

const quick = function(array) { _quick(array, 0, array.length - 1) }

const merge = (array) => {
    const arrSz = array.length;
    if (arrSz <= 1) return;

    // divide
    const leftSz = Math.floor(arrSz / 2);
    const rightSz = arrSz - leftSz;
    const leftArr = array.slice(0, leftSz)
    const rightArr = array.slice(leftSz)

    // conquer
    merge(leftArr);
    merge(rightArr);

    // merge
    // 좌우측 배열에서 순서대로 뽑아 array에 재정렬
    let lIdx = 0,  rIdx = 0,  aIdx = 0;

    while (lIdx < leftSz && rIdx < rightSz) {
        if (leftArr[lIdx] < rightArr[rIdx])     array[aIdx++] = leftArr[lIdx++]
        else                                    array[aIdx++] = rightArr[rIdx++]
    }

    // 나머지 채워넣기
    while (lIdx < leftSz)       array[aIdx++] = leftArr[lIdx++]
    while (rIdx < rightSz)      array[aIdx++] = rightArr[rIdx++]
}

const getRandInt = (max) => {
    return Math.floor(Math.random() * max) + 1
}

const getRandIntArray = (size, max = 10000) => {
    res = []
    for (let i = 0; i < size; ++i) {
        res.push(getRandInt(max))
    }
    return res
}

const main = () => {
    // 육안 검사
    let sample = [ 2, 3, 7, 1, 9, 6, 0, 5, 4, 8 ];
    printArr(sample);
    quick(sample)
    printArr(sample);
    

    // 단일시간측정
    const func = quick;
    let randSample = getRandIntArray(100000000, 10000)
    let startTime = performance.now()
    func(randSample)
    let resTime = performance.now() - startTime
    print(resTime / 1000 + " s\n")
}

main()
