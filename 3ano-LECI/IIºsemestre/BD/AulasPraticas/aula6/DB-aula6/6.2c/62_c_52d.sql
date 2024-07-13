SELECT item.codProd, item.unidades, encomenda.fornecedor
FROM item JOIN encomenda ON
(item.numEnc = encomenda.numero);
