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
		    		<p>Contact us</p>           
		  		</div>
		   	</div>
		    <div id="header_sub_secondary_right">
		      We would like to hear from you!
		    </div>                            
		</div><!-- end header lower-->
	</div><!-- end header -->
</div>

{literal}
<script type="text/javascript">
$(document).ready(function(){
	$("input[type=submit]").click(function(e){
		if ($("#name").val() == ''){
			$("p.error").html('Please enter your name.');
			e.preventDefault();
			$("#name").focus();
		} else if ($("#email").val() == ''){
			$("p.error").html('Please enter an email address.');
			e.preventDefault();
			$("#email").focus();
		} else if (!(/^[_a-z0-9]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,3})$/i.test($("#email").val()))) {
			$("p.error").html('Please enter a valid email address.');
			e.preventDefault();
			$("#email").focus();
		} else if ($("#message").val() == ''){
			$("p.error").html('Please enter your message.');
			e.preventDefault();
			$("#message").focus();
		}
	})
});
</script>
{/literal}

<div id="page{if !$homepage}_secondary{/if}"><!-- start page content -->
    
	<div id="main_content">
		<div id="main_content_left_secondary">
       		<fieldset id="contact">
       			<div id="status">{if $message}{$message}{/if}</div>
	       		<legend>Please fill out the below form:</legend>
                <form id='contactus' method="post" action="contact.php">
                	<p class="error">&nbsp;{if $err_message}{$err_message}{/if}</p>
                    <p><label for="name">Name: </label><input type="text" name="name" id="name"></p>
	        		<p><label for="email">Email: </label><input type="text" name="email" id="email"></p>
	        		<p><label for="message">Message: </label><textarea name = "message" id="message"></textarea></p>
	        		<p><input type="submit" name="submit" value="SEND"></p>
                </form>
        	</fieldset>
		</div><!-- end main content left  -->
    </div> <!-- end main content  -->
	<div style="clear: both;">&nbsp;</div>                
</div>

{include file='footer.tpl'}
