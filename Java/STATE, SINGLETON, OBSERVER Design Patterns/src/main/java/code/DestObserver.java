package hw1;
import java.util.HashMap;

// TODO HW1 P3

public class DestObserver implements Observer {
	private String name;
	
	//sets the name passed in
	public DestObserver(String n) {
		// TODO?
		this.name = n;
	}

	//logs the destination state
	@Override
	public void update(Subject o, String source, String destination) {
		// TODO?
		LibraryLogger.getInstance().writeLine(this.toString() + " OBSERVED " + o.toString() + " REACHING STATE: " + destination);
	}

	//returns name of the observer
	@Override
	public String toString() {
		return name;
	}
}
