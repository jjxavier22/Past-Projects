package hw1;
import java.util.ArrayList;
import java.util.List;
// TODO HW1 P2

public class LibraryBook implements Subject {
    //                   ^ uncomment for P3
    private List<Observer> listOfObservers = new ArrayList<>();
    private String name;
    private LBState currentState;
    private String src;
    private String dest;

    
    //initalizes ensuring SINGLETON Pattern and assigns the name attribute
    public LibraryBook(String name) {
        // TODO HW1 P2
        this.name = name;
        if(currentState == null) {
            this.currentState = OnShelf.getInstance();
        }
    }
    
    //returns current State
    public LBState getState() {
        // TODO?
        return currentState;
    }

    public void setCurrentState(LBState currentState) {
        this.currentState = currentState;
    }
    
    public void returnIt() {
        // TODO?
        currentState.returnIt(this);
    }
    
    public void shelf() {
        // TODO?
        currentState.shelf(this);
    }
    
    public void extend() {
        // TODO?
        currentState.extend(this);
    }
    
    public void issue() {
        // TODO?
        currentState.issue(this);
    }

    //attaches an observer ensuring they are not already attached
    @Override
    public void attach(Observer o) {
        if (listOfObservers.contains(o)) {
            LibraryLogger.getInstance().writeLine(o.toString() + " is already attached to " + this.toString());
        } else {
            listOfObservers.add(o);
            LibraryLogger.getInstance().writeLine(o.toString() + " is now watching " + this.toString());
        }
    }
    
    //detaches an observer who is already attached
    @Override
    public void detach(Observer o) {
        if(listOfObservers.contains(o)) {
            LibraryLogger.getInstance().writeLine(o.toString() + " is no longer watching " + this.toString());
        }
        listOfObservers.remove(o);
    }

    //lets the observers know a change in state
    @Override
    public void notifyObservers(Subject o, String source, String destination) {
        this.src = source;
        this.dest = destination;
        for(Observer observer: listOfObservers) {
            observer.update(o, source, destination);
        }
    }
    
    //returns name of the book
    @Override
    public String toString() {
        // TODO?
        return name;
    }

    public String getSource() {
        // TODO?
        return src;
    }

    public String getDest() {
        // TODO?
        return dest;
    }

}