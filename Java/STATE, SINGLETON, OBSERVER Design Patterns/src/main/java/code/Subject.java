package hw1;

public interface Subject {
	// TODO HW1 P3
	public void attach(Observer o);
	public void detach(Observer o);
	public void notifyObservers(Subject o, String source, String destination);
}
