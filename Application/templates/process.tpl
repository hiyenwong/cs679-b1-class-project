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
	        		<div id="status" style="height:1em;">{$message}</div>
	        	
	        		<table style="margin: 0 auto;">
	        			<tr>
	        				<th>File</th>
	        				<td class="leftalign"><input type="file" name="csv_file" id="csv_file"></td>
	        			</tr>
	        			<tr>
	        				<th>Mapping Type</th>
	        				<td class="leftalign">{html_options name=mapping_type id=mapping_type options=$mappingTypes}</td>
	        			</tr>
	        			<tr>
	        				<td colspan="2" class="rightalign"><input type="submit" name="submit" value="Process File" onclick="upload()"></td>
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

{literal}
<script type="text/javascript">
function upload() {
	$('#status').html('<img src="'+image_url+'/loading.gif" />');
}
</script>
{/literal}

{include file='footer.tpl'}
