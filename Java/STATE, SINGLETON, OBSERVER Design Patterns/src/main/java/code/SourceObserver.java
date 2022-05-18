package hw1;
import java.util.HashMap;

// TODO HW1 P3

public class SourceObserver implements Observer {
	private String name;
	private HashMap<Subject, String> subjectToPastStateName = new HashMap<>();
	
	public SourceObserver(String n) {
		// TODO?
		this.name = n;
	}

	//stores state details in the hashmap to check if State is UNOBSERVED
	@Override
	public void update(Subject o, String source, String destination) {
		// TODO?
		if((subjectToPastStateName.containsValue(source) && subjectToPastStateName.containsKey(o))){
			LibraryLogger.getInstance().writeLine(this.toString() + " OBSERVED " + o.toString() + " LEAVING STATE: " + source);
			subjectToPastStateName.put(o, destination);
		}
		else {
			subjectToPastStateName.put(o, destination);
			LibraryLogger.getInstance().writeLine(this.toString() + " OBSERVED " + o.toString() + " LEAVING STATE: UNOBSERVED");
		}	
	}

	//returns the name of the observer
	@Override
	public String toString() {
		return name;
	}
}
