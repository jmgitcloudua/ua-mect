SELECT farmaco.nome
FROM (
	SELECT *
	FROM (
		SELECT *
		FROM presc_farmaco
		WHERE presc_farmaco.numRegFarm = 906
	) as r1 RIGHT outer JOIN (
		SELECT *
		FROM farmaco
		WHERE farmaco.numRegFarm = 906
	) as r2
	ON r1.nomeFarmaco = r2.nome
	WHERE r1.numPresc IS null
) AS r;
