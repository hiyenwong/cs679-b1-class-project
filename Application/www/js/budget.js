$(document).ready(function () {

    $("#addBudgetRow").dialog({autoOpen: false})

    $("#addBudget").click(function () {
        $("#addBudgetRow").dialog("open");
    });
    
    $("#saveBudgetItem").click(function() {
        $.ajax({
            type: "POST",
            url: "budget.php",
            data: $("#addBudgetRow form").serialize()
        });
        
        $("#addBudgeted").val("");
        $("#addBudgetRow").dialog("close");
    });
    
    $("#cancelBudgetItem").click(function() {
        $("#addBudgetRow").dialog("close");
    });
    
});

var removeBudgetItem = function(obj, key) {
    $.ajax({
        type: "POST",
        url: "budget.php",
        data: {"action" : "remove", "key" : key}
    });

    $(obj).parents("tr").remove();
}
