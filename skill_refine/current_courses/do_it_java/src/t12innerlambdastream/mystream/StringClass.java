package t12innerlambdastream.mystream;

public class StringClass {
    private String str;
    public StringClass(String str) { this.str = str; }

    protected String getStr() { return (this.str == null)? "" : this.str; }
    protected void setStr(String str) { this.str = str; }

    @Override
    public String toString() { return getStr(); }

    @Override
    public boolean equals(Object other) {
        if (this == other) return true;
        if (other instanceof StringClass bf) { return getStr().equals(bf.str); }
        return false;
    }

    @Override
    public int hashCode() { return getStr().hashCode(); }

    public StringClass toUpper() {
        char[] chars = str.toCharArray();
        for (int i = 0; i < chars.length; ++i) {
            if (chars[i] >= 'a' && chars[i] <= 'z') {
                chars[i] = (char) (chars[i] - ('a' - 'A'));
            }
        }
        setStr(new String(chars));
        return this;
    }

    public StringClass toLower() {
        char[] chars = str.toCharArray();
        for (int i = 0; i < chars.length; ++i) {
            if (chars[i] >= 'A' && chars[i] <= 'Z') {
                chars[i] = (char) (chars[i] + ('a' - 'A'));
            }
        }
        setStr(new String(chars));
        return this;
    }


}
