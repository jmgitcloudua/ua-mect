SELECT  presc.nome, presc_farmaco.numRegFarm, COUNT(presc_farmaco.numPresc) AS num_vendidos
FROM
	presc_farmaco JOIN (
		SELECT *
		FROM prescricao JOIN farmacia
		ON farmacia = nome
	) AS presc
	ON presc_farmaco.numPresc = presc.numPresc
GROUP BY presc.nome, presc_farmaco.numRegFarm
