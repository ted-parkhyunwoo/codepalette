# https://www.codewars.com/kata/55171d87236c880cea0004c6/train/python

#TODO: 챌린지는 완벽히 작동하며 그 외 실사용 코드도 작성되었음. 주석과 함수명 등 리펙토링이 필요함.

'''
1. 보드판 자료형은 2차원 배열로 이루어짐. 예: [[1, 0, 3...],[2, 5, 4...]....]
2. row, column, suqare-sector 세가지 구역으로 요소들을 다루고 있음.
3. 비어있는 값은 0으로 처리됨
4. 2번을 참고하여 빈칸에 들어갈 가능성이 있는 경우가 단 1가지 뿐인것을 해결하는 함수는 solvePossible() 로 연쇄 해결함.
5. solvePossible() 가 해결하지 못하는, 경우의 수가 2개 이상인 순간부터는 bfSolve() 가 강제로 선택하고, 틀리면 백트래킹방식으로 해결함. bfSolve()도 solvePossible()을 내장하고 있기 때문에, bfSolve() 만 실행해도 모든 문제가 해결됨.
5-1. bfSolve 함수는 solvePossible을 먼저 실행하고 나머지는 백트래킹을 이용해 강제 풀이 시도함.
6. 챌린지에서는 잘못된 보드에 대한 문제가 주어지지 않아 문제가 없었으나, 직접 추가한 사용자 입출력단에서는 예외가 발생할 수 있으므로 checkBoard()함수로 유효한 보드의 상태인지 점검 가능함: 정확히는 bad puzzle인지 검사.
7. 해결한 보드인지는 isSolved()로 점검하지만 단순 0이 없는지 보는것이기 때문에, 퍼즐 유효성은 checkBoard() 로 검사를 같이 동반 수행해야됨.
'''

# For find square sector Elements.
tmpIdx = [(0, 0), (0, 1), (0, 2), (1, 0), (1, 1), (1, 2), (2, 0), (2, 1), (2, 2)]
squareIdx = [[(x + i * 3, y + j * 3) for (x, y) in tmpIdx] for i in range(3) for j in range(3)]

# 특정 좌표의 사각형 섹터를 리턴. 3*3 전화기 키패드패턴.
def getSquareSector(row: int, col: int) -> int:
    rowSector = (row // 3) + 1
    colSector = (col // 3) + 1
    return (rowSector - 1) * 3 + colSector

# 특정 사각형섹터의 요소들을 찾아 리스트로 리턴하는 함수. (0도 포함됨.)
def getSquareSectorElements(sector: int, board:list) -> list:
    sectors = {i+1 : squareIdx[i] for i in range(9)}
    return [board[pos[0]][pos[1]] for pos in sectors[sector]]

# 특정 좌표에 대입 가능한 요소들을 찾는 함수(0 일때만 정상사용 가능하며, 아닐시 비어있는 배열 리턴.)
def possibleNums(x:int, y:int, board:list) -> list:
    if board[x][y] != 0: return []
    rowE = [(board[x][i]) for i in range(9) if board[x][i] != 0] 
    colE = [(board[i][y]) for i in range(9) if board[i][y] != 0]
    sqrE = getSquareSectorElements(getSquareSector(x,y), board)
    allE = set(rowE + colE + sqrE)
    return [i for i in range(1, 10) if i not in allE]

# 비어있는 칸의 좌표들을 찾아 (x, y):tuple 리스트로 만들어 리턴하는 함수.
def getEmptyPos(board: list) -> list:
    return [(x, y) for x in range(9) for y in range(9) if board[x][y] == 0]

# 보드의 유효성 검사: bad puzzle checker.
def checkBoard(board: list) -> bool:
    # 9 * 9 검사
    if len(board) != 9: return False
    for i in range(9):
        if len(board[i]) != 9: return False

    # 가로/세로/사각섹터 중복요소 검사
    def check(nums: list) -> bool:
        nums = [n for n in nums if n != 0]
        return len(nums) == len(set(nums))
    for i in range(9):
        rowE:list = board[i]
        colE:list = [board[x][i] for x in range(9)]
        sqrE:list = getSquareSectorElements(i + 1, board)
        if not (check(rowE) and check(colE) and check(sqrE)): return False
    return True

# 해결된 sudoku인지 검토: 0이 있는지만 점검하며, 유효성 검사는 안함.
def isSolved(board: list) -> bool:
    for row in board:
        for num in row:
            if num == 0: return False
    return True

# 가능한 경우의 수가 1개인 0을 불가능 할 때 까지 해결하는 함수
def solvePossible(board: list) -> list:
    while True:
        updated = False
        emptyPos = getEmptyPos(board)
        for pos in emptyPos:
            p_nums = possibleNums(*pos, board = board)
            if len(p_nums) == 1:
                board[pos[0]][pos[1]] = p_nums[0]
                updated = True
        if not updated: break
    return board

# 가장 먼저 해결해야할 좌표(tuple)를 골라 리턴하는 함수.
def getPriority(board: list) -> tuple:
    emptyPos = getEmptyPos(board) 
    res = (0, 0)
    res_len = 9
    for pos in emptyPos:
        p_nums = possibleNums(*pos, board = board)
        if len(p_nums) < res_len:
            res_len = len(p_nums)
            res = pos
    #! 해결할 것이 없다면 -1,-1 리턴: 오류 아님: 백트래킹방식 해결 진입시도를 위한 트리거.
    if (res_len == 0): return (-1, -1)  
    return res

# 백트래킹을 사용하여 스도쿠 퍼즐을 해결하는 함수
def bfSolve(board: list) -> list | bool:
    if not checkBoard(board):   # 보드가 유효하지 않으면 False 반환
        return False 
    
    if isSolved(board):         # 해결된경우 조기리턴.
        return board
    
    priorityPos: tuple = getPriority(board)         

    if priorityPos == (-1, -1): # getPriority 결과 가능한 숫자가 없는 경우 -> 아래 백트래킹 진입
        return False            #! debug: 처음엔 아래 isSolved랑 조건을 묶어 board를 리턴했으나, 자세히 생각해보면 백트래킹 진입을 위해 False가 맞음.

    priorityPosPossibleNums: list = possibleNums(*priorityPos, board = board)

    for guess in priorityPosPossibleNums:  # 가능한 숫자 시도
        lastBoard: list = [row[:] for row in board]  # 현재 상태 저장
        board[priorityPos[0]][priorityPos[1]] = guess
        board = solvePossible(board)

        if checkBoard(board):  # 유효한 보드인지 확인
            if isSolved(board):  # 해결된 경우 반환
                return board
            res = bfSolve(board)  # 재귀 호출
            if res:  # 성공 시 반환
                return res

        board = [row[:] for row in lastBoard]  # 실패 시 상태 복원

    return False  # 모든 경우 실패 시 False 반환

# 위 모든 함수들을 종합하여 자동으로 실행.
def solve(board: list[list[int]]) -> list | bool:
    return board if checkBoard(board) and isSolved(board) else bfSolve(board)


###! 챌린지 요구조건 외 직접 커스텀한 함수들이 아래에 추가됨: 사용자 입출력 함수

# 보드 출력함수. 비어있는경우 강제 리턴.
def prettyPrintSudoku(board: list | bool) -> None:
    if type(board) == bool:  # 보드에 문제가 있으면 None으로 해석되는 상태.
        print("ERR:\nSomething Wrong.")
        return
    
    print("RESULT:")
    for i in range(9):
        if i % 3 == 0 and i != 0:  # 세로 구획선을 추가
            print("- - - + - - - + - - -")

        row = board[i]
        for j in range(9):
            if j % 3 == 0 and j != 0:  # 가로 구획선을 추가
                print("|", end=" ")

            print(row[j], end=" ")
        print()

# 보드 입력함수(한칸씩 진행, 그냥 엔터치면 0으로 입력함.)
def readSudoku() -> list:
    res = []
    tmp = []
    for i in range(9):
        for j in range(9):
            n = input(f"{i + 1}x{j + 1}: ")
            if not n:
                n = "0"
            tmp.append(int(n))
        res.append(tmp)
        tmp = []
    return res

# 보드 입력함수(섹터단위): 공백은 빈칸이며, 마지막까지 입력안하면 입력부분 뒤 나머지 공백처리.
"""
1 2 3
4 5 6
7 8 9
순서로 구역별 입력. 구역과 구역내 요소들은 항상 좌측 상단순서로 시작한다.
"""
def readSudokuSector() -> list:  
    res = [[0 for _ in range(9)] for _ in range(9)]
    for sector in range(1, 10):
        sector_input = input(f"Enter numbers for sector {sector}: ")
        sector_values = []
        for char in sector_input:
            if char.isdigit(): sector_values.append(int(char))
            else: sector_values.append(0)
        if len(sector_values) < 9:
            for _ in range(9 - len(sector_values)): sector_values.append(0)
        if len(sector_values) > 9:
            print(f"Error: Sector {sector} must have exactly 9 values.")
            return res
        sector_coords = squareIdx[sector - 1]
        for idx, (row, col) in enumerate(sector_coords):
            res[row][col] = sector_values[idx]
    return res


#! TEST CASES.
# 빈칸 채워넣기만으로 해결가능한 문제
pz1 = [
    [5,3,0,0,7,0,0,0,0],
    [6,0,0,1,9,5,0,0,0],
    [0,9,8,0,0,0,0,6,0],
    [8,0,0,0,6,0,0,0,3],
    [4,0,0,8,0,3,0,0,1],
    [7,0,0,0,2,0,0,0,6],
    [0,6,0,0,0,0,2,8,0],
    [0,0,0,4,1,9,0,0,5],
    [0,0,0,0,8,0,0,7,9]]

# back tracking 없이는 해결 불가능한 문제
pz2 = [[9, 0, 0, 0, 8, 0, 0, 0, 1], 
       [0, 0, 0, 4, 0, 6, 0, 0, 0], 
       [0, 0, 5, 0, 7, 0, 3, 0, 0], 
       [0, 6, 0, 0, 0, 0, 0, 4, 0], 
       [4, 0, 1, 0, 6, 0, 5, 0, 8], 
       [0, 9, 0, 0, 0, 0, 0, 2, 0], 
       [0, 0, 7, 0, 3, 0, 2, 0, 0], 
       [0, 0, 0, 7, 0, 5, 0, 0, 0], 
       [1, 0, 0, 0, 4, 0, 0, 0, 7]]

# 모두 비어있는경우도 brute force로 해결할 수 있는지 점검.
pz3 = [[0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,0],]

# debug sample: bfsolve -1,-1 일 시 오류나던 반례.->OK
pz4 =  [            
    [0, 0, 0, 0, 1, 0, 0, 4, 7],
    [0, 0, 0, 0, 0, 0, 0, 0, 3],
    [5, 0, 7, 8, 0, 3, 0, 0, 0],
    [0, 0, 0, 9, 0, 2, 0, 5, 0],
    [0, 8, 0, 0, 0, 0, 0, 0, 0],
    [2, 7, 0, 5, 0, 0, 0, 8, 6],
    [0, 2, 0, 0, 5, 0, 0, 0, 0],
    [0, 0, 1, 0, 0, 6, 0, 7, 0],
    [3, 5, 0, 7, 0, 0, 4, 9, 0],
]


# bad cases. 잘못된 스도쿠. 오류출력하도록 유도하는 예제들
badpz1 = [[0,0,0,0],
       [0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,0],]

badpz2 = [[1,1,1,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,0],
       [0,0,0,0,0,0,0,0,0],]


# 일반 테스트케이스(모두 0으로 채워도 brute-force) -> OK
# prettyPrintSudoku(solve(pz1))
# prettyPrintSudoku(solve(pz2))
# prettyPrintSudoku(solve(pz3))
prettyPrintSudoku(solve(pz4))

# 오류 테스트케이스; ERR: Something Wrong. 출력 -> OK
# prettyPrintSudoku(solve(badpz1))
# prettyPrintSudoku(solve(badpz2))


#! 사용자입력 자동풀이 -> OK
# prettyPrintSudoku(solve(readSudoku())         # 한칸씩 진행.
# prettyPrintSudoku(solve(readSudokuSector()))  # 섹터단위 진행.


#! 현재 코드 작성 초기단계에 적어두었던 설계 계획 메모.
# 모든 값이 정상 값인지 검토하는 함수 작성
# 가로, 세로, 사각형 모두 고려 기준 현재 좌표(x, y) 에 가능한 숫자들을 나열하는 함수 작성.
# 0인 좌표들의 리스트를 나열하는 함수작성
# 위의 결과를 토대로 먼저 해결되어야 할 우선순위(가능성이 1개밖에 없음) 해결.


# 해결이 되지 않고 무언가를 정해야 하는 경우: 
#       그 시점의 값들을 저장하여, 임의선택 후 해결이 되는지. (이것은 직전의 결과를 다시 불러오는식으로 진행)

