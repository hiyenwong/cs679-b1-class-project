$(document).ready(function () {

    $("#addBudgetRow").dialog({autoOpen: false, title: "Add Budget Item"});

    $("#addBudget").click(function () {
        $("#addBudgetRow").dialog("open");
    });
    
    $("#saveBudgetItem").click(function() {
    
        if (!$("#addBudgeted").val().match(/^\d+(\.\d{2})?$/)) {
            $("#addBudgetError").html("Please enter a valid number in the form of either <b>5</b> or <b>5.20</b>.");
            return;
        }
        $("#addBudgetError").html("");
    
        $("#status").html('<img src="'+image_url+'/loading.gif" /> Creating budget item');
        
        $.ajax({
            type: "POST",
            url: "budget.php",
            data: $("#addBudgetRow form").serialize(),
            success: function(data) {
                $("#budgetTable").html(data);
                $("#status").html("");
            }
        });
        
        $("#addBudgeted").val("");
        $("#addBudgetRow").dialog("close");
    });
    
    $("#cancelBudgetItem").click(function() {
        $("#addBudgetError").html("");
        $("#addBudgeted").val("");
        $("#addBudgetRow").dialog("close");
    });
    
});

var removeBudgetItem = function(obj, key) {
    $("#status").html('<img src="'+image_url+'/loading.gif" /> Removing budget item');
    $.ajax({
        type: "POST",
        url: "budget.php",
        data: {"action" : "remove", "key" : key},
        success: function(data) {
            $("#budgetTable").html(data);
            $("#status").html("");
        }
    });

    //$(obj).parents("tr").remove();
};
