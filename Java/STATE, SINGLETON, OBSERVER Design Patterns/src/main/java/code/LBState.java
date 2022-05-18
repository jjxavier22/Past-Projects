package hw1;

// TODO HW1 P2
//State Interface used to implement specific states
public interface LBState 
{
    public void returnIt(LibraryBook book);
    public void shelf(LibraryBook book);
    public void extend(LibraryBook book);
    public void issue(LibraryBook book);
}
