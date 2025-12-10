public class MyIntArray {
    public static void main(String[] args) {
        int numbers[] = new int[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        IntArray t = new IntArray(numbers);
        t.print();
        t.set(0, 0);
        t.print();

        System.out.println(t.get(9));

        System.out.println(t.set(0, 1));
        t.print();

        System.out.println(t.toString());

        t.insert(1, 999);
        t.print();
        t.insert(1, 888);
        t.print();
 

        t.remove(1);
        t.remove(1);
        t.print();
        t.remove(9);
        t.remove(0);
        t.print();


        System.out.println("------");

        IntArray t2 = new IntArray(10);
        t2.insert(0, 1);
        t2.print();
        t2.remove(0);

        for (int i = 0; i < t2.size(); ++i) 
            t2.set(i, i +1);
        
        t2.print();

    }
}





class IntArray {
    private int[]       array;              // 기반은 전통배열
    private int         size;               // array.length와는 다르게 작동하는 size
    final boolean       holdSize;           // size로 초기화 하면 절대 insert, remove 할 수 없도록 하는 boolean

    public IntArray() { this.holdSize = false; }

    // 이 생성자는 굳이 size를 넣었으므로, 캐파를 고정한다. (여분 메모리 할당하지 않는 효과)
    public IntArray(int size) {
        array =         new int[size];
        this.size =     size;
        this.holdSize = true;
    }

    // 직접 캐퍼 고정 혹은 동적크기 지정도 가능
    public IntArray(int size, boolean capafree) {
        array =         new int[size];
        this.size =     size;
        this.holdSize = !capafree;
    }

    // 전통배열로 초기화.
    public IntArray(int arr[]) {
        this.holdSize = false;
        this.initArray(arr);
    }

    // 복사생성자.(캐파까지 복사하진 않음. size / 5만큼만 추가)
    public IntArray(IntArray other) {
        this.size =     other.size;
        this.holdSize = other.holdSize;
        this.array =    new int[size + (int)(size) / 5];
        System.arraycopy(other.array, 0, this.array, 0, size);
    }

    // 전통배열의 깊은 복사로 수동 초기화 가능.
    public void initArray(int[] arr) {
        this.size =     arr.length;
        this.array =    new int[size + (int)(size / 5)];
        System.arraycopy(arr, 0, this.array, 0, size);
    }


    // size getter
    public int size()   { return this.size; }

    // void print array.
    public void print() { System.out.println(this.toString()); }


    public void insert(int idx, int val) {
        if (this.holdSize || idx > this.size || idx < 0) {
            System.out.println("삽입불가");
            return;
        }

        // 실질적인 길이 여유분이 있다면 새로 할당할 필요 없음
        if (this.array.length > this.size) {
            System.arraycopy(this.array, idx, this.array, idx + 1, this.size - idx);
            this.array[idx] = val;
            this.size++;
            return;
        }
        
        // 실질적 배열 여유분 없는 경우 size / 5 만큼 크기 재할당
        int newCapa = this.size + this.size / 5;            // size가 혹시 1도 안늘어날 수 있으니 조건검사후 최소 1이라도 강제증가
        if (newCapa == this.size)
            newCapa++;
        int buffer[] =  new int[newCapa];
        System.arraycopy(this.array, 0, buffer, 0, idx);
        buffer[idx] =   val;
        System.arraycopy(this.array, idx, buffer, idx + 1, this.size - idx);
        this.size++;
        this.array =    buffer;
    }

    // idx 요소를 삭제하되, 리턴함.
    public int remove(int idx) {
        if (this.holdSize || idx < 0 || idx >= this.size) {
            System.out.println("삭제불가");
            return 0;
        }
        
        int bf = this.array[idx];
        System.arraycopy(this.array, idx + 1, this.array, idx, this.size - idx - 1);
        this.array[size - 1] = 0;
        this.size--;
        //TODO 용량 축소 로직 추가 예정
        return bf;
    }

    //TODO remove from start to end 로 범위삭제 기능 추가 예정


    public int get(int idx) {
        if (idx < this.size && idx >= 0)
            return this.array[idx];
        else
            System.out.println("index error");
            return 0;
    }

    public int set(int idx, int val) {
        if (idx < this.size && idx >= 0)
            return this.array[idx] = val;
        else
            System.out.println("index error");
            return 0;
    }


    @Override
    public String toString() {
        String res = "{ ";
        if (this.size > 0) {
            res += this.get(0);
            for (int i = 1; i < this.size; ++i) 
                res += ", " + String.valueOf(this.get(i));
        }
        res += " }";
        return res;
    }
}
