sql

CopyEdit

SELECT Member_Id, COUNT(Book_Id) AS Total_Books_Borrowed

FROM BOOK_ISSUE

GROUP BY Member_Id;

• Number of books published each year:

sql

CopyEdit

SELECT EXTRACT(YEAR FROM Published_Date) AS Year, COUNT(Book_Id) AS Books_Published

FROM BOOK

GROUP BY EXTRACT(YEAR FROM Published_Date);

• Books published by publishers located in India:

sql

CopyEdit

SELECT Title

FROM BOOK

WHERE Publisher_Id IN (SELECT Publisher_Id FROM PUBLISHER WHERE Pub_Address = 'India');

• Books borrowed by members with overdue books:

sql

CopyEdit

SELECT DISTINCT Title

FROM BOOK

WHERE Book_Id IN (SELECT Book_Id FROM BOOK_ISSUE WHERE Status = 'Overdue');

• Books published by McGrawhill:

sql

CopyEdit

SELECT Title

FROM BOOK

WHERE Publisher_Id = (SELECT Publisher_Id FROM PUBLISHER WHERE Name = 'McGrawhill');

• Members who borrowed books authored by Silberschatz:

sql

CopyEdit

SELECT DISTINCT MEMBER.Name

FROM MEMBER

JOIN BOOK_ISSUE ON MEMBER.Member_Id = BOOK_ISSUE.Member_Id

JOIN BOOK_AUTHOR ON BOOK_ISSUE.Book_Id = BOOK_AUTHOR.Book_Id

JOIN AUTHOR ON BOOK_AUTHOR.Author_Id = AUTHOR.Author_Id

WHERE AUTHOR.Name = 'Silberschatz';

• Books borrowed by Hrithika and not by Kevin:

sql

CopyEdit

SELECT Title

FROM BOOK

WHERE Book_Id IN (

 SELECT Book_Id FROM BOOK_ISSUE

 WHERE Member_Id = (SELECT Member_Id FROM MEMBER WHERE Name = 'Hrithika')

)

AND Book_Id NOT IN (SELECT Book_Id FROM BOOK_ISSUE

 WHERE Member_Id = (SELECT Member_Id FROM MEMBER WHERE Name = 'Kevin')

);

• Books borrowed by John or a member with overdue books:

sql

CopyEdit

SELECT DISTINCT Title

FROM BOOK

WHERE Book_Id IN (

 SELECT Book_Id FROM BOOK_ISSUE

 WHERE Member_Id = (SELECT Member_Id FROM MEMBER WHERE Name = 'John')

 OR Status = 'Overdue'

);

• Member who borrowed the maximum number of books:

sql

CopyEdit

SELECT Name, COUNT(Book_Id) AS Books_Borrowed

FROM MEMBER

JOIN BOOK_ISSUE ON MEMBER.Member_Id = BOOK_ISSUE.Member_Id

GROUP BY Name

ORDER BY Books_Borrowed DESC

FETCH FIRST 1 ROW ONLY;

• Names of all books along with their author names:

sql

CopyEdit

SELECT BOOK.Title, AUTHOR.Name AS Author_Name

FROM BOOK

JOIN BOOK_AUTHOR ON BOOK.Book_Id = BOOK_AUTHOR.Book_Id

JOIN AUTHOR ON BOOK_AUTHOR.Author_Id = AUTHOR.Author_Id;

• Books published by Pearson, sorted by publication date:

sql

CopyEdit

SELECT Title

FROM BOOK

WHERE Publisher_Id = (SELECT Publisher_Id FROM PUBLISHER WHERE Name = 'Pearson')

ORDER BY Published_Date;

• Book with minimum price, maximum price, and greatest volume:

sql

CopyEdit

SELECT

 (SELECT Title FROM BOOK WHERE MRP = (SELECT MIN(MRP) FROM BOOK)) AS Min_Price_Book,

 (SELECT Title FROM BOOK WHERE MRP = (SELECT MAX(MRP) FROM BOOK)) AS Max_Price_Book,

 (SELECT Title FROM 
