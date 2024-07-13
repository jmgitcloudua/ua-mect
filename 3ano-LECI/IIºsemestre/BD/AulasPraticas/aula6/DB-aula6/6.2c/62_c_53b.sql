SELECT medico.especialidade, COUNT(medico.numSNS) as nMedicos
FROM prescricao JOIN medico
	ON prescricao.numMedico = medico.numSNS
GROUP BY medico.especialidade;
