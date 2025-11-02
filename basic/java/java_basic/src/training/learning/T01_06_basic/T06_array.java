package training.learning.T01_06_basic;

import java.util.Arrays;

public class T06_array {

    // +@. 배열요소출력함수. 사실상 매개변수는 참조자료형과 idx가 아닌
    // 기본자료형 하나여도 상관없는상태임..
    static void printElement(int[] arr, int idx) {
        System.out.println(arr[idx]);
    }

    public static void main(String[] args) {

        // 가능하면 선언과 대입(할당)을 동시에 할 것
        // 선언만 할 경우 랜덤한 할당공간을 포인팅만 한 상태로 추측.
        // 만약 할당공간이 모자라다면 넉넉한 공간에 재할당후 포인팅 변경하는 구조로 보임.

        // 다양한 배열선언과 할당방법.
        int[] arr;          //??? 할당만 해도 문제없는 코드...
        arr = new int[3];        // java스타일.
        int arr2[] = {1, 2, 3};    // c스타일.
        char arr3[] = new char[] {'A', 'B', 'C'};


        // 반복문에서의 활용
        // 조건식의 length는 size()나 length();cpp에서의.
        for (int i = 0; i < arr.length; ++i) {
            arr[i] = i + 1;

            // 형변환; type참고.
            if (i == 2) {
                arr[i] = 'A';
                System.out.println((char)arr[i]);
            } else
                System.out.println(arr[i]);

            // +@. 함수 사용해보기.
            printElement(arr2, i);
        }

        // advancded for문 : 공식명칭은 enhanced for loop.
        // cpp 에서는 range-based(범위기반) for loop 로 불림.
        // 두 언어 다 통틀어 for-each 반복문이라고도 함
        for (char c: arr3) {
            System.out.println(c);
        }


        // 배열 자체 출력(문자열전환): Arrays.toString 활용.
        System.out.println("배열출력:" + Arrays.toString(arr3));


        // 정적배열의 크기 재할당(사실상 복사)
        System.out.println("배열복사:");
        int arr4[] = new int[5];
        for(int i = 0; i < 3; ++i) {
            arr4[i] = arr2[i];
        }
        arr4[3] = 4;
        arr4[4] = 5;
        System.out.println(Arrays.toString(arr4));

        // 배열복사 기본 제공 API활용시 (System.arraycopy())
        int arr5[] = new int[5];
        // 원본, 원본시작점, 복사본, 복사본시작점, 원본의 복사할 길이
        System.arraycopy(arr2, 0, arr5, 0, arr2.length);
        arr5[3] = 4;
        arr5[4] = 5;
        System.out.println(Arrays.toString(arr5));


        // 2차원배열
        System.out.println("2차원배열: ");
        int sz = 5;
        int[][] big = new int[sz][];
        // int big[][] = new int[sz][];
        // int[] big[] = new int[sz][];     // 별 방법으로 다 됨.
        for (int i = 0; i < big.length; ++i) {
            big[i] = new int[sz];
            for (int j = 0; j < big[i].length; ++j) {
                big[i][j] = i + j;
            }
            System.out.println(Arrays.toString(big[i]));
        }
        // 2차원배열 자체출력: 참조자료형이 출력됨(객체)
        System.out.println("2차원배열자체출력: "+Arrays.toString(big));

    }
}
