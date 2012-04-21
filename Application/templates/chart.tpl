{include file='header.tpl'}

{literal}
<script type="text/javascript">
	google.load("visualization", "1", {packages:["corechart"]});
	google.setOnLoadCallback(drawChart);
	function drawChart() {
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
          width: 400,
          height: 300
        };
		chart.draw(data, options);
	}
</script>
{/literal}

<div id="header_wrap{if !$homepage}_secondary{/if}">
	<div id="header{if $secondary}_secondary{/if}"><!-- begin header -->
		{include file='upperheader.tpl' user=$user}
	  
	  	{include file='lowerheader.tpl' title='Charts' message='Vizualise your data'}
	</div><!-- end header -->
</div>

<div id="page{if !$homepage}_secondary{/if}" id="chart"><!-- start page content -->
          
	<div id="main_content">
		{include file="leftnav.tpl" active='Chart'}
		
		<div id="main_content_left_secondary"></div><!-- end main content left  -->
		
		<div id="pie_chart_div"></div>
		<div style="clear: both;"></div>
      	<!-- end main content right  -->
    </div><!-- end main content  -->       
          
</div>
<div class="push"></div>

{include file='footer.tpl'}
