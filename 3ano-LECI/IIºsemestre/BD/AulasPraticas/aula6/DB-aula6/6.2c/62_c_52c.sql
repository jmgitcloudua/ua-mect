SELECT AVG(r.cnt_) AS avg_ FROM (
	SELECT num_enc, COUNT(codProd) AS cnt_ FROM item GROUP BY numEnc
) as r;
