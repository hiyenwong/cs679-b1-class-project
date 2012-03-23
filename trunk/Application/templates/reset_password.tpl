{include file='header.tpl'}
<div id="header_wrap{if !$homepage}_secondary{/if}">
	<div id="header{if $secondary}_secondary{/if}"><!-- begin header -->
		<div id="header_upper">
			<div id="header_logo"></div>
				     
	     	<div id="navs"><!-- begin navigations -->
	       		<div id="navs_left"></div>
	       		<div id="navs_center">
	         		<ul>
	             		<li><a href="index.php">Home</a></li>
	        	    	<li><a href="about.php">About</a></li>
	               	  	<li><a href="contact.php">Contact</a></li>     
	               	  	<li><a href="login.php">Log In</a></li>     
	                	<li><a href="register.php">Register</a></li>     
	       			</ul>
	       		</div>
	   			<div id="navs_right"> </div>
	  		</div><!-- end navigations -->
	 	</div><!-- end header upper -->
	  
	  	<div id="header_lower">	   
		 	<div id="header_sub_secondary"> 
		    	<div id="header_sub_text_secondary">
		    		<p>Reset password</p>           
		  		</div>
		   	</div>
		    <div id="header_sub_secondary_right">
		      Reset it here
		    </div>                            
		</div><!-- end header lower-->
	</div><!-- end header -->
</div>

<div id="page{if !$homepage}_secondary{/if}"><!-- start page content -->
          
	<div id="main_content">
		<div id="main_content_left_secondary">
       		<fieldset id="forgot_password">
	       		<legend>Reset password</legend>
	        	<form action="{$form_action}" method="POST">
	        		<p class="error">&nbsp;{if $err_message}{$err_message}{/if}</p>
	        		<input type="hidden" name="username" value="{$username}">
					<input type="hidden" name="pid" value="{$pid}">
					<p><label for="new_password">Password:</label><input type="password" name="new_password" id="new_password" ></p>
					<p><label for="verify_new_password">Repeat Password:</label><input type="password" name="verify_new_password" id="verify_new_password"></p>
	        		<p><input type="submit" name="submit" value="Submit"></p>
	        	</form>
        	</fieldset>
                    
		</div><!-- end main content left  -->
      		<!-- end main content right  -->
    </div> <!-- end main content  -->
	<div style="clear: both;">&nbsp;</div>       
          
</div>
<div class="push"></div>

<script type="text/javascript">
$(document).ready(function(){
	$("input[type=submit]").click(function(e){
		if ($("#email").val() == ''){
			$("p.error").html('Please enter your email');
			e.preventDefault();
			$("#email").focus();
		}
	})
});

</script>

{include file='footer.tpl'}