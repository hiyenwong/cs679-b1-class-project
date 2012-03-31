{include file='header.tpl'}
<div id="header_wrap{if !$homepage}_secondary{/if}">
	<div id="header{if $secondary}_secondary{/if}"><!-- begin header -->
		{include file='upperheader.tpl' user=$user}
	  
	  	{include file='lowerheader.tpl' title='Budgets' message='Modify your budgets'}
	</div><!-- end header -->
</div>
		
<div id="page{if !$homepage}_secondary{/if}"><!-- start page content -->
          
	<div id="main_content">
		{include file="leftnav.tpl" active='Budget'}

		<div id="main_content_left_secondary">   
          	
                    
		</div><!-- end main content left  -->
      		<!-- end main content right  -->
    </div> <!-- end main content  -->
	<div style="clear: both;">&nbsp;</div>       
          
</div>
<div class="push"></div>

{include file='footer.tpl'}
