This Java Project Analayzes a GitHub Issues Log by parsing the contents of the log using streams.

The Github Log contains all of the issues reported by individuals along with key details of the project to which the issue concerns.
The Github Log is stored in the data folder as a csv file.

This project can read in the data from the .csv file and several different functions are implemented that allow for the filtering and searching of the log based on different evaluation criteria.
Functions such as:
    getWordCount()
    countWordOccurancesInSingleComment()
    getPerProjectCount()
    getAuthorActivity()
    getCommentUrlAuthorCount()
    filterCommentsWithUrl()
    getAuthorAverageVerbosity()
    findCommentLength()
    getAuthorWordCountPerProject()