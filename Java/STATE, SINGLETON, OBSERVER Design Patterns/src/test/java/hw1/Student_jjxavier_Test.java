package hw1;
import static org.junit.jupiter.api.Assertions.assertArrayEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class Student_jjxavier_Test {
    @BeforeEach
    public void resetLog() {
        LibraryLogger.getInstance().clearWriteLog();
    }

    @Test
	public void studentTest() {
		/** 
		 * A end-to-end test created by Jiss Xavier to test a specific assertion for Problem 2.
		 */

		LibraryBook book = new LibraryBook("Jiss's Book");
        book.issue();
        book.extend();
		book.extend();
        book.shelf();
        book.issue();
        book.extend();
		book.returnIt();
		book.returnIt();
		book.extend();
		book.shelf();
		book.extend();

		assertArrayEquals(
			new String [] {
                "Leaving State OnShelf for State Borrowed",
                "Leaving State Borrowed for State Borrowed",
				"Leaving State Borrowed for State Borrowed",
                "BadOperationException - Can't use shelf in Borrowed state",
                "BadOperationException - Can't use issue in Borrowed state",
                "Leaving State Borrowed for State Borrowed",
                "Leaving State Borrowed for State GotBack",
				"BadOperationException - Can't use returnIt in GotBack state",
                "BadOperationException - Can't use extend in GotBack state",
				"Leaving State GotBack for State OnShelf",
                "BadOperationException - Can't use extend in OnShelf state"	
			}, 
			LibraryLogger.getInstance().getWrittenLines()
		);
		
	}

}
