SET STATISTICS IO ON;

DBCC FREEPROCCACHE;
DBCC DROPCLEANBUFFERS;

 SELECT WorkOrderID, StartDate FROM AdventureWorks2012.Production.WorkOrder 
WHERE ProductID = 945 AND StartDate = '2006-01-04'


-- SELECT * FROM sys.dm_db_index_physical_stats ( db_id('AdventureWorks2012'), object_id('dbo.mytemp'), NULL, NULL, 'DETAILED');
-- SET IDENTITY_INSERT mytemp ON
