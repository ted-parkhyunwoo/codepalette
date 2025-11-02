package training.learning.T12_modifiers;

// 접근제한자에 대한 서술은 ModifierClass2에서 설명한다. (상속시 접근제한자 사용에 대한 서술이 추가됨.)

class ModifireClass {
    public int test = 1;
    protected int test2 = 2;
    int test4 = 4;
    public void printHey() { System.out.println("Hey"); }

    // 캡슐화 테스트(test3의 정보은닉 : 데이터 직접 접근 막기- 메서드를 통해서만 입출력 가능하도록)
    private int test3 = 3;
    public void printTest() { System.out.println(test3); }
}

