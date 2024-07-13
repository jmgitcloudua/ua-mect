create database medicamentos;	
use medicamentos;

-- Ainda que seja contra intuitivo, identificadores podem ser negativos.
-- Optou-se por não se restringir a identificadores positivos para haver maior rentabilização do espaço de possibilidades
-- Apenas se verifica este caso para números conhecidos que não possam ser negativos, como números do SNS e CC.

create table paciente (
	n_utente integer primary key, 
	nome varchar(20) not null,
	data_nasc date not null,
	endereco varchar(30) not null
);
create table medico (
	n_sns integer primary key check (n_sns > 0),
	especialidade varchar(20) not null,
	nome varchar(20) not null
);
create table farmacia (
	nif integer primary key check (nif > 0),
	nome varchar(20) not null,
	telefone varchar(12) not null,
	endereço varchar(30) not null
);
create table prescricao (
	n_prescricao integer primary key,
	data_presc date not null,
	n_utente integer not null references paciente(n_utente) on delete cascade on update cascade,
	nif integer not null references farmacia(nif) on delete cascade on update cascade,
	data_proc date,
	n_sns integer references medico(n_sns)
);
create table companhia (
	n_reg_nac integer primary key,
	nome varchar(20) not null,
	telefone varchar(12) not null,
	endereco varchar(30) not null
);
create table farmaco (
	nome_comercial varchar(20) not null,
	formula varchar(20) not null,
	n_reg_nac integer not null references companhia(n_reg_nac) on delete cascade on update cascade,
	codigo integer primary key
);
create table vende (
	nif integer not null references farmacia(nif) on delete cascade on update cascade,
	codigo integer not null references farmaco(codigo) on delete cascade on update cascade,
	primary key (nif, codigo)
);
