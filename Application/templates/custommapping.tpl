{include file='header.tpl'}
<div id="header_wrap{if !$homepage}_secondary{/if}">
	<div id="header{if $secondary}_secondary{/if}"><!-- begin header -->
		{include file='upperheader.tpl' user=$user}
	  
	  	{include file='lowerheader.tpl' title='Custom Mapping' message='Create / Manage Custom CSV Mapping'}
	</div><!-- end header -->
</div>

<div id="page{if !$homepage}_secondary{/if}"><!-- start page content -->
          
	<div id="main_content">
		{include file="leftnav.tpl" active='Mapping'}
	
		<div id="main_content_left_secondary">
       		<fieldset>
	       		<legend>Upload file for preview</legend>
	       		<form id="custommapping" action="custommapping.php" method="post" enctype="multipart/form-data">
		        	<p>Please Keep File below 200 Lines, approximately 2Kb</p>
	        		<p><label for="email">File</label><input type="file" name="csv_file" id="csv_file" onchange="clearProgress()" /></p>
	        		<div style="text-align:right">
	        			<div class="progress">
	        				<div class="bar"></div>
	        				<div class="percent">0%</div>
	        			</div>
	        			<input type="submit" id="submitted" name="submitted" style="margin-left: 30px !important" value="Preview" />
	        		</div>
	        	</form>
        	</fieldset>
            
            <div id="status"></div>
            
		</div><!-- end main content left  -->
      		<!-- end main content right  -->
    </div> <!-- end main content  -->
	<div style="clear: both;">&nbsp;</div>       
          
</div>
<div class="push"></div>

{literal}
<script>
var workingTable = null;

function clearProgress() {
	var percentVal = '0%';
	$('#status').empty();
	$('.bar').width(percentVal)
	$('.percent').html(percentVal);
}

(function() {
$('form').ajaxForm({
	beforeSend: function() {
		workingTable = null;
		var percentVal = '0%';
		$('#status').empty();
		$('.bar').width(percentVal);
		$('.percent').html(percentVal);
	},
	uploadProgress: function(event, position, total, percentComplete) {
		var percentVal = percentComplete + '%';
		$('.bar').width(percentVal)
		$('.percent').html(percentVal);
	},
	complete: function(xhr) {
		var json = jQuery.parseJSON(Base64.decode(xhr.responseText));
		if (json.success == 'yes') {
			var results = json.results;
			var table = document.createElement('table');
			for (var i = 0; i < results.length; i++) {
				var lastRow = table.insertRow(table.rows.length);
				for (var j = 0; j < results[i].length; j++) {
					var cell = lastRow.insertCell(j);
					if (typeof results[i][j] != 'undefined' && results[i][j] != null) { 
						var textNode = document.createTextNode(unescape(results[i][j].toString()));
						cell.appendChild(textNode);
					}
				}
			}
			workingTable = table;
			$('#status').empty(); $('#status').append(table);
		} else {
			$('#status').html("Something went wrong, please try again later");
		}
	}
}); 

})();       
</script>
{/literal}

{include file='footer.tpl'}
