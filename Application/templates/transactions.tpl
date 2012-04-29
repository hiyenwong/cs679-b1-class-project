{include file='header.tpl'}

<style type="text/css">
	@import "{$style_url}/datatable/demo_page.css";
	@import "{$style_url}/datatable/jquery.dataTables.css";
	@import "{$style_url}/datatable/TableTools.css";
	@import "{$style_url}/datatable/dataTables.editor.css";
	@import "{$style_url}/datatable/jquery.dataTables_themeroller.css";
	@import "{$style_url}/datatable/TableTools_JUI.css";
	@import "{$style_url}/datatable/site.css";
</style>
  
  <script type="text/javascript" charset="utf-8" src="{$js_url}/jquery-1.7.2.min.js"></script>
  <script type="text/javascript" charset="utf-8" src="{$js_url}/datatable/jquery.dataTables.js"></script>
  <script type="text/javascript" charset="utf-8" src="{$js_url}/datatable/TableTools.js"></script>
  <script type="text/javascript" charset="utf-8" src="{$js_url}/datatable/dataTables.editor.js"></script>
  <script type="text/javascript" charset="utf-8" src="{$js_url}/jquery-ui-1.8.19.custom.min.js"></script>
  <script type="text/javascript" charset="utf-8" src="{$js_url}/datatable/ZeroClipboard.js"></script>
		
<div id="header_wrap{if !$homepage}_secondary{/if}">
	<div id="header{if $secondary}_secondary{/if}"><!-- begin header -->
		{include file='upperheader.tpl' user=$user}
	  	{include file='lowerheader.tpl' title='Transactions' message='Transaction Details'}
	</div><!-- end header -->
</div>
		
<div id="page{if !$homepage}_secondary{/if}"><!-- start page content -->
          
	<div id="main_content">
		{include file="leftnav.tpl" active='Transaction'}
         
		<div id="main_content_left_secondary">   
          	{if sizeof($user->getActivities())}
			
			<table cellpadding="0" cellspacing="0" border="0" class="display" id="dataTables">
				<thead>
					<tr>
						<th>ID</th>
						<th>Trans. Name</th>
						<th>Category</th>
						<th>Trans. Date</th>
						<th>Amount</th>
					</tr>
				</thead>
				<tbody>
					{foreach from=$res item=i}
				  	<tr align="left">
					  	<td id=myId>{$i->getId()}</td>
					  	<td>{$i->getName()}</td>
					  	<td>{$i->getCategory()}</td>
					  	<td>{$i->getTransactionDate()}</td>
					  	<td>{$i->getAmount()}</td>
				  	</tr>
					{/foreach}
				</tbody>
				<tfoot>
					<tr>
						<th>ID</th>
						<th>Trans. Name</th>
						<th>Category</th>
						<th>Trans. Date</th>
						<th>Amount</th>
					</tr>
				</tfoot>
			</table>        

                   
		{literal}
		<script type="text/javascript" charset="utf-8" id="init-code">
		
		var editor; // use a global for the submit and return data rendering in the examples
		
		$(document).ready(function() {
		    editor = new $.fn.dataTable.Editor( {
		        "ajaxUrl": base_url+"/transactions.php",
		        "domTable": "#dataTables",
		        "events": {
		            "onCreate": function (json, data) {
		            	document.location.reload();
		            },
		            "onEdit": function (json, data) {
		            	document.location.reload();
		            },
		            "onRemove": function (json, data) {
		            	document.location.reload();
		            }
		        },
		        "fields": [ {
		                "label": "ID:",
		                "name": "id",
		                "type": "hidden",
		                "dataProp": 0
		            }, {
		                "label": "Trans Name:",
		                "name": "name",
		                "dataProp": 1
		            }, {
		                "label": "Category:",
		                "name": "category",
		                "type": "select",
		                "ipOpts": [{/literal}{$allCategories}{literal}],
			            "default": "",
	                	"dataProp": 2	                
		            }, {
		                "label": "Trans. Date:",
		                "name": "transdate",
		                "type": "date",
		                "dateFormat": "M d, yy",
		                "dataProp": 3
		            }, {
		                "label": "Amount:",
		                "name": "amount",
		                "dataProp": 4
		            }
		        ]
		    } );
		    
		    $('#dataTables').dataTable( {
	    		"bJQueryUI": true,
	    		"sPaginationType": "full_numbers",
	    		"sDom": '<"H"Tlfr>t<"F"ip>',
	            "aLengthMenu": [[10, 25, 50, 100, -1], [10, 25, 50, 100, "All"]],
	            "iDisplayLength": 25,	 
		        "oTableTools": {
		            "sRowSelect": "single",
		            "sSwfPath": "http://datatables.net/release-datatables/extras/TableTools/media/swf/copy_csv_xls_pdf.swf",
		            "aButtons": [
		                { "sExtends": "editor_create", "editor": editor },
		                { "sExtends": "editor_edit",   "editor": editor },
		                { "sExtends": "editor_remove", "editor": editor },
		                "copy", "csv", "xls", "pdf"
		            ]
		        }
		    } );
		} );
		</script>

{/literal}

            {else}<p>{$user->getFirstName()} has no activities.</p>{/if}
		</div><!-- end main content left  -->
    </div> <!-- end main content  -->
	<div class="clear">&nbsp;</div>       
          
</div>
<div class="push"></div>

{include file='footer.tpl'}
