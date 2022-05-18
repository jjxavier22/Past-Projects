package hw1;

// TODO HW1 P2
public class GotBack implements LBState {
    //Singleton
    private static GotBack instance = new GotBack();
 
    private GotBack() {}
 
    //returns the instance
    public static GotBack getInstance() {
        return instance;
    }

    //invalid state change
    @Override
    public void returnIt(LibraryBook book) 
    {
        BadOperationException.throwException("returnIt", this.toString());
    }

    //succesful change of states, inform all observers
    @Override
    public void shelf(LibraryBook book) 
    {
        LibraryLogger.getInstance().writeLine("Leaving State GotBack for State OnShelf");
        book.notifyObservers(book, "GotBack", "OnShelf");
        book.setCurrentState(OnShelf.getInstance());
    }

    //invalid state change
    @Override
    public void extend(LibraryBook book) 
    {
        BadOperationException.throwException("extend", this.toString());
    }

    //invalid state change
    @Override
    public void issue(LibraryBook book) 
    {
        BadOperationException.throwException("issue", this.toString());
    }

    //returns name of the state
    public String toString(){
        return "GotBack";
    }
}