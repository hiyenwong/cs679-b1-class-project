{include file='header.tpl'}
<div id="header_wrap{if !$homepage}_secondary{/if}">
	<div id="header{if $secondary}_secondary{/if}"><!-- begin header -->
		
		{include file='upperheader.tpl' user=$user}
	  
	  	<div id="header_lower">	   
		 	<div id="header_sub_secondary"> 
		    	<div id="header_sub_text_secondary">
		    		<p>Log In</p>           
		  		</div>
		   	</div>
		    <div id="header_sub_secondary_right">
		      Log in and start managing your budget
		    </div>                            
		</div><!-- end header lower-->
	</div><!-- end header -->
</div>

<div id="page{if !$homepage}_secondary{/if}"><!-- start page content -->
          
	<div id="main_content">
		<div id="main_content_left_secondary">
       		<fieldset>
	       		<legend>Log In to iBudget</legend>
	        	<form action="login.php" method="POST">
                    <input type="hidden" name="submitted" value="true" />
	        		<p><label for="username">Username: </label><input type="text" name="username" id="username"></p>
	        		<p><label for="password">Password: </label><input type="password" name="password" id="password"></p>
	        		{if isset($errorMessage)}<p><span class="error">{$errorMessage}</span></p>{/if}
	        		<a href="forgot_password.php" style="margin-left:180px">Forgot your password?</a>
	        		<p><input type="submit" name="submit" value="Log In"></p>
	        	</form>
        	</fieldset>
        	
        	<p class="center">Don't have an account yet? Create one <a href="register.php">here</a></p>
                    
		</div><!-- end main content left  -->
      		<!-- end main content right  -->
    </div> <!-- end main content  -->
	<div style="clear: both;">&nbsp;</div>       
          
</div>
<div class="push"></div>

{include file='footer.tpl'}
