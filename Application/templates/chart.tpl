{include file='header.tpl'}

<div id="header_wrap{if !$homepage}_secondary{/if}">
	<div id="header{if $secondary}_secondary{/if}"><!-- begin header -->
		{include file='upperheader.tpl' user=$user}
	  
	  	{include file='lowerheader.tpl' title='Charts' message='Vizualise your data'}
	</div><!-- end header -->
</div>

<div id="page{if !$homepage}_secondary{/if}"><!-- start page content -->
          
	<div id="main_content">
		{include file="leftnav.tpl" active='Chart'}
	
		<div id="main_content_left_secondary">
			<table>
				<tr>
					<td><span id="pie_chart_div" style="width:345px; height:300px"></span></td>
					<td><span id="bar_chart_div" style="width:345px; height:300px"></span></td>
				</tr>
			</table>
		</div><!-- end main content left  -->
    </div> <!-- end main content  -->
	<div class="clear">&nbsp;</div>       
          
</div>
<div class="push"></div>

{literal}
<script type="text/javascript">
	google.load("visualization", "1", {packages:["corechart"]});
	google.setOnLoadCallback(drawPieChart);
	function drawPieChart() {
		var jsonData = $.ajax({
			url: base_url + "/chart.php?func=getData&chart=pie",
			dataType:"json",
			async: false}).responseText;
		var data = new google.visualization.DataTable(jsonData);
		var chart = new google.visualization.PieChart(document.getElementById('pie_chart_div'));
		var formatter = new google.visualization.NumberFormat({prefix: '$', negativeColor: 'red', negativeParens: true});
		formatter.format(data, 1);
		var options = {
          title: 'Past 6 Months Spending',
          allowHtml: true,
          width: 345,
          height: 300
        };
		chart.draw(data, options);
	}
	
	google.load("visualization", "1", {packages:["corechart"]});
	google.setOnLoadCallback(drawBarChart);
	function drawBarChart() {
		var jsonData = $.ajax({
			url: base_url + "/chart.php?func=getData&chart=bar",
			dataType:"json",
			async: false}).responseText;
		var data = new google.visualization.DataTable(jsonData);
		var chart = new google.visualization.BarChart(document.getElementById('bar_chart_div'));
		// var formatter = new google.visualization.NumberFormat({prefix: '$', negativeColor: 'red', negativeParens: true});
		// formatter.format(data, 1);
		var options = {
          title: 'Past 6 Months Spending By Category',
          allowHtml: true,
          width: 345,
          height: 300
        };
		chart.draw(data, options);
	}
</script>
{/literal}

{include file='footer.tpl'}
