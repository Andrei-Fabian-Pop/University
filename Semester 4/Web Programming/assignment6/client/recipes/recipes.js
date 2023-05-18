$(function () {
    const tableName = "Recipes";
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
                const header = "<tr class='table-row'><th>ID</th><th>Name</th><th>Description</th><th>Author</th></tr>";
                datatable.append(header);

                result.forEach(function (item) {
                    const row = "<tr class='clickable-row'><td>" + item.id +
                        "</td><td>" + item.name +
                        "</td><td>" + item.description +
                        "</td><td>" + item.author + "</td></tr>";
                    datatable.append(row);
                });
            }
        });
    });

    // Insert data into the database
    $("#insert-button").on("click", function () {
        const name = $("#name-input");
        const description = $("#description-input");
        const author = $("#author-input");

        if (name.val() === "") {
            alert("name is empty");
            return;
        }
        if (description.val() === "") {
            alert("description is empty");
            return;
        }
        if (author.val() === "") {
            alert("author is empty");
            return;
        }

        const data = {
            name: name.val(),
            description: description.val(),
            author: author.val()
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
            name: $("#name-update-input").val(),
            description: $("#description-update-input").val(),
            author: $("#author-update-input").val()
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

    $(document).on("click", ".clickable-row", function () {
        $(this).addClass('selected').siblings().removeClass('selected');
        selectedTableId = $(this).find('td:first').html();

        const name = $(this).find('td:nth-child(2)');
        const description = $(this).find('td:nth-child(3)');
        const author = $(this).find('td:nth-child(4)');

        console.log(name.html(), description.html(), author.html());

        $("#name-update-input").val(name.html());
        $("#description-update-input").val(description.html());
        $("#author-update-input").val(author.html());

        console.log("selected id: " + selectedTableId);
    });

    $("#filter-button").on("click", function () {
        const filter_text = $("#filter-input").val();
        if (filter_text === "") {
            $("#select-button").click();
        }
        const datatable = $("#data-table");
        let rows = $('.clickable-row');
        let res = "";

        for (let i = 0; i < rows.length; ++i) {
            if (rows[i].innerHTML.includes(filter_text)) {
                res += rows[i].innerHTML;
            }
        }

        datatable.empty();

        const header = "<tr><th>ID</th><th>Name</th><th>Description</th><th>Author</th></tr>";
        datatable.append(header);
        datatable.append(res);
    })
});
