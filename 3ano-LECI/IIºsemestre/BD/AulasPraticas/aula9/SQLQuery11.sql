use company;

DROP DATABASE company;
CREATE DATABASE company;
USE company;

create type name_t from varchar(20);
create type addr from varchar(30);

create table department (
	Dname name_t not null,
	Dnumber int primary key,
	Mgr_ssn int, -- Fk
	Mgr_start_date date
);
drop table employee;
create table employee (
	Fname name_t not null,
	Minit char(1),
	Lname name_t not null,
	Ssn int primary key,
	Bdate date not null,
	Address addr not null,
	Sex char(1),
	Salary int not null check (Salary >= 0),
	Super_ssn int references employee(Ssn), -- on delete set null on update cascade,
	Dno int references department(Dnumber) on delete set null on update cascade, -- ??????
);
drop table dept_locations;
create table dept_locations (
	Dnumber int references department(Dnumber) on delete cascade on update cascade, -- ???????
	Dlocation addr,
	primary key(Dnumber, Dlocation)
);
create table project (
	Pname name_t not null,
	Pnumber int primary key,
	Plocation addr,
	Dnum int references department(Dnumber) on delete set null on update cascade, -- ??????
);
create table works_on (
	Essn int references employee(Ssn) on delete cascade on update cascade,
	Pno int references project(Pnumber), -- on delete cascade on update cascade, -- ????
	Hours int not null check (Hours >= 0) default 0,
	primary key(Essn, Pno)
);
create table dependant (
	Essn int references employee(Ssn) on delete cascade on update cascade, -- ????
	Dependent_name name_t,
	Sex char(1),
	Bdate date not null,
	Relationship name_t not null,
	primary key (Essn, Dependent_name)
);
alter table department add constraint Mgr_ssn references employee(Ssn);

alter table employee add constraint Dno references department(Dnumber) on delete set null on update cascade;
alter table employee add constraint Super_ssn references employee(Ssn); -- on delete set null on update cascade,

alter table dept_locations add constraint Dnumber references department(Dnumber) on delete cascade on update cascade;
	
alter table project add constraint Dnum references department(Dnumber) on delete set null on update cascade;
	
alter table works_on add constraint Essn references employee(Ssn) on delete cascade on update cascade;
alter table works_on add constraint Pno references project(Pnumber);
	
alter table dependent add constraint Essn references employee(Ssn) on delete cascade on update cascade;


-- f
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