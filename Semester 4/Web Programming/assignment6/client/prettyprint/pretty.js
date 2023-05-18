$(function () {
    const recipesTable = "Recipes";
    const instructionsTable = "RecipeInstructions";
    const ingredientsTable = "Ingredients";

    function makeRecipe(name, description, author, ingredientsList) {
        let html = ""

        html += "<span>" + name + "</span><br>";
        html += "<span>" + description + "</span><br>";
        html += "<span>" + author + "</span><br>";
        html += "<table>";

        ingredientsList.forEach(function (item) {
            html += "<tr><th>" + item.ingredient + "</th><th>" + item.amount + "</th></tr>";
        });

        html += "</table>";
        html += "<hr>";
        return html;
    }

    $("#show-button").on("click", function () {
        const recipesDiv = $("recipes-div");

        $.ajax({
            url: "http://127.0.0.1:1234",
            type: "GET",
            data: {action: "pretty_print"},
            dataType: 'json',
            success: function (result) {
                console.log(result);
            }
        });

        // $.ajax({
        //     url: "http://127.0.0.1:1234",
        //     type: "GET",
        //     data: {action: "select_data", table_name: recipesTable},
        //     dataType: 'json',
        //     success: function (result) {
        //         // Clear the table
        //         recipesDiv.empty();
        //
        //         result.forEach(function (recipe) {
        //             var ingredientsList = [];
        //             $.ajax({
        //                 url: "http://127.0.0.1:1234",
        //                 type: "GET",
        //                 data: {action: "select_specific_data", table_name: instructionsTable, key: "recipe", value: recipe.id},
        //                 dataType: 'json',
        //                 success: function (result) {
        //                     result.forEach(function (instruction) {
        //                         $.ajax({
        //                             url: "http://127.0.0.1:1234",
        //                             type: "GET",
        //                             data: {action: "select_specific_data", table_name: ingredientsTable, key: "id", value: instruction.ingredient},
        //                             dataType: 'json',
        //                             success: function (result) {
        //                                 console.log(result.id);
        //                                 ingredientsList.push({
        //                                     amount: instruction.amount,
        //                                     ingredient: result.name
        //                                 });
        //                             }
        //                         });
        //                     });
        //                 }
        //             });
        //             let res = makeRecipe(recipe.name, recipe.description, recipe.author, ingredientsList);
        //             console.log(res);
        //             // add element
        //             recipesDiv.append(res);
        //         });
        //     }
        // });
    });
});