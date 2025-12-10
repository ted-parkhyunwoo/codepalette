package t06arraylist;

public class Book {
    private String bookName;
    private String author;

    public Book(){}
    public Book(String bookName, String author) {
        this.bookName = bookName;
        this.author = author;
    }

    // 개인적으로 추가한 내용. 딥카피용.
    public Book(Book obj) {
        this.bookName = obj.getBookName();
        this.author = obj.getAuthor();
    }

    public String getBookName() { return bookName; }
    public void setBookName(String bookName) { this.bookName = bookName; }
    public String getAuthor() { return author; }
    public void setAuthor(String author) { this.author = author; }

    public void showBookInfo() { System.out.println(bookName + ", " + author); }
}