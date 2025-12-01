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


---comment
---@param arr table
---@param si integer
---@param ei integer
local function bubble(arr, si, ei)
    if not checkIdx(#arr, si, ei) then
        return;
    end

    for i=si, ei-1 do
        for j=si, ei-i do
            if arr[j] > arr[j + 1] then
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
            end
        end
    end
end


--메인실행코드 함수화
local function main()

    local sampleSize = 10;
    local sample = getRandArray(sampleSize, 50)
    printArr(sample)
    local startTime = os.clock()
    bubble(sample, 1, sampleSize)
    print(string.format("sorting time: %.6f\n", os.clock() - startTime))
    printArr(sample)

end

math.randomseed(os.time() + os.clock() * 1000000)
main()
