{include file='header.tpl'}
<div id="header_wrap{if !$homepage}_secondary{/if}">
	<div id="header{if $secondary}_secondary{/if}"><!-- begin header -->
		{include file='upperheader.tpl' user=$user}
	  
	  	{include file='lowerheader.tpl' title='Uploader' message='Upload a CSV file'}
	</div><!-- end header -->
</div>

<div id="page{if !$homepage}_secondary{/if}"><!-- start page content -->
          
	<div id="main_content">
		{include file="leftnav.tpl" active='Upload'}
	
		<div id="main_content_left_secondary">
       		<fieldset>
	       		<legend>Upload a CSV file</legend>
	        	<form action="process.php" method="POST" enctype="multipart/form-data">
	        		<table style="margin: 0 auto;">
	        			<tr>
	        				<th>File</th>
	        				<td class="leftalign"><input type="file" name="csv_file" id="csv_file"></td>
	        			</tr>
	        			<tr>
	        				<th nowrap="nowrap">Mapping Type</th>
	        				<td class="leftalign">{html_options name=mapping_type id=mapping_type options=$mappingTypes}</td>
	        			</tr>
	        			<tr>
	        				<td colspan="2" class="rightalign"><input type="submit" name="submit" value="Process File"></td>
	        			</tr>
	        		</table>
	        	</form>
        	</fieldset>
                    
		</div><!-- end main content left  -->
      		<!-- end main content right  -->
    </div> <!-- end main content  -->
	<div style="clear: both;">&nbsp;</div>       
          
</div>
<div class="push"></div>

{include file='footer.tpl'}
