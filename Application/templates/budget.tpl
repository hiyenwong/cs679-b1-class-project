{include file='header.tpl'}

<script type="text/javascript" src="{$js_url}/budget.js"></script>

<div id="header_wrap{if !$homepage}_secondary{/if}">
	<div id="header{if $secondary}_secondary{/if}"><!-- begin header -->
		{include file='upperheader.tpl' user=$user}
	  
	  	{include file='lowerheader.tpl' title='Budgets' message='Modify your budgets'}
	</div><!-- end header -->
</div>
		
<div id="page{if !$homepage}_secondary{/if}" id="budget"><!-- start page content -->
          
	<div id="main_content">
		{include file="leftnav.tpl" active='Budget'}

		<div id="main_content_left_secondary">   
          	<table>
                <thead>
                    <tr>
                        <th>Budget</th>
                        <th>Spent</th>
                        <th>&nbsp;</th>
                    </tr>
                </thead>
                <tbody id="budgetRows">                   
                    {foreach from=$allCategories key=k item=v}
                    <tr>
                        <td>{$v}</td>
                        <td>0</td>
                        <td><input type="button" value="Remove" /></td>
                    </tr>
                    {/foreach}                    
                    <tr id="addBudgetRow">
                        <td>
                            <select id="addCategory">
                            {foreach from=$allCategories key=k item=v}
                               <option value="{$k}">{$v}</option>
                            {/foreach}
                            {foreach from=$userCategories key=k item=v}
                               <option value="{$k}">{$v}</option>
                            {/foreach}
                            </select>
                        </td>
                        <td><input type="text" id="addBudgeted" /></td>
                        <td><input type="button" value="Save" id="saveBudgetItem" /></td>
                    </tr>
                </tbody>
          	</table>
          	<input type="button" value="Add Budget Item" id="addBudget" />
          	
          	<div id="error"></div>
                    
		</div><!-- end main content left  -->
      		<!-- end main content right  -->
    </div> <!-- end main content  -->
	<div style="clear: both;">&nbsp;</div>       
          
</div>
<div class="push"></div>

{include file='footer.tpl'}
