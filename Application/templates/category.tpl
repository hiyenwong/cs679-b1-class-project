{include file='header.tpl'}

<script type="text/javascript" src="{$js_url}/category.js"></script>
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
		{include file="leftnav.tpl" active='Category'}

		<div id="main_content_left_secondary">
            <div id="categoryList">
                {include file='category_list.tpl'}
          	</div>
          	
          	<div id="addCategoryDialog">
                <form>
                    <input type="hidden" value="add" name="action" />
                    <p>
                        <label for="categoryName">Name: </label>
                        <input type="text" id="categoryName" name="categoryName" />
                        <div id="addCategoryError" class="error"></div>
                    </p>
                    <p>
                        <input type="button" value="Save" id="saveCategoryItem" />
                        <input type="button" value="Cancel" id="cancelCategoryItem" />
                    </p>
                </form>
            </div>
            
          	<input type="button" value="Add New Category" id="addCategory" />
                    
		</div><!-- end main content left  -->
    </div> <!-- end main content  -->
	<div class="clear">&nbsp;</div>       
          
</div>
<div class="push"></div>

{include file='footer.tpl'}
