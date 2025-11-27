--[[
    Lua 핵심 기능 요약 파일
    함수, 변수, 조건문, 반복문, 테이블(배열/해시맵) 기본 사용법 정리.
--]]

--------------------------------------------------
-- 1. 함수 (Functions)
--------------------------------------------------

-- 함수 정의 및 호출
function sum(a, b)
    print(string.format("%d + %d = %d", a, b, a + b))
    return a + b
end

print(sum(4, 2))
print("---") -- 구획 분리

--------------------------------------------------
-- 2. 변수 (Variables)
--------------------------------------------------

-- 전역 변수 선언: 'local' 키워드가 없으면 전역 변수가 된다.
a = 6
-- 지역 변수 선언: 반드시 'local' 키워드를 사용한다.
local b = 6

--------------------------------------------------
-- 3. 조건문 (Control Flow)
--------------------------------------------------

-- C/C++의 if-else if-else와 동일하며, 끝에 'end'가 필요하다.
-- 참고: Lua에서 조건문의 거짓은 'nil'과 'false' 뿐이다.
if a > b then
    print(string.format("%d > %d", a, b))
elseif a == b then
    print(string.format("%d = %d (a: %d, b: %d)", a, b, a, b))
else
    print(string.format("%d < %d", a, b))
end
print("---") -- 구획 분리

--------------------------------------------------
-- 4. 반복문 (For Loops)
--------------------------------------------------

-- 일반적인 숫자형 for 루프 (선언, 조건, 증감(1일땐 생략가능))
io.write("[반복문] ")
for i = 0, 10, 1 do
    -- 줄 바꿈 없는 출력: io.write() 사용
    io.write(string.format("%d ", i))
end
io.write("\n")
print("---") -- 구획 분리

--------------------------------------------------
-- 5. 테이블 (Table) 활용: 배열 및 맵
--------------------------------------------------

-- 배열 (Array)처럼 사용: 인덱스는 1부터 시작
local array = {}
for i = 0, 9 do
    table.insert(array, i)
end

-- 마지막에 추가되는 개념
table.insert(array, 11)
-- 위치에 삽입(11번 요소를 밀어내고 10 추가)
table.insert(array, 11, 10)

-- 마지막요소 삭제(하면서 반환)
table.remove(array)
-- 특정요소를 삭제(하면서 반환)
local removed = table.remove(array, 11)
print(string.format("[배열] 삭제된 요소: %d", removed))

-- 배열 사이즈 확인: # 연산자 (nil이 없는 순차적인 정수 인덱스만 센다)
local sz = #array
print(string.format("array size: %d", sz))

-- 배열 순회 (1번 인덱스부터 사이즈까지)
io.write("[배열] 숫자형 for 루프: ")
for i = 1, sz do
    io.write(string.format("%d ", array[i]))
end
io.write("\n")

-- 0인덱스는 없음. nil은 null같은 개념이다.
print(string.format("[배열] array[0] 값: %s", tostring(array[0])))

-- Advanced for (Generic For) - 배열 전용 순회 (ipairs)
-- ipairs는 순차적인 정수 키(i)와 값(val) 쌍으로 리턴하며 순서 보장된다.
io.write("[배열ipairs] ipairs 순회: ")
for i, val in ipairs(array) do
    -- tostring 으로 문자열 전환하여 출력
    io.write(string.format("[idx:%d val:%s], ", i, tostring(val)));
end
print "\n배열설명 끝"; -- 괄호 없는 print 구문도 유효하다.
print("---") -- 구획 분리

--------------------------------------------------
-- 6. 해시맵 (Hashmap) unordered_map 처럼 순서보장X
--------------------------------------------------

local mydict = { a = 1, b = 2, c = 3, d = 4 };

-- 페어 추가 (dot접근, []접근)
mydict.e = 5
mydict["f"] = 6
mydict.g = 8

-- 페어 수정
mydict.g = 7

-- 페어 삭제
mydict.g = nil


-- Advanced for (Generic For): pairs() 함수를 사용해 키(k)와 값(v)을 순회
print("[해시맵] 순회 결과:")
for k, v in pairs(mydict) do
    print(string.format("%s = %d", k, v));
end
