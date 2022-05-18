import java.io.*;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.concurrent.TimeUnit;
import java.time.LocalTime;

class TM {
    public static void main(String[] args) {

        if(args.length < 1){
            BadOperationException.throwDefaultException();
        }
        else if (args[0].equals("describe") && args.length == 3){
            userOptions.describe(args);
        }
        else if (args.length > 2){
            BadOperationException.throwDefaultException();
        }
        else if (args[0].equals("start") && args.length == 2){
            userOptions.start(args);
        }
        else if (args[0].equals("stop") && args.length == 2){
            userOptions.stop(args);
        }
        else if (args[0].equals("summary") && args.length == 2){
            userOptions.singleSummary(args);
        }
        else if (args[0].equals("summary") && args.length == 1){
            userOptions.fullSummary(args);   
        }
        else {
            BadOperationException.throwDefaultException();
        }
    }
}




public class userOptions {
    private static ArrayList<Task> listOfTasks = new ArrayList<>();

    public static void start(String[] args){
        if(persistentStore.doesStorageFileExist() && tasksList.getTask(args[1]) != null){
            Task currentTask = tasksList.getTask(args[1]);
            currentTask.setNewStartTime();
            listOfTasks = tasksList.updateTaskList(persistentStore.getAllTasks(), currentTask);

        }
        else {
            Task newTask = new Task(args[1]);
            if(persistentStore.doesStorageFileExist()){
                listOfTasks = persistentStore.getAllTasks();
            }
            listOfTasks.add(newTask);
            persistentStore.storeObject(listOfTasks); 
        }
    }

    public static void stop(String[] args){
        if(!persistentStore.doesStorageFileExist()){
            BadOperationException.throwNoTaskError();
            BadOperationException.throwDefaultException();
        }
        else if(tasksList.getTask(args[1]) == null){
            BadOperationException.throwNoTaskError();
            BadOperationException.throwDefaultException();
        }
        else {
            long endTime = System.currentTimeMillis() / 1000;
            Task currentTask = tasksList.getTask(args[1]);
            currentTask.setDuration(endTime);
            listOfTasks = tasksList.updateTaskList(persistentStore.getAllTasks(), currentTask);
            persistentStore.storeObject(listOfTasks); 
        }
    }

    public static void describe(String[] args){
        if(!persistentStore.doesStorageFileExist()){
            BadOperationException.throwNoTaskError();
            BadOperationException.throwDefaultException();
        }
        else if(tasksList.getTask(args[1]) == null){
            BadOperationException.throwNoTaskError();
            BadOperationException.throwDefaultException();
        }
        else {
            Task currentTask = tasksList.getTask(args[1]);
            currentTask.setDescription(args[2]);
            listOfTasks = tasksList.updateTaskList(persistentStore.getAllTasks(), currentTask);
            persistentStore.storeObject(listOfTasks); 
        }
    }

    public static void singleSummary(String[] args){
        if(!persistentStore.doesStorageFileExist()){
            BadOperationException.throwNoTasksStarted();
        }
        else if(tasksList.getTask(args[1]) == null){
            BadOperationException.throwNoTaskError();
            BadOperationException.throwDefaultException();
        }
        else {
            Task currentTask = tasksList.getTask(args[1]);
            currentTask.printSummary();
        }
        
    }

    public static void fullSummary(String[] args){
        if(!persistentStore.doesStorageFileExist()){
            BadOperationException.throwNoTasksStarted();
        }
        long totalTime = 0;
        listOfTasks = persistentStore.getAllTasks();
        for(int i=0; i < listOfTasks.size(); i++){
            listOfTasks.get(i).printSummary();
            totalTime += listOfTasks.get(i).endTime;
        }
        LocalTime timeOfDay = LocalTime.ofSecondOfDay(totalTime);
        String time = timeOfDay.toString();
        System.out.println("Total time spent on all tasks: " + time);
    }
}




public class Task implements Serializable {
    String taskName;
    long beginingTime;
    String description;
    long endTime;

    public Task(String taskName){
        this.taskName = taskName;
        this.beginingTime = System.currentTimeMillis() / 1000;
        this.endTime = 0;
    }

    public void setDescription(String description){
        this.description = description;
    }

    public void setDuration(long endTime){
        this.endTime += (endTime - beginingTime);
    }

    public void setNewStartTime(){
        long newStartTime = System.currentTimeMillis() / 1000;
        if(endTime == 0){
            endTime = newStartTime - beginingTime;
        }
        this.beginingTime = newStartTime; 
    }

    public void printSummary(){
        System.out.println("Summary for task     : " + taskName);
        System.out.println("Description          : " + description);
        LocalTime timeOfDay = LocalTime.ofSecondOfDay(endTime);
        String time = timeOfDay.toString();
        System.out.println("Total time on task   : " + time + "\n");
    }
}




public class persistentStore{
    public static void clear()
    {
        try
        {
            new FileOutputStream("Log.txt").close();
        }
        catch (Exception exception)
        {
            System.out.println(exception);
        }

    }

    public static boolean doesStorageFileExist(){
        File fileName = new File("Log.txt");
        boolean fileExists = fileName.exists();
        return fileExists;
    }

    public static void storeObject(ArrayList<Task> listOfTasks) 
    {
        File fileName = new File("Log.txt");
        try
        {
            FileOutputStream fileOutputStream = new FileOutputStream(fileName);
            ObjectOutputStream objectOutputStream = new ObjectOutputStream(fileOutputStream);
            objectOutputStream.writeObject(listOfTasks);
            objectOutputStream.flush();
            objectOutputStream.close();
        }
        catch (Exception exception)
        {
            System.out.println(exception);
        }

    }

    public static ArrayList<Task> getAllTasks() 
    {
        ArrayList<Task> pulledTasks = new ArrayList<>();
        try
        {
            FileInputStream fis = new FileInputStream("Log.txt");
            ObjectInputStream ois = new ObjectInputStream(fis); 
            pulledTasks = (ArrayList<Task>)ois.readObject();    
        }
        catch (Exception exception)
        {
            exception.printStackTrace(); 
        }
        return pulledTasks;
    }

}




public class tasksList {

    public static Task getTask(String taskName){
        ArrayList<Task> listOfAllExisitingTasks = new ArrayList<Task>();
        listOfAllExisitingTasks = persistentStore.getAllTasks();
        
        for(int i=0; i<listOfAllExisitingTasks.size(); i++) {
            if(listOfAllExisitingTasks.get(i).taskName.equals(taskName)){
                return listOfAllExisitingTasks.get(i);
            }
        }
        return null;
    }

    public static ArrayList<Task> updateTaskList(ArrayList<Task> oldList, Task updatedTask){
        for(int i=0; i < oldList.size(); i++){
            if(updatedTask.taskName.equals(oldList.get(i).taskName)){
                oldList.remove(i);
            }
        }
        oldList.add(updatedTask);
        return oldList;
    }

}




public class BadOperationException extends Exception {
    
    public static void throwDefaultException() 
    {
        System.out.println("Usage:");
        System.out.println("\t TM start <task name>  |"); 
        System.out.println("\t TM stop <task name> |");
        System.out.println("\t TM describe <task name> <task description in quotes> |");
        System.out.println("\t TM summary <task name> |");
        System.out.println("\t TM summary");
    }

    public static void throwNoTaskError() 
    {
        System.out.println("No such task exists.");
    }

    public static void throwNoTasksStarted() 
    {
        System.out.println("No tasks have been started.");
    }

}

