package hw1;

public class BadOperationException extends Exception {
    // TODO HW1 P2
    
    //Logs the Bad Operation that was attempted
    public static void throwException(String action, String state) 
    {
        LibraryLogger.getInstance().writeLine("BadOperationException - Can't use " + action + " in " + state +" state");
    }
}
