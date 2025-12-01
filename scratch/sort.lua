---table(배열) 을 출력
---@param t table
local function printArr(t)
    local sz = #t
    io.write("{ ")
    if sz >= 1 then
        io.write(t[1])
    end
    for i=2, sz do
        io.write(string.format(", %d", t[i]))
    end
    print(" }")
end


---정수 랜덤배열 생성
---@param size integer
---@param max integer
---@return table
local function getRandArray(size, max)
    local result = {}
    for i=1, size do
        table.insert(result, math.random(max))
    end
    return result
end


--- start index, end index가 멀쩡한 상태인지 점검하는 함수
--- @param sz integer
--- @param si integer
--- @param ei integer
--- @return boolean
local function checkIdx(sz, si, ei)
    if si == ei or si >= ei or ei - si + 1 > sz then
        print("index error")
        return false
    end
    if ei - si + 1 == sz and si ~= 1 then
        print("out of idx")
        return false
    end
    return true
end


--- bubble sort
---@param arr table
---@param si integer
---@param ei integer
local function sort_bubble(arr, si, ei)
    if not checkIdx(#arr, si, ei) then
        return;
    end

    for i = si, ei - 1 do
        -- for j = si, ei - i do        -- 인덱스기반이므로 이 조건은 잘못됐다.
        for j = si, ei - 1 - (i - si) do
            if arr[j] > arr[j + 1] then
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
            end
        end
    end
end


--- selection sort
---@param arr table
---@param si integer
---@param ei integer
local function sort_select(arr, si, ei)
    if not checkIdx(#arr, si, ei) then
        return;
    end
    
    for i = si, ei do
        local m = i;
        for j = i, ei do
            if arr[j] < arr[m] then
                m = j;
            end
        end
        if m ~= i then
            arr[i], arr[m] = arr[m], arr[i]
        end
    end
end


--- insertion sort
---@param arr table
---@param si integer
---@param ei integer
local function sort_insert(arr, si, ei)
    if not checkIdx(#arr, si, ei) then
        return;
    end
    
    for i = si + 1, ei do
        local bf = arr[i]
        local j = i
        -- j > 1로 하면 안됨. si로 해야함
        while(j > si and arr[j - 1] > bf) do
            arr[j] = arr[j - 1]
            j = j - 1
        end

        if j ~= i then
            arr[j] = bf
        end
    end
end


--- shell sort - knuth gap
---@param arr table
---@param si integer
---@param ei integer
local function sort_shell(arr, si, ei)
    if not checkIdx(#arr, si, ei) then
        return;
    end

    local gap = 1
    while (gap < math.floor(#arr / 3)) do
        gap = gap * 3 + 1
    end

    while (gap > 0) do
    
        for i = si + gap, ei do
            local bf = arr[i]
            local j = i
            -- index기반이기 때문에, pointer 혹은 index 방식을 따라서 작성하도록. 조건식 j - gap 이 si보다는 커야함. (j > gap 혹은 j >= gap  같은 size기반이랑 다름)
            while(j - gap >= si and arr[j - gap] > bf) do
                arr[j] = arr[j - gap]
                j = j - gap
            end
            
            if j ~= i then
                arr[j] = bf
            end
        end

        gap = math.floor(gap / 3) 
    end
end



local function printSortCorrectly(func, size)
    size = size or 10000
    local max = 1000

    local arr = getRandArray(size, max)
    local cp  = {}
    local ref = {}
    for i = 1, #arr do
        cp[i] = arr[i]
        ref[i] = arr[i]
    end

    table.sort(ref)

    local t0 = os.clock()
    func(cp, 1, #cp)
    local dt = os.clock() - t0

    local ok = true
    for i = 1, #cp do
        if cp[i] ~= ref[i] then
            ok = false
            break
        end
    end

    print(string.format("오름차순: %s  소요시간: %.6f", ok and "성공!" or "실패", dt))
end


local function sortingTime(sortFunction, sampleSize, sampleMaxInt, printArray)

    local sample = getRandArray(sampleSize, sampleMaxInt)
    
    if printArray == true then
        printArr(sample)
    end

    local startTime = os.clock()
    sortFunction(sample, 1, sampleSize)
    local resultTime = os.clock() - startTime

    if printArray == true then
        printArr(sample)
    end

    print(string.format("sorting time: %.6f", resultTime))

    
end



--메인실행코드 함수화
local function main()

    -- 정렬검증. 배열 복사후 내장정렬(table.sort(array)) 과 비교
    printSortCorrectly(sort_bubble, 1000)
    
    -- 정렬 시간 검사
    local sampleSize = 5000

    sortingTime(sort_bubble, sampleSize, 10000, false)
    sortingTime(sort_select, sampleSize, 10000, false)
    sortingTime(sort_insert, sampleSize, 10000, false)
    sortingTime(sort_shell, sampleSize, 10000, false)

    -- 100만개 shell정렬        1.57 언저리로, 다른 언어에 비해(파이썬보단 양호) 고성능 정렬엔 적합하지 않은 언어
    -- c: 0.0699      cpp(vector): 0.0768     cpp(ptr): 0.0699     python: 3.5118     java:0.079      js:0.1393
    sortingTime(sort_shell, 1000000, 10000, false)

end



math.randomseed(os.time() + os.clock() * 1000000)
main()
