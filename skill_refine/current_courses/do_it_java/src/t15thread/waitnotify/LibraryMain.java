package t15thread.waitnotify;

//! 큰 맥락: 동시에 많은 트랜젝션 발생시 대기 태움.

//! 작은 요약:
// 자원(책) 은 3개뿐인데, 6개의 쓰레드에서 사용할 경우, wait으로 대기태우고
// notify (notifyAll) 로 다시 깨워 사용 가능.
// Library는 공유객체, Student는 각각의 쓰레드로 사용됨.


// 참고사항
// notify, wait, sleep 등은 예외처리 없이 사용이 불가능하여 코드가 좀 지저분해 보이긴 하나,
// 예외처리 없다고 생각하면 보기 편함 (try 문만 해석)

// notify, wait, notifyAll 은 Thread 가 아닌 Object 클래스의 메서드임

import java.util.ArrayList;

class Library {
    private ArrayList<String> shelf = new ArrayList<>();

    public Library() {
        shelf.add("태백산맥 1");
        shelf.add("태백산맥 2");
        shelf.add("태백산맥 3");
    }

    // 빌리고 반납하는데 꼬일수 있으니 syncronized 키워드 사용
    public synchronized String lendBook() throws InterruptedException {
        Thread t = Thread.currentThread();

        //! 책이 없는경우 쓰레드 대기
        while (shelf.isEmpty()) {
            System.out.println(t.getName() + " waitting start");
            wait();
            System.out.println(t.getName() + " waitting end");
        }

        String book = shelf.removeFirst();  // 맨앞 책만 빌리는 시나리오.
        // 이 쓰레드에서 책을 빌렸다 출력
        System.out.println(t.getName() + ":" + book + " lend");
        return book;
    }

    public synchronized void returnBook(String book) {
        Thread t = Thread.currentThread();
        shelf.add(book);
        //! 쓰레드를 모두 깨움.(java에선 가능한 쓰레드 모두 깨우는것을 권장)
        notifyAll();    // 영원히 안깨어나는 쓰레드가 있을 수 있으므로 notify 대신사용
        // 이 쓰레드에서 반납했다 출력
        System.out.println(t.getName() + ":" + book + " return");
    }
}

class Student extends Thread {
    public void run() {
        // 5초동안 빌린다는 시나리오: sleep idea 자동생성 catch에 반납 메서드 추가
        try {
            // 이전에 title은 분리되었으나, 하나의 예외처리만 작성하려고 try문에 삽입
            String title = LibraryMain.library.lendBook();
            Thread.sleep(5000); // 5초간 읽고
            LibraryMain.library.returnBook(title); // 반납
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

    }
}

public class LibraryMain {
    // 공유객체 생성(각 Student 객체들이 사용)
    public static Library library = new Library();

    public static void main(String[] args) {
        Student std1 = new Student();
        Student std2 = new Student();
        Student std3 = new Student();
        Student std4 = new Student();
        Student std5 = new Student();
        Student std6 = new Student();
        std1.start();
        std2.start();
        std3.start();
        std4.start();
        std5.start();
        std6.start();
    }
}
