package t12innerlambdastream.stream;

import java.util.ArrayList;
import java.util.List;

public class IqInfoTest {
    public static void main(String[] args) {
        List<IqInfo> list = new ArrayList<>();

        list.add(new IqInfo("이씨", 114, 37));
        list.add(new IqInfo("박씨", 124, 29));
        list.add(new IqInfo("김씨", 110, 32));
        list.add(new IqInfo("박씨", 90, 36));
        list.add(new IqInfo("이씨", 105, 47));
        list.add(new IqInfo("권씨", 85, 24));


        // 이름이 박씨인 사람만 출력
        list.stream().filter(a -> a.getName().equals("박씨")).forEach(System.out::println);

        // 나이가 35세 이상인 경우만 iq를 정수로 맵핑하여 정렬하고 IQ만 format스타일로 출력
        list.stream().filter(a -> a.getAge() >= 35).mapToInt(IqInfo::getIq).sorted().forEach(iq -> System.out.printf("IQ: %d\n", iq));

        // +@위의 경우를 내림차순으로 할 경우.
        list.stream().filter(a -> a.getAge() >= 35).mapToInt(IqInfo::getIq).boxed().sorted((a, b)-> b - a).forEach(iq -> System.out.printf("IQ: %d\n", iq));


        // 이씨인 사람이면서 iq가 100이 넘는 사람만 리스트로 재 저장
        List<IqInfo> result = list.stream().filter(e -> e.getName().equals("이씨") && e.getIq() > 100).toList();
        System.out.println(result);

        // 모든사람의 iq 에서 100을 뺀 값을 Integer리스트로 저장
        List<Integer> result2 = list.stream().map(e -> e.getIq() - 100).toList();
        System.out.println(result2);

    }
}
