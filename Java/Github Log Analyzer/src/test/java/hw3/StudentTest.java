//Jiss Xavier
//916427256

package hw3;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.assertFalse;

import java.util.HashMap;
import java.util.Map;
import java.util.stream.Stream;
import org.junit.jupiter.api.Test;

public class StudentTest {
    Stream<GitHubComment> getStudentTestData() {
        return Stream.of(
            new GitHubComment(
                //8026
                "22433035",
                "fd309b8a0b3b6e1b9d36528c46a152374aa6c2c2",
                "https://github.com/rails/rails/pull/18313#discussion_r22433035",
                "simi",
                "2015-01-03T17:17:00Z",
                "What about to use [named capture](http://stackoverflow.com/a/18825787/319233) instead of `$1`?"),
            new GitHubComment(
                //2529
                "22434305",
                "23549056fcc36988bd0e5381bcc083a0e159cfad",
                "https://github.com/TuxedoJS/TuxWebsite/pull/1#discussion_r22434305",
                "Cheerazar",
                "2015-01-03T19:46:53Z",
                "I'd recommend against adding divs and breaks when rendering a Link component."
                    + " This indicates to me that you should create a separate component that does this work for you. "
                    //added by Student
                    + " Please refer to https://stackoverflow.com/ and https://google.com/"),
            new GitHubComment(
                //10097
                "22400809",
                "3f9a4f94c9d4223cb5c2a58337fca2274d939aae",
                "https://github.com/gonum/stat/pull/22#discussion_r22400809",
                "jonlawlor",
                "2015-01-01T17:50:03Z",
                "Negative weights can also be interpreted as removing a sample.  See for example https://github.com/glycerine/zettalm"
                    + "  which is a regression package.  So there are similar cases where a negative weight can be used."),
            new GitHubComment(
                //2507
                "22434264",
                "23549056fcc36988bd0e5381bcc083a0e159cfad",
                "https://github.com/TuxedoJS/TuxWebsite/pull/1#discussion_r22434264",
                "Cheerazar",
                "2015-01-03T19:40:42Z",
                "Put image tag on a separate line."
                //added by Student
                + " Use this link as a resource https://canvas.ucdavis.edu/courses/637640/modules"));
      }




    //Student Written Test that test for Authors that have multiple comments containing URLs
    @Test
    public void shouldCountCommentsWithMultipleUrlsPerAuthor() { // TODO: rename test name to something meaningful
        var testMap = GitHubProc.getCommentUrlAuthorCount(getStudentTestData()); // TODO: implement a non-trivial test
        var expectedMap = new HashMap<String, Long>();
        expectedMap.put("simi", 1L);
        expectedMap.put("Cheerazar", 2L);
        expectedMap.put("jonlawlor", 1L);
        assertEquals(expectedMap, testMap); 
    }
}
