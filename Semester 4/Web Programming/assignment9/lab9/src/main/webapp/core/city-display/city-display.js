function addDestination() {
    let destinations = $("#destinations");
    let childrenLength = destinations.children().length;

    let prevCity = $("#destination" + (childrenLength - 1))[0];
    console.log(destinations.children().length - 1);

    let selectedCity = prevCity.value;

    console.log(selectedCity);

    $.ajax({
        url: 'neighbour-display',
        method: 'GET',
        data: {
            id: selectedCity
        },
        dataType: 'json',
        success: function (response) {
            let newCity = document.createElement("select");
            newCity.id = "destination" + (childrenLength);
            newCity.setAttribute("onchange", "historyChanged(" + childrenLength +")");

            response.forEach(function (city) {
                let option = document.createElement("option");
                option.value = city.id;
                option.text = city.name;
                newCity.appendChild(option);
            });

            destinations.append(newCity);
        },
        error: function (xhr, status, error) {
            console.log(error);
            console.log(status);
            console.log(xhr.responseText);
        }
    });
}

function historyChanged(id) {
    let destinations = $("#destinations");
    destinations.children("select").each(function () {
        let id2 = parseInt(this.id.substring(11));
        if (id < id2) {
            $(this).remove();
        }
    })
    addDestination();
}

function logout() {
    $.ajax({
        async: true,
        url: "logout",
        method: "GET",
        error: function (xhr, status, error) {
            console.log("yuk");
            console.log(error);
            console.log(status);
            console.log(xhr.responseText);
        }
    });
}
