create database Gest_Stock;
use Gest_Stock;

create type name_t from varchar(20);
create type addr from varchar(30);

create table tipo_fornecedor (
	codigo int primary key,
	designacao name_t
);
create table fornecedor (
	nif int primary key,
	nome name_t not null,
	fax int not null,
	endereco addr not null,
	condpag int not null,
	tipo int references tipo_fornecedor(codigo) on delete set null on update cascade
);
create table produto (
	codigo int primary key,
	nome name_t not null,
	preco int not null check (preco >= 0),
	iva int not null check (iva >= 0),
	unidades int not null check (unidades >= 0)
);
create table encomenda (
	numero int primary key,
	data date not null,
	fornecedor int not null references fornecedor(nif) on delete cascade on update cascade
);
create table item (
	numEnc int not null references encomenda(numero) on delete cascade on update cascade,
	codProd int not null references produto(codigo) on delete cascade on update cascade,
	unidades int not null check (unidades >= 0),
	primary key(numEnc, codProd)
);
