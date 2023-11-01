--Queries--
--1
SELECT COUNT(*) "Total Member" 
FROM MEMBER;

--2
SELECT * 
FROM STUDENT 
WHERE Course = 'CS';

--3
SELECT * 
FROM STAFF 
WHERE Gender = 'Female';

--4
SELECT * 
FROM STAFF 
WHERE Campus = 'Kampar';

--5
SELECT * 
FROM STAFF 
WHERE Campus = 'Kampar' AND Gender = 'Male';

--6
SELECT ( s.FName || ' ' || s.LName ) AS "Staff Name", m.RegisterDate 
FROM STAFF s, MEMBER m 
WHERE m.RegisterDate LIKE '%-APR-%' AND m.M_ID = s.M_ID;

--7
SELECT ( s.FName || ' ' || s.LName ) AS "Student Name" 
FROM STUDENT s, MEMBER m 
WHERE m.TotalLending = 0 AND m.M_ID = s.M_ID;

--8
SELECT ( s.FName || ' ' || s.LName ) AS "Student Name" 
FROM STUDENT s, RESERVE r 
WHERE r.M_ID = s.M_ID;

--9
SELECT DISTINCT Category 
FROM BOOK;

--10
SELECT Title
FROM BOOK 
WHERE Category = 'Mathematic' AND Campus = 'Sungai Long';

--Stored Procedures--
--1
SET SERVEROUTPUT ON
CREATE OR REPLACE PROCEDURE create_new_book
(
create_B_ID IN VARCHAR2,
create_Category IN VARCHAR2,
create_Title IN VARCHAR2,
create_Publisher IN VARCHAR2,
create_Quantity IN NUMBER,
create_Campus IN VARCHAR2
)
IS
BEGIN
INSERT INTO BOOK
VALUES
(
create_B_ID,
create_Category,
create_Title,
create_Publisher,
create_Quantity,
create_Campus
);
COMMIT;
DBMS_OUTPUT.PUT_LINE('Successfully Insert New Book');
END;
/
EXECUTE create_new_book('B00006','Mathematic','A Study on Linear Equation','ASD Sdn Bhd',2,'Sungai Long');

--2
SET SERVEROUTPUT ON
CREATE OR REPLACE PROCEDURE update_student_contactNo
(
cur_M_ID IN VARCHAR2,
new_ContactNo IN VARCHAR2
)
IS
BEGIN
UPDATE STUDENT
SET ContactNo = new_ContactNo
WHERE M_ID = cur_M_ID;
COMMIT;
DBMS_OUTPUT.PUT_LINE('Successfully Update Contact Number');
END;
/
EXECUTE update_student_contactNo('M00002','01012332321');

--3
SET SERVEROUTPUT ON
CREATE OR REPLACE PROCEDURE delete_reservation
(
cur_RS_ID IN VARCHAR2
)
IS
BEGIN
DELETE FROM RESERVE 
WHERE RS_ID = cur_RS_ID;
COMMIT;
DBMS_OUTPUT.PUT_LINE('Successfully Delete Reservation');
END;
/
EXECUTE delete_reservation('RS00001');

--4
SET SERVEROUTPUT ON
CREATE OR REPLACE PROCEDURE update_penalty_fee
(
cur_L_ID IN VARCHAR2
)
IS
BEGIN
UPDATE LEND
SET PenaltyFees = SYSDATE - DUEDATE
WHERE L_ID = cur_L_ID;
COMMIT;
DBMS_OUTPUT.PUT_LINE('Successfully Update Penalty Fees');
END;
/
EXECUTE update_penalty_fee('L00001');

--5
SET SERVEROUTPUT ON
CREATE OR REPLACE PROCEDURE update_lend_status
(
cur_L_ID IN VARCHAR2,
new_Status IN VARCHAR2
)
IS
BEGIN
UPDATE LEND
SET Status = new_Status 
WHERE L_ID = cur_L_ID;
COMMIT;
DBMS_OUTPUT.PUT_LINE('Successfully Update Lending Status');
END;
/
EXECUTE update_lend_status('L00001','Returned');


--Functions--
--1
SET SERVEROUTPUT ON
CREATE OR REPLACE FUNCTION calculate_student
RETURN NUMBER
IS
total_student NUMBER;
BEGIN
SELECT COUNT(*) INTO total_student
FROM STUDENT
WHERE Campus = 'Kampar';
RETURN total_student;
END;
/
DECLARE
total_student NUMBER;
BEGIN
total_student := calculate_student;
DBMS_OUTPUT.PUT_LINE('There are total ' || total_student || ' student registered in Kampar.');
END;
/

--2
SET SERVEROUTPUT ON
CREATE OR REPLACE FUNCTION calculate_fee
RETURN NUMBER
IS
total_fee NUMBER;
BEGIN
SELECT SUM(PenaltyFees) INTO total_fee
FROM LEND;
RETURN total_fee;
END;
/
DECLARE
total_fee NUMBER;
BEGIN
total_fee := calculate_fee;
DBMS_OUTPUT.PUT_LINE('There are total ' || total_fee || ' of penalty fees.');
END;
/

--3
SET SERVEROUTPUT ON
CREATE OR REPLACE FUNCTION find_staff_campus
(
cur_M_ID IN VARCHAR2
)
RETURN VARCHAR2
IS
cur_campus VARCHAR2(30);
BEGIN
SELECT Campus INTO cur_Campus
FROM STAFF
WHERE M_ID = cur_M_ID;
RETURN cur_Campus;
END;
/
DECLARE
M_ID VARCHAR2(6);
Campus VARCHAR2(30);
BEGIN
M_ID := 'M00001';
Campus := find_staff_campus(M_ID);
DBMS_OUTPUT.PUT_LINE('The Staff with member ID ' || M_ID || ' is belong to ' || Campus || '.');
END;
/

--4
SET SERVEROUTPUT ON
CREATE OR REPLACE FUNCTION calculate_average_age_student
RETURN NUMBER
IS
avg_age NUMBER;
BEGIN
SELECT ROUND(AVG(Age),2) INTO avg_age
FROM STUDENT
WHERE Campus = 'Kampar';
RETURN avg_age;
END;
/
DECLARE
avg_age NUMBER;
BEGIN
avg_age := calculate_average_age_student;
DBMS_OUTPUT.PUT_LINE('The average age of students in kampar are ' || avg_age || '.');
END;
/

--5
SET SERVEROUTPUT ON
CREATE OR REPLACE FUNCTION find_total_lending
(
cur_M_ID IN VARCHAR2
)
RETURN NUMBER
IS
total_lending NUMBER;
BEGIN
SELECT TotalLending INTO total_lending
FROM MEMBER
WHERE M_ID = cur_M_ID;
RETURN total_lending;
END;
/
DECLARE
M_ID VARCHAR2(6);
total_lending NUMBER;
BEGIN
M_ID := 'M00001';
total_lending := find_total_lending(M_ID);
DBMS_OUTPUT.PUT_LINE('The Staff with member ID ' || M_ID || ' has total lending of ' || total_lending || ' number of book(s).');
END;
/
