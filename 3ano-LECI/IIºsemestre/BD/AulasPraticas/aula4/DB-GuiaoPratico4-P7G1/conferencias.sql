create database conferencias;
use conferencias;

-- Ainda que seja contra intuitivo, identificadores podem ser negativos.
-- Optou-se por não se restringir a identificadores positivos para haver maior rentabilização do espaço de possibilidades
-- Apenas se verifica este caso para números conhecidos que não possam ser negativos, como números do SNS e CC.

create table inscricao(
	id integer primary key,
	valor integer not null check (valor > 0),
);
create table conferencia(
	id integer primary key,
);
create table artigo(
	n_registo integer primary key,
	titulo varchar(40) not null
);
create table apresenta(
	id integer not null references conferencia(id) on delete cascade on update cascade, 
	n_registo integer not null references artigo(n_registo) on delete cascade on update cascade 
);
create table instituicao(
	endereco varchar(30) primary key,
	nome varchar(20) not null
);
create table pessoa(
	email varchar(30) primary key,
	nome varchar(20) not null
);
create table autor(
	email varchar(30) primary key references pessoa(email) on delete cascade on update cascade,
	endereco varchar(30) not null
);
create table publica(
	email varchar(30) not null references autor(email) on delete cascade on update cascade,
	n_registo integer not null references artigo(n_registo) on delete cascade on update cascade
);
create table participante(
	email varchar(30) primary key references pessoa(email) on delete cascade on update cascade,
	morada varchar(30) not null,
	data_insc date,
);
create table nao_estudante(
	email varchar(30) primary key references participante(email) on delete cascade on update cascade,
);
create table transacao(
	n_transacao integer primary key,
	id integer not null references inscricao(id) on delete cascade on update cascade,
	email varchar(30) not null references nao_estudante(email) on delete cascade on update cascade,
);
create table estudante(
	email varchar(30) primary key references participante(email) on delete cascade on update cascade,
);
create table comprovativo(
	localizacao varchar(30) primary key,
	id integer not null references inscricao(id) on delete cascade on update cascade,
	email varchar(30) not null references estudante(email) on delete cascade on update cascade,
	endereco varchar(30) not null references instituicao(endereco) on delete cascade on update cascade
);
