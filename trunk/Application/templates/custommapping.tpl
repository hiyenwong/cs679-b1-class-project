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
	        	
	        	<div id="status" style="height:1em"></div>
	        	
	        	<div id="fileControllSection" style="display:none">
	        		<div id="fileControllStatus" style="height:1em;"></div>
	        		<table cellspacing="0" cellpadding="0">
	        			<tr>
	        				<td class="startingRows" rowspan="2">Starting Row: </td>
	        				<td id="beginRow" class="startingRows" rowspan="2">0</td>
	        				<td><a class="pointer" onclick="updateStartRow(1)"><img src="{$image_url}/bullet_up.png"/></a></td>
	        			</tr>
	        			<tr>
	        				<td><a class="pointer" onclick="updateStartRow(-1)"><img src="{$image_url}/bullet_down.png"/></a></td>
	        			</tr>
	        		</table>
	        		<table cellspacing="0" cellpadding="0">
	        			<tr>
	        				<td colspan="3" class="rightalign middlealign">Mapping Name <input type="text" name="name" id="name" /></td>
	        			</tr>
	        			<tr>
	        				<td colspan="3" style="padding-top: 15px; padding-bottom: 5px">Please Enter the Column # into each field for mapping. Enter just the number.</td>
	        			</tr>
	        			<tr>
	        				<td colspan="3" class="rightalign middlealign">Transaction Date <input type="text" name="transaction_date" id="transaction_date" /></td>
	        			</tr>
	        			<tr>
	        				<td colspan="3" class="rightalign middlealign">Description <input type="text" name="description" id="description" /></td>
	        			</tr>
	        			<tr>
	        				<td colspan="3" class="rightalign middlealign">Amount <input type="text" name="amount" id="amount" /></td>
	        			</tr>
	        			<tr>
	        				<td colspan="3" class="rightalign"><input type="button" value="Create Custom Mapping" onclick="createCustomMapping()" /></td>
	        			</tr>
	        		</table>
	        	</div>
        	</fieldset>
            
            <fieldset style="width: 100% !important">
            	<legend>Preview</legend>
            	<div id="preview"></div>
            </fieldset>
            
		</div><!-- end main content left  -->
      		<!-- end main content right  -->
    </div> <!-- end main content  -->
	<div style="clear: both;">&nbsp;</div>       
          
</div>
<div class="push"></div>

{literal}
<script>

var headerRow = null;

function clearProgress() {
	headerRow = null;
	var percentVal = '0%';
	$('#preview').empty();
	$('.bar').width(percentVal)
	$('.percent').html(percentVal);
	$('#fileControllSection').hide();
	$('#beginRow').html("0");
	
	
}

function updateStartRow(change) {
	var startRow = parseInt($('#beginRow').html()) + change;
	if (startRow < 0) {
		$('#fileControllStatus').html('You have reach the beginning of the preview');
	} else if (startRow > 20) {
		$('#fileControllStatus').html('You have reach the end of the preview');
	} else {
		$('#fileControllStatus').html("");
		$('#beginRow').html(startRow);
		
		$("#previewTable tr:gt(0)").each(function(index) {
			if (index < startRow) {
				$('#'+this.id).hide();
			} else  if (index == startRow+1) {
				$('#headerRow td').each(function(index) {
					$('#'+this.id).remove();
				});
				$('#'+this.id+' td').each(function(index) {
					var headerCell = headerRow.insertCell(index);
					headerCell.id = 'HeaderColumn' + index;
					headerCell.appendChild(document.createTextNode("Column " + index));
				});
			
				$('#'+this.id).show();
			} else {
				$('#'+this.id).show();
			}
		});
	}
}

function createCustomMapping() {
	var startingRow = parseInt($('#beginRow').html()) + 1;
	var name = $('#name').val();
	var transactionDate = $('#transaction_date').val();
	var description = $('#description').val();
	var amount = $('#amount').val();
	
	$('#status').html('<img src="'+image_url+'/loading.gif"/> Please wait while we create your custom mapping');
	jQuery.ajax({
		url:base_url+'/custommapping.php?submitted=Save&startingRow='+startingRow+'&name='+name+'&transactionDate='+transactionDate+'&description='+description+'&amount='+amount
	}).done(function(data) {
		window.location.href = base_url+"/dashboard.php";
	}).fail(function(data) {
		$('#preview').html(data);
	}).always(function(data) {
		$('#status').html('');
	});
	
}

(function() {
$('form').ajaxForm({
	beforeSend: function() {
		headerRow = null;
		var percentVal = '0%';
		$('#preview').empty();
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
			table.id = "previewTable";
			
			headerRow = table.insertRow(table.rows.length);
			headerRow.id = 'headerRow';
			
			for (var i = 0; i < results.length; i++) {
				var currentRow = table.insertRow(table.rows.length);
				currentRow.id = 'row' + i;
				for (var j = 0; j < results[i].length; j++) {
					if (i == 0) {
						var headerCell = headerRow.insertCell(j);
						headerCell.id = 'HeaderColumn' + j;
						headerCell.appendChild(document.createTextNode("Column " + j));
					}
				
					var cell = currentRow.insertCell(j);
					cell.id = 'Column ' + j;
					cell.appendChild((typeof results[i][j] != 'undefined' && results[i][j] != null) ? document.createTextNode(unescape(results[i][j].toString())) : document.createTextNode(""));
				}
			}
			$('#preview').empty(); $('#preview').append(table);
			$('#previewTable').css('width', '100%');
			$('#fileControllSection').show();
		} else {
			$('#preview').html("Something went wrong, please try again later");
		}
	}
}); 

})();       
</script>
{/literal}

{include file='footer.tpl'}
