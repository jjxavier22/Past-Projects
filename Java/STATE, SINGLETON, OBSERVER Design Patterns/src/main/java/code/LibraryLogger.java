package hw1;
import java.util.ArrayList;

public class LibraryLogger {
    //declares onlyInstance and intialize logList
    private static LibraryLogger onlyInstance;
    ArrayList<String> logList = new ArrayList<String>();

    public void writeLine(String line) {
        //add line to the array and writes line to standard out
        logList.add(line);
        System.out.println("LibraryLogger: " + line);
    }

    public String[] getWrittenLines() {
        //moves contents of ArrayList to a string[] to be returned
        String writtenLines[] = new String[logList.size()];              
		for(int i =0;i<logList.size();i++){
		  writtenLines[i] = logList.get(i);
		}
        return writtenLines;
    }

    public void clearWriteLog() {
        //clears logList
        logList.clear();
    }
    
    public static LibraryLogger getInstance() {
        //initalizes if no other instances exist
        if (onlyInstance == null)
            onlyInstance = new LibraryLogger();
            ExpensiveComputeToy.performExpensiveLogSetup();
        return onlyInstance;
    }
}
