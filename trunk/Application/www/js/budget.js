$(document).ready(function () {

    //validate and show next set of fields (first, last names)
    $("#addBudget").click(function () {
        $("#addBudgetRow").toggle();
    });
    
    $("#saveBudgetItem").click(function() {
        var category = "", budgeted = 0;
        categoryId = $("#addCategory").val();
        budgetedAmount = $("#addBudgeted").val();
        
        $.ajax({
            type: "POST",
            url: "budget.php",
            data: {"categoryId" : categoryId, "budgetedAmount" : budgetedAmount},
            success: function (msg) {
                alert(msg);
                $("#error").html(msg);
            }
        });
    });
    
});
