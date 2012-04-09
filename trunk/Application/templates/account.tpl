{include file='header.tpl'}
<div id="header_wrap{if !$homepage}_secondary{/if}">
	<div id="header{if $secondary}_secondary{/if}"><!-- begin header -->
		{include file='upperheader.tpl' user=$user}
	  
	  	{include file='lowerheader.tpl' title='Account Info' message='Modify your account'}
	</div><!-- end header -->
</div>
		
<div id="page{if !$homepage}_secondary{/if}"><!-- start page content -->
          
	<div id="main_content">
		{include file="leftnav.tpl" active='Accounts'}

		<div id="main_content_left_secondary" class="account"> 
          	
          	<form action="account.php" method="POST">
          		<p class="error">{if $e_message}{$err_message}{/if}</p>
	          	<p><label for="firstName">First Name: </label><input type="text" name="firstName" id="firstName" value="{$user->getFirstName()}"></p>
	          	<p><label for="lastName">Last Name: </label><input type="text" name="lastName" id="lastName" value="{$user->getLastName()}"></p>
        		<p><input type="submit" value="Update Name" name="update_name"></p>
        	</form>
        	<form action="account.php" method="POST">
          		<p class="error">{if $err_message}{$err_message}{/if}</p>
        		<p><label for="new_password">Password: </label><input type="password" name="new_password" id="new_password"></p>
        		<p><label for="verify_new_password">Repeat Password: </label><input type="password" name="verify_new_password" id="verify_new_password"></p>
        		<p><input type="submit" value="Submit" name="update_password"></p>
        	</form>   
	        <p>Date registered: {$user->getCreatedDate()|date_format:"%A, %B %e, %Y at %I:%M:%S %p"}</p>
		</div><!-- end main content left  -->
      		<!-- end main content right  -->
    </div> <!-- end main content  -->
	<div style="clear: both;">&nbsp;</div>       
          
</div>
<div class="push"></div>

{include file='footer.tpl'}
