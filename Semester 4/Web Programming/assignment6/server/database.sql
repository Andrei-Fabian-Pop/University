# mysql

create table Recipes
(
    id          int primary key auto_increment,
    name        varchar(128) unique,
    description varchar(512),
    author      varchar(64)
);

create table Ingredients
(
    id   int primary key auto_increment,
    name varchar(64)
);

create table RecipeInstructions
(
    id         int primary key auto_increment,
    recipe     int not null,
    ingredient int not null,
    amount     int,

    constraint recipesForeignKey foreign key (recipe) references Recipes (id),
    constraint ingredientsForeignKey foreign key (ingredient) references Ingredients (id)
);

INSERT INTO Recipes (name, description, author)
VALUES ('Spaghetti Bolognese', 'Classic Italian dish made with spaghetti and a meat sauce', 'Maria Rossi'),
       ('Chicken Curry', 'Creamy curry made with chicken, onions, and spices', 'David Lee'),
       ('Grilled Salmon', 'Fresh salmon fillet grilled to perfection', 'Emily Chen'),
       ('Pesto Pasta', 'Pasta dish made with homemade pesto sauce and cherry tomatoes', 'Giuseppe Bianchi'),
       ('Tuna Salad', 'Healthy salad made with tuna, greens, and a lemon vinaigrette', 'Jessica Kim'),
       ('Beef Stew', 'Hearty stew made with beef, potatoes, and carrots', 'Michael Nguyen'),
       ('Veggie Stir-Fry', 'Stir-fry made with assorted vegetables and tofu', 'Sara Lee'),
       ('Blueberry Pancakes', 'Fluffy pancakes with fresh blueberries and maple syrup', 'John Smith'),
       ('Roasted Chicken', 'Juicy chicken roasted with herbs and spices', 'Anna Garcia'),
       ('Mushroom Risotto', 'Creamy risotto made with mushrooms and parmesan cheese', 'Giovanni Rossi');


INSERT INTO Ingredients (name)
VALUES ('Flour'),
       ('Sugar'),
       ('Salt'),
       ('Baking Powder'),
       ('Eggs'),
       ('Milk'),
       ('Butter'),
       ('Olive Oil'),
       ('Garlic'),
       ('Onion'),
       ('Tomatoes'),
       ('Lettuce'),
       ('Chicken'),
       ('Beef'),
       ('Pork'),
       ('Salmon'),
       ('Shrimp'),
       ('Lemon'),
       ('Lime'),
       ('Cilantro');

INSERT INTO RecipeInstructions (recipe, ingredient, amount)
VALUES (5, 1, 300),
       (6, 2, 100),
       (7, 3, 10),
       (8, 4, 5),
       (9, 11, 3),
       (10, 13, 500),
       (2, 8, 20),
       (2, 9, 3),
       (2, 10, 2),
       (2, 12, 100),
       (2, 13, 500),
       (2, 15, 500),
       (3, 8, 10),
       (3, 16, 4),
       (3, 17, 20),
       (3, 18, 10),
       (4, 1, 300),
       (4, 2, 50),
       (4, 3, 5),
       (4, 4, 5),
       (4, 8, 20);
