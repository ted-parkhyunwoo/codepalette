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


// TODO quick 전용 전환 삽입정렬. 인레이 구현 등 리펙토링 필요
function insertSort(array, startIdx, endIdx) {
    for (let i = startIdx + 1; i <= endIdx; i++) {
        let key = array[i];
        let j = i - 1;
        while (j >= startIdx && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

const _quick = function(array, startIdx, endIdx) {
    if (endIdx - startIdx + 1 <= 256) {
        insertSort(array, startIdx, endIdx);
        return;
    }

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
    
    if (arrSz <= 256) {
        insert(array);
        return;
    }

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

    // 출력
    {
        let sample = [ 2, 3, 7, 1, 9, 6, 0, 5, 4, 8 ];
        printArr(sample);
        insert(sample)
        printArr(sample);
    }

    // 두 정렬 비교출력(길이 50 미만시)
    {
        const sampleSize = 100;
        let randSample = getRandIntArray(sampleSize, 300);
        let cp = randSample.slice()
        if (sampleSize <= 50) printArr(randSample);

        quick(randSample);
        // shell(randSample);
        cp.sort((a, b) => a - b);
        

        console.log((
            () => {
            for (let i = 0; i < sampleSize; ++i) {
                if (cp[i] != randSample[i]) {
                    if (sampleSize <= 50) {
                        printArr(randSample);
                        printArr(cp);
                    }
                    else {
                        console.log(`${i}번 index ${cp[i]} != ${randSample[i]}`);
                    }
                    return "[FAIL] 정렬 결과 같지않음";
                }
            }
            return "[SUCCESS] 정렬 결과 같음";
        })());
    }
    
    // 단일시간측정
    {
        const func = merge;
        const sampleSize = 100000000;

        let randSample = getRandIntArray(sampleSize, 10000)
        let startTime = performance.now()
        func(randSample)
        // randSample.sort((a, b) => a - b);       // 기본정렬 사용시
        const resTime = performance.now() - startTime
        print(resTime / 1000 + " s\n")
    }
}

main()
