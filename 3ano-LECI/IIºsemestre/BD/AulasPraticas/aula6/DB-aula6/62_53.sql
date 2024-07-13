create database prescricao;
use prescricao;

create type name_t from varchar(20);
create type addr from varchar(30);

create table medico(
	numSsn int primary key,
	nome name_t not null,
	especialidade name_t not null
);
create table paciente(
	numUtente int primary key,
	nome name_t not null,
	dataNasc date not null,
	endereco addr not null
);
create table farmacia(
	nome name_t not null,
	telefone int check (telefone >= 0),
	endereco addr primary key
);
create table farmaceutica(
	numReg int primary key,
	nome name_t not null,
	endereco addr references farmacia(endereco) on delete set null on update cascade
);
create table farmaco(
	numRegFarm int unique references farmaceutica(numReg) on delete cascade on update cascade,
	nome name_t unique,
	formula name_t not null,
	primary key(numRegFarm, nome)
);
create table presc_farmaco(
	numPresc int primary key,
	numRegFarm int not null references farmaco(numRegFarm) on delete cascade on update cascade,
	nomeFarmaco name_t not null references farmaco(nome), -- on delete cascade on update cascade
);
create table prescricao(
	numPresc int not null references presc_farmaco(numPresc) on delete cascade on update cascade,
	numUtente int not null references paciente(numUtente) on delete cascade on update cascade,
	numMedico int not null references medico(numSsn) on delete cascade on update cascade,
	farmacia addr not null references farmacia(endereco), -- on delete cascade on update cascade,
	dataProc date
);
