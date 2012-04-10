{include file='header.tpl'}

<script type="text/javascript" src="https://www.google.com/jsapi"></script>
<script type="text/javascript" src="{$js_url}/chart.js"></script>
<link type="text/css" href="{$style_url}/ui-lightness/jquery-ui-1.8.18.custom.css" rel="Stylesheet" />
<script type="text/javascript" src="{$js_url}/jquery-ui-1.8.18.custom.min.js"></script>

{literal}
<script>
	$(function() {
		$( "#tabs" ).tabs();
	});
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
		
		<div id="main_content_left_secondary">   
                    
		</div><!-- end main content left  -->
		<div id="chart_div" style="width:400; height:300; float:left;"></div>
		<div id="barchart_div" style="width:400; height:300; float:right; margin-top: -300px"></div>
		<div style="clear: both;"></div>
      	<!-- end main content right  -->
    </div> <!-- end main content  -->       
          
</div>
<div class="push"></div>

{include file='footer.tpl'}
