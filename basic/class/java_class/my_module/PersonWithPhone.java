package java_class.my_module;

import java.util.ArrayList;

public class PersonWithPhone extends Person implements PersonInterface {
    private String Phone;

    public PersonWithPhone() {
        super();
        Phone = "000-0000-0000";
    }
    public PersonWithPhone(String name, int age, String Phone) {
        super(name, age);
        this.Phone = Phone;
    }

    @Override
    public void setInfo(String name, int age) {
        super.setInfo(name, age);
    }

    public void setInfo(String name, int age, String Phone) {
        super.setInfo(name, age);
        this.Phone = Phone;
    }

    public ArrayList<Object> getInfo() {
        ArrayList<Object> res = new ArrayList<>();
        res.add(super.getName());
        res.add(super.getAge());
        res.add(this.Phone);
        return res;
    }

    @Override
    public String toString() {
        return super.toString() + ", phone: " + this.Phone;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj.getClass().getName().equals(this.getClass().getName())) {
            PersonWithPhone o = (PersonWithPhone) obj;

            if ( this == obj ||
                    ( 
                        (o != null && this != null) && 
                        o.getName() == this.getName()  &&
                        o.getAge() == this.getAge() &&
                        o.Phone == this.Phone
                    ) 
                ) return true;
        }
        return false;
    }
        
}
