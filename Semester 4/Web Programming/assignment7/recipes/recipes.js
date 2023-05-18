// Define the Angular app and controller
let app = angular.module('recipesApp', []);
app.controller('recipesCtrl', function ($scope) {
    $scope.recipes = []; // Array to store recipes
    $scope.newRecipe = {}; // Object to store new recipe
    $scope.selectedRecipe = {}; // Object to store selected recipe
    $scope.filterText = ""; // Filter text
    $scope.tableName = "Recipes"; // Database table name

    // Function to filter recipes based on filter text
    $scope.filterRecipes = function () {
        // Filter recipes array based on filter text
        $scope.recipes = $scope.recipes.filter(function (recipe) {
            return recipe.name.toLowerCase().includes($scope.filterText.toLowerCase());
        });
    };

    // Function to show all recipes
    $scope.selectRecipes = function () {
        // Reset filter text and load all recipes
        $scope.filterText = "";
        $scope.loadRecipes();
    };

    // Function to insert new recipe
    $scope.insertRecipe = function () {
        if ($scope.newRecipe.name === "") {
            alert("name is empty");
            return;
        }
        if ($scope.newRecipe.description === "") {
            alert("description is empty");
            return;
        }
        if ($scope.newRecipe.author === "") {
            alert("author is empty");
            return;
        }

        $.ajax({
            async: true,
            url: "http://127.0.0.1:1234",
            type: "POST",
            dataType: 'text',
            data: {action: "insert_data", table_name: $scope.tableName, data: angular.copy($scope.newRecipe)},
            success: function (result) {
                $scope.newRecipe = {};
                alert(result);
            }
        });
    };

    // Function to delete selected recipe
    $scope.deleteRecipe = function () {
        // Find index of selected recipe in recipes array
        let index = $scope.selectedRecipe.id;
        alert(index);

        $.ajax({
            async: true,
            url: "http://127.0.0.1:1234",
            type: "POST",
            dataType: 'text',
            data: {action: "delete_data", table_name: $scope.tableName, id: index},
            success: function (result) {
                // Reset selectedRecipe object
                $scope.selectedRecipe = {};
                alert(result);
            }
        });
    };

    // Function to update selected recipe
    $scope.updateRecipe = function () {
        // Find index of selected recipe in recipes array
        let index = $scope.selectedRecipe.id;

        $.ajax({
            async: true,
            url: "http://127.0.0.1:1234",
            type: "POST",
            dataType: 'text',
            data: {action: "update_data", table_name: $scope.tableName, id: index, data: $scope.selectedRecipe},
            success: function (result) {
                alert(result);
            }
        });

        // Reset selectedRecipe object
        $scope.selectedRecipe = {};
    };

    // Function to load recipes (sample data)
    $scope.loadRecipes = function () {
        $.ajax({
            async: true,
            url: "http://127.0.0.1:1234",
            type: "GET",
            data: {action: "select_data", table_name: $scope.tableName},
            dataType: 'json',
            success: function (result) {
                $scope.recipes = result;
            }
        });
    };

    $scope.selectRecipe = function(recipe) {
        // Set selectedRecipe to the clicked recipe
        $scope.selectedRecipe = angular.copy(recipe);
        console.log($scope.selectedRecipe);
    };

    // Load recipes on page load
    $scope.loadRecipes();
});