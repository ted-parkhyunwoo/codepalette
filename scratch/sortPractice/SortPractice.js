function swap(array, i, j) {
    let tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

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
    let size = array.length;
    let i = 1;
    while (i < size) {
        let buffer = array[i];
        let j = i; 
        while (j > 0 && array[j - 1] > buffer) {
            array[j] = array[j - 1];
            --j;
        }
        if (j != i)                             array[j] = buffer;
        ++i;
    }
}

const shell = function(array) {
    const size = array.length;
    let step = size / 2;
    while (step > 0) {
        for (let i = step; i < size; ++i) {
            const buffer = array[i];
            let j;
            for (j = i; j >= step && array[j - step] > buffer; j -= step)
                array[j] = array[j - step];
            if (j !== i)        array[j] = buffer;
        }
        
        step = Math.floor(step /= 2);
    }
}



const main = () => {
    let test = [ 2, 3, 7, 1, 9, 6, 0, 5, 4, 8 ];
    console.log(test)
    select(test)
    console.log(test)
}

main()
