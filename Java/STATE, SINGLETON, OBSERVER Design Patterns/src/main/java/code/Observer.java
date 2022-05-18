package hw1;

//interface that serves as the base for the two types of observers
public interface Observer {
	public void update(Subject o, String source, String destination);
}
