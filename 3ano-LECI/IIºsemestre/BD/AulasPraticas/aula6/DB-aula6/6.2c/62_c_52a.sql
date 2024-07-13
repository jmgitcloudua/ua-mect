SELECT fornecedor.nif, fornecedor.nome FROM 
	(encomenda RIGHT OUTER JOIN fornecedor ON 
		encomenda.fornecedor = fornecedor.nif) 
WHERE encomenda.fornecedor = null;



