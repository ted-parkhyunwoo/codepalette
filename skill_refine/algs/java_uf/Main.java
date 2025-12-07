package java_uf;
import java.util.List;
import java.util.ArrayList;


public class Main {
    public static <T> void print(T t) { System.out.println(t); }

    public static void main(String[] args) {
        //! 나잇대별로 union 하여 친구를 맺음. .age()호출해야함.   여기서 말하는 친구는 다 연결된 친구.
        // 필요시 조건에 따라 age 말고도 x살 차이, 성별 등으로 변경도 고려.
        // UF는 기본 뼈대, User는 데이터클래스.
        // UserUF 는 두개를 연결지음.
        
        // 1. List<Ovject>  {"이름", 나이:int} 형식으로 저장됨. User 객체는 리스트로 초기화 가능, 혹은 직접 User("이름", 나이:int) 로 초기화
        List<Object> ted = new ArrayList<>();
        ted.add("ted"); ted.add(32);
        List<Object> tom = new ArrayList<>();
        tom.add("tom"); tom.add(38);
        List<Object> sally = new ArrayList<>();
        sally.add("sally"); sally.add(27);


        // 2. 전체 13개의 데이터를 담을 User 배열 생성
        User users[] = new User[13];
        users[0] = new User(ted);
        users[1] = new User(tom);
        users[2] = new User(sally);
        users[3] = new User("mike", 45);
        users[4] = new User("lisa", 19);
        users[5] = new User("jack", 20);
        users[6] = new User("jane", 51);
        users[7] = new User("chris", 35);
        users[8] = new User("anna", 30);
        users[9] = new User("leo", 68);
        users[10] = new User("ruby", 40);
        users[11] = new User("peter", 22);
        users[12] = new User("elsa", 59);

        
        UserUF data = new UserUF(users);
        print(data);
        data.age();
        print(data);

        data.printFriends(users[0]);

        // 객체별 친구인지 boolean 리턴.
        print(data.isFriend(users[0], users[1]));

    }
}
