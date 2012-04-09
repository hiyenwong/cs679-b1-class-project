$(document).ready(function() {
	 var data;
     var chart;
     google.load('visualization', '1', {'packages':['corechart']});
     google.setOnLoadCallback(drawChart);

     // Callback that creates and populates a data table,
     // instantiates the pie chart, passes in the data and
     // draws it.
     function drawChart() {

       // Create our data table.
       data = new google.visualization.DataTable();
       data.addColumn('string', 'Topping');
       data.addColumn('number', 'Slices');
       data.addRows([
         ['Mushrooms', 3],
         ['Onions', 1],
         ['Olives', 1],
         ['Zucchini', 1],
         ['Pepperoni', 2]
       ]);

       // Set chart options
       var options = {'title':'How Much Pizza I Ate Last Night', 'width':400,
                      'height':300};

       // Instantiate and draw our chart, passing in some options.
       chart = new google.visualization.PieChart(document.getElementById('chart_div'));
       google.visualization.events.addListener(chart, 'select', selectHandler);
       chart.draw(data, options);
     }

     function selectHandler() {
       var selectedItem = chart.getSelection()[0];
       var value = data.getValue(selectedItem.row, 0);
       alert('The user selected ' + value);
     }
});