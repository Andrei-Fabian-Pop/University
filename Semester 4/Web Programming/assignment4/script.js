function sortAndDisplay() {
    const input = document.getElementById('input').value.trim();
    const numArray = input.split(/\s+/).map(Number);

    numArray.sort((a, b) => a - b);

    const output = document.getElementById('output');
    output.innerHTML = '';

    const rows = Math.ceil(numArray.length / 5);
    for (let i = 0; i < rows; ++i) {
        const row = document.createElement('tr');
        for (let j = 0; j < 5; ++j) {
            const index = i * 5 + j;
            if (index >= numArray.length) {
                break;
            }

            const cell = document.createElement('td');
            cell.innerText = numArray[index].toString();
            row.appendChild(cell);
        }
        output.appendChild(row);
    }
}

window.addEventListener("keypress", function (event) {
    if (event.key === "Enter" && event.ctrlKey.valueOf()) {
        sortAndDisplay();
    }
});
