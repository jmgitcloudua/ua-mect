CREATE DATABASE company;
USE company;

create type name_t from varchar(20);
create type addr from varchar(30);

create table department (
	Dname name_t not null,
	Dnumber int primary key,
	Mgr_ssn int not null, -- Fk
	Mgr_start_date date not null
);
-- drop table employee;
create table employee (
	Fname name_t not null,
	Minit char(1),
	Lname name_t not null,
	Ssn int primary key,
	Bdate date not null,
	Address addr not null,
	Sex bit,
	Salary int not null check (Salary >= 0),
	Super_ssn int references employee(Ssn), -- on delete set null on update cascade,
	Dno int references department(Dnumber) on delete set null on update cascade, -- ??????
);
alter table department add constraint Mgr_ssn references employee(Ssn);
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
create table dependent (
	Essn int references employee(Ssn) on delete cascade on update cascade, -- ????
	Dependent_name name_t,
	Sex bit,
	Bdate date not null,
	Relationship name_t not null,
	primary key (Essn, Dependent_name)
);
