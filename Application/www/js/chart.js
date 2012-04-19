// Load the Visualization API and the piechart package.
google.load('visualization', '1.0', {'packages':['corechart']});
// Set a callback to run when the Google Visualization API is loaded.
google.setOnLoadCallback(drawChart);

// Callback that creates and populates a data table, 
// instantiates the pie chart, passes in the data and
// draws it.
function drawChart() {
    var jsonData = $.ajax({
        url: "chart_data.php",
        dataType:"json",
        async: false
        }).responseText;
        
    // Create our data table out of JSON data loaded from server.
    var data = new google.visualization.DataTable(jsonData);

    // Instantiate and draw our chart, passing in some options.
    var chart = new google.visualization.PieChart(document.getElementById('chart_div'));
    chart.draw(data, {width: 400, height: 240});
    var chart2 = new google.visualization.BarChart(document.getElementById('barchart_div'));
    chart2.draw(data, {width: 400, height: 240});
  }