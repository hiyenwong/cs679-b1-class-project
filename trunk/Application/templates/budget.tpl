{include file='header.tpl'}

<script type="text/javascript" src="{$js_url}/budget.js"></script>
<link type="text/css" href="{$style_url}/redmond/jquery-ui-1.8.19.custom.css" rel="Stylesheet" />
<script type="text/javascript" src="{$js_url}/jquery-ui-1.8.19.custom.min.js"></script>

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
            <div id="budgetTable">
                {include file='budget_table.tpl'}
          	</div>
          	
          	<div id="addBudgetRow">
                <form>
                    <input type="hidden" value="add" name="action" />
                    <div id="register_user_password" class="register_toggle">
                        <p>
                            <label for="addCategory">Category: </label>
                            <select id="addCategory" name="categoryId">
                                {foreach from=$allCategories key=k item=v}
                                    <option value="{$k}">{$v}</option>
                                {/foreach}
                                {foreach from=$userCategories key=k item=v}
                                    <option value="{$k}">{$v}</option>
                                {/foreach}
                            </select>
                        </p>
                        <p>
                            <label for="addBudgeted">Amount: </label>
                            <input type="text" id="addBudgeted" name="budgetedAmount" />
                            <div id="addBudgetError" class="error"></div>
                        </p>
                        <p>
                            <input type="button" value="Save" id="saveBudgetItem" />
                            <input type="button" value="Cancel" id="cancelBudgetItem" />
                        </p>
                    </div>
                </form>
            </div>
            
          	<input type="button" value="Add Budget Item" id="addBudget" />
                    
		</div><!-- end main content left  -->
    </div> <!-- end main content  -->
	<div class="clear">&nbsp;</div>       
          
</div>
<div class="push"></div>

{include file='footer.tpl'}
