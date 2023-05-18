$(function () {
    const tableName = "Ingredients";
    let selectedTableId = -1;

    // Select data from the database
    $("#select-button").on("click", function () {
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
                const header = "<tr><th>ID</th><th>Name</th></tr>";
                datatable.append(header);

                result.forEach(function (item) {
                    const row = "<tr class='clickable-row'><td>" + item.id +
                        "</td><td>" + item.name + "</td></tr>";
                    datatable.append(row);
                });
            }
        });
    });

    // Insert data into the database
    $("#insert-button").on("click", function () {
        const name = $("#name-input");

        if (name.val() === "") {
            alert("name is empty");
            return;
        }

        const data = {
            name: name.val()
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
            name: $("#name-update-input").val()
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
        const name = $(this).find('td:nth-child(2)');
        console.log(name.html());
        $("#name-update-input").val(name.html());
        console.log("selected id: " + selectedTableId);
    });
});
