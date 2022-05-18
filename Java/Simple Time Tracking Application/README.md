This application is designed to be a simple command-line time tracking application that allows users to monitor how much time they spend on a specific application. More specifically, how it works is the user indicates to the application that they have started a task by entering into the command line java TM.java start <task name>, this input assigns a name to the task and sets the start time of this particular task. This named task is now considered to be active. The user can terminate an active task by entering the command java TM.java stop <task name>, this terminates the task’s active status, and the time spent on the task is recorded and stored. Furthermore, the user has the ability to describe a named task by entering the command java TM.java describe <task name> <description>. It is important to note that the user can describe a task regardless of whether the task is active or not. Another implementation choice made for this application is in regards to returning to an existing task. While the prompt is not specific regarding this scenario, as a user, it would be useful for one to restart an existing task and the application to record the total time the user has spent on the particular task. Therefore, this time tracking application allows the user to restart existing tasks and know the total time spent on a particular task. This enables the application to be useful and applicable in the real world by servicing the real-world needs of users.
Finally, the user can see the time results of all their tasks by utilizing the summary feature. By entering java TM.java summary <task name>, the user is able to see the description of the particular named task, along with the description, if provided, and the time spent on that particular task. Additionally, the user can enter java TM.java summary to see the list of all tasks, their descriptions, and the total time spent on each task. Finally entering this command will also allow the users to see the total time spent on all tasks that have been provided to track by the application. As a student, I would use this application to see how much time I spend on services
Jiss Xavier 916427256 February 17th, 2022 ECS 160
such as Netflix, TikTok, and others. Seeing the individual times and total times can allow me to better understand how much time I consume with these different tasks. In terms, of things that could go wrong, it is important that the application is able to guide and be transparent with the user regarding what they can and can’t do. For example, if the user tries to stop a task that hasn’t been started the application will indicate such a task hasn’t been started yet. Similarly calling the summary feature before calling stop will print a summary of the task absent of the total time spent since the task has yet to be stopped. Input should be in the appropriate format and this will be indicated to the user in case they enter a command line input that is not valid. Now onto the possible implementation.