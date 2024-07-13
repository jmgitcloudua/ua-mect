use dbname;

-- Insert dummy data

insert into recipie
(recipieName, author, calories, preparingTime)
values
('Padding', 'Someone', 40, 1000),
('Target', 'Me', 90, 10),
('Another', 'Someone', 900, 100);
insert into utensil
(utensilName, dimention, unit)
values
('Bimbi', 1, 'a'),
('Colher', 2, 'b'),
('Chávena', 3, 'c'),
('Batedeira', 4, 'd');
insert into ingredient
(ingredientName, description)
values
('Tomate', 'fruta'),
('Carne', 'muito específico'),
('Leite', 'I forgor 💀');
insert into category
(categoryName, description),
values
('Dieta', 'Removes fat in 30 days, doctors shocked'),
('Another', 'Does not remove fat, doctors unresponsive');
insert into step
(stepID, description, image)
values
(1, 'Certa 1', 'img.png'),
(2, 'Certa 2', 'img.png'),
(3, 'Certa 3', 'img.png'),
(4, 'Errada 1', 'img.png'),
(5, 'Errada 2', 'img.png');
insert into has
(id, recipieName, stepID, stepNum)
values
(1, 'Target', 1, 1),
(2, 'Target', 2, 2),
(3, 'Target', 3, 3),
(4, 'Another', 4, 4),
(5, 'Another', 5, 5);
insert into usesUtensil
(id, stepID, utensilName)
values
(1, 1, 'Bimbi'),
(2, 2, 'Colher'),
(3, 3, 'Chávena'),
(4, 4, 'Batedeira');
insert into usesIngredient
(id, stepID, ingredientName, quantity, unit)
values
(1, 1, 'Tomate', 2, 'g'),
(2, 2, 'Leite', 4, 'kg'),
(3, 3, 'Tomate', 6, 'L'),
(4, 4, 'Carne', 100, 'nC');
insert into belongs
(recipieName, categoryName)
values
('Target', 'Dieta');
('Another', 'Another');
('Padding', 'Another');

-- List ingredients

select distinct ingredient.ingredientName
from
	(
		ingredient join usesIngredient
		on ingredient.ingredientName = usesIngredient.ingredientName
	) join (
		has join step
		on has.stepID = step.stepID
	) on usesIngredient.stepID = step.stepID
where has.recipieName = 'Target';

-- List utensils

select distinct usesUtensil.utensilName
from
	usesUtensil
	join (
		has join step
		on has.stepID = step.stepID
	) on usesUtensil.stepID = step.stepID
where has.recipieName = 'Target';

-- List recipies by category

select belongs.recipieName
from belongs 
where belongs.categoryName = 'Dieta';

-- List recipies by author 

select *
from recipie
where recipie.author = 'Me';
