$(function () {
    const tableName = "RecipeInstructions";
    let selectedTableId = -1;

    // Select data from the database
    $("#select-button").on("click", function () {
        // console.log("select function");
        const datatable = $("#data-table");

        $.ajax({
            async: true,
            url: "http://127.0.0.1:1234",
            type: "GET",
            data: {action: "select_data", table_name: tableName},
            dataType: 'json',
            success: function (result) {
                // Clear the table
                datatable.empty();

                // Add the table header
                const header = "<tr><th>ID</th><th>Recipe</th><th>Ingredient</th><th>Amount</th></tr>";
                datatable.append(header);

                result.forEach(function (item) {
                    const row = "<tr class='clickable-row'><td>" + item.id +
                        "</td><td>" + item.recipe +
                        "</td><td>" + item.ingredient +
                        "</td><td>" + item.amount + "</td></tr>";
                    datatable.append(row);
                });
            }
        });
    });

    // Insert data into the database
    $("#insert-button").on("click", function () {
        const recipe = $("#recipe-input");
        const ingredient = $("#ingredient-input");
        const amount = $("#amount-input");

        if (recipe.val() === "") {
            alert("name is empty");
            return;
        }
        if (ingredient.val() === "") {
            alert("description is empty");
            return;
        }
        if (amount.val() === "") {
            alert("author is empty");
            return;
        }

        const data = {
            recipe: recipe.val(),
            ingredient: ingredient.val(),
            amount: amount.val()
        };

        $.ajax({
            async: true,
            url: "http://127.0.0.1:1234",
            type: "POST",
            dataType: 'text',
            data: {action: "insert_data", table_name: tableName, data: data},
            success: function (result) {
                alert(result);
            }
        });
    });

    // Delete data from the database
    $("#delete-button").on("click", function () {
        $("#delete-text-area").val(selectedTableId);

        $.ajax({
            async: true,
            url: "http://127.0.0.1:1234",
            type: "POST",
            dataType: 'text',
            data: {action: "delete_data", table_name: tableName, id: selectedTableId.valueOf()},
            success: function (result) {
                alert(result);
            }
        });
    });

    // Update data in the database
    $("#update-button").on("click", function () {
        const id = selectedTableId;
        const data = {
            recipe: $("#recipe-update-input").val(),
            ingredient: $("#ingredient-update-input").val(),
            amount: $("#amount-update-input").val()
        };

        $.ajax({
            async: true,
            url: "http://127.0.0.1:1234",
            type: "POST",
            dataType: 'text',
            data: {action: "update_data", table_name: tableName, id: id, data: data},
            success: function (result) {
                alert(result);
            }
        });
    });

    $(document).on("click", ".clickable-row", function(){
        $(this).addClass('selected').siblings().removeClass('selected');
        selectedTableId = $(this).find('td:first').html();

        const recipe = $(this).find('td:nth-child(2)');
        const ingredient = $(this).find('td:nth-child(3)');
        const amount = $(this).find('td:nth-child(4)');

        console.log(recipe.html(), ingredient.html(), amount.html());

        $("#name-update-input").val(recipe.html());
        $("#description-update-input").val(ingredient.html());
        $("#author-update-input").val(amount.html());

        console.log("selected id: " + selectedTableId);
    });
});
