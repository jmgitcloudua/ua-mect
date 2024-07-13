SELECT paciente.numUtente, paciente.nome
FROM
	paciente LEFT outer JOIN prescricao
	ON (paciente.numUtente = prescricao.numUtente)
WHERE prescricao.numPresc IS null;
