$(document).ready(function () {

    $("#addCategoryDialog").dialog({autoOpen: false, title: "Add Category"})

    $("#addCategory").click(function () {
        $("#addCategoryDialog").dialog("open");
    });
    
    $("#saveCategoryItem").click(function() {
    
        /*if (!$("#addBudgeted").val().match(/^\d+(\.\d{2})?$/)) {
            $("#addBudgetError").html("Please enter a valid number in the form of either <b>5</b> or <b>5.20</b>.");
            return;
        }*/
        $("#addCategoryError").html("");
    
        $.ajax({
            type: "POST",
            url: "category.php",
            data: $("#addCategoryDialog form").serialize(),
            success: function(data) {
                $("#categoryList").html(data);
            }
        });
        
        $("#categoryName").val("");
        $("#addCategoryDialog").dialog("close");
    });
    
    $("#cancelCategoryItem").click(function() {
        $("#addCategoryError").html("");
        $("#categoryName").val("");
        $("#addCategoryDialog").dialog("close");
    });
    
});

var removeCategory = function(obj, key) {
    $.ajax({
        type: "POST",
        url: "category.php",
        data: {"action" : "remove", "key" : key},
        success: function(data) {
            $("#categoryList").html(data);
        }
    });
}
