// Run script once DOM is loaded
document.addEventListener('DOMContentLoaded', function() {

    // Alert when Search button clicked
    document.querySelector('form').addEventListener('submit', function(e) {
        alert("How many developers does it take to screw in a lightbulb? \n\nNone. It's a hardware problem.");
        e.preventDefault();
    });

    // Show block of text corresponding to list selection in professional info
    let prof_list_selection = document.querySelectorAll('.list-group-item');
    for (let selection of prof_list_selection) {
        selection.addEventListener("click", function() {
            let blockId = selection.dataset.blockId;
            prof_list_result = document.querySelectorAll('.prof-list-result div');
            for (let text of prof_list_result) {
                if (text.id === blockId) {
                    // show block selected
                    text.style.display = 'block';
                } else {
                    // hide others
                    text.style.display = 'none';
                }
            }
        });
    }
});
