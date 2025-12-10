package t06arraylist;

public class ArrayTest {
    public static void main(String[] args) {

        // 정수배열
        int numbers[] = new int[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        for (int i = 0; i < 10; ++i)
            System.out.printf("%d ", numbers[i]);
        System.out.println();


        // 문자배열
        char[] alphabets = new char[26];
        char ch = 'A';

        for (int i = 0; i < alphabets.length; ++i, ++ch)
            alphabets[i] = ch;

        for (int i = 0; i < alphabets.length; ++i)
            System.out.printf("%c", alphabets[i]);
        System.out.println();


        // 2차원배열
        int arr[][] = {{1,2,3}, {4, 5, 6}, {7, 8}, {9}};

        for (int i = 0; i < arr.length; ++i) {
            for (int j = 0; j < arr[i].length; ++j)
                System.out.printf("%d ", arr[i][j]);
            System.out.println();
        }
        System.out.println();


        // 객체배열 (Book 클래스 작성한것을 사용)
        Book books[] = new Book[3];
        books[0] = new Book("태백산맥", "조정래");
        books[1] = new Book("데미안", "헤르만 헤세");
        books[2] = new Book("개미", "베르나르베르베르");

        for (int i = 0; i < books.length; ++i)
            books[i].showBookInfo();

        System.out.println("--------");


        // 배열복사(shallowCopy) (원본, 원본시작idx, 대상, 대상시작idx, 복사요소갯수)
        Book books2[] = new Book[5];
        books2[0] = new Book("a", "a");
        System.arraycopy(books, 0, books2, 1, 3);
        books2[4] = new Book("c", "c");

        // 원본변경했는데도 사본이 바뀜: 참조자료형이라 shallow copy라는 증거.(주소값이 복사)
        books[0].setBookName("나목");
        books[0].setAuthor("박완서");

        for (int i = 0; i < books2.length; ++i)
            books2[i].showBookInfo();

        System.out.println("--------");


        // deep copy
        Book books3[] = new Book[books.length];
        for (int i = 0; i < books3.length; ++i)
            books3[i] = new Book(books[i]);     // 객체를 받아 깊은복사하는 생성자 만듬.

        books[0].setBookName("태백산맥");       // 원본을 수정해도 book3는 이제 안바뀜
        books[0].setAuthor("조정래");
        // advanced for:
        for (Book b : books3)
            b.showBookInfo();

    }
}

