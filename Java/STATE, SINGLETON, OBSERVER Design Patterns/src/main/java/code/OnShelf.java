package hw1;
// TODO HW1 P2

public class OnShelf implements LBState {
    //Singleton
    private static OnShelf instance = new OnShelf();
 
    private OnShelf() {}
 
    public static OnShelf getInstance() {
        return instance;
    }

    //invalid state change
    @Override
    public void returnIt(LibraryBook book) 
    {
        BadOperationException.throwException("returnIt", this.toString());
    }

    //invalid state change
    @Override
    public void shelf(LibraryBook book) 
    {
        BadOperationException.throwException("shelf", this.toString());
    }

    //invalid state change
    @Override
    public void extend(LibraryBook book) 
    {
        BadOperationException.throwException("extend", this.toString());
    }

    //succesful change of states, inform all observers
    @Override
    public void issue(LibraryBook book) 
    {
        LibraryLogger.getInstance().writeLine("Leaving State OnShelf for State Borrowed");
        book.notifyObservers(book, "OnShelf", "Borrowed");
        book.setCurrentState(Borrowed.getInstance());
    }

    //returns name of the state
    public String toString(){
        return "OnShelf";
    }
}