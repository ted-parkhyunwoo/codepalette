package src.string;
class string{
    public static void main(String[] args) {
        String test = "HEllo WoRlD";
        int length = test.length();                         // 길이 반환
        String Upper = test.toUpperCase();                  // 전체 대문자
        String Lower = test.toLowerCase();                  // 전체 소문자
        boolean isContainWorld = test.contains("WoRlD");    //  포함여부
        boolean isNotContainJava = !test.contains("Java");
        int WorldIdx = test.indexOf("WoRlD");               // 해당문자열 시작인덱스 찾기
        int lastO = test.lastIndexOf("o");                  // 해당문자열 마지막인덱스 찾기
        int lastLL = test.lastIndexOf("ll");
        int lastTest = test.lastIndexOf("Test");            // 없는 문자열 인덱스 찾기: -1


        // std::stringstream 처럼 작동하는 StringBuilder. append와 동시에 String이 연결되기 때문에, list처럼 append된 요소를 다시 꺼낼 순 없다.
        StringBuilder sb = new StringBuilder();
        sb.append("String test: " + test + '\n');
        sb.append("length():" + length + '\n');
        sb.append("toUperCase(): " + Upper + '\n') ;
        sb.append("toLowerCase(): " + Lower + '\n');
        sb.append("contains(\"WoRlD\"): " + isContainWorld + '\n');
        sb.append("!contains(\"Java\"): " + isNotContainJava + '\n');
        sb.append("indoxOf(\"WoRlD\"): " + WorldIdx + '\n');
        sb.append("lastIndexOf(\"o\"):" + lastO + '\n');
        sb.append("lastIndexOf(\"ll\"): " + lastLL + '\n');
        sb.append("lastIndexOf(\"Test\"): " + lastTest + '\n');         // -1
        sb.append("String 멤버메서드 실험 종료\n\n");
        System.out.println(sb);
        sb.delete(0, sb.length());

        String test2 = "I like Java";
        boolean startWithILike = test2.startsWith("I Like");    // 이 문자열로 시작하는지
        boolean endWithDot = test2.endsWith(".");               // 이 문자열로 끝나는지
        String LikeToLove = test2.replace("like", "love");      // 직접 바꾸진 못함.
        String subSeven = test2.substring(7);                   // 7번부터 끝까지 슬라이싱
        String subOneToFour = test2.substring(1, 4);            // 1포함 1 부터 4직전(3까지)
        String TrimSubOneToFour = subOneToFour.trim();          // 앞뒤 공백 제거
        String ConCatKE = TrimSubOneToFour.concat("ke");        // 문자열 결합
        
        sb.append("String test2: " + test2 + '\n');
        sb.append("startsWith(\"I Like\"): " + startWithILike + '\n');
        sb.append("endsWith(\".\"): " + endWithDot + '\n'); 
        sb.append("replace(\"like\", \"love\"): " + LikeToLove + '\n');
        sb.append("substring(7): " + subSeven + '\n');
        sb.append("substring(1, 4): " + subOneToFour + '\n');
        sb.append("trim(): " + TrimSubOneToFour + '\n');
        sb.append("concat(\"ke\"): " + ConCatKE + '\n');
        sb.append("String 멤버메서드 실험 종료\n");
        System.out.println(sb);

        String specialChars = "\t탭 \n줄바꿈 \\ 역슬래시 \"쌍따옴표\' 홑따옴표";
        System.out.println(specialChars);
        // 역슬래시는 하나씩 더 붙여줘야함. 따라서 쌍역슬래시를 표현하려면 4개 필요
        String specialChars2 = "\\n, \\t, \\\\, \\\" , \\\' ";
        System.out.println(specialChars2);
    }
}