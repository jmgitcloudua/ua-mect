SELECT *
FROM (
	SELECT prescricao.farmacia, COUNT(prescricao.numPresc) AS n_presc
	FROM prescricao
	GROUP BY prescricao.farmacia
) as r
WHERE r.farmacia IS NOT null;
