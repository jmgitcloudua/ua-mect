use pubs ;

--Problema 6.1

-- a)
-- SELECT * FROM authors;

-- b)
-- SELECT au_lname, au_fname, phone FROM authors;

-- c)
-- SELECT au_lname, au_fname, phone FROM authors ORDER BY au_fname, au_lname;

-- d)
-- SELECT au_lname AS first_name, au_fname AS last_name, phone AS telephone FROM authors ORDER BY au_fname, au_lname;

-- e)
-- SELECT au_lname AS first_name, au_fname AS last_name, phone AS telephone FROM authors WHERE au_lname != 'Ringer' and state = 'CA' ORDER BY au_fname, au_lname ;

-- f)
-- SELECT * FROM publishers WHERE pub_name LIKE '%Bo%';

-- g)
-- SELECT DISTINCT p.pub_name FROM publishers AS P INNER JOIN titles AS T ON P.pub_id = T.pub_id WHERE T.type = 'Business';

-- h)
-- SELECT p.pub_id, p.pub_name, SUM(t.ytd_sales) AS total_sales FROM publishers AS p INNER JOIN titles AS t ON p.pub_id = t.pub_id GROUP BY p.pub_id, p.pub_name;

-- i)
-- SELECT p.pub_id, p.pub_name, t.title, SUM(t.ytd_sales) AS total_sales FROM publishers AS p JOIN titles AS t ON p.pub_id = t.pub_id GROUP BY p.pub_id, p.pub_name, t.title;

-- j)
-- SELECT DISTINCT title AS Bookbeat_title FROM titles AS t INNER JOIN sales AS sa ON t.title_id = sa.title_id INNER JOIN stores AS str ON sa.stor_id = str.stor_id WHERE  stor_name ='Bookbeat';

-- k)
-- SELECT au.au_id, au.au_lname, au.au_fname FROM authors AS au INNER JOIN titleauthor AS tau ON au.au_id = tau.au_id INNER JOIN titles AS t ON tau.title_id = t.title_id  GROUP BY au.au_id, au.au_lname, au.au_fname;

-- l)
-- SELECT titles.type, pub_id, AVG(price) AS avg_price, SUM(sales.qty) AS total_sales FROM titles INNER JOIN sales ON titles.title_id = sales.title_id GROUP BY titles.type, pub_id;

-- m)
--SELECT titles.type FROM titles GROUP BY titles.type HAVING MAX(advance) > AVG(price) * 1.5;

-- n)
-- SELECT t.title, au.au_lname, au.au_fname, t.price * t.ytd_sales * t.royalty AS profit FROM authors AS au INNER JOIN titleauthor AS tau ON au.au_id = tau.au_id INNER JOIN titles AS t ON tau.title_id = t.title_id GROUP BY t.title, au.au_lname, au.au_fname, t.price * t.ytd_sales * t.royalty;

-- o)
--SELECT title, ytd_sales, ytd_sales * price AS faturacao, ytd_sales * price * royalty/100 AS auths_revenue , ( ytd_sales * price) - (ytd_sales * price * royalty/100) AS publisher_revenue FROM titles WHERE ytd_sales is not null;

-- p)
--SELECT title, ytd_sales, au.au_fname +' ' + au.au_lname AS author, ytd_sales * price * royalty/100 AS auths_revenue , ( ytd_sales * price) - (ytd_sales * price * royalty/100) AS publisher_revenue FROM titles AS t INNER JOIN titleauthor as tau ON t.title_id = tau.title_id INNER JOIN authors AS au ON au.au_id = tau.au_id WHERE ytd_sales is not null;

-- q)
/*SELECT * FROM (SELECT COUNT(*) AS n_titles FROM titles) AS total_t INNER JOIN (SELECT st.stor_id, st.stor_name, COUNT(t.title_id) AS title_per_store
 FROM (stores AS st INNER JOIN sales AS sa ON st.stor_id=sa.stor_id)
        INNER JOIN titles AS t ON sa.title_id=t.title_id
    GROUP BY st.stor_id, st.stor_name) AS per_st
    ON n_titles=title_per_store;*/

-- r)
/*SELECT stor_id, stor_name
FROM (SELECT avg(qty) AS avg_sales_all_stores
		FROM stores AS st INNER JOIN sales ON st.stor_id=sales.stor_id) AS z
	INNER JOIN
		(SELECT st.stor_id, st.stor_name, avg(sales.qty) AS avg_per_store
		FROM stores AS st INNER JOIN sales ON st.stor_id=sales.stor_id
		GROUP BY st.stor_id, st.stor_name) AS zz
	ON avg_per_store > avg_sales_all_stores;*/

-- s)
/*SELECT title
	FROM titles
	LEFT JOIN sales
		JOIN stores ON stores.stor_id=sales.stor_id
	ON sales.title_id=titles.title_id
	EXCEPT
	SELECT title
		FROM titles JOIN sales JOIN stores
		ON sales.stor_id = stores.stor_id
		ON titles.title_id=sales.title_id
		WHERE stor_name='Bookbeat'*/

-- t)
SELECT pu.pub_id, pu.pub_name, st.stor_id, st.stor_name
FROM publishers AS pu, stores AS st
GROUP BY pu.pub_id, pu.pub_name, st.stor_id, st.stor_name
EXCEPT
SELECT pu.pub_id, pu.pub_name, st.stor_id, st.stor_name
FROM ((publishers AS pu INNER JOIN titles AS t ON pu.pub_id=t.pub_id)
						INNER JOIN sales ON t.title_id=sales.title_id)
						INNER JOIN stores AS st ON st.stor_id=sales.stor_id
GROUP BY pu.pub_id, pu.pub_name, st.stor_id, st.stor_name