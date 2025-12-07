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


// quick, merge에서 전환용으로 쓰는 인덱스기반 삽입정렬
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

function _merge(arr, startIdx, endIdx, bf) {
    // 기저조건
    const sz = endIdx - startIdx + 1;
    if (sz <= 1) return;
    if (sz <= 64) {
        insertSort(arr, startIdx, endIdx);
        return;
    }

    // 분할위치선정
    const leftSz = Math.floor(sz / 2);
    const rightSz = sz - leftSz;

    // 정복
    _merge(arr, startIdx, startIdx + leftSz - 1, bf);
    _merge(arr, startIdx + leftSz, startIdx + sz - 1, bf);

    // 합병
    let lBegin = startIdx, rBegin = startIdx + leftSz, bIdx = startIdx;         // 시작점 인덱스기반,
    let lEnd = startIdx + leftSz, rEnd = lEnd + rightSz, bEnd = endIdx;         // 주의: 도달하면 안됨
    while (lBegin < lEnd && rBegin < rEnd && bIdx < bEnd) {
        if (arr[lBegin] < arr[rBegin]) {
            bf[bIdx++] = arr[lBegin++];
        } else {
            bf[bIdx++] = arr[rBegin++];
        }
    }

    while (lBegin < lEnd)   bf[bIdx++] = arr[lBegin++];
    while (rBegin < rEnd)   bf[bIdx++] = arr[rBegin++];

    // 결과 적용 bf -> arr
    for (let i = startIdx; i <= endIdx; ++i)    arr[i] = bf[i];
    // System.arraycopy(bf, startIdx, arr, startIdx, endIdx - startIdx + 1);    // 아주 미세한 성능향상

}

function merge(array) {
    // 버퍼공간을 미리 할당하여 재사용하는 방식으로 개선.
    let sz = array.length;
    let bf = [];
    _merge(array, 0, sz - 1, bf);
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

//! ---- MAIN ----
const main = () => {

    // 출력
    {
        let sample = [ 2, 3, 7, 1, 9, 6, 0, 5, 4, 8 ];
        printArr(sample);
        quick(sample)
        printArr(sample);
    }

    // 두 정렬 비교출력(길이 50 미만시)
    {
        const sampleSize = 100;
        let randSample = getRandIntArray(sampleSize, 300);
        let cp = randSample.slice()
        if (sampleSize <= 50) printArr(randSample);

        quick(randSample);
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
        const func = quick;
        const sampleSize = 100000000;

        let randSample = getRandIntArray(sampleSize, 10000)
        let startTime = performance.now()
        func(randSample)
        // randSample.sort((a, b) => a - b);       // 기본정렬로 측정시: 생각보다 많이 느림
        const resTime = performance.now() - startTime
        print(resTime / 1000 + " s\n")
    }
}

main()
