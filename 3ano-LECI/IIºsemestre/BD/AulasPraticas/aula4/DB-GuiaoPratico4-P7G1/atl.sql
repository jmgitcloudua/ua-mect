create database atl;
use atl;

-- Ainda que seja contra intuitivo, identificadores podem ser negativos.
-- Optou-se por não se restringir a identificadores positivos para haver maior rentabilização do espaço de possibilidades
-- Apenas se verifica este caso para números conhecidos que não possam ser negativos, como números do SNS e CC.

create table atl (
	atl_id integer primary key
);
create table pessoa (
	cc integer primary key check (cc > 0),
	nome varchar(20) not null,
	morada varchar(30) not null,
	data_nasc date not null
);
create table classe (
	id integer primary key,
);
create table turma (
	id integer primary key,
	designacao varchar(20) not null unique,
	max_alunos integer not null check (max_alunos >= 0),
	ano_letivo integer not null,
	atl_id integer not null references atl(atl_id),
	classe_id integer not null references classe(id)
);
create table aluno (
	cc integer primary key references pessoa(cc) on delete cascade on update cascade,
	turma integer not null references turma(id),
);
create table classe_0 (
	classe_id integer references classe(id)
);
create table classe_1 (
	classe_id integer references classe(id)
);
create table classe_2 (
	classe_id integer references classe(id)
);
create table classe_3 (
	classe_id integer references classe(id)
);
create table classe_4 (
	classe_id integer references classe(id)
);
create table atividade (
	id integer primary key,
	custo smallmoney not null check (custo >= 0),
	designacao varchar(20) not null
);
create table tem (
	id_turma integer references turma(id) on delete cascade on update cascade,
	id_atividade integer references atividade(id) on delete cascade on update cascade,
	primary key (id_turma, id_atividade)
);
create table adulto (
	cc integer primary key references pessoa(cc) on delete cascade on update cascade,
	telefone varchar(12) not null,
	email varchar(20) not null
);
create table encarregado_ed (
	cc integer primary key references adulto(cc) on delete cascade on update cascade,
);
create table professor (
	cc integer primary key references adulto(cc) on delete cascade on update cascade,
	n_funcionario integer not null
);
create table natureza (
	cc_enc_ed integer not null references encarregado_ed(cc),
	cc_educando integer not null references aluno(cc),
	primary key (cc_enc_ed, cc_educando)
);
create table pode_levantar (
	cc_adulto integer not null references adulto(cc),
	cc_aluno integer not null references aluno(cc),
	primary key (cc_adulto, cc_aluno)
);
create table frequenta (
	cc_aluno integer not null references aluno(cc) on delete cascade on update cascade,
	id integer not null references atividade(id) on delete cascade on update cascade,
	primary key (cc_aluno, id)
);
