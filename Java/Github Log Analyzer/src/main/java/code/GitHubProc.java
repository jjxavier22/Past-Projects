//Jiss Xavier
//916427256

package hw3;

import java.util.*;
import java.util.Map;
import java.util.stream.Stream;
import java.util.stream.Collectors;
import static java.util.stream.Collectors.counting;
import static java.util.stream.Collectors.averagingDouble;
import static java.util.stream.Collectors.summingLong;


public class GitHubProc {
  public static Long getWordCount(Stream<GitHubComment> stream, String word) {
    long matchCount = stream.parallel()
                            .mapToLong(GitHubComment -> countWordOccurancesInSingleComment(GitHubComment, word))
                            .sum();
    return matchCount;
  }

  public static Long countWordOccurancesInSingleComment(GitHubComment comment, String word) {
    String[] body = Util.getWords(comment.body());
    long matchCount = Arrays.stream(body)
                            .parallel()
                            .filter(i -> i.equals(word))
                            .count();
    return matchCount;
  }



  public static Map<String, Long> getPerProjectCount(Stream<GitHubComment> stream) {
    var projectCountMap = stream.parallel()
                                .collect(Collectors.groupingBy(GitHubComment -> Util.getProject(GitHubComment),
                                                                                    counting()));
    return projectCountMap;
  }



  public static Map<String, Long> getAuthorActivity(Stream<GitHubComment> stream) {
    var authorCommentMap = stream.parallel()
                                 .collect(Collectors.groupingBy(GitHubComment::author,
                                                                counting()));
    return authorCommentMap;
  }



  public static Map<String, Long> getCommentUrlAuthorCount(Stream<GitHubComment> stream) {
    var authorURLCommentMap = stream.parallel()
                                    .filter(GitHubComment -> doesContainURL(GitHubComment))
                                    .collect(Collectors.groupingBy(GitHubComment::author,
                                                               counting()));
    return authorURLCommentMap;
  }



  public static Stream<GitHubComment> filterCommentsWithUrl(Stream<GitHubComment> comments) {
    return comments.parallel()
                   .filter(GitHubComment -> doesContainURL(GitHubComment));
  }

  public static boolean doesContainURL(GitHubComment comment){
    String[] body = Util.getWords(comment.body());
    long urlCount = Arrays.stream(body)
                          .parallel()
                          .filter(i -> i.contains("http://") || i.contains("https://"))
                          .count();
    if(urlCount >= 1){
      return true;
    }
    else{
      return false;
    }
  }
  



  public static Map<String, Double> getAuthorAverageVerbosity(Stream<GitHubComment> stream) {
    var authorAverageVerbosityMap = stream.parallel()
                                          .collect(Collectors.groupingBy(GitHubComment::author,
                                                   averagingDouble(GitHubComment -> findCommentLength(GitHubComment))));
    return authorAverageVerbosityMap;
  }

  public static double findCommentLength(GitHubComment comment) {
    String[] body = Util.getWords(comment.body());
    double wordCount = Arrays.stream(body)
                             .parallel()
                             .count();
    return wordCount;
  }



  public static Map<String, Map<String, Long>> getAuthorWordCountPerProject(
      Stream<GitHubComment> stream, String word) {
      var map = stream.parallel()
                      .collect(Collectors.groupingBy(GitHubComment -> Util.getProject(GitHubComment),
                                                    Collectors.groupingBy(GitHubComment::author,
                                                                          summingLong(GitHubComment -> countWordOccurancesInSingleComment(GitHubComment, word))))); 

    return map;
  }
}
