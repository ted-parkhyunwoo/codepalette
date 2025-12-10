package t06arraylist;

import java.util.ArrayList;

public class ArrayListTest {
    public static void main(String[] args) {
        // boolean add(E e) 요소 하나를 추가
        // int size() 전채 갯수 반환
        // E get(int idx) 해당인덱스 값 반환
        // E remove(int idx) 삭제후 삭제값 반환
        // Boolean isEmpty() 비어있는지

        ArrayList<Book> booksArrayList = new ArrayList<>();
        booksArrayList.add(new Book("태백산맥", "조정래"));
        booksArrayList.add(new Book("데미안", "헤르만 헤세"));
        booksArrayList.add(new Book("개미", "베르나르베르베르"));

        for (int i = 0; i < booksArrayList.size(); ++i)
            booksArrayList.get(i).showBookInfo();


        for (Book book : booksArrayList)
            book.showBookInfo();
    }
}
