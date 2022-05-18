package hw1;

// TODO HW1 P2
//Borrowed State
public class Borrowed implements LBState {
    //Singleton
    private static Borrowed instance = new Borrowed();
 
    private Borrowed() {}
 
    //Returns the instance
    public static Borrowed getInstance() {
        return instance;
    }

    //succesful change of states, inform all observers
    @Override
    public void returnIt(LibraryBook book) 
    {
        LibraryLogger.getInstance().writeLine("Leaving State Borrowed for State GotBack");
        book.notifyObservers(book, "Borrowed", "GotBack");
        book.setCurrentState(GotBack.getInstance());
    }

    //invalid state change
    @Override
    public void shelf(LibraryBook book) 
    {
        BadOperationException.throwException("shelf", this.toString());
    }

    //succesful change of states, inform all observers
    @Override
    public void extend(LibraryBook book) 
    {
        LibraryLogger.getInstance().writeLine("Leaving State Borrowed for State Borrowed");
        book.notifyObservers(book, "Borrowed", "Borrowed");
        book.setCurrentState(Borrowed.getInstance());
    }

    //invalid state change
    @Override
    public void issue(LibraryBook book) 
    {
        BadOperationException.throwException("issue", this.toString());
    }

    //name of the state
    public String toString(){
        return "Borrowed";
    }
}