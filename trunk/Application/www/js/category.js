$(document).ready(function () {

    $("#addCategoryDialog").dialog({autoOpen: false, title: "Add Category"});

    $("#addCategory").click(function () {
        $("#addCategoryDialog").dialog("open");
    });
    
    $("#saveCategoryItem").click(function() {
    	$("#status").html('<img src="'+image_url+'/loading.gif" /> Creating category');
        $("#addCategoryError").html("");
    
        $.ajax({
            type: "POST",
            url: "category.php",
            data: $("#addCategoryDialog form").serialize(),
            success: function(data) {
                $("#categoryList").html(data);
                $("#status").html("");
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
	$("#status").html('<img src="'+image_url+'/loading.gif" /> Removing category');
    $.ajax({
        type: "POST",
        url: "category.php",
        data: {"action" : "remove", "key" : key},
        success: function(data) {
            $("#categoryList").html(data);
            $("#status").html("");
        }
    });
};
