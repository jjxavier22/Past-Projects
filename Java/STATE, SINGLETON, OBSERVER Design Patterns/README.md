Expanded from Professor Daryl Posnett's Library Environment Project.

This Java Project Exhibits 3 Software Engineering Design Patterns for a Library Environment:

1.) The Singleton Pattern: The Singleton Design Pattern should allow at most one instance to be created of an object. 
    In this project the Singleton Pattern is used to ensure only one instance of the LibraryLogger class exists. The LibraryLogger logs everything that takes place in the library.
2.) The State Pattern: The State Pattern allows an object to alter its behavior when its internal state changes.
    In this project, the state of a Library Book is implement. There are 3 states of a book: OnShelf, Borrowed, and GotBack and the functions issue(), extend(), returnIt(), and shelf() are used to transition between the states.
3.) The Observer Pattern: The Observer Pattern consists of an object, named the subject, that maintains a list of its dependents, called observers, and notifies them automatically of any state changes, usually by calling one of their methods
    The observer pattern was applied to this particular project. In this project, observers can attach and detach to a Book object and be notified as it transitions states. 