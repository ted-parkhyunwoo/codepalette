# https://www.codewars.com/kata/541af676b589989aed0009e7/train/c

def find_unique_combinations_unlimited(arr, target):
    # results = [] # 최종 고유 조합들을 저장할 리스트
    res = [0]
    # 중복된 조합을 피하려면 배열을 정렬하는 것이 필수적
    arr.sort() 

    def backtrack(remaining_target, start_index, res):
        # 1. 종료 조건 
        if remaining_target == 0:
            # 합 0에 도달하면, 현재 조합을 결과에 추가
            # results.append(list(current_combination)) 
            res[0] += 1
            return
        
        if remaining_target < 0:
            # 목표를 초과하면 중단
            return

        # 2. 재귀 호출 (백트래킹)
        # start_index부터 시작하여 중복된 조합([2,3]과 [3,2])을 방지
        for i in range(start_index, len(arr)):
            num = arr[i]
            
            # 현재 숫자를 조합에 추가
            res[0] += 1
            
            # 재귀 호출: **i를 그대로 넘겨** 현재 숫자를 다음 단계에서 다시 선택할 수 있도록 허용 (무제한 사용)
            backtrack(remaining_target - num, i, res)
            
            # 백트래킹: 조합에서 현재 숫자를 제거하고 다음 숫자로 넘어감
            res[0] -= 1
            

    # 탐색 시작
    backtrack(target, 0, res)
    
    return res[0]

# 예시
arr = [2, 3, 5]
target_sum = 7

combinations = find_unique_combinations_unlimited(arr, target_sum)

print(f"대상 배열: {arr}")
print(f"목표 합: {target_sum}")
print("-" * 30)
print("찾은 모든 고유 조합:")
print(combinations)
# for combo in combinations:
#     print(f"  {combo}") 

# 출력:
# 찾은 모든 고유 조합:
#   [2, 2, 3] (2+2+3=7)
#   [2, 5]    (2+5=7)