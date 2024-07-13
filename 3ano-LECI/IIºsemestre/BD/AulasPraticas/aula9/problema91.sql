

/************All problems are solved below*******************/

-- a)
GO
CREATE PROCEDURE removeEmployee(@number INT) AS 
BEGIN 
    DELETE FROM DEPENDENT WHERE Essn = @number; 
    DELETE FROM WORKS_ON WHERE Essn = @number;
    UPDATE DEPARTMENT SET  Mgr_ssn = NULL WHERE Mgr_ssn = @number;
    UPDATE EMPLOYEE SET  Super_ssn = NULL WHERE Super_ssn = @number;
    DELETE FROM EMPLOYEE WHERE Ssn = @number;
END
GO

-- b)
GO
CREATE PROCEDURE employeeManager(@oldYear INT OUTPUT, @oldSsn INT OUTPUT) AS 
BEGIN 
    SELECT Fname, Minit, Lname, Ssn, Salary, Dno, Dname, Mgr_start_date FROM EMPLOYEE, DEPARTMENT WHERE Ssn = Mgr_ssn;
    SELECT TOP(1) @oldSsn = Ssn, @oldYear = YEAR(Mgr_start_date) FROM EMPLOYEE, DEPARTMENT  WHERE Ssn = Mgr_ssn ORDER BY Mgr_start_date;
END
GO

-- c)
GO
CREATE TRIGGER employeeManagerTrigger ON DEPARTMENT INSTEAD OF INSERT, UPDATE AS
BEGIN
    DECLARE @Mgr_Ssn INT;
    SELECT @Mgr_Ssn = Mgr_ssn FROM INSERTED;

    IF @Mgr_Ssn IN (SELECT Mgr_Ssn FROM DEPARTMENT) 
        BEGIN
            PRINT 'Employee already manages one department';
        END
    ELSE
        BEGIN
            INSERT INTO DEPARTMENT SELECT * FROM INSERTED;
            PRINT 'Successfully added employee to department';
        END
END
GO
/*
--It is just a Testing
SELECT * FROM DEPARTMENT;
SELECT * FROM EMPLOYEE;
INSERT INTO DEPARTMENT VALUES ('DPTEST', 4, 21312332,'2022-05-31');
INSERT INTO DEPARTMENT VALUES ('DPTEST', 4, 345355435 ,'2022-05-31');
*/

-- d)
GO
CREATE TRIGGER checkSalaryEmployeeMgrTrigger ON EMPLOYEE AFTER INSERT, UPDATE AS
BEGIN
    DECLARE @Salary AS INT;
	DECLARE @MgrSalary AS INT;
	DECLARE @Ssn AS INT;
	DECLARE @Dno AS INT;
	DECLARE @Mgr_ssn AS INT;

    SELECT @Salary = Salary, @Ssn = Ssn, @Dno = Dno FROM INSERTED;
    SELECT @Mgr_ssn = Mgr_ssn, @Salary = Salary FROM EMPLOYEE, DEPARTMENT WHERE @Dno = Dnumber AND @Ssn = Ssn;
    SELECT @MgrSalary = Salary FROM EMPLOYEE WHERE @Mgr_ssn = Ssn;

    IF @Salary > @MgrSalary
        BEGIN
            UPDATE EMPLOYEE SET @Salary = @MgrSalary - 1 WHERE @Ssn = Ssn;
        END 
END
GO

-- e)
GO
CREATE FUNCTION getUDF_Location (@Ssn CHAR(9)) RETURNS @table TABLE 
(
   Pname VARCHAR(20),
   Plocation VARCHAR(20)

)
AS
BEGIN
    INSERT @table
    SELECT Pname, Plocation FROM WORKS_ON, PROJECT WHERE  @Ssn = Essn AND Pno = Pnumber;
    RETURN;
END
GO
-- It is just a Testing
--SELECT * FROM getUDF_Location(21312332);


-- f
create type name_t from varchar(20);
create type addr from varchar(30);

GO
CREATE FUNCTION dbo.GetEmployees(@dno int) returns @res table (empName name_t)
AS BEGIN
	declare @avg_sal int;
	select @avg_sal = 
		AVG(Salary) 
		from employee 
		where Dno=@dno;
	
	insert @res (empName) 
		select Fname from employee
		where Salary > @avg_sal and Dno=@dno

	return;
END
GO

select * from dbo.GetEmployees(1);
select * from dbo.GetEmployees(2);
select * from dbo.GetEmployees(3);

-- g
drop function dbo.employeeDeptHighAverage;
GO
CREATE FUNCTION dbo.employeeDeptHighAverage(@pno int) returns @res table (pName name_t, pNumber int, pLocation addr, Dnum int, budget money, totalBudget money )
AS BEGIN
	declare @salary int, @hours int;
	declare c cursor fast_forward for
		select employee.Salary, works_on.Hours
		from works_on join employee
			on works_on.Essn = employee.Ssn
		where works_on.Pno = @pno

	open c;
	fetch c into @salary, @hours;

	declare @proj_bud int, @total_bud int; 
	select @proj_bud = 0, @total_bud = 0;
	while @@FETCH_STATUS = 0 begin
		set @proj_bud += (@hours * @salary / 40)
		set @total_bud += @salary
		fetch c into @salary, @hours;
	end

	close c;
	deallocate c;

	insert @res (pName, pNumber, pLocation, Dnum, budget, totalBudget)
		select project.Pname, project.Pnumber, project.Plocation, project.Dnum, @proj_bud, @total_bud
		from project
		where project.Pnumber = @pno
	return;
END
GO

select * from dbo.employeeDeptHighAverage(1);
select * from dbo.employeeDeptHighAverage(2);
select * from dbo.employeeDeptHighAverage(3);

-- h
-- Como vamos dar sempre rollback não devemos usar after, pois a query executa até uma fase muito posterior e tudo o que fizer será revertido
GO
CREATE TRIGGER delDept ON dbo.department 
AFTER DELETE
AS
	IF (NOT EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES
	WHERE TABLE_SCHEMA = 'dbo' AND TABLE_NAME = 'department_deleted')) BEGIN
		create table department_deleted (
			Dname name_t not null,
			Dnumber int primary key,
			Mgr_ssn int, -- Fk
			Mgr_start_date date
		);
	END

	ROLLBACK TRAN;

	declare @a name_t, @b int, @c int, @d date;
	select @a=deleted.Dname, @b=deleted.Dnumber, @c=deleted.Mgr_ssn, @d=Mgr_start_date from deleted;
	insert into department_deleted values (@a,@b,@c,@d);
GO


GO
CREATE TRIGGER delDeptInstOf ON dbo.department 
INSTEAD OF DELETE
AS
	IF (NOT EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES
	WHERE TABLE_SCHEMA = 'dbo' AND TABLE_NAME = 'department_deleted')) BEGIN
		create table department_deleted (
			Dname name_t not null,
			Dnumber int primary key,
			Mgr_ssn int, -- Fk
			Mgr_start_date date
		);
	END

	declare @a name_t, @b int, @c int, @d date;
	select @a=deleted.Dname, @b=deleted.Dnumber, @c=deleted.Mgr_ssn, @d=Mgr_start_date from deleted;
	insert into department_deleted values (@a,@b,@c,@d);
GO

-- g 
-- Apenas uma UDF pode retornar uma tabela.
-- Como não pode retornar uma tabela, um SP não pode usar Select, Where ou Having ao contrário duma UDF
-- Apenas SPs têm exception handling
-- Apenas SPs podem fazer transações 
-- Apenas SPs podem chamar SPs
-- Assim, em situações onde se pretende retornar vários tuplos (problemas do tipo "retorne todos os que obdecem a uma regra") é obrigatório usar UDFs
--	Quando há a necessidade de controlo de erros mais complexos ou chamar um SP é necessário usar um SP

